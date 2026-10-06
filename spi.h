#include <avr/io.h> 
#include "stdio.h"
#include "stdint.h"
#include "util/delay.h"

#define DISP_RESET PB1
#define DISP_DC PB2
#define DISP_SS PB3
#define IO_SS PB4
#define DISP_SDIN PB5
#define IO_MISO PB6
#define DISP_SCK PB7
#define SELECT_DISP 1
#define SELECT_IO 2
#define CAN_SS PD4
#define CAN_INTERRUPT PD3



void SPI_master_init();

void SPI_master_transmit(char cData,uint8_t slave);

void SPI_transfer_n_bytes(const uint8_t *p_data,uint8_t len, uint8_t slave);

// void SPI_slave_init(void);

// char SPI_slave_receive(void); 

void SPI_select_unit(uint8_t selected_unit);
