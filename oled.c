#include "oled.h"


void oled_command(uint8_t command, uint8_t* args, uint8_t arg_len){
  PORTB &= ~(1<<DISP_DC); // setter D/C# lav for command
  SPI_master_transmit(command, SELECT_DISP);
  if (arg_len > 0){
    SPI_transfer_n_bytes(args,arg_len,SELECT_DISP);
  }
  _delay_us(40);
}

void oled_data(uint8_t *data, uint8_t length){
  PORTB |= (1<<DISP_DC); // setter D/C# høy for data
  SPI_transfer_n_bytes(data,length,SELECT_DISP);
}

void oled_init(){ // må initialiseres etter SPI init duh
  PORTB &= ~(1<<DISP_RESET); // Sette reset lav for å starte initalisering
  _delay_us(4);
  PORTB |= (1<<DISP_RESET); // Setter reset høy gjen etter å ha ventet bittelitt 
  _delay_us(4);
  oled_command(OLED_DISP_ON,0,0); //skru på display etter reset
}

void oled_select_col(uint8_t column, uint8_t page){
  uint8_t col_low = column & 0x0F; // sette nedre nibble
  uint8_t col_high = (column) & 0xF0; //setter øvre nibble

  oled_command(0xB0 | (page & 0x07),0,0); //velger page 
  oled_command(0x00| col_low, 0,0); //velger nedre nibble
  oled_command(0x10 | col_high,0,0); // velger øvre nibble  
}

void oled_clear(){
  uint8_t null[128] = {0};
  for (int i = 0; i < 8; i++){
    oled_select_col(0,i);
    oled_data(null,128);
  }
}