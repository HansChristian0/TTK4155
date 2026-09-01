#include "usart.h"

void usart_transmit(unsigned char data){
    
    while(!(UCSR0A & (1<<UDRE0))){
    }
    UDR0 = data;

}

void usart_init(unsigned int ubrr){
    UBRR0H = (unsigned char)(ubrr >> 8); //baudrate err?
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0); //usart controll and status reg B
    UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00); //URSEL velger å skrive til UCSRC USBS setter stop antall bit til 2 UCSZ0 setter char size til 8 bit
}

unsigned char usart_receive(){
    usart_init(MYUBRR);

    while(!(UCSR0A & (1<<RXC0))){

    }
    return UDR0;
}