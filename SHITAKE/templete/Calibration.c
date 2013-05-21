#include"Calibration.h"

/*
 * キャリブレーション用のプライベート関数
 */
void RN_setting();
void RN_set_gyro_start();
void RN_set_gyro();
void RN_set_gyro_end();
void RN_set_ok();
void RN_set_ok_end();
void RN_set_color_black();
void RN_set_color_white();
void RN_set_color_gray();


void Calibration(){
	RN_setting();

}

/*
 * キャリブレーション用のプライベート関数
 */
void RN_setting(){
	
	switch (setting_mode){
		case (RN_SETTINGMODE_GYRO_START):
			RN_set_gyro_start();
			break;

		case (RN_SETTINGMODE_GYRO):
			RN_set_gyro();
			break;

		case (RN_SETTINGMODE_GYRO_END):
			RN_set_gyro_end();
			break;

		case (RN_SETTINGMODE_OK):
			RN_set_ok();
			break;

		case (RN_SETTINGMODE_OK_END):
			RN_set_ok_end();
			break;

		case (RN_SETTINGMODE_END):
			runner_mode = RN_MODE_CONTROL;
			break;

		case (RN_SETTING_BLACK):
			RN_set_color_black();
			break;

		case (RN_SETTING_WHITE):
			RN_set_color_white();
			break;

		case (RN_SETTING_GRAY_ZONE):
			RN_set_color_gray();
			break;
		default:
			break;
	}

}
void RN_set_gyro_start();
void RN_set_gyro();
void RN_set_gyro_end();
void RN_set_ok();
void RN_set_ok_end();
void RN_set_color_black();
void RN_set_color_white();
void RN_set_color_gray();
