#include "can_ctrl.h"


void can_ctrl_init(){
    //pins som har blitt koblet til can saken sette ouput
    DDRD |= (1 << CAN_SS);
    DDRD &= ~(1 << CAN_INTERRUPT);
    //må resettes ved start for å putte rett register verdi overalt og sette i config mode
    can_reset();
    _delay_ms(100); // må vente litt etter reset 100 ms er sikkert litt i overkant

    //sette no klokke
    can_ctrl_write(0x01,CNF1);
    can_ctrl_write(0xD1,CNF2);
    can_ctrl_write(0x81,CNF3);
    //setter klokke til Nominal Bit Rate 1/8TQ

    can_ctrl_write(0x00,CANCTRL); // setter til loopback til å begyne med
    can_ctrl_write(0x04, MCP_CANINTE);
}

uint8_t can_ctrl_read(uint8_t address){
    SPI_select_unit(SELECT_CAN); //starter med å senke CS
    //første byte er command
    SPI_master_transmit(CAN_READ,SELECT_CAN); 
    SPI_master_transmit(address,SELECT_CAN);
    uint8_t data = SPI_master_read(SELECT_CAN);

    //send adresse
    //data stored 

    SPI_deselect_unit(SELECT_CAN); //terminerer med å øke CD
    return data;
}

void can_set_loopback(){
    can_reset();
    _delay_ms(10);

    can_ctrl_write(0x40,CANCTRL);

    uint8_t status = can_ctrl_read(0x0E);
    if((status &0xE0) == 0x40){
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

void can_ctrl_write(uint8_t data, uint8_t addr){ // skriver med SPI til et register
    SPI_select_unit(SELECT_CAN);
    uint8_t cmd[3] = {CAN_WRITE,addr,data};
    SPI_transfer_n_bytes(cmd,3,SELECT_CAN);
    SPI_deselect_unit(SELECT_CAN);

}

void can_ctrl_request_to_send(uint8_t TXB){
    SPI_select_unit(SELECT_CAN);
    
    TXB &= 0x07; // bryr meg bare om de siste tre bitsa 
    if(TXB == 0){ // ignorere når buffer bits er 000
        return;
    }

    SPI_master_transmit(0x80 | TXB,SELECT_CAN); // bruker 0x80 siden de ulike buffer selectsa er 0x81 (TXB1) til 0x87 (ALLE)
    SPI_deselect_unit(SELECT_CAN);
}

uint8_t can_ctrl_read_status(){
    SPI_select_unit(SELECT_CAN);
    SPI_master_transmit(MCP_READ_STATUS,SELECT_CAN); // sender en read status kommando
    uint8_t status = 0;
    status = SPI_master_read(SELECT_CAN); // neste byte etter kommandoen vil være statuses på form funnet i datablad s. 69
    SPI_deselect_unit(SELECT_CAN);
    return status;
}

void can_ctrl_bit_modify(uint8_t reg_addr, uint8_t mask, uint8_t data){ // kan kun brukes på visse registre
    SPI_select_unit(SELECT_CAN);
    SPI_master_transmit(MCP_BITMOD,SELECT_CAN);
    SPI_master_transmit(reg_addr,SELECT_CAN);
    SPI_master_transmit(mask,SELECT_CAN); // bestemer hvilke bits som kan endres 1 gir endrebart bit 0 gir ikke endrebart bit
    SPI_master_transmit(data,SELECT_CAN); // data bestemer hva som skal endres
    SPI_deselect_unit(SELECT_CAN);

}

//brukervennlig bit modyfy
void can_ctrl_set_bit(uint8_t reg_addr, uint8_t bit){
    uint8_t mask = 0;
    uint8_t data = 0;
    mask = (1 << bit);
    data = (1 << bit);
    can_ctrl_bit_modify(reg_addr,mask,data);
}

void can_ctrl_clear_bit(uint8_t reg_addr, uint8_t bit){ // setter mask til bit data er null som gir 0 på det ene bit
    uint8_t mask = 0;
    uint8_t data = 0;
    mask = (1 << bit);
    can_ctrl_bit_modify(reg_addr,mask,data);
}

