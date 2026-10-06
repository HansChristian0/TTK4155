#include <avr/io.h> 
#include "stdio.h"
#include "stdint.h"
#include "util/delay.h"
#include "spi.h"

#define CAN_RESET 0b11000000
#define CAN_READ 0b00000011

#define CAN_WRITE 0b00000010

#define CAN_READ_STATUS 0b10100000
#define CAN_RX_STATUS 0b10110000
#define CAN_BIT_MODIFY 0b00000101

#define CNF1 0x2A
#define CNF2 0x29
#define CNF3 0x28

#define CANSTAT 0x0E
#define CANCTRL 0x0F




void can_ctrl_init();
uint8_t can_read(uint8_t address);

void can_reset();

void can_ctrl_write(uint8_t data, uint8_t addr);
void can_set_loopback();