#include"servo_pwm.h"


void pwm_init(){
    PMC->PMC_PCER1 |= PMC_PCER1_PID36; // Enable klokke for PIO med id 36 som er PWM
   // PMC->PMC_PCDR1 &= ~(1 << PMC_PCDR1_PID36); // tror ikke denne trengs men 

    PIOB->PIO_ABSR |= PIO_ABSR_P13; //AB periferal select multiplexer to funk på en pin virker vansklig vi driter i det
    PIOB->PIO_PDR |= (1 << 13); //gir pinen til periferien
    PWM->PWM_WPCR = (0x50574D << 8) | (7 << 1 ) | 0; //sender Key for å låse opp write protect for | låser opp alle siden jeg ikke vet hvilken vi trenger.. | disable write protect
    PWM->PWM_CH_NUM[1].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_32;
    PWM->PWM_CH_NUM[1].PWM_CPRD = PWM_DEF_CPRD;
    PWM->PWM_CH_NUM[1].PWM_CDTY = PWM_DEF_CPRD / 7;
    PWM->PWM_ENA |= (1 << 1);
}

void pwm_servo_ctrl(){
    CanMsg joy_pos;
    if(can_rx_buffered(&joy_pos)){
        switch (joy_pos.byte[0])
        {
        case POS_LEFT:
            PWM->PWM_CH_NUM[1].PWM_CDTY = PWM_DEF_CPRD - 2362;

            break;
        case POS_RIGHT:
            PWM->PWM_CH_NUM[1].PWM_CDTY =PWM_DEF_CPRD - 5512;
            break;
        case POS_NEUTRAL:
            PWM->PWM_CH_NUM[1].PWM_CDTY = PWM_DEF_CPRD - 3937;
            break;
        default:
            break;
        }
    }
    
}




