#include "PIDControl.h"
#include "CurvatureDetecter.h"

static float RKp=1.2,RKi=0,RKd=0.03;


int curvature_PID_control(float target_R,float current_R)
{
	static float bf_dev = 0.0;

	float dev =  current_R - target_R;
	float i_dev = i_dev + (dev * 0.004);
	float d_dev = (dev - bf_dev) / 0.004;
	bf_dev = dev;

	S8 turn = RKp * dev + RKi * i_dev + RKd * d_dev;
	if (-100 > turn) {
		turn = -100;
	}
	else if (100 < turn) {
		turn = 100;
	}
	return turn;
}
