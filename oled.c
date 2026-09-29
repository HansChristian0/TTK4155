#include "oled.h"


void oled_command(uint8_t command, uint8_t* args, uint8_t arg_len){
  PORTB &= ~(1<<DISP_DC); // setter D/C# lav for command
  SPI_master_transmit(command, SELECT_DISP);
  if (arg_len > 0){
    SPI_transfer_n_bytes(args,arg_len,SELECT_DISP);
  }
}

void oled_data(uint8_t *data, uint8_t length){
  PORTB |= (1<<DISP_DC); // setter D/C# høy for data
  SPI_transfer_n_bytes(data,length,SELECT_DISP);
}

void oled_init(){ // må initialiseres etter SPI init duh
  PORTB &= ~(1<<DISP_RESET); // Sette reset lav for å starte initalisering
  _delay_us(4);
  PORTB |= (1<<DISP_RESET); // Setter reset høy gjen etter å ha ventet bittelitt 
  oled_command(OLED_DISP_ON,0,0); //skru på display etter reset
  oled_command(OLED_ENTIRE_DISP_ON,0,0);
}
