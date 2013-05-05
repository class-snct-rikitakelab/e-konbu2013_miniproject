/*
 * sample133.c
 *
 * バランスして立ち、ライントレースする、PID制御
 * (c) COPYRIGHT 2010 Afrel., Inc.
 * All rights reserved
 */

#include "sample133.h"
#include "MoveDistance.h"





static float hensa = 0;

/* 自己位置同定用　変数宣言 */
float d_theta_r;					/* 現在の右モータ回転角度 [rad] */
float d_theta_l;					/* 現在の左モータ回転角度 [rad] */
static float d_theta_r_t;			/* 1 ステップ前の右モータ回転角度 [rad] */
static float d_theta_l_t;			/* 1 ステップ前の左モータ回転角度 [rad] */
float velocity_r;					/* 右車輪移動速度 [cm/s] */
float velocity_l;					/* 左車輪移動速度 [cm/s] */
float velocity;						/* ロボットの移動速度 [cm/s] */
float omega;						/* ロボットの回転角角度 [rad/s] */
//static float position_x = POSITION_X0; /* ロボットの x 座標 */
//static float position_y = POSITION_Y0; /* ロボットの y 座標 */
//static float theta = THETA_0;		/* ロボットの姿勢角 */
unsigned short int l_val;			/* 光センサ値 */
int temp_x;							/* ロボットの x 座標（出力処理用） */
int temp_y;							/* ロボットの y 座標（出力処理用） */
static double omega_r;			//右車輪の回転角速度
static double omega_l;			//左車輪の回転角速度
unsigned char tx_buf[256]; /* 送信バッファ */



int light_white,light_black,color_gray;
/*
 * システム全体の状態
 */
typedef enum{
	RN_MODE_INIT, 		/* system initialize mode */
	RN_MODE_CONTROL,		/* control mode */
	RN_MODE_STOP /* control mode */
} RN_MODE;


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
	RN_SETTING_WHITE
} RN_SETTINGMODE;


/*
 *初期状態
 */

RN_MODE runner_mode = RN_MODE_INIT;					/* NXTway-GS mode */
RN_SETTINGMODE setting_mode = RN_SETTINGMODE_GYRO_START;/* キャリブレーションの状態 */


/*
 * ジャイロセンサオフセット計算用変数
 */
static U32	gyro_offset = 0;    /* gyro sensor offset value */
static U32	avg_cnt = 0;		/* average count to calc gyro offset */
static U32	cal_start_time;		/* calibration start time */


/* バランスコントロールへ渡すコマンド用変数 */
S8  cmd_forward, cmd_turn;
/* バランスコントロールから返されるモータ制御用変数 */
S8	pwm_l, pwm_r;
	
	
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


/*
 * ロボット制御用のプライベート関数
 */
int RN_move();

/*
 *カウンタの宣言
 */
DeclareCounter(SysTimerCnt);


/*
 *タスクの宣言
 */
DeclareTask(ActionTask);
DeclareTask(ActionTask2);
DeclareTask(DisplayTask);
DeclareTask(LogTask);


/*
 *液晶ディスプレイに表示するシステム名設定
 */
const char target_subsystem_name[] = "SHITAKE";


/*
 *初期処理
 */
void ecrobot_device_initialize(void)
{
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
	ecrobot_set_motor_rev(NXT_PORT_A,0);
	ecrobot_set_motor_rev(NXT_PORT_B,0);
	ecrobot_set_motor_rev(NXT_PORT_C,0);

	ecrobot_init_bt_slave("LEJOS-OSEK");
}


/*
 *後始末処理
 */
void ecrobot_device_terminate(void)
{
	ecrobot_set_motor_speed(NXT_PORT_B, 0);
	ecrobot_set_motor_speed(NXT_PORT_C, 0);
	ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
	ecrobot_term_bt_connection();
}


/*--------------------------------------------------------------------------*/
/* OSEK hooks                                                               */
/*--------------------------------------------------------------------------*/
void StartupHook(void){}
void ShutdownHook(StatusType ercd){}
void PreTaskHook(void){}
void PostTaskHook(void){}
void ErrorHook(StatusType ercd){}


/*--------------------------------------------------------------------------*/
/* Function to be invoked from a category 2 interrupt                       */
/*--------------------------------------------------------------------------*/
void user_1ms_isr_type2(void){
	StatusType ercd;
	/*
	 *  Increment OSEK Alarm System Timer Count
     */
	ercd = SignalCounter( SysTimerCnt );
	if( ercd != E_OK ){
		ShutdownOS( ercd );
	}
}


/*
 *タスク1用の関数
 */
TASK(ActionTask)
{

	switch (runner_mode){
		case (RN_MODE_INIT):
			RN_setting();
		
			cmd_forward = 0;
			cmd_turn = 0;

			break;

		case (RN_MODE_CONTROL):
			balance_control(
				(F32)cmd_forward,
				(F32)cmd_turn,
				(F32)ecrobot_get_gyro_sensor(NXT_PORT_S1),
				(F32)gyro_offset,
				(F32)nxt_motor_get_count(NXT_PORT_C),
				(F32)nxt_motor_get_count(NXT_PORT_B),
				(F32)ecrobot_get_battery_voltage(),
				&pwm_l,
				&pwm_r);
			nxt_motor_set_speed(NXT_PORT_C, pwm_l, 1);
			nxt_motor_set_speed(NXT_PORT_B, pwm_r, 1);
			break;

		default:
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
			break;
	}
	TerminateTask();
}


/*
 *表示用の関数
 */
TASK(DisplayTask)
{
	/* モニタにシステム名を表示する */
	ecrobot_status_monitor(target_subsystem_name);

	/* 自タスクの終了 */
	/* 具体的には，自タスクを実行状態から休止状態に移行させ，*/
	/* タスクの終了時に行うべき処理を行う */
	TerminateTask();
}



/*
 *タスク1用の関数
 */
TASK(ActionTask2)
{
	
	static const float Kp = 5.0;
	//static float hensa = 0;
	static float speed = 0;

	cmd_forward = 50;
	
	color_gray=(light_white + light_black)/2;

	hensa = (color_gray) - ecrobot_get_light_sensor(NXT_PORT_S3);
	//hensa = LIGHT_THRESHOLD - ecrobot_get_light_sensor(NXT_PORT_S3);
	/* 白いと＋値 */
	/* 黒いと－値 */

	cmd_turn = Kp*hensa;
	if (cmd_turn < -100) {
		cmd_turn = -100;
	}else if (cmd_turn > 100) {
		cmd_turn = 100;
	}

	/* 自タスクの終了 */
	/* 具体的には，自タスクを実行状態から休止状態に移行させ，*/
	/* タスクの終了時に行うべき処理を行う */
	//logSend(0,0,0,hensa,0,0,0,0);

	BLNU_turn(cmd_turn);


	TerminateTask();
}

TASK(LogTask)
{
	logSend(0,0,gyro_offset,cmd_turn,hensa,0,0,0);		//ログ取り
	TerminateTask();
}


/*
 *プライベート関数の実装
 */
void RN_setting()
{
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
		default:
			break;
	}
}


void RN_set_gyro_start()
{
	/* ジャイロセンサの設定を始める */
	if (ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE) {
		ecrobot_sound_tone(880, 512, 30);

		/* ジャイロセンサの値を計算するための開始時間をセットする */
		cal_start_time = ecrobot_get_systick_ms();
		setting_mode = RN_SETTINGMODE_GYRO;
	}
}




void RN_set_gyro()
{
	/* ジャイロセンサの設定をする */
	gyro_offset += (U32)ecrobot_get_gyro_sensor(NXT_PORT_S1);
	avg_cnt++;
	
	/* 1秒経過したら、ジャイロセンサのオフセット値の平均値を計算し、次の状態に遷移する。 */
	if ((ecrobot_get_systick_ms() - cal_start_time) >= 1000U) {
		gyro_offset /= avg_cnt;

		ecrobot_sound_tone(440U, 500U, 30U);

		setting_mode = RN_SETTINGMODE_GYRO_END;
	}

	if ((ecrobot_get_systick_ms() - cal_start_time) >= 1000U) {
	
			
		ecrobot_sound_tone(440U, 500U, 30U);

		setting_mode = RN_SETTINGMODE_GYRO_END;
	}
}


void RN_set_gyro_end()
{
	/* バンパを離すと次の状態に遷移する */
	if (ecrobot_get_touch_sensor(NXT_PORT_S4) != TRUE) {
		setting_mode = RN_SETTING_BLACK;
	}
}

void RN_set_color_black()
{
	/*if(ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE){
		light_black=ecrobot_get_light_sensor(NXT_PORT_S3);
		ecrobot_sound_tone(880, 512, 30);
		systick_wait_ms(500);
		setting_mode = RN_SETTING_WHITE;
	}*/
	while(1){
		if(ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE)
		{
			ecrobot_sound_tone(906, 512, 30);
			light_black=ecrobot_get_light_sensor(NXT_PORT_S3);
			systick_wait_ms(500);
			break;
		}
	}
	setting_mode = RN_SETTING_WHITE;

}

void RN_set_color_white()
{
	/*if(ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE){
		light_white=ecrobot_get_light_sensor(NXT_PORT_S3);
		ecrobot_sound_tone(880, 512, 30);
		systick_wait_ms(500);
		setting_mode = RN_SETTINGMODE_OK;
	}*/

	while(1){
		if(ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE)
		{
			ecrobot_sound_tone(906, 512, 30);
			light_white=ecrobot_get_light_sensor(NXT_PORT_S3);
			systick_wait_ms(500);
			break;
		}
	}
	setting_mode = RN_SETTINGMODE_OK;

}


void RN_set_ok()
{	
	/* スタート位置にロボットを置き、バンパを押すと次の状態に遷移する。 */
	if (ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE) {
		ecrobot_sound_tone(880, 512, 30);
		setting_mode = RN_SETTINGMODE_OK_END;
	}
}


void RN_set_ok_end()
{
	/* バンパを離すと次の状態に遷移する(設定モードを終了する）*/
	if (ecrobot_get_touch_sensor(NXT_PORT_S4) != TRUE) {
		ecrobot_sound_tone(880, 512, 30);
		setting_mode = RN_SETTINGMODE_END;
	}
}

/******************************** END OF FILE ********************************/
