#include <avr/io.h> 
#include "stdio.h"
#include "stdint.h"
//#include "fonts.h"
#include "spi.h"


// D/C# = 0
#define OLED_SET_CONTRAST 0x81 // + 1 BYTE SOM SETTER KONTRAST 0 TIL 255
#define OLED_DISP_ON 0xAF
#define OLED_DISP_OFF 0xAE
#define OLED_NO_DISP_INVERT 0xA6
#define OLED_INVERT_DISP 0xA7
#define OLED_ENTIRE_DISP_ON 0xA5
#define OLED_ENTIRE_DISP_OFF 0xA4
// SCROLL SETUP TROR JEG
#define OLED_RIGHT_HORIZONTAL_SCROLL 0x26

//ARESSE SETTING COMMAND TABLE foreslår page adressing
#define OLED_SET_MEMORY_ADDRESSING_MODE 0x20 // + 1 ; lsb; OO = HORIZONTAL; 01 = VERTICAL ; 10= PAGE

void oled_init();

void oled_command(uint8_t command, uint8_t* args, uint8_t arg_len);

void oled_data(uint8_t *data, uint8_t length);

void oled_select_col(uint8_t column, uint8_t page);

void oled_clear();






