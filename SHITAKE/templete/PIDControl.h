#ifndef _PIDControl
#define _PIDControl


#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"

int light_PID_control(float target_bright);
int curvature_PID_control(float target_R,float current_R);

#endif 