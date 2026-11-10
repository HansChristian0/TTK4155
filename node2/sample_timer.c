#include "sample_timer.h"

volatile uint8_t g_reg_flag = 0;

void sample_timer_init(){
    PMC->PMC_PCER0 |= PMC_PCER0_PID27; // aktivere klokka for TC0
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC; // velger MCK/2 =42Mhz wave mode og RC compare trigger
    TC0->TC_CHANNEL[0].TC_RC = 420000; // setter compare verdien slik at det blir 100hz siden 42Mz/4,200,000
    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS; // compare RC interupt enabled

    NVIC_EnableIRQ(TC0_IRQn);

    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG; // starter teller


}

void TC0_Handler(){
    volatile uint32_t status = TC0->TC_CHANNEL[0].TC_SR; // tømmer interuupt registeret ved å lese det, 
    g_reg_flag = 1;

}