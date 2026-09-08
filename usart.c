#include "usart.h"

int usart_transmit(char data){
    
    while(!(UCSR0A & (1<<UDRE0))){
    }
    UDR0 = data;
    return 1;
}

void usart_init(unsigned int ubrr){
    UBRR0H = (unsigned char)(ubrr >> 8); //baudrate err?
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0); //usart controll and status reg B
    UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00); //URSEL velger å skrive til UCSRC USBS setter stop antall bit til 2 UCSZ0 setter char size til 8 bit
}

int usart_receive(){

    while(!(UCSR0A & (1<<RXC0))){

    }
    return UDR0;
}

//wrapper for å bruke printf()

int usart_putchar(char data, FILE *stream)
{
    (void)stream;
    return usart_transmit(data);
}

int usart_getchar(FILE *stream)
{
    (void)stream;
    return usart_receive();
}