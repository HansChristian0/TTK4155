#include <avr/io.h> 
#define BAUD 9600
#define FOSC 4915200 //klokke frekvens
#define MYUBRR FOSC/16/BAUD-1 //skamløst kopiert fra datablad


void usart_transmit(unsigned char data);

void usart_init(unsigned int ubrr);

unsigned char usart_receive();