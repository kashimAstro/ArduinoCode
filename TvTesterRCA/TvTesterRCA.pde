#include <TVout.h>

TVout TV;

int WIDTH = 128;
int HEIGHT = 56;
int x = 10;
int y = PI*x;

void setup()  {
  //1k sram(m168) use TV.begin(_PAL,128,56)
  //TV.start_render(_PAL);
  TV.begin(_PAL,WIDTH,HEIGHT);
}

void loop() {
  TV.delay_frame(160);
  TV.clear_screen();
  TV.print_str(0,0,"TEster print text =P");
}
