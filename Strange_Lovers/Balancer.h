#ifndef _BALANCER_
#define _BALANCER_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h"

static S8 forward = 20;
static S8 turn = 0;
S8	pwm_l, pwm_r;

static U32	gyro_offset = 600;

extern void Balance_running();
extern void Set_forward(int forward_buf);
extern void Set_turn(int turn_buf);

#endif