
#include "SelfLocation.h"



//自己位置同定関数
void self_location(){
	
	float fi_l = (float)nxt_motor_get_count(NXT_PORT_C);
	float fi_r = (float)nxt_motor_get_count(NXT_PORT_B);
	float dist_l = deg2rad(fi_l * W_RADIUS);
	float dist_r = deg2rad(fi_r * W_RADIUS);

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

void resetSelfLocation(){
	dist_t = 0;
	theta_t = 0;
	R =0;
	dist=0;
	theta=0;
	x_r = 0;		//車体のX座標
	 y_r = 0;
}
//ゲッター群
float getDistance( )
{
	return dist;
}

float getXCoo( )
{
	return x_r;
}

float getYCoo( )
{
	return y_r;
}

float getTheta( )
{
	return theta;
}
float getR(){

	return R;
}