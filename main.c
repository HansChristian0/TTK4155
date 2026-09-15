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
    //initialisering//
    
    SRAM_test();
    CLK_signal();

    while(1){
        volatile uint8_t* ADC = (uint8_t * ) 0x1000;
        uint8_t value = *ADC;
        printf("%d \n \r",value);
    }
}