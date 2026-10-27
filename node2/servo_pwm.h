#include "sam.h"
#include "can.h"

#define POS_LEFT 0
#define POS_RIGHT 1
#define POS_NEUTRAL 4

#define PWM_CENTER 1.5
#define PWM_RIGHT 0.9
#define PWM_LEFT 2.1
#define PWM_DEF_CPRD 52500



void pwm_init();

void pwm_servo_ctrl();