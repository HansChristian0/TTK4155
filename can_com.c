#include "can_com.h"

typedef struct{ // veldig usikker på om dette er no interessant i det hele tatt
    //Start of frame bit
    uint16_t id;// siste bit her er Remote transmition request
    uint8_t data_len; //data len counter føreste bit er ID extended bit
    uint8_t data; // data
}dataframe;


void can_com_transmit(const dataframe frame; uint8_t buffer){
    can_ctrl_request_to_send(buffer); // request to send legger message 
    
    //putte data i TXn buffer!!! hvor putter jeg det???
    
    


}

uint8_t can_com_receive(){
    // no interrupt tullball


}