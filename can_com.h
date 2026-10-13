#include <avr/io.h> 
#include "stdio.h"
#include "stdint.h"
#include "util/delay.h"
#include "spi.h"
#include "can_cmds.h"
#include "can_ctrl.h"

typedef struct{ // veldig usikker på om dette er no interessant i det hele tatt
    //Start of frame bit
    uint16_t id;// siste bit her er Remote transmition request
    uint8_t data_len; //data len counter føreste bit er ID extended bit
    char data[]; // data
}Dataframe;

void can_com_load_tx(Dataframe *frame ,uint8_t buffer);

void can_com_transmit(const Dataframe *frame, uint8_t buffer);