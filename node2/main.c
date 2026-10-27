#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "uart.h"
#include "time.h"
#include "can.h"
#include "servo_pwm.h"

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
    //inits
    
    
    //Uncomment after including uart above

    CanMsg m = {.id = 67, .length = 1, .byte8 = 'y'};
    can_tx(m);
    while (1)
    {
        /* code */
        // PIOB->PIO_SODR = PIO_PB27;
        // for(int i = 0; i < 1000000;i++){}
        // PIOB->PIO_CODR = PIO_PB27;
        // for(int i = 0; i < 1000000;i++){}
        if(can_rx_buffered(&m)){
            can_printmsg(m);
        }
        pwm_servo_ctrl();
        
    }
    
}