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



//�ړ������N���X

typedef struct {
	S16 revL_buf,revR_buf; //���s�����v���J�n�n�_�ł̃��[�^��]�p�ۑ��p
}MoveDistance;

int detect_move_distance();

void MoveDistance_init(MoveDistance *this_MoveDistance);	

//���݂̃��[�^��]�p��ۑ�
void MoveDistance_reset_move_distance_measurement(MoveDistance *this_MoveDistance);

//�ړ�������Ԃ�
int MoveDistance_detect_move_distance(MoveDistance *this_MoveDistance);

#endif
