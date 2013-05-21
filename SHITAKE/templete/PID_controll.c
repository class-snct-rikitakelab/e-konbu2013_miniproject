#include"PID_controll.h"
#include"LightSensorLPF.h"
#include "sample133.h"

int PID_controll(){

	static float hensa = 0;

	static const float Kp =	9.0;		//0.38;
	static const float Ki =	0.0	;	//0.06;
	static const float Kd =	5.0	;	//0.0027;
	static const float b = 0;

	static float i_hensa = 0;
	static float d_hensa = 0;
	static float bf_hensa = 0;

	static int cmd_turn=0;

	if(smoothed_ligh_sensor_value() >= (get_gray_zone()-10) && smoothed_ligh_sensor_value() <= (get_gray_zone()+10))
		hensa = get_gray_zone() - smoothed_ligh_sensor_value();
	else hensa = (get_color_gray()) - smoothed_ligh_sensor_value();

	hensa = hoge(hensa);
	/*
	if(hensa>45)hensa=45;
	if(hensa<-45)hensa=-45;
	*/
	i_hensa = i_hensa + (hensa * 0.004);

	d_hensa = (bf_hensa - hensa )/0.004;
	bf_hensa = hensa;

	cmd_turn = Kp*hensa + Ki*i_hensa + Kd*d_hensa + b;

	if (cmd_turn < -100) {
		cmd_turn = -100;
	}else if (cmd_turn > 100) {
		cmd_turn = 100;
	}

	return cmd_turn;

}

static 