#include "sam.h"
#include "can.h"
#include "encoder.h"
#include "time.h"

#define MOTOR_PWM_CPRD 840

void motor_drive_init();

void motor_move(uint16_t duty_cycle, uint16_t dir);

void motor_controller(CanMsg m, int16_t encoder, int16_t encoder_center, int16_t encoder_half);

void motor_calibrate_encoder(int32_t *encoder_center, int32_t *encoder_half);