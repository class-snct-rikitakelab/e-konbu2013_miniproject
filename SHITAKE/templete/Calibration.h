#ifndef _Calibration_
#define _Calibration_


/*
 * キャリブレーションの状態
 */
typedef enum{
	RN_SETTINGMODE_GYRO_START,
	RN_SETTINGMODE_GYRO,
	RN_SETTINGMODE_GYRO_END,
	RN_SETTINGMODE_OK,
	RN_SETTINGMODE_OK_END,
	RN_SETTINGMODE_END,
	RN_SETTING_BLACK,
	RN_SETTING_WHITE,
	RN_SETTING_GRAY_ZONE
} RN_SETTINGMODE;

RN_SETTINGMODE setting_mode = RN_SETTINGMODE_GYRO_START;/* キャリブレーションの状態 */

void Calibration();

#endif