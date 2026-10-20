#include "can_com.h"




void can_com_load_tx( Dataframe *frame){ //buffer styrer hvor addr_pointer starter 000 -> TXB0SIDH 001->TXB0D0 010 -> TXB1SIDH 011-> TXBD1D0 100->TXB2SIDH 101->TXB2D0

    SPI_select_unit(SELECT_CAN);
    while(can_ctrl_read(MCP_TXB0CTRL) & 0x08){}// sjekker TXDRQS bit

    // deler opp id mellom de to registreme
    can_ctrl_write((uint8_t)(frame->id >> 3), MCP_TXB0SIDH);
    can_ctrl_write((uint8_t)((frame->id & 0x07) << 5), MCP_TXB0SIDL);

    can_ctrl_write(frame->data_len,MCP_TXB0DLC);

    for(uint8_t i = 0;  i < frame->data_len ; i++){
        can_ctrl_write(frame->data[i],MCP_TXBD0 + i);
    }


    SPI_deselect_unit(SELECT_CAN);
}

void can_com_transmit(const Dataframe *frame, uint8_t buffer){
    SPI_select_unit(SELECT_CAN);
    can_com_load_tx(frame); // laster hele meldignern i tx buffer 
 
    can_ctrl_request_to_send(buffer); // request to send legger message klar til sending fra samme buffer som vi lasta inn ista 

}


void can_com_receive(Dataframe *msg){
    while(!(can_ctrl_read(MCP_CANINTF) & 0x01)){
        // return;
    }

    uint8_t sidh = can_ctrl_read(MCP_RXB0SIDH);
    uint8_t sidl = can_ctrl_read(MCP_RXB0SIDH + 1); // neste! adresse
    

    msg->id = ((uint16_t)sidh << 3) | (sidl >> 5);

    msg->data_len = can_ctrl_read(MCP_RXB0DLC) & 0b00001111; //max 8 i lengde frodi det bare er 8 reg i buffer 0
    if(msg->data_len > 8){
        msg->data_len = 8;
    }

    for (uint8_t i = 0; i < msg->data_len; i++){
        msg->data[i] = can_ctrl_read(MCP_RXB0D0 + i);
        // printf("i=%d, data=%c, hex=0x%02X\r\n",i, msg->data[i], (unsigned char)msg->data[i]);

    }
    can_ctrl_bit_modify(MCP_CANINTF,MCP_RX0IF,0x00);
}
