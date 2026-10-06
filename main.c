#include <avr/io.h> //ser ut til å gå bra med rød strek
#include "usart.h"
#include "SRAM.h"
#include "teste_SRAM.h"
#include "util/delay.h"
#include "spi.h"
#include "oled.h"
#include "buttons.h"
#include "can_ctrl.h"

int main(void){
    //initalisering//
    usart_init(MYUBRR);
    printf("lalalal");
    fdevopen(usart_putchar,usart_getchar);
    xmem_init();
    adc_init();
    CLK_signal();
    //initialisering//
    // uint8_t* calibration = pos_calibrate();
    // printf("%d %d %d %d", calibration[0], calibration[1], calibration[2], calibration[3]);
    uint8_t curr_pos_x = 0;
    uint8_t curr_pos_y = 0;
    uint8_t curr_pos_x_pad = 0;
    uint8_t curr_pos_y_pad = 0;
    int8_t percent_pos_x = 0;
    int8_t percent_pos_y = 0;
    pos_t direction = NEUTRAL;
    uint8_t Can_data = 0;
    SRAM_test();
    printf("start for faen");
    char *menu_list[7] = {"Nytt spill", "Dagens vits", "hei", "paa", "deg", "Nei", "jo"};
    SPI_master_init();
    oled_init();
    oled_clear();
    oled_creat_menu(menu_list, 7); 
    DDRB &= ~(1<<PB0);
    can_set_loopback();
    can_ctrl_init();
    while(1){
            // curr_pos_x = adc_read(1);
            // curr_pos_y = adc_read(0);
            // curr_pos_x_pad = adc_read(3);
            // curr_pos_y_pad = adc_read(2);
            // percent_pos_x = pos_read_percent_x(calibration, curr_pos_x);
            // percent_pos_y = pos_read_percent_y(calibration, curr_pos_y);
            // direction = pos_read(percent_pos_x, percent_pos_y);

            // oled_menu_select(menu_list, 7, direction);
            // if(!(PINB & (1 << PB0))){
            //     printf("%s \r\n", menu_list[g_curr_page]);
            // }
            // Buttons btn = read_buttons();
            // if(btn.L5){
            //     printf("L5");
            // }
            // if(btn.R6){
            //     printf("R6");
            // }
            can_ctrl_write(0b10001000,0b00110101);
            _delay_ms(1000);
            Can_data = can_read(0b00110101);
        }
  
    // _delay_ms(1000);
    // oled_clear();
    
}