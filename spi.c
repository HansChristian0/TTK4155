#include "spi.h"


void SPI_master_init(){
    /* Set MOSI and SCK output, all others input */
    DDRB |= (1<<DISP_SDIN)|(1<<DISP_SCK) |(1<<DISP_SS);
    
    // kanskje sette ALt av SS til høyt så ingenting drives
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

}

void SPI_master_transmit(char cData, uint8_t slave){
    /* Start transmission */
    SPI_select_unit(slave);
    SPDR = cData;
    /* Wait for transmission complete */ 
    while(!(SPSR & (1<<SPIF)));
}

void SPI_select_unit(uint8_t selected_unit){
    // sett enten SS for display eller for IO lav
    switch (selected_unit)
    {
    case 1:
        PORTB &= ~(1<<DISP_SS); 
        PORTB |= (1<<IO_SS);
        break;
    case 2:
        PORTB &= ~(1<<IO_SS);
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