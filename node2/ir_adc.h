#include "sam.h"
#include "time.h"

void ir_adc_init();

uint16_t ir_adc_read();

void ADC_Handler();

uint16_t ball_blocking();

uint32_t ir_release_count(void);