#include "PIDControl.h"
#include "CurvatureDetecter.h"

static float RKp=1.2,RKi=0,RKd=0.03;
static const float Kp =	9.0;		//0.38;
static const float Ki =	0.0	;	//0.06;
static const float Kd =	5.0	;	//0.0027;


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


int light_PID_control(float target_bright){
	static int brightness=0,brightness_buf=0;
	float hensa;

	brightness=ecrobot_get_light_sensor(NXT_PORT_S3);

		/*•½ŠŠ‰»*/
	brightness=(brightness+brightness_buf)/2;
	 hensa = target_bright - brightness;
	
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

	brightness_buf=brightness;

	return turn;

}