#include "buttons.h"

Buttons read_buttons(){
    Buttons btn;
    SPI_master_transmit(0x04,SELECT_IO);
    _delay_us(50);
    // SPI_master_read(SELECT_IO);

    uint8_t data[3];
    SPI_read_n_bytes(data,3,SELECT_IO); 
    btn.right = data[0];
    btn.left = data[1];
    btn.nav = data[2];
    return btn;
}

uint8_t joystick_btn_pressed(){
    SPI_master_transmit(0x03,SELECT_IO);
    _delay_us(50);
    volatile uint8_t data = 0;
    data = SPI_master_read(SELECT_IO);
    printf("x: %d \r\n",data);
    data = SPI_master_read(SELECT_IO);
    printf("y: %d \r\n",data);
    data = SPI_master_read(SELECT_IO);
    printf("btn: %d \r\n",data);
    return data;
}