#include "SRAM.h"

void xmem_init(){
    MCUCR |= (1 << SRE); //aktivere eksternal memory
    SFIOR |= (1 << XMM2); //Mask port PC7-PC4 for 12 bits adresse
}

void xmem_write(uint8_t data, uint16_t address){
    volatile char * ext_mem = (char * ) BASE_ADDRESS; //BASE_ADDRESS er til  ADC 
    ext_mem [address] = data;
}

uint8_t xmem_read(uint16_t address){
    volatile char * ext_mem = (char * ) BASE_ADDRESS;
    uint8_t ret_val = ext_mem[address];
    return ret_val;
}
