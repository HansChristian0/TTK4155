#include"stdint.h"

void CLK_signal();

void adc_init(void);
uint8_t adc_read(uint8_t channel);
// pos_calibrate();
// pos_t pos_read(void);