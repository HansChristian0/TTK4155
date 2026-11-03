#include "encoder.h"


void encoder_init(){
    PMC->PMC_PCER1 = PMC_PCER1_PID33 | PMC_PCER1_PID34; //enable cklokke fra 
    PIOC->PIO_PDR = PIO_PDR_P25 | PIO_PDR_P26; // gir pinsa til periferien
    PIOC->PIO_ABSR |= PIO_PC25B_TIOA6 | PIO_PC26B_TIOB6; // sette til periferal B modus

    //initialisere TC2
    TC2->TC_BMR = TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA; // sette quadrature encoder mode, posisjonsmåling og detetkterer både A og B
    TC2->TC_CHANNEL[0].TC_CMR = TC_CMR_ABETRG | TC_CMR_TCCLKS_XC0; //setter TIOA som external trigger og setter XC0 som klokke
    TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG; //enepler klokka og kjørere en software trigger som resetter count og starter klokke
}