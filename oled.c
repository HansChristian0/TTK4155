#include "oled.h"



void oled_print_arrow(uint8_t row, uint8_t col) //eksempel kode fra lab forelesning
{
oled_pos (row, col);
oled_write_data(0b00011000);
oled_write_data(0b00011000);
oled_write_data(0b01111110);
oled_write_data(0b00111100);
oled_write_data(0b00011000);
}

void oled_write_data(uint8_t command) {
  volatile char *ext_oled_command = (char *) 0x1000;
  ext_oled_command[0] = command;
}