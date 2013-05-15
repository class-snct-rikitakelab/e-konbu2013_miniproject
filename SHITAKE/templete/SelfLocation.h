#ifndef __SELFLOCATION
#define __SELFLOCATION

#include "ecrobot_interface.h"
#include "mymath.h"
#include "math.h"

/*
// �ԗ֔��a�A���s�̕�
#define WHEEL_R		41	//[mm]
#define MACHINE_W	162	//[mm]
*/
//�ǂ������������́H_________
// �ԗ֔��a�A���s�̕�
#define W_RADIUS	4.1	//[mm]
#define W_DIST		16.2//[mm]
//S___________________________ */

#define CIRCUMFERENCE	25.8	//�ԗւ̉~��

/* ���Ȉʒu����p�ϐ� */
static float x_r = 0;		//�ԑ̂�X���W
static float y_r = 0;		//�ԑ̂�Y���W
static float dist = 0;		//�ړ�����
static float theta = 0;		//�ԑ̂̊p�x
static float R = 0;			//�ȗ����a

static float dist_t = 0.0;
	static float theta_t = 0.0;

extern void self_location();

extern float getDistance();

extern float getXCoo();

extern float getYCoo();

extern float getTheta();

extern float getR();
void resetSelfLocation();

#endif
