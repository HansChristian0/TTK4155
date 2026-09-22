#include"adc.h"
#include <avr/io.h>
#include "util/delay.h"
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
    DDRE &= ~(1<<PE0); //sette E0 lav slik at den kan ta imot busy signal
    volatile uint8_t* ADC = (uint8_t * ) 0x1000; 
}

uint8_t adc_read(uint8_t channel){
    volatile uint8_t *adc = (uint8_t*)0x1000;
    adc[0] = 0; // setter den i normal modus etter å ha knfigurert kanalene
    volatile uint8_t value;
    while (!(PINE & (1 << PE0))) {} //vente til busy går lav
    for (int i=0; i <= channel; i++) { // lese ut for antall kanal slik at vi returnerer 
        value = adc[0];    
    }

    return value;
}
volatile uint8_t* pos_calibrate(){
    volatile uint8_t min_max_xy[4] = {0,0,0,0}; //to første er x nest er y min så max
    printf("Hold til venstre \r \n"); 
    _delay_ms(20000);
    uint8_t var = adc_read(1);
    var = adc_read(1);
    min_max_xy[0] = var;
    printf("%d \r \n", var);

    printf("Hold til høyre \r \n");
    _delay_ms(20000);
    var = adc_read(1);
    var = adc_read(1);
    min_max_xy[1] = var;
    printf("%d \r \n", var);
    
    printf("Hold ned \r \n");
    _delay_ms(20000);
    var = adc_read(0);
    var = adc_read(0);
    min_max_xy[2] = var;
    printf("%d \r \n", var);
    
    printf("Hold opp \r \n");
    _delay_ms(20000);
    var = adc_read(0);
    var = adc_read(0);
    min_max_xy[3] = var;
    printf("%d \r \n", var);
    return min_max_xy;
}

int8_t pos_read_percent_x(uint8_t* calibration, uint8_t curr_pos_x){
    int8_t neutral_x = (calibration[0] + calibration[1]) / 2;
    return (curr_pos_x - neutral_x)/(calibration[1]-neutral_x);
}

int8_t pos_read_percent_y(uint8_t* calibration, uint8_t curr_pos_y){
    int8_t neutral_y = (calibration[2] + calibration[3]) / 2;
    return (curr_pos_y - neutral_y)/(calibration[1]-neutral_y);
}

// pos_t pos_read(uint8_t* calibration){
//     uint8_t x = adc_read(1);
//     uint8_t y = adc_read(0);
//     uint8_t neutral_x = (calibration[0] + calibration[1]) / 2;
//     uint8_t neutral_y = (calibration[2] + calibration[3]) / 2;
//     if(x >= calibration[1]*0.75){
//         retun LEFT;
//     }
// }