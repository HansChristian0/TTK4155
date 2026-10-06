#include "spi.h"


void SPI_master_init(){
    /* Set MOSI and SCK output, all others output */
    DDRB |= (1<<MOSI)|(1<<DISP_SCK) |(1<<DISP_SS) |(1<<IO_SS) |(1<<DISP_RESET) | (1<<DISP_DC);
    DDRB &= ~(1<<MISO); 
    
    // kanskje sette ALt av SS til høyt så ingenting drives
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

    PORTB |= (1<<DISP_RESET) | (1<<DISP_SS) | (1<<IO_SS); // setter disp reset høy fra start

    // CAN ports 
    DDRD |= (1 << CAN_SS) |(1 << CAN_INTERRUPT);

    PORTD |= (1<<CAN_SS);

}

void SPI_master_transmit(char cData, uint8_t slave){
    /* Start transmission */
    SPI_select_unit(slave);
    SPDR = cData;
    /* Wait for transmission complete */ 
    while(!(SPSR & (1<<SPIF)));
}

void SPI_transfer_n_bytes(const uint8_t *p_data, uint8_t len, uint8_t slave){
    SPI_select_unit(slave);
    for(uint8_t i = 0; i < len; i++){
        SPDR = p_data[i];

    /* Wait for transmission complete */ 
        while(!(SPSR & (1<<SPIF))){}
    }
}

uint8_t SPI_master_read(uint8_t slave){
    SPI_select_unit(slave);
    uint8_t dummy = 0;
    SPDR = dummy; // sende noe tullball
    while(!(SPSR & (1<<SPIF))){} // vente til vi har sendt alt
    return SPDR;
}

void SPI_read_n_bytes(uint8_t *data, uint8_t length, uint8_t slave){ // lese av masse ulike greier som er mega fun
    SPI_select_unit(slave);

    for(uint8_t i = 0; i < length; i++){
        data[i] = SPI_master_read(slave);
        printf("%d \r\n", data[i]);
        _delay_us(4);
    }
}

void SPI_select_unit(uint8_t selected_unit){
    // sett enten SS for display eller for IO lav
    switch (selected_unit)
    {
    case 1: //Display lav og IO høy aka velde display
        PORTB &= ~(1<<DISP_SS); 
        PORTB |= (1<<IO_SS);
        PORTD |= (1<<CAN_SS);
        break;
    case 2: //display høy og IO lav aka velde IO
        PORTB &= ~(1<<IO_SS);
        PORTB |= (1<<DISP_SS);
        PORTD |= (1<<CAN_SS);
        break;
    case 3:
        //for å velge en tredje enhet må legge til litt snadder på de andre casene og
        PORTD &= ~(1<<CAN_SS); 
        PORTB |= (1<<IO_SS);
        PORTB |= (1<<DISP_SS);
        break;
    default:
        break;
    }


}

// void SPI_slave_init(void)
// {
//     /* Set MISO output, all others input */
//     DDR_SPI = (1<<DD_MISO);
//     /* Enable SPI */
//     SPCR = (1<<SPE);
// }

// char SPI_slave_receive(void){
//     /* Wait for reception complete */
//     while(!(SPSR & (1<<SPIF)))
//     ;
//     /* Return data register */
//     return SPDR;
// }