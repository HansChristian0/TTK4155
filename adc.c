#include"adc.h"
#include <avr/io.h>

void CLK_signal(){
    DDRD |= (1 << PD5); //setter DataDirection REgister D slik at PD5 er sat til ocillating OC1A aka outout for PWM
    uint8_t compare_value = 0; //teller fra 0 til 1 og hver gang den treffer 1 flagges OC1A også 
    OCR1A = compare_value; //verdien som TOP sammenliknes med 

    TCCR1A = (1 << COM1A0); //toggler OC1A på compare match og 
    TCCR1B = (1 << WGM12) | (1 << CS10); //timer control register B slik at den er i CTC modus, nå uten prescaler
}

// adc_init(void){

// }
// uint8_t adc_read(uint8_t channel);
// pos_calibrate();
// pos_t pos_read(void);