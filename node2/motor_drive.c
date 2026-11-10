#include "motor_drive.h"


void motor_drive_init(){
    //allered fått PCM klokkke fra servo init
    PMC->PMC_PCER1 |= PMC_PCER1_PID36; // aktivere klokke for PWM
    //init motor dir pin på PC23
    PMC->PMC_PCER0 = PMC_PCER0_PID12; // gi klokke til PIOB
    PMC->PMC_PCER0 = PMC_PCER0_PID13; // gir klokke til PIOC
    PIOC->PIO_PER = PIO_PC23; // setter direction pin som enable gpio
    PIOC->PIO_OER = PIO_PC23; // setter PC23 som en utgang 
    //PIOC->PIO_SODR = PIO_PC23; // setter den til noe ved start
    //init motor drive pwm
    PIOB->PIO_ABSR |= PIO_ABSR_P12; //AB periferal select multiplexer to funk på en pin virker 
    PIOB->PIO_PDR |= (1 << 12); //gir pinen til periferien uskker på denne


    PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_MCK | PWM_CMR_CPOL; // dette setter prescaler vi setter til 1
    PWM->PWM_CH_NUM[0].PWM_CPRD = MOTOR_PWM_CPRD; //velger 100kh som frekvens 84mhz/840hz = 100khz vamanos
    PWM->PWM_CH_NUM[0].PWM_CDTY = 420;
    PWM->PWM_ENA |= (1 << 0); //pwm enable! channal 0

}

void motor_move(uint16_t duty_cycle, uint16_t dir){
    if(duty_cycle >= 100){ //ugyldig dutycycle er teit
        return;
    }
    PWM->PWM_CH_NUM[0].PWM_CDTY = duty_cycle*MOTOR_PWM_CPRD/100;
    if(dir == 1){
        PIOC->PIO_SODR = PIO_PC23;
    }
    else{
        PIOC->PIO_CODR = PIO_PC23;
    }
}

void motor_controller(CanMsg m){
    uint8_t position = m.byte[1];
    printf("position = %d\r\n",position);

}
