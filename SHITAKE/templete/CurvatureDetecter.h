#ifndef _CurvatureDetector_
#define _CurvatureDetector_

#include "mymath.h"
#include "math.h"
#include "ecrobot_interface.h"

// 車輪半径、走行体幅
#define W_RADIUS	4.1	//[mm]
#define W_DIST		16.2//[mm]
//S___________________________ */

#define CIRCUMFERENCE	25.8	//車輪の円周

/* 自己位置同定用変数 */
static float x_r = 0;		//車体のX座標
static float y_r = 0;		//車体のY座標

static float theta = 0;		//車体の角度
static float R = 0;			//曲率半径



void calcCurvature();
float getCurvature();


#endif