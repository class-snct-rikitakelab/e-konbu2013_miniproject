#include "PIDControl.h"
#include "CurvatureDetecter.h"
#include "BrightnessLPF.h"

static float RKp=2.2,RKi=0.00,RKd=0.03;

static const float Kp =1.2;
static const float Ki =	0.06;
static const float Kd =	0.027;


int curvature_PID_control(float target_R,float current_R)
{
	static float bf_dev = 0.0;

	float dev =  target_R - current_R;
	float i_dev = i_dev + (dev * 0.004);
	float d_dev = (dev - bf_dev) / 0.004;
	bf_dev = dev;

	int turn = RKp * dev + RKi * i_dev + RKd * d_dev;
	if (-100 > turn) {
		turn = -100;
	}
	else if (100 < turn) {
		turn = 100;
	}
	return turn;
}


int light_PID_control(float target_bright){
	float hensa;

	hensa = target_bright - get_brightness_LPF();
	
	if(hensa>45)hensa=45;
	if(hensa<-45)hensa=-45;

	
	static float i_hensa = 0;
	static float d_hensa = 0;
	static float bf_hensa = 0;

	i_hensa = i_hensa + (hensa * 0.004);

	d_hensa = (bf_hensa - hensa )/0.004;
	bf_hensa = hensa;

	S8 turn = Kp*hensa + Ki*i_hensa + Kd*d_hensa;

	if (turn < -100) {
		turn = -100;
	}else if (turn > 100) {
		turn = 100;
	}

	return turn;

}