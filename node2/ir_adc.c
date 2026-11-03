#include "ir_adc.h"

static volatile uint16_t g_lives = 3;
static volatile uint16_t g_bbl = 0; // ball block laser

void ir_adc_init(){
    PMC->PMC_PCER1 |= PMC_PCER1_PID37; //skru på klokka for ADC i PMc id 37
    
    ADC->ADC_CR = ADC_CR_SWRST; //reset adc

    // ADC->ADC_WPMR |= (0x414443 << 7) | (1 << 0);
    ADC->ADC_CHER |= ADC_CHER_CH0;
    ADC->ADC_MR |= (3u << ADC_MR_PRESCAL_Pos) | ADC_MR_STARTUP_SUT512 | ADC_MR_TRACKTIM(10) | ADC_MR_TRANSFER(5)| ADC_MR_FREERUN_ON; // max frekvens adc er 22Mhz, F_adc = MCK/(2*(1+Prescale)) =10,5 MHZ! med prescale = 3, startup tid på 48 mikro sek!
    // setter trcktim og transfer til litt tilfeldige verdier:) og free run så kjører den kontinuerlig

    //interrupt init

    ADC->ADC_EMR |= ADC_EMR_CMPMODE_LOW | ADC_EMR_CMPFILTER_Msk | ADC_EMR_CMPSEL(0); // sette comp mode lav og 4 sucsessive lave målinger for å trigger interupt
    ADC->ADC_CWR |= ADC_CWR_LOWTHRES(300) | ADC_CWR_HIGHTHRES(700); //setter low thres til 300 og high til 700
    ADC->ADC_IER |= ADC_IER_COMPE; //aktivere comparativ interupt
    NVIC_EnableIRQ(ADC_IRQn);
    
}

uint16_t ir_adc_read(){
    ADC->ADC_CR |= ADC_CR_START;
    //printf("PCSR1=%08lx MR=%08lx CHSR = %08lx ISR = %08lx \r\n",PMC->PMC_PCSR1,ADC->ADC_MR,ADC->ADC_CHSR, ADC->ADC_ISR);
    while(!(ADC->ADC_ISR & ADC_ISR_EOC0)){} //venter til END of Conversion
    return ADC->ADC_CDR[0]; // lese ut fra rett kanal dataen som ligger der
}

void ADC_Handler(){
    uint32_t status = ADC->ADC_ISR;
    if(status & ADC_ISR_COMPE){
        if(!g_bbl){ //hvis sist interupt var på at ball ikke blokerte laser skal spiller miste et liv og interrupt se etter adc høy
            g_bbl = 1;
            g_lives--;
            ADC->ADC_EMR |=ADC_EMR_CMPSEL(0) | ADC_EMR_CMPMODE_HIGH;
        }
        else{ //om ball har blokkert ir og den går høy så setter vil bbl lav og interupt til å se etter lav
            g_bbl = 0;
            ADC->ADC_EMR |= ADC_EMR_CMPSEL(0) | ADC_EMR_CMPMODE_LOW;
        }
    }
}

uint16_t ball_blocking(){
    return g_bbl;
}