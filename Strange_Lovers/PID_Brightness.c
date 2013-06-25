#include "PID_Brightness.h"

void PID_Brightness(){

	static float hensa = 0;

	static const float Kp =	5.0;
	static const float Ki =	0.0	;
	static const float Kd =	3.0	;
	static const float b = 0;

	static float i_hensa = 0;
	static float d_hensa = 0;
	static float bf_hensa = 0;

	static int turn=0;

	hensa = target_value - ecrobot_get_light_sensor(NXT_PORT_S3);

	i_hensa = i_hensa + (hensa * 0.004);

	d_hensa = (bf_hensa - hensa )/0.004;
	bf_hensa = hensa;

	turn = Kp*hensa + Ki*i_hensa + Kd*d_hensa + b;

	if (turn < -100) {
		turn = -100;
	}else if (turn > 100) {
		turn = 100;
	}

	Set_turn(turn);
	Balance_running();

}