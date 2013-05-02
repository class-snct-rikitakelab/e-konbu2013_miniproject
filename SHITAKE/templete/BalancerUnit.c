/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * BalancerUnit.c
 * バランサーユニットクラス
 *
 * クラス名: BalancerUnit(BLNU)
 * 属性: cmd_forward, cmd_turn, gyro_offset
 * 操作: pre, post, forward, backward, turn_right, turn_left, stop,
 *       set_gyro_offset, balance_control
 * 関連: common, nxt_config, balancer
 */

#include "BalancerUnit.h"

#define Max_VALUE 100
#define Min_VALUE -100

#define Robot_WIDTH 157	/* ロボットの横幅 mm */
#define Wheel_DIAMETER 80	/* タイヤの直径 mm */

static BOOL BLNU_motor_angle_control; /* 角度制御開始フラグ */
static F32 start_l_motor_rev; /* 角度制御開始時のモータ角度(左） */
static F32 start_r_motor_rev; /* 角度制御開始時のモータ角度(右） */
static F32 finish_motor_rev; /* 角度制御目標のモータ角度 */

/**
 * バランスコントロール
 */
void BLNU_balance_control(void);

/**
 * BalancerUnitの初期化処理
 */
void BLNU_pre(void) {
	ecrobot_set_motor_rev(L_MOTOR_PORT, 0);
	ecrobot_set_motor_rev(R_MOTOR_PORT, 0);
	balance_init();
	BLNU_motor_angle_control = false;
}

/**
 * BalancerUnitの終了処理
 */
void BLNU_post(void) {
	/* DO NOTHING*/
}

static BOOL BLNU_balance_startflg = FALSE; /* バランス開始フラグ */
static S8 BLNU_cmd_forward = 0; /* 前進コマンド値 */
static S8 BLNU_cmd_turn = 0; /* 回転コマンド値 */
static U32 BLNU_gyro_offset = 0; /* ジャイロセンサオフセット値 */

/**
 * 前進する
 */
void BLNU_forward(S8 command) {
	if (Max_VALUE < command) {
		command = Max_VALUE;
	}

	if (0 > command) {
		command = command * (-1);
	}

	BLNU_cmd_forward = command;
}

/**
 * 後退する
 */
void BLNU_backward(S8 command) {
	if (Min_VALUE > command) {
		command = Min_VALUE;
	}

	if (0 < command) {
		command = command * (-1);
	}

	BLNU_cmd_forward = command;
}

/**
 * 右に回転する
 */
void BLNU_turn_right(S8 command) {
	if (Max_VALUE < command) {
		command = Max_VALUE;
	}

	if (0 > command) {
		command = command * (-1);
	}

	BLNU_cmd_turn = command;
}

/**
 * 左に回転する
 */
void BLNU_turn_left(S8 command) {
	if (command < Min_VALUE) {
		command = Min_VALUE;
	}

	if (0 < command) {
		command = command * (-1);
	}

	BLNU_cmd_turn = command;
}

/**
 * 左右に回転する
 */
void BLNU_turn(S8 command) {
	BLNU_cmd_turn = command;
}

/**
 * 停止する
 */
void BLNU_stop(void) {
	BLNU_cmd_forward = 0;
	BLNU_cmd_turn = 0;
}

/**
 * ジャイロセンサオフセット値の設定
 */
void BLNU_set_gyro_offset(void) {
	BLNU_gyro_offset = (U32) ecrobot_get_gyro_sensor(BLNU_PORT);
}

/**
 * 指定した角度だけ、ロボットを右回転させる
 * 引数angleは、ロボットの回転角度
 */
extern BOOL BLNU_angle_turn_right(F32 angle) {

	/** モータ回転コントロールを開始するときには、
	 *  最初の回転角度を取得する */
	if (BLNU_motor_angle_control == false) {
		BLNU_motor_angle_control = true;
		start_l_motor_rev = nxt_motor_get_count(L_MOTOR_PORT); /* 左のモータの回転角度 */
		start_r_motor_rev = nxt_motor_get_count(R_MOTOR_PORT); /* 右のモータの回転角度 */
		F32 a = Robot_WIDTH; /* ロボットの横幅 mm */
		F32 b = Wheel_DIAMETER; /* タイヤの直径 mm */
		finish_motor_rev = 2* (a /b)*angle; /* angle度回転させるために必要な左右のモータの回転角度の合計値 */
	}

	/** 右に回転する */
	BLNU_cmd_forward = 0;
	BLNU_cmd_turn = 50;

	/** 現在の左右のモータ回転角度の合計値が、目標値を超えたらtrueを返す */
	if((nxt_motor_get_count(L_MOTOR_PORT) - start_l_motor_rev)
			+ (start_r_motor_rev - nxt_motor_get_count(R_MOTOR_PORT)) >=finish_motor_rev){
		BLNU_motor_angle_control = false;
		return true;
	}else{
		return false;
	}
}

		/**
		 * 指定した角度だけ、ロボットを左回転させる
		 * 引数angleは、ロボットの回転角度
		 */
extern BOOL BLNU_angle_turn_left(F32 angle) {

	/** モータ回転コントロールを開始するときには、
	 *  最初の回転角度を取得する */
	if (BLNU_motor_angle_control == false) {
		BLNU_motor_angle_control = true;
		start_l_motor_rev = nxt_motor_get_count(L_MOTOR_PORT); /* 左のモータの回転角度 */
		start_r_motor_rev = nxt_motor_get_count(R_MOTOR_PORT); /* 右のモータの回転角度 */
		F32 a = Robot_WIDTH; /* ロボットの横幅 mm */
		F32 b = Wheel_DIAMETER; /* タイヤの直径 mm */
		finish_motor_rev = 2* (a /b)*angle; /* angle度回転させるために必要な左右のモータの回転角度の合計値 */
	}

	/** 左に回転する */
	BLNU_cmd_forward = 0;
	BLNU_cmd_turn = -50;

	/** 現在の左右のモータ回転角度の合計値が、目標値を超えたらtrueを返す */
	if((nxt_motor_get_count(R_MOTOR_PORT) - start_r_motor_rev)
	+ (start_l_motor_rev - nxt_motor_get_count(L_MOTOR_PORT)) >= finish_motor_rev) {
		BLNU_motor_angle_control = false;
		return true;
	} else {
		return false;
	}
}

/**
 * バランスコントロール
 */
void BLNU_balance_control(void) {
	S8 pwm_l, pwm_r;

	/* NXTway-GS C API balance control function (has to be invoked in 4msec period) */
	balance_control((F32) BLNU_cmd_forward, (F32) BLNU_cmd_turn,
			(F32) ecrobot_get_gyro_sensor(BLNU_PORT), (F32) BLNU_gyro_offset,
			(F32) nxt_motor_get_count(L_MOTOR_PORT), (F32) nxt_motor_get_count(
					R_MOTOR_PORT), (F32) ecrobot_get_battery_voltage(), &pwm_l,
			&pwm_r);
	nxt_motor_set_speed(L_MOTOR_PORT, pwm_l, 1);
	nxt_motor_set_speed(R_MOTOR_PORT, pwm_r, 1);
}

/**
 * バランスコントロール開始フラグセット
 */
extern void BLNU_balance_start(void) {
	BLNU_balance_startflg = TRUE;
}

/******************************************************************************
 * TASK			: BalanceTask
 * ARGUMENT		: none
 * RETURN		: none
 * DESCRIPTION 	: 4msec periodical Task
 *****************************************************************************/
TASK(BalanceTask)
{
	if (TRUE == BLNU_balance_startflg) {
		BLNU_balance_control();
	}

	TerminateTask();
}

/******************************** END OF FILE ********************************/
