#include "sam.h"
#include "can.h"
#include "encoder.h"

#define MOTOR_PWM_CPRD 840

void motor_drive_init();

void motor_move(uint16_t duty_cycle, uint16_t dir);

void motor_controller(CanMsg m);