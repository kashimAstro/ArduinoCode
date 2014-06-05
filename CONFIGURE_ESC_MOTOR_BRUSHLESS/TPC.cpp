// Thanks to Frank

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "TPC.h"

// initializes the settings to default values
void TPC_loadDefault(TPC_settings_t* x)
{
    x->brake 					= 0;
    x->battType 			= TPC_battType_Li;
    x->cutoffType 		= TPC_cutoffType_softCut;
    x->cutoffVoltage 	= TPC_cutoffVoltage_middle;
    x->startMode 			= TPC_startMode_normal;
    x->timingMode 		= TPC_timingMode_low;
    x->lipoCells 			= TPC_lipoCells_autoDetect;
    x->governorMode 	= 0;
}
 
// configs the settings struct with 2 bytes (which you should get from the ESC, but you can also store it in your own EEPROM or something)
void TPC_word_to_struct(TPC_settings_t* x, unsigned short y)
{
    // map the bits to the settings
    x->brake           = (y & (1 << 0)) == 0 ? 0 : 1;
    x->battType        = (y & (1 << 1)) == 0 ? TPC_battType_Li : TPC_battType_Ni;
    x->cutoffType      = (y & (1 << 2)) == 0 ? TPC_cutoffType_softCut : TPC_cutoffType_cutoff;
    x->cutoffVoltage   = (TPC_cutoffVoltage_t) ((y & (0x03 << 3)) >> 3);
    x->startMode       = (TPC_startMode_t) ((y & (0x03 << 5)) >> 5);
    x->timingMode      = (TPC_timingMode_t) ((y & (0x03 << 8)) >> 8);
    x->lipoCells       = (TPC_lipoCells_t) ((y & (0x0F << 10)) >> 10);
    x->governorMode    = (y & (1 << 7)) == 0 ? 0 : 1;
}
 
// translates the settings struct into 2 bytes (which you can send to the ESC, or store in your own EEPROM or something)
unsigned short TPC_struct_to_word(TPC_settings_t* x)
{
    return 0 |
           ((x->brake ? 1 : 0) << 0) |
           ((x->battType ? 1 : 0) << 1) |
           ((x->cutoffType ? 1 : 0) << 2) |
           ((x->cutoffVoltage & 0x03) << 3) |
           ((x->startMode & 0x03) << 5) |
           ((x->timingMode & 0x03) << 8) |
           ((x->lipoCells & 0x0F) << 10) |
           ((x->governorMode ? 1 : 0) << 7);
}
 
// reads a byte from a psuedo 10-bit UART
unsigned char TPC_ser_read()
{
    unsigned char i, x = 0;
     
    TPC_PIN_ON(); // input
    TPC_PIN_INPUT();

    while (TPC_PIN_IS_OFF()); // wait for powerup if not already
    while (TPC_PIN_IS_ON()); 	// wait until start of frame
    while (TPC_PIN_IS_OFF()); // this period indicates start of frame
    while (TPC_PIN_IS_ON()); 	// the first bit always seems to be 1
   
    TPC_delay_us(TPC_READ_BIT_TIME_WIDTH + TPC_READ_HALF_BIT_TIME_WIDTH); // skip
     
    // read the 8 bits LSB first
    for (i = 0; i < 8; i++)
    {
        x |= (TPC_PIN_IS_ON() ? 1 : 0) << i;
        TPC_delay_us(TPC_READ_BIT_TIME_WIDTH);
    }
     
    return x;
}
 
// writes a byte to a psuedo 10-bit UART
void TPC_ser_write(unsigned char x)
{  
    TPC_PIN_ON(); // make sure
    TPC_PIN_OUTPUT();
    TPC_delay_us(TPC_WRITE_BIT_TIME_WIDTH);
     
    TPC_PIN_OFF(); // signal start
    TPC_delay_us(TPC_WRITE_BIT_TIME_WIDTH);
     
    TPC_PIN_ON(); // first bit always 1
    TPC_delay_us(TPC_WRITE_BIT_TIME_WIDTH);
     
    TPC_PIN_OFF(); // 2nd bit always 0
    TPC_delay_us(TPC_WRITE_BIT_TIME_WIDTH);
     
    // send the byte LSB first
    char i;
    for (i = 0; i < 8; i++)
    {
        if ((x & (1 << i)) == 0)
        {
            TPC_PIN_OFF();
        }
        else
        {
            TPC_PIN_ON();
        }
        TPC_delay_us(TPC_WRITE_BIT_TIME_WIDTH);
    }
    TPC_PIN_ON(); // leave as input
    TPC_PIN_INPUT();
}
 
// must be sent after receiving configuration from ESC upon initialization
void TPC_send_init_ack(void)
{
    TPC_PIN_ON();
    TPC_PIN_OUTPUT();
    TPC_delay_us(TPC_WRITE_BIT_TIME_WIDTH);
     
    // send pulses
    char i;
    for (i = 0; i < 6; i++)
    {
        TPC_PIN_OFF();
        TPC_delay_us(TPC_WRITE_BIT_TIME_WIDTH);
        TPC_PIN_ON();
        TPC_delay_us(TPC_WRITE_BIT_TIME_WIDTH);
    }
     
    TPC_PIN_INPUT(); // leave clean
}
 
// receive the ack from ESC after writing config to ESC
void TPC_wait_for_ack()
{
    TPC_ser_read();
}
 
// receive current config from ESC
void TPC_read_init(TPC_settings_t* x)
{
    // read in 2 bytes
    unsigned short y;
    y = TPC_ser_read();
    y |= TPC_ser_read() << 8;
     
    TPC_word_to_struct(x, y);
     
    TPC_delay_us(TPC_READ_BIT_TIME_WIDTH); // a small delay
    TPC_delay_us(TPC_READ_BIT_TIME_WIDTH); // a small delay
    TPC_delay_us(TPC_READ_BIT_TIME_WIDTH); // a small delay
    TPC_delay_us(TPC_READ_BIT_TIME_WIDTH); // a small delay
   
    TPC_send_init_ack(); // must be sent after receiving configuration from ESC upon initialization
}
 
// sends configuration to ESC
void TPC_send_config(TPC_settings_t* x)
{
    unsigned short y = TPC_struct_to_word(x);
     
    // start writing the config, LSB first
    TPC_ser_write(y & 0xFF);
    TPC_ser_write((y >> 8) & 0xFF);
    // just a small note, these two bytes match the received config during initialization
     
    // the settings are sent in this format
    TPC_ser_write((y & (0x01 << 0)) >> 0);
    TPC_ser_write((y & (0x01 << 1)) >> 1);
    TPC_ser_write((y & (0x01 << 2)) >> 2);
    TPC_ser_write((y & (0x03 << 3)) >> 3);
    TPC_ser_write((y & (0x03 << 5)) >> 5);
    TPC_ser_write((y & (0x03 << 8)) >> 8);
    TPC_ser_write((y & (0x01 << 7)) >> 7);
     
    // this is where the string of notes would be, but I don't have that implemented, so these two are just null
    TPC_ser_write(0);
    TPC_ser_write(0);
     
    TPC_ser_write(11); // this is actually a byte count
     
    TPC_wait_for_ack(); // do not unpower ESCs until the ack has been received, since it's writing to EEPROM during this time
}
/*
static int ser_tx(char c, FILE* f)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}
 
static FILE mystdout = FDEV_SETUP_STREAM(ser_tx, NULL, _FDEV_SETUP_WRITE);
*/
/*
int main()
{
    // setup for 57600 baud
    UBRR0H = 0;
    UBRR0L = 12;
     
    UCSR0B = _BV(TXEN0) | _BV(RXEN0); // start serial port
    stdout = &mystdout; // setup stream
     
    DDRD |= _BV(4); // LED pin output
     
    TPC_PIN_ON();
    TPC_PIN_INPUT();
     
    printf("\r\nTesting Begin\r\n");
    // at this point, plug the ESC in to the battery
     
    static volatile TPC_settings_t mySettings;
     
    PORTD |= _BV(4); // LED on
    TPC_read_init(&mySettings);
    PORTD &= ~_BV(4); // LED off
     
    unsigned short x = TPC_struct_to_word(&mySettings);
    printf("Read from ESC: 0x%x\r\n", x);
     
    // here we change all the settings
    mySettings.brake = mySettings.brake ? 0 : 1;
    mySettings.battType = mySettings.battType ? 0 : 1;
    mySettings.cutoffType = mySettings.cutoffType ? 0 : 1;
    mySettings.cutoffVoltage = (mySettings.cutoffVoltage + 1) % 3;
    mySettings.startMode = (mySettings.startMode + 1) % 3;
    mySettings.timingMode = (mySettings.timingMode + 1) % 3;
    mySettings.lipoCells = (mySettings.lipoCells + 1) % (TPC_lipoCells_12 + 1);
    mySettings.governorMode = mySettings.governorMode ? 0 : 1; 
    x = TPC_struct_to_word(&mySettings);
    printf("Sending to ESC: 0x%x\r\n", x);
    // and send it back
     
    _delay_ms(1000);
     
    PORTD |= _BV(4); // LED on
    TPC_send_config(&mySettings);
    PORTD &= ~_BV(4); // LED off
     
    printf("Test Complete\r\n");
     
    // now the ESC must be unpowered
    // then reset the system
    // to confirm settings
     
    while (1);
    return 0;
}
*/
