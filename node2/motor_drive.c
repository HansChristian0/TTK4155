#include "motor_drive.h"


void motor_drive_init(){
    //allered fått PCM klokkke fra servo init

    //init motor dir pin på PC23
    PMC->PMC_PCER0 = PMC_PCER0_PID13| PMC_PCER0_PID12; // gi klokke til motor dir pin
    PIOC->PIO_PER |= PIO_PC23; // setter direction pin som enable gipio
    PIOC->PIO_OER = PIO_PC23; // setter PC23 som en utgang 


    PIOB->PIO_ABSR |= PIO_ABSR_P12; //AB periferal select multiplexer to funk på en pin virker vansklig vi driter i det
    PIOB->PIO_PDR |= (1 << 12); //gir pinen til periferien

    PWM->PWM_WPCR = (0x50574D << 8) | (7 << 1 ) | 0; //sender Key for å låse opp write protect for | låser opp alle siden jeg ikke vet hvilken vi trenger.. | disable write protect
    PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_MCK; // dette setter prescaler vi setter til 1
    PWM->PWM_CH_NUM[0].PWM_CPRD = 840; //velger 100kh som frekvens 84mhz/840hz = 100khz vamanos
     // setter en tilf dutycycle
    PWM->PWM_ENA |= (1 << 0);

}

void motor_move(uint16_t duty_cycle, uint16_t dir){
    if(duty_cycle <= 1){
        return;
    }
    PWM->PWM_CH_NUM[0].PWM_CDTY = 100000 / duty_cycle;
    if(dir == 1){
        PIOC->PIO_SODR = PIO_PC23;
    }
    else{
        PIOC->PIO_CODR = PIO_PC23;
    }
}

