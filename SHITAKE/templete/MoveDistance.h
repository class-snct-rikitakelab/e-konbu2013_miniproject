#ifndef __MoveDistance
#define __MoveDistance

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h"

 /* �ԗ֔��a�A���s�̕�*/
#define W_RADIUS	4.1	//[mm]
#define W_DIST		16.2//[mm]


//�ړ������N���X

typedef struct {
	
float target_move_distance;

}MoveDistance;

int detect_move_distance();

void MoveDistance_init(MoveDistance *this_MoveDistance);	

#endif
