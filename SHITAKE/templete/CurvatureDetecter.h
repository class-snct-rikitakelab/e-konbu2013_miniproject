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


void calc_curvature();
float get_curvature();


#endif