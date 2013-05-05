#include "MoveDistance.h"

 //走行距離計測開始地点でのモータ回転角保存用
static S16 revL_buf,revR_buf;

int MoveDistance_detect_move_distance()
{
	int result=0;
	S16 revL=0,revR=0;
	int move_distance = 0;
	revL = nxt_motor_get_count(NXT_PORT_C);
	revR = nxt_motor_get_count(NXT_PORT_B);	

	
	move_distance = CIRCUMFERENCE/360.0 * (((revL - revL_buf) + (revR- revR_buf)) /2.0);
	return move_distance;
}

void MoveDistance_create()
{
	 revL_buf=0;
	 revR_buf=0;
}

static void MoveDistance_reset_move_distance_measurement()
{
	revL_buf=nxt_motor_get_count(NXT_PORT_C);
	revR_buf=nxt_motor_get_count(NXT_PORT_B);
}
