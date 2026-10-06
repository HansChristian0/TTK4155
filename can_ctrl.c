#include "can_ctrl.h"


void can_ctrl_init(){
    //pins som har blitt koblet til can saken sette ouput
    DDRD |= (1 << CAN_SS) |(1 << CAN_INTERRUPT);
    can_reset();
    _delay_ms(100);
    can_ctrl_write(0x01,CNF1);
    can_ctrl_write(0xD1,CNF2);
    can_ctrl_write(0x81,CNF3);


    can_ctrl_write(0x60,0x60);
    can_ctrl_write(0x40,CANCTRL);
}

uint8_t can_read(uint8_t address){
    SPI_select_unit(3); //starter med å senke CS
    //første byte er command
    SPI_master_transmit(CAN_READ,3); 
    SPI_master_transmit(address,3);
    uint8_t data = SPI_master_read(3);

    //send adresse
    //data stored 

    SPI_deselect_unit(3); //terminerer med å øke CD
    return data;
}

void can_set_loopback(){
    can_reset();
    _delay_ms(10);

    can_ctrl_write(0x0F,0x40);

    uint8_t status = can_read(0x0E);
    if((status &0x0E) == 0x40){
        printf("vi er i loopback");
    }
    else{
        printf("vi er ikke i loopback");
    }
}


void can_reset(){
    SPI_select_unit(SELECT_CAN);
    SPI_master_transmit(CAN_RESET,SELECT_CAN);
    SPI_deselect_unit(SELECT_CAN);
}

void can_ctrl_write(uint8_t data, uint8_t addr){
    SPI_select_unit(SELECT_CAN);
    uint8_t cmd[3] = {CAN_WRITE,addr,data};
    SPI_transfer_n_bytes(cmd,3,SELECT_CAN);
    SPI_deselect_unit(SELECT_CAN);

}