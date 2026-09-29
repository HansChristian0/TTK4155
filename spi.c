#include "spi.h"


void SPI_master_init(){
    /* Set MOSI and SCK output, all others input */
    DDRB |= (1<<DISP_SDIN)|(1<<DISP_SCK) |(1<<DISP_SS) |(1<<IO_SS) |(1<<DISP_RESET);
    
    // kanskje sette ALt av SS til høyt så ingenting drives
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

    PORTB |= (1<<DISP_RESET); // setter disp reset høy fra start

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
        printf("%d \r \n",p_data[i]);
        _delay_ms(1000);
    /* Wait for transmission complete */ 
        while(!(SPSR & (1<<SPIF))){}
    }
}

void SPI_select_unit(uint8_t selected_unit){
    // sett enten SS for display eller for IO lav
    switch (selected_unit)
    {
    case 1: //Display lav og IO høy aka velde display
        PORTB &= ~(1<<DISP_SS); 
        PORTB |= (1<<IO_SS);
        break;
    case 2: //display høy og IO lav aka velde IO
        PORTB &= ~(1<<IO_SS);
        PORTB |= (1<<DISP_SS);
        break;
    case 3:
        //for å velge en tredje enhet må legge til litt snadder på de andre casene og
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