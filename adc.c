#include"adc.h"
#include <avr/io.h>
#include "stdio.h"

void CLK_signal(){
    DDRD |= (1 << PD5); //setter DataDirection REgister D slik at PD5 er sat til ocillating OC1A aka outout for PWM
    uint8_t compare_value = 0; //teller fra 0 til 1 og hver gang den treffer 1 flagges OC1A også 
    OCR1A = compare_value; //verdien som TOP sammenliknes med 

    TCCR1A = (1 << COM1A0); //toggler OC1A på compare match og 
    TCCR1B = (1 << WGM12) | (1 << CS10); //timer control register B slik at den er i CTC modus, nå uten prescaler
}

void adc_init(void){
    DDRA = 0x00; //setter retting på databussen 
    DDRE |= (0<<PE0); //sette E0 slik at den kan ta imot busy signal
    volatile uint8_t* ADC = (uint8_t * ) 0x1000; 
    DDRD |= (1 << PD6);       // PD6 = output (WR)
    DDRD |= (1 << PD7);       // PD7 = output (RD)
}

uint8_t adc_read(uint8_t channel){
    PORTD |= (1 << PD6);
    PORTD &= ~(1 << PD6);
    PORTD |= (1 << PD6);
    while (!(PINE & (1 << PE0))){ // vente til busy går høy
        printf("evigløkke:)");
    }
    for (uint8_t i = 0; i < channel; i++){ // kjøre anntall stobes for den kanalen vi vil lese av 
        PORTD |= (1 << PD7);
        PORTD &= ~(1 << PD7);
        PORTD |= (1 << PD7);// read strobe   
    }
    volatile uint8_t* ADC = (uint8_t * ) 0x1000;
    volatile uint8_t value = *ADC;
    return value;
}
// pos_calibrate();
// pos_t pos_read(void);