#include "Balancer.h"

void Balance_running(){

	balance_control(
				(F32)forward,
				(F32)turn,
				(F32)ecrobot_get_gyro_sensor(NXT_PORT_S1),
				(F32)gyro_offset,
				(F32)nxt_motor_get_count(NXT_PORT_C),
				(F32)nxt_motor_get_count(NXT_PORT_B),
				(F32)ecrobot_get_battery_voltage(),
				&pwm_l,
				&pwm_r);
				nxt_motor_set_speed(NXT_PORT_C, pwm_l, 1);
				nxt_motor_set_speed(NXT_PORT_B, pwm_r, 1);
}

void Set_forward(int forward_buf){

	forward = forward_buf;
}

void Set_turn(int turn_buf){

	turn = turn_buf;
}