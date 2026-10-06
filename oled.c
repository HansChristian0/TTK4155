#include "oled.h"
#include "string.h"
#include <ctype.h>

uint8_t g_curr_page = 0;

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
  uint8_t contrast = 255;
  PORTB &= ~(1<<DISP_RESET); // Sette reset lav for å starte initalisering
  _delay_us(4);
  PORTB |= (1<<DISP_RESET); // Setter reset høy gjen etter å ha ventet bittelitt 
  _delay_us(4);
  oled_command(OLED_SET_CONTRAST,&contrast,1);
  oled_command(OLED_SEGMENT_REMAP,0,0);
  oled_command(OLED_PAGE_REMAP,0,0);
  oled_command(OLED_DISP_ON,0,0); //skru på display etter reset
}

void oled_select_col(uint8_t column, uint8_t page){
  uint8_t col_low = column & 0x0F; // sette nedre nibble
  uint8_t col_high = (column >> 4) & 0x0F; //setter øvre nibble

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

void read_font(char c,uint8_t *out){
  uint8_t index = c - ' '; //trekke fra mellomrom siden vi begynner på mellomrom
  for (uint8_t i = 0; i < FONTSIZE; i++){
    out[i] = pgm_read_byte(&(font5[index][i]));
  }
}

int oled_print_char(char c){ // printer på 
  uint8_t q[FONTSIZE];
  read_font(c, q);
  oled_data(q,FONTSIZE);
  return 0;
}

void printff(char *str, uint8_t length, uint8_t page, uint8_t col){
  oled_select_col(col,page);
  for(int i = 0; i < length; i++){
    oled_print_char(str[i]);
  }
}

void oled_creat_menu(char *menu_list[], uint8_t len){
  for (int i=0; i<len; i++) {
    printff(menu_list[i], strlen(menu_list[i]), i, 2);
  }
}

void to_lower_except_first(char *str)
{
    for (int i = 1; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void to_upper_except_first(char *str)
{
    for (int i = 1; str[i] != '\0'; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

void oled_menu_select(char *menu_list[], uint8_t length, pos_t direction) {
  switch (direction)
  {
  case UP:
    if (g_curr_page-1 >= 0) {
      to_lower_except_first(menu_list[g_curr_page]);
      printff(menu_list[g_curr_page], strlen(menu_list[g_curr_page]), g_curr_page,2);
      g_curr_page -= 1;
      to_upper_except_first(menu_list[g_curr_page]);
      printff(menu_list[g_curr_page], strlen(menu_list[g_curr_page]), g_curr_page,2);
      _delay_ms(1000);
    }

    break;
  case DOWN:
    if (g_curr_page+1 <= length-1) {
      to_lower_except_first(menu_list[g_curr_page]);
      printff(menu_list[g_curr_page], strlen(menu_list[g_curr_page]), g_curr_page,2);
      g_curr_page += 1;
      to_upper_except_first(menu_list[g_curr_page]);
      printff(menu_list[g_curr_page], strlen(menu_list[g_curr_page]), g_curr_page,2);
      _delay_ms(1000);
    }

  default:
    break;
  }
}