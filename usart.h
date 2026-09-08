#include <avr/io.h> 
#include "stdio.h"
#define BAUD 9600
#define FOSC 4915200 //klokke frekvens
#define MYUBRR FOSC/16/BAUD-1 //skamløst kopiert fra datablad


int usart_transmit(char data);

void usart_init(unsigned int ubrr);

int usart_receive();

int usart_putchar(char data, FILE *stream);

int usart_getchar(FILE *stream);

