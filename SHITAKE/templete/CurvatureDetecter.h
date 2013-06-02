#ifndef _CurvatureDetector_
#define _CurvatureDetector_

#include "mymath.h"
#include "math.h"
#include "ecrobot_interface.h"

// �ԗ֔��a�A���s�̕�
#define W_RADIUS	4.1	//[mm]
#define W_DIST		16.2//[mm]
//S___________________________ */

#define CIRCUMFERENCE	25.8	//�ԗւ̉~��

/* ���Ȉʒu����p�ϐ� */
static float x_r = 0;		//�ԑ̂�X���W
static float y_r = 0;		//�ԑ̂�Y���W

static float theta = 0;		//�ԑ̂̊p�x
static float R = 0;			//�ȗ����a



void calcCurvature();
float getCurvature();


#endif