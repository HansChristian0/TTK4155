#include <avr/io.h> //ser ut til å gå bra med rød strek
#include "usart.h"
#include "SRAM.h"
#include "teste_SRAM.h"


int main(void){
    //initalisering//
    usart_init(MYUBRR);
    fdevopen(usart_putchar,usart_getchar);
    printf("nu kjor med");
    xmem_init();
    //initialisering//
    printf("nu kjor med");
    SRAM_test();
}