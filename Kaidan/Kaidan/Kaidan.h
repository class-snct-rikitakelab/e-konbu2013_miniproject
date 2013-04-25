
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h"
#include "logSend.h"
#include "math.h"
#include "tyreal_light_ver.h"

/*
 *	各種変数定義
 */

//ライントレース用目標値
static unsigned int BLACK_VALUE;	//黒値
static unsigned int WHITE_VALUE;	//白値
static unsigned int GRAY_VALUE;		//灰色値（現在は黒と白の平均値）

//ジャイロオフセット値
static unsigned int GYRO_OFFSET;	

//尻尾設定角度
#define ANGLEOFDOWN 95			//降下目標角度
#define ANGLEOFUP 5				//上昇目標角度
#define ANGLEOFPUSH 115 			//走行体跳ね上げ目標角度
#define ANGLEOFSTAND 106		//直立目標角度

//速度調節係数
#define SPEED_COUNT 10

//バッテリ降下値
#define STEP_BATTERY 250		//段差検知時
#define STOP_BATTERY 400

//ジャイロ振幅値
#define PM_GYRO 65				

//車輪の円周[cm]
#define CIRCUMFERENCE 25.8			//車輪の円周

#define CMD_START '1'    			//リモートスタートコマンド(変更禁止)
#define rapid_SPEED_UP_SIGNAL '3'

#define POSITION_X0 0
#define POSITION_Y0 0
#define THETA_0 0

#define WHEEL_R		41
#define MACHINE_W	162

#define RIGHT_ANGLE_LIGHT_VALUE GRAY_VALUE * 0.96		//ラインから脱した際の光センサの値(570)
#define RIGHT_ANGLE_AIM 120				//回転角度(160)

/*
 *	状態定義
 */

//システム全体の状態
typedef enum{
	RN_MODE_INIT, 					//初期状態
	RN_MODE_BALANCE,				//倒立制御ON
	RN_MODE_BALANCEOFF,				//倒立制御OFF
} RN_MODE;


typedef enum{
	RN_SETTINGMODE_START,		//初期状態
	RN_RUN,						//基本走行（ライントレース）
	RN_STOP,					//停止
	RN_STEP_RAPID,
	RN_STEP_SHOCK,
	RN_STEP_SLOW,
	RN_STEP_STAY,
	RN_STEP_SECOND,
	RN_STEP_TURN_START,
	RN_STEP_TURN_LEFT,
	RN_STEP_TURN_FORWARD,
	RN_STEP_TURN_TAILUP,
	TYREAL,
	RN,
} RN_SETTINGMODE;


//尻尾の状態
typedef enum{
	RN_TAILDOWN,				//尻尾降下
	RN_TAILUP,					//尻尾上昇
	RN_TAILPUSH,				//走行体持ち上げ
	RN_TAILSTAND,				//走行体直立
} RN_TAILMODE;

//初期状態
RN_MODE runner_mode = RN_MODE_INIT;
RN_SETTINGMODE setting_mode = RN_SETTINGMODE_START;
//RN_SETTINGMODE setting_mode = TYREAL;
RN_TAILMODE tail_mode = RN_TAILDOWN;