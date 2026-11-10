#include "sam.h"
#include "time.h"

#define IR_LOW_THRES 1200
#define IR_HIGH_THRES 2000

void ir_adc_init();

uint16_t ir_adc_read();

void ADC_Handler();

uint16_t ball_blocking();

uint32_t ir_release_count(void);