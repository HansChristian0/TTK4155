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
#include "sample_timer.h"
#include "solenoide.h"

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
    sample_timer_init();
    solenoide_init();
    
    //inits
    volatile int32_t enc_center;
    volatile int32_t enc_half;
    motor_calibrate_encoder(&enc_center,&enc_half);
    printf("enc_center = %d enc_half = %d \r\n",enc_center,enc_half);
    //Uncomment after including uart above

    CanMsg m = {.id = 67, .length = 1, .byte8 = 'y'};
    volatile uint16_t adc_val = 0;
    can_tx(m);
    uint32_t seen = 0;
    uint32_t goals = 0;
    int dir = 1;

    
    while (1)
    {

        if(can_rx_buffered(&m)){
            pwm_servo_ctrl(m);
            
            if(g_reg_flag){
                int32_t encoder = encoder_read();
                motor_controller(m,encoder,enc_center,enc_half);    

                g_reg_flag = 0;
            }
            solenoide_polling(m);
        }   



        uint32_t releases = ir_release_count();
        if (releases != seen) {
            seen = releases;
            goals++;
            printf("GOAL!!! Current Score: %i\r\n", goals);
        }

    }
    
}