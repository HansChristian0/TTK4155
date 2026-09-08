#include <avr/io.h> 
#include "stdio.h"
#define BASE_ADDRESS 0x1800

void xmem_init();

void xmem_write(uint8_t data, uint16_t address);

uint8_t xmem_read(uint16_t address);