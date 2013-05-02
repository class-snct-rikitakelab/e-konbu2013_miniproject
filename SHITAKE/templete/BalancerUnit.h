/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * BalancerUnit.h
 * バランサーユニットクラス
 *
 * クラス名: BalancerUnit(BLNU)
 * 属性: cmd_forward, cmd_turn, gyro_offset
 * 操作: pre, post, forward, backward, turn_right, turn_left, stop,
 *       set_gyro_offset, balance_control
 * 関連: common, nxt_config, balancer
 */

#ifndef __BalancerUnit_h__
#define __BalancerUnit_h__

#include "common.h"
#include "nxt_config.h"
#include "balancer.h"

/**
 * BalancerUnitの初期化処理
 */
extern void BLNU_pre(void);

/**
 * BalancerUnitの終了処理
 */
extern void BLNU_post(void);

/**
 * 前進する
 */
extern void BLNU_forward(S8 command);

/**
 * 後退する
 */
extern void BLNU_backward(S8 command);

/**
 * 右に回転する
 */
extern void BLNU_turn_right(S8 command);

/**
 * 左に回転する
 */
extern void BLNU_turn_left(S8 command);

/**
 * 左右に回転する
 */
extern void BLNU_turn(S8 command);

/**
 * 停止する
 */
extern void BLNU_stop(void);

/**
 * ジャイロセンサオフセット値の設定
 */
extern void BLNU_set_gyro_offset(void);

/**
 * バランスコントロール開始フラグセット
 */
extern void BLNU_balance_start(void);

/**
 * 指定した角度だけ、ロボットを右回転させる
 * 引数angleは、ロボットの回転角度
 */
extern BOOL BLNU_angle_turn_right(F32 angle);

/**
 * 指定した角度だけ、ロボットを左回転させる
 * 引数angleは、ロボットの回転角度
 */
extern BOOL BLNU_angle_turn_left(F32 angle);

#endif /**__BalancerUnit_h__ */
