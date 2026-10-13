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
    // uint8_t* calibration = pos_calibrate();
    // printf("%d %d %d %d", calibration[0], calibration[1], calibration[2], calibration[3]);
    printf("\n \nstart for faen\r\n");
    char *menu_list[7] = {"Nytt spill", "Dagens vits", "hei", "paa", "deg", "Nei", "jo"};
    oled_creat_menu(menu_list, 7); 
    DDRB &= ~(1<<PB0);
    //can_set_loopback();
    can_ctrl_init();
    Dataframe msg;
    msg.id = 8;
    msg.data_len = 1;
    msg.data[0] = 'a';
    // msg.data[1] = 'b';
    // msg.data[2] = 'c';
    can_com_transmit(& msg,0x01);
    
    Dataframe new_msg;
    printf("id: %d lengde: %d data: %d \r\n",new_msg.id,new_msg.data_len,new_msg.data);


    can_com_receive(&new_msg);

    printf("id: %d lengde: %d data: %c \r\n",new_msg.id,new_msg.data_len,new_msg.data[0]);
    _delay_ms(1000);

    printf("register verdien : %c", can_ctrl_read(MCP_RXB0D0));

    while(1){}
    return 0;
    // oled_clear();
    
}





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

            // can_ctrl_write(0b10000100,0x30);
            // _delay_ms(1000);
            // Can_data = can_ctrl_read(0x30);
            // printf("%d\r \n",Can_data);
        