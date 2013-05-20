#ifndef __SELFLOCATION
#define __SELFLOCATION

#include "ecrobot_interface.h"
#include "mymath.h"
#include "math.h"

/*
// 車輪半径、走行体幅
#define WHEEL_R		41	//[mm]
#define MACHINE_W	162	//[mm]
*/
//どっちが正しいの？_________
// 車輪半径、走行体幅
#define W_RADIUS	4.1	//[mm]
#define W_DIST		16.2//[mm]
//S___________________________ */

#define CIRCUMFERENCE	25.8	//車輪の円周

/* 自己位置同定用変数 */
static float x_r = 0;		//車体のX座標
static float y_r = 0;		//車体のY座標
static float dist = 0;		//移動距離
static float theta = 0;		//車体の角度
static float R = 0;			//曲率半径

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
