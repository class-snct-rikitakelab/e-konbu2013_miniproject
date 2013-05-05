#ifndef __MoveDistance
#define __MoveDistance

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h"


 /* �ԗ֔��a�A���s�̕�*/
#define W_RADIUS	4.1	//[mm]
#define W_DIST		16.2//[mm]
//�ԗւ̉~��[cm]
#define CIRCUMFERENCE 25.8			//�ԗւ̉~��


int MoveDistance_detect_move_distance();

void MoveDistance_create();	

//�ړ�������Ԃ�
int MoveDistance_detect_move_distance();



//���̃N���X���炵���Ă΂�Ȃ�private�Ȋ֐�

//���݂̃��[�^��]�p��ۑ�
static void MoveDistance_reset_move_distance_measurement();


#endif
