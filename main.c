#include <avr/io.h> //ser ut til å gå bra med rød strek
#include "usart.h"
#include "SRAM.h"
#include "teste_SRAM.h"
#include "adc.h"


int main(void){
    //initalisering//
    usart_init(MYUBRR);
    fdevopen(usart_putchar,usart_getchar);
    xmem_init();
    adc_init();
    CLK_signal();
    //initialisering//
    uint8_t* calibration = pos_calibrate();
    printf("%d %d %d %d", calibration[0], calibration[1], calibration[2], calibration[3]);
    uint8_t curr_pos_x = 0;
    uint8_t curr_pos_y = 0;
    int8_t percent_pos_x = 0;
    int8_t percent_pos_y = 0;
    SRAM_test();
    printf("start for faen");
    while(1){
        curr_pos_x = adc_read(1);
        curr_pos_y = adc_read(0);
        percent_pos_x = pos_read_percent_x(calibration, curr_pos_x);
        printf("%d prosent X pos \r\n",percent_pos_x);
        percent_pos_y = pos_read_percent_y(calibration, curr_pos_y);
        printf("%d prosent Y pos \r\n",percent_pos_y);
    }
}