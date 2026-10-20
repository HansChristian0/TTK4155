#include "joy_to_can.h"


void joystick_to_can(){
    uint8_t curr_pos_x = 0;
    uint8_t curr_pos_y = 0;
    int8_t percent_pos_x = 0;
    int8_t percent_pos_y = 0;
    pos_t direction = NEUTRAL;

    curr_pos_x = adc_read(1);
    curr_pos_y = adc_read(0);
    uint8_t*  calibration = hard_cal();
    percent_pos_x = pos_read_percent_x(calibration, curr_pos_x);
    percent_pos_y = pos_read_percent_y(calibration, curr_pos_y);
    direction = pos_read(percent_pos_x, percent_pos_y);

    Dataframe m = {.id = 1, .data_len = 1, .data = direction};

    can_com_transmit(&m,0x01);
}