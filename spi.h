#include <avr/io.h> 
#include "stdio.h"
#include "stdint.h"

#define DISP_DC PB2
#define DISP_SS PB3
#define IO_SS PB4
#define DISP_SDIN PB5
#define IO_MISO PB6
#define DISP_SCK PB7



void SPI_master_init();

void SPI_master_transmit(char cData,uint8_t slave);

// void SPI_slave_init(void);

// char SPI_slave_receive(void); 

void SPI_select_unit(uint8_t selected_unit);
