/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * TimerUnit.c
 * タイマクラス
 *
 * クラス名: TimerUnit(TU)
 * 属性: timerResult, timerCount, interval, timeOut, timerStart
 * 操作: start, finish, isStart, isTimeout
 * 関連: common
 */

#include "TimerUnit.h"

/** タイマの状態を表す変数 タイムアウトしたときはTRUE(1)，タイムアウトしていないときはFALSE(0)を示す */
static int TU_timerResult = FALSE;
/** タイマのカウント値を表す変数 */
static int TU_timerCount = 0;
/** タイマ間隔(ms)を表す変数 タスクの起動周期と一致する */
static int TU_interval = 10;
/** タイアウト(ms)を表す変数 */
static int TU_timeOut = 0;
/** タイマの監視状態を表す変数 監視中はTRUE(1)，監視中ではないときはFALSE(0)を示す */
static int TU_timerStart = FALSE;

/**
 * タイマの監視を開始する
 * @param msec タイムアウトまでの時間(msec)
 */
void TU_start(int msec) {
	TU_timerCount = 0;
	TU_timerResult = FALSE;
	TU_timeOut = msec;
	TU_timerStart = TRUE;
}

/**
 * タイマの監視を終了する
 */
void TU_finish(void) {
	TU_timerCount = 0;
	TU_timerResult = FALSE;
	TU_timeOut = 0;
	TU_timerStart = FALSE;
}

/**
 * タイマの監視状態を示す
 * @return int 監視中はTRUE(1)，監視中ではないときはFALSE(0)を返す
 */
int TU_is_start(void) {
	return TU_timerStart;
}

/**
 * タイマの状態を示す
 * @return int タイムアウトのときはTRUE(1)を返し，それ以外はFALSE(0)を返す
 */
int TU_is_timeout(void) {
	return TU_timerResult;
}

/**
 * タイマ監視を行うAlramCallback
 */
ALARMCALLBACK(CountTimer)
{
	if (TU_timerStart) {
		if (TU_timerCount == (TU_timeOut / TU_interval)) {
			TU_timerCount = 0;
			TU_timerResult = TRUE;
		}
		TU_timerCount++;
	}

	/** タスクを終了する */
	TerminateTask();
}

