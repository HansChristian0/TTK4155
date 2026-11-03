#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "uart.h"
#include "time.h"
#include "can.h"
#include "servo_pwm.h"
#include "ir_adc.h"
#include "encoder.h"
#include "motor_drive.h"

/*
 * Remember to update the Makefile with the (relative) path to the uart.c file.
 * This starter code will not compile until the UART file has been included in the Makefile. 
 * If you get somewhat cryptic errors referencing functions such as _sbrk, 
 * _close_r, _write_r, _fstat etc, you have most likely not done that correctly.

 * If you get errors such as "arm-none-eabi-gcc: no such file", you may need to reinstall the arm gcc packages using
 * apt or your favorite package manager.
 */
//#include "../path_to/uart.h"

int main()
{
    SystemInit();
    PMC->PMC_PCER0 = (1 << ID_PIOB);
    PIOB->PIO_PER = PIO_PB27;
    PIOB->PIO_CODR =(1 << 27);
    PIOB->PIO_OER = PIO_PB27;
    
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer
    
    //inits
    uart_init(84000000, 115200); //velger baud basert på vibes
    printf("Hello World\r\n");
    CanInit can_init_parameters = {.phase2 = 1, .propag = 1, .phase1 = 2, .sjw = 1, .brp = 20, .smp = 0};
    can_init(can_init_parameters,1);
    pwm_init();
    ir_adc_init();
    encoder_init();
    motor_drive_init();
    //inits
    
    
    //Uncomment after including uart above

    CanMsg m = {.id = 67, .length = 1, .byte8 = 'y'};
    volatile uint16_t adc_val = 0;
    can_tx(m);
    uint32_t seen = 0;
    uint32_t goals = 0;
    while (1)
    {
        /* code */
       
        if(can_rx_buffered(&m)){
            can_updatemsg(m);
        }
        pwm_servo_ctrl();
        // printf("ir = %4lu  bbl = %u EMR = %08lx ISER1 = %08lx ISPR1 = %08lx PRIMASK = %lu\r\n",ADC->ADC_CDR[0], ball_blocking(),ADC->ADC_IMR,ADC->ADC_EMR,NVIC->ISER[1],NVIC->ISPR[1],__get_PRIMASK());
        // time_spinFor(msecs(100));
        // printf("ir = %lu\r\n", ADC->ADC_CDR[0]);


        // if(ball_blocking()){
        //     printf("du suger du mista et liv git good\r\n");
        // }

        uint32_t releases = ir_release_count();
        if (releases != seen) {
            seen = releases;
            goals++;
            printf("GOAL!!! Current Score: %i\r\n", goals);
        }

        motor_move(10,0);
        // uint32_t encoderPos = TC2->TC_CHANNEL[0].TC_CV;
        // printf("%d\r\n",encoderPos);

    }
    
}