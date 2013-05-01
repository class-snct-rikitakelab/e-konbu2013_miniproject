/**
 *******************************************************************************
 **	FILE NAME : nxt_config.h
 **
 **	ABSTRUCT  : NXT device configration
 *******************************************************************************
 **/

#ifndef __nxt_confit_h__
#define __nxt_confit_h__

#include "ecrobot_interface.h"

/* NXT motor port configuration */
#define R_MOTOR_PORT	NXT_PORT_B
#define L_MOTOR_PORT	NXT_PORT_C

/* NXT Bluetooth configuration */
#define BT_PASS_KEY		"1234"

/* バランサーに使用するジャイロセンサを接続するポートを指定する（ポート4に接続する場合）*/
#define BLNU_PORT		NXT_PORT_S4

/* 障害物監視に使用する超音波センサを接続するポートを指定する(ポート2に接続する場合) */
#define BMU_PORT		NXT_PORT_S2

/* ライン監視に使用する光センサを接続するポートを指定する(ポート3に接続する場合) */
#define LMU_PORT		NXT_PORT_S3

/* バンパに使用するタッチセンサの接続ポートを指定する(ポート1に接続する場合) */
#define BU_PORT			 NXT_PORT_S1

#endif /* __nxt_confit_h__ */
