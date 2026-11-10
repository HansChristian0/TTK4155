#include "motor_drive.h"

void motor_drive_init(){
    //allered fått PCM klokkke fra servo init
    PMC->PMC_PCER1 |= PMC_PCER1_PID36; // aktivere klokke for PWM
    //init motor dir pin på PC23
    PMC->PMC_PCER0 |= PMC_PCER0_PID12; // gi klokke til PIOB
    PMC->PMC_PCER0 |= PMC_PCER0_PID13; // gir klokke til PIOC
    PIOC->PIO_PER = PIO_PC23; // setter direction pin som enable gpio
    PIOC->PIO_OER = PIO_PC23; // setter PC23 som en utgang 
    //PIOC->PIO_SODR = PIO_PC23; // setter den til noe ved start
    //init motor drive pwm
    PIOB->PIO_ABSR |= PIO_ABSR_P12; //AB periferal select multiplexer to funk på en pin virker 
    PIOB->PIO_PDR |= (1 << 12); //gir pinen til periferien uskker på denne


    PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_MCK | PWM_CMR_CPOL; // dette setter prescaler vi setter til 1
    PWM->PWM_CH_NUM[0].PWM_CPRD = MOTOR_PWM_CPRD; //velger 100kh som frekvens 84mhz/840hz = 100khz vamanos
    //PWM->PWM_CH_NUM[0].PWM_CDTY = 420;
    PWM->PWM_ENA |= (1 << 0); //pwm enable! channal 0

}

void motor_calibrate_encoder(int32_t *encoder_center, int32_t *encoder_half){
    printf("kalibrerer.....");
    int32_t encoder_left;
    int32_t encoder_right;

    motor_move(50,1);
    time_spinFor(msecs(1500));
    encoder_left = encoder_read();
    motor_move(50,0);
    time_spinFor(msecs(1500));
    encoder_right = encoder_read();
    *encoder_center = (encoder_right + encoder_left)/2;
    *encoder_half = (encoder_right - encoder_left)/2;
    printf("right = %d, left = %d ", encoder_right,encoder_left);
    motor_move(0,0);
}

void motor_move(uint16_t duty_cycle, uint16_t dir){
    if(duty_cycle >= 100){ //ugyldig dutycycle er teit
        duty_cycle = 90;
    }
    PWM->PWM_CH_NUM[0].PWM_CDTY = duty_cycle*MOTOR_PWM_CPRD/100;
    if(dir == 1){
        PIOC->PIO_SODR = PIO_PC23;
    }
    else{
        PIOC->PIO_CODR = PIO_PC23;
    }
}

void motor_controller(CanMsg m, int16_t encoder, int16_t encoder_center, int16_t encoder_half){
    float Kp = 0.6; //HC liker denne tuningen siden den er litt treig tilbake så han kan flikke baller
    float Ki = 0.5;
    float T = 0.01;
    static int16_t err_sum = 0;
//trenger å kalibrere encoderen
    int8_t joy_position = m.byte[1];
    // printf("encoder = %d joy_position = %d\r\n ",encoder-encoder_center,joy_position);
    int16_t enc_pos = encoder - encoder_center;
    int16_t enc_percent = enc_pos * 100 / encoder_half;

    int16_t e = joy_position - enc_percent;
    err_sum += e;
    int16_t u =  Kp*e + T*Ki*err_sum; // lager en P regulator til å begynne med
    int16_t dir = !(u >= 0); //0 om større 1 om mindre, blir rett rettning
    int16_t duty;

    if(u < 0){
        duty = -u;
    }
    else{
        duty = u;
    }
    if(duty > 100){ //mettning
        duty = 100;
    }
    if(duty < 20){ //dødbånd
        duty = 0;
    }
    motor_move(duty,dir);

    // printf("u = %d e = %d\r\n",u,enc_percent);
}


