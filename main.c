#include <avr/io.h> //ser ut til å gå bra med rød strek
#include "usart.h"
#include "SRAM.h"
#include "teste_SRAM.h"
#include "util/delay.h"
#include "spi.h"
#include "oled.h"
#include "buttons.h"
#include "can_ctrl.h"
#include "can_com.h"
#include "joy_to_can.h"

int main(void){
    //initalisering//
    usart_init(MYUBRR);
    fdevopen(usart_putchar,usart_getchar);
    xmem_init();
    adc_init();
    CLK_signal();
    SPI_master_init();
    oled_init();
    oled_clear();
    //initialisering//
    uint8_t* calibration = hard_cal();
    printf("%d %d %d %d", calibration[0], calibration[1], calibration[2], calibration[3]);
    printf("\n \nstart for faen\r\n");
    char *menu_list[7] = {"Nytt spill", "Dagens vits", "hei", "paa", "deg", "Nei", "jo"};

    uint8_t curr_pos_x = 0;
    uint8_t curr_pos_y = 0;
    uint8_t curr_pos_x_pad = 0;
    uint8_t curr_pos_y_pad = 0;
    int8_t percent_pos_x = 0;
    int8_t percent_pos_y = 0;
    pos_t direction = NEUTRAL;


    SPI_master_init();
    oled_init();
    oled_clear();
    oled_creat_menu(menu_list, 7); 
    DDRB &= ~(1<<PB0);

    //can_set_loopback();
    can_ctrl_init();
    Dataframe msg = {0};
    msg.id = 8;
    msg.data_len = 1;
    msg.data[0] = 'a';

    Dataframe newMsg = {0};

    can_com_receive(&newMsg);
    printf("%c",newMsg.data[0]);
  
    can_com_transmit(&msg,0x01);
    msg.data[0]='b';
    can_com_transmit(&msg,0x01);
 
    //_delay_ms(1000);
    // can_com_transmit(& msg,0x01);


    msg.data[0] = 'q';
    msg.data[1] = 'r';
    msg.data[2] = 'Q';
    msg.data[3] = 'f';
    msg.data[4] = 'h';
    msg.data[5] = 'd';
    msg.data[6] = 'a';
    msg.data[7] = 'p';
    msg.data_len = 8;
    msg.id = 18;
    can_com_transmit(&msg,0x01);

    msg.data[0] = 'q';
    msg.data[1] = 'r';
    msg.data[2] = 'Q';
    msg.data[3] = 'f';
    msg.data[4] = 'h';
    msg.data[5] = 'd';
    msg.data[6] = 'a';
    msg.data[7] = 'p';
    msg.data_len = 8;
    msg.id = 109;
    can_com_transmit(&msg,0x01);

    msg.data[0] = 'q';
    msg.data[1] = 'r';
    msg.data[2] = 'Q';
    msg.data[3] = 'f';
    msg.data[4] = 'h';
    msg.data[5] = 'd';
    msg.data[6] = 'a';
    msg.data[7] = 'p';
    msg.data_len = 8;
    msg.id = 16;
    can_com_transmit(&msg,0x01);

    msg.data[0] = 'q';
    msg.data[1] = 'r';
    msg.data[2] = 'Q';
    msg.data[3] = 'f';
    msg.data[4] = 'h';
    msg.data[5] = 'd';
    msg.data[6] = 'a';
    msg.data[7] = 'p';
    msg.data_len = 8;
    msg.id = 11;
    can_com_transmit(&msg,0x01);



  
    while(1){


        curr_pos_x = adc_read(1);
        curr_pos_y = adc_read(0);
        percent_pos_x = pos_read_percent_x(calibration, curr_pos_x);
        percent_pos_y = pos_read_percent_y(calibration, curr_pos_y);
        direction = pos_read(percent_pos_x, percent_pos_y);

        joystick_to_can();
        oled_menu_select(menu_list, 7, direction);
        if(!(PINB & (1 << PB0))){
            printf("%s \r\n", menu_list[g_curr_page]);
        }
        Buttons btn = read_buttons();
        if(btn.L5){
            printf("L5");
        }
        if(btn.R6){
            printf("R6");
        }


    }
    return 0;
    // oled_clear();
    
}




// 
