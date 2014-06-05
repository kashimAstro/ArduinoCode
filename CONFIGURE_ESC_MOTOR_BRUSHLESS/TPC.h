
#ifndef TPC_H
#define TPC_H

 
#define TPC_PIN_INPUT() DDRB &= ~_BV(2)
#define TPC_PIN_OUTPUT() DDRB |= _BV(2)
#define TPC_PIN_ON() PORTB |= _BV(2)
#define TPC_PIN_OFF() PORTB &= ~_BV(2)
#define TPC_PIN_IS_ON() bit_is_set(PINB, 2)
#define TPC_PIN_IS_OFF() bit_is_clear(PINB, 2)
#define TPC_delay_us(x) _delay_us(x)
#define TPC_READ_BIT_TIME_WIDTH 2437
#define TPC_READ_HALF_BIT_TIME_WIDTH (TPC_READ_BIT_TIME_WIDTH/2)
#define TPC_WRITE_BIT_TIME_WIDTH TPC_READ_BIT_TIME_WIDTH
#define TPC_WRITE_HALF_BIT_TIME_WIDTH (TPC_WRITE_BIT_TIME_WIDTH/2)
 
enum TPC_battType_t
{
    TPC_battType_Li = 0,
    TPC_battType_Ni = 1
};
 
enum TPC_cutoffType_t
{
    TPC_cutoffType_softCut = 0,
    TPC_cutoffType_cutoff = 1
};
 
enum TPC_cutoffVoltage_t
{
    TPC_cutoffVoltage_low = 0,
    TPC_cutoffVoltage_middle = 1,
    TPC_cutoffVoltage_high = 2
};
 
enum TPC_startMode_t
{
    TPC_startMode_normal = 0,
    TPC_startMode_soft = 1,
    TPC_startMode_verySoft = 2
};
 
enum TPC_timingMode_t
{
    TPC_timingMode_low = 0,
    TPC_timingMode_middle = 1,
    TPC_timingMode_high = 2
};
 
enum TPC_lipoCells_t
{
    TPC_lipoCells_autoDetect = 0,
    TPC_lipoCells_2 = 1,
    TPC_lipoCells_3 = 2,
    TPC_lipoCells_4 = 3,
    TPC_lipoCells_5 = 4,
    TPC_lipoCells_6 = 5,
    TPC_lipoCells_7 = 6,
    TPC_lipoCells_8 = 7,
    TPC_lipoCells_9 = 8,
    TPC_lipoCells_10 = 9,
    TPC_lipoCells_11 = 10,
    TPC_lipoCells_12 = 11
};
 
typedef struct TPC_settings_t_
{
    int8_t			brake;
    enum TPC_battType_t 	battType;
    enum TPC_cutoffType_t 	cutoffType;
    enum TPC_cutoffVoltage_t 	cutoffVoltage;
    enum TPC_startMode_t 	startMode;
    enum TPC_timingMode_t 	timingMode;
    enum TPC_lipoCells_t 	lipoCells;
    int8_t 			governorMode;
     
} TPC_settings_t;
 
// initializes the settings to default values
void TPC_loadDefault(TPC_settings_t* x);

// configs the settings struct with 2 bytes (which you should get from the ESC, but you can also store it in your own EEPROM or something)
void TPC_word_to_struct(TPC_settings_t* x, unsigned short y);

// translates the settings struct into 2 bytes (which you can send to the ESC, or store in your own EEPROM or something)
unsigned short TPC_struct_to_word(TPC_settings_t* x);

// reads a byte from a psuedo 10-bit UART
unsigned char TPC_ser_read();

// writes a byte to a psuedo 10-bit UART
void TPC_ser_write(unsigned char x);

// must be sent after receiving configuration from ESC upon initialization
void TPC_send_init_ack(void);

// receive the ack from ESC after writing config to ESC
void TPC_wait_for_ack(void);

// receive current config from ESC
void TPC_read_init(TPC_settings_t* x);

// sends configuration to ESC
void TPC_send_config(TPC_settings_t* x);

//static int ser_tx(char c, FILE* f);


#endif
