#include"servo_pwm.h"


void pwm_init(){
    PMC->PMC_PCER1 |= PMC_PCER1_PID36; // Enable klokke for PIO med id 36 som er PWM
   // PMC->PMC_PCDR1 &= ~(1 << PMC_PCDR1_PID36); // tror ikke denne trengs men 

    PIOA->PIO_ABSR = PIO_ABSR_P8; //AB periferal select multiplexer to funk på en pin virker vansklig vi driter i det
    PIOA->PIO_PDR |= (1 << 8); //gir pinen til periferien
    PWM->PWM_WPCR = (0x50574D << 8) | (7 << 1 ) | 0; //sender Key for å låse opp write protect for | låser opp alle siden jeg ikke vet hvilken vi trenger.. | disable write protect
    PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_32;
    PWM->PWM_CH_NUM[0].PWM_CPRD = PWM_DEF_CPRD;
    PWM->PWM_CH_NUM[0].PWM_CDTY = PWM_DEF_CPRD / 7;
    PWM->PWM_ENA |= (1 << 0);
}

