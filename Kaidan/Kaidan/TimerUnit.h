/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * TimerUnit.h
 * タイマクラス
 *
 * クラス名: TimerUnit(TU)
 * 属性: timerResult, timerCount, interval, timeOut, timerStart
 * 操作: start, finish, is_start, is_timeout
 * 関連: common
 */

#ifndef __TimerUnit_h__
#define __TimerUnit_h__

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h" /* 倒立振子制御用ヘッダファイル */
#include "logSend.h"

/**
 * タイマの監視を開始する
 * @param msec タイムアウトまでの時間(msec)
 */
extern void TU_start(int msec);

/**
 * タイマの監視を終了する
 */
extern void TU_finish(void);

/**
 * タイマの監視状態を示す
 * @return int 監視中はTRUE(1)，監視中ではないときはFALSE(0)を返す
 */
extern int TU_is_start(void);

/**
 * タイマの状態を示す
 * @return int タイムアウトのときはTRUE(1)を返し，それ以外はFALSE(0)を返す
 */
extern int TU_is_timeout(void);

#endif /**__TimerUnit_h__ */
