#include "solenoide.h"

void solenoide_init(){
    PMC->PMC_PCER0 |= PMC_PCER0_PID13; // gir klokke til PIOC
    PIOC->PIO_PER = PIO_PC28; // setter direction pin som enable gpio
    PIOC->PIO_OER = PIO_PC28; // setter PC23 som en utgang 
}

void solenoide_activate(){
    PIOC->PIO_SODR = PIO_PC28;
    time_spinFor(msecs(50));
    PIOC->PIO_CODR = PIO_PC28;
}

void solenoide_polling(CanMsg m){
    printf("jeg trenger jesus");
    uint8_t joy_btn = m.byte[2];
    if(joy_btn){
        solenoide_activate();
    }
}