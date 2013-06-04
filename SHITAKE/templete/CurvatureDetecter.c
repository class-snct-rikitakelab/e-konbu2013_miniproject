#include "CurvatureDetecter.h"


/* 自己位置同定用変数 */
static float x_r = 0;		//車体のX座標
static float y_r = 0;		//車体のY座標

static float theta = 0;		//車体の角度
static float R = 0;			//曲率半径


void calc_curvature(){
	
	float fi_l = (float)nxt_motor_get_count(NXT_PORT_C);
	float fi_r = (float)nxt_motor_get_count(NXT_PORT_B);
	float dist_l = deg2rad(fi_l * W_RADIUS);
	float dist_r = deg2rad(fi_r * W_RADIUS);
	static float dist_t = 0,theta_t=0;
	static float dist = 0;		//移動距離


	dist = (dist_l + dist_r) / 2.0;
	theta = W_RADIUS / W_DIST * (fi_r - fi_l);
	x_r += (dist - dist_t) * sin(deg2rad(theta));
	y_r += (dist - dist_t) * cos(deg2rad(theta));
	if(!(theta == theta_t)){
		R = rad2deg((dist - dist_t) / (theta - theta_t));
	}
	else{
		R= 0.0;
	}
	dist_t = dist;
	theta_t = theta;
}

float get_curvature(){
	return R;
}

