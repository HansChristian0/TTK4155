#include "SRAM.h"

void xmem_init(){
    MCUCR |= (1 << SRE);
    SFIOR |= (1 << XMM2);
}

void xmem_write(uint8_t data, uint16_t address){
    volatile char * ext_mem = (char * ) BASE_ADDRESS; //BASE_ADDRESS er til sram modulen ikke ADC tenker vi gjør det i en annen fil
    ext_mem [address] = data;
}

uint8_t xmem_read(uint16_t address){
    volatile char * ext_mem = (char * ) BASE_ADDRESS;
    uint8_t ret_val = ext_mem[address];
    return ret_val;
}
