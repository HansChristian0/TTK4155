#include "can_com.h"



void can_com_load_tx( Dataframe *frame ,uint8_t buffer){ //buffer styrer hvor addr_pointer starter 000 -> TXB0SIDH 001->TXB0D0 010 -> TXB1SIDH 011-> TXBD1D0 100->TXB2SIDH 101->TXB2D0
    buffer &= 0x07;
    SPI_select_unit(SELECT_CAN);
    SPI_master_transmit(0x40 | buffer,SELECT_CAN);
    SPI_master_transmit(frame->id, SELECT_CAN);
    SPI_master_transmit(frame->data_len,SELECT_CAN);
    SPI_master_transmit(*(frame->data),SELECT_CAN);
    SPI_deselect_unit(SELECT_CAN);
    // for(uint8_t i = 0;  i < frame->data_len ; i++){
    //     SPI_master_transmit(frame->data[i],SELECT_CAN);
    // }
}

void can_com_transmit(const Dataframe *frame, uint8_t buffer){
    SPI_select_unit(SELECT_CAN);
    can_com_load_tx(frame, buffer); // laster hele meldignern i tx buffer 
 
    can_ctrl_request_to_send(buffer); // request to send legger message klar til sending fra samme buffer som vi lasta inn ista 
    
}

//uint8_t can_com_receive(){
//    // no interrupt tullball
//
//
//}