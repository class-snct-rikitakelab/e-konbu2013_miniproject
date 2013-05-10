#include "MoveDistance.h"

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h"

int MoveDistance_detect_move_distance(MoveDistance *this_MoveDistance)
{
	int result=0;
	S16 revL=0,revR=0;
	int move_distance = 0;
	revL = nxt_motor_get_count(NXT_PORT_C);
	revR = nxt_motor_get_count(NXT_PORT_B);	

	
	move_distance = CIRCUMFERENCE/360.0 * (((revL -this_MoveDistance->revL_buf) + (revR-this_MoveDistance-> revR_buf)) /2.0);
	return move_distance;
	revL = nxt_motor_get_count(NXT_PORT_C);
	revR = nxt_motor_get_count(NXT_PORT_B);	

	if(30/*this_MoveDistance->target_move_distance*/ <= CIRCUMFERENCE/360.0 * ((revL+revR)/2.0)){
		result = 1;
	}
	return result;
}

void MoveDistance_init(MoveDistance *this_MoveDistance)
{
	this_MoveDistance-> revL_buf=0;
	this_MoveDistance-> revR_buf=0;
}

void MoveDistance_reset_move_distance_measurement(MoveDistance *this_MoveDistance)
{
	this_MoveDistance-> revL_buf=nxt_motor_get_count(NXT_PORT_C);
	this_MoveDistance-> revR_buf=nxt_motor_get_count(NXT_PORT_B);
	this_MoveDistance-> target_move_distance=0;
}

void MoveDistance_set_target_distance(MoveDistance *this_MoveDistance,float target_distance)
{
	this_MoveDistance-> target_move_distance = target_distance;
}
