#include <avr/io.h> //ser ut til å gå bra med rød strek
#include "usart.h"




int main(void){
    usart_init(MYUBRR);
    unsigned char data = 'a';
    while (1)
    {
        usart_transmit(data);
        //data = usart_receive();
        //usart_transmit(data);
    }
    
}