#include "Runner.h"

void RN_mode_change();
void RN_run();

//走行状態初期化
RN_STATE rn_state = RN_CALIBRATION;

//カウンタの宣言
DeclareCounter(SysTimerCnt);

//タスクの宣言
DeclareTask(ActionTask);

//初期処理
void ecrobot_device_initialize(void){

	ecrobot_set_motor_rev(NXT_PORT_A,0);
	ecrobot_set_motor_rev(NXT_PORT_B,0);
	ecrobot_set_motor_rev(NXT_PORT_C,0);

}

//後始末処理
void ecrobot_device_terminate(void){

	ecrobot_set_motor_speed(NXT_PORT_B, 0);
	ecrobot_set_motor_speed(NXT_PORT_C, 0);

}



TASK(ActionTask){

	RN_mode_change();
	RN_run();
	TerminateTask();
}

void RN_mode_change(){

	switch (rn_state){
		case (RN_CALIBRATION):
			if(ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE){
				rn_state = RN_RUNNING;
			}
			break;

		case (RN_RUNNING):
			break;

		case (RN_COMPLATION):
			break;
	}

}
void RN_run(){

	switch (rn_state){
		case (RN_CALIBRATION):

			break;

		case (RN_RUNNING):
			Balance_running();
			break;

		case (RN_COMPLATION):
			break;
	}

}