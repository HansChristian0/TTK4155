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
    //initialisering//
    
    SRAM_test();
    CLK_signal();
    printf("start for faen");
    while(1){
        volatile uint8_t a = adc_read(0);
        printf("%d \n\r",a);
        volatile uint8_t b = adc_read(2);
        printf("%d \n\r",b);
        volatile uint8_t c = adc_read(1);
        printf("%d \n\r",c);
        volatile uint8_t d = adc_read(3);
        printf("%d \n\r",d);
    }
}