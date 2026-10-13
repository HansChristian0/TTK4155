#include <avr/io.h> 
#include "stdio.h"
#include "stdint.h"
#include "util/delay.h"
#include "spi.h"
#include "can_cmds.h"

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
uint8_t can_ctrl_read(uint8_t address);

void can_reset();

void can_ctrl_write(uint8_t data, uint8_t addr);
void can_set_loopback();

void can_ctrl_request_to_send(uint8_t TXB);

uint8_t can_ctrl_read_status();

void can_ctrl_bit_modify(uint8_t reg, uint8_t mask, uint8_t);

void can_ctrl_set_bit(uint8_t reg_addr, uint8_t bit);

void can_ctrl_clear_bit(uint8_t reg_addr, uint8_t bit);