#include "buttons.h"

Buttons read_buttons(){
    Buttons btn;
    SPI_master_transmit(0x04,SELECT_IO);
    _delay_us(50);
    uint8_t *data;
    SPI_read_n_bytes(data,3,SELECT_IO); 
    btn.right = data[0];
    btn.left = data[1];
    btn.nav = data[2];
    return btn;
}