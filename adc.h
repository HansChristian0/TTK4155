#include"stdint.h"

void CLK_signal();

void adc_init(void);
uint8_t adc_read(uint8_t channel);
volatile uint8_t* pos_calibrate();

enum pos_t{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL,
};

// pos_t pos_read(void);

int8_t pos_read_percent_x(uint8_t* calibration, uint8_t curr_pos_x);
int8_t pos_read_percent_y(uint8_t* calibration, uint8_t curr_pos_y);