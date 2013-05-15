#include "mymath.h"
/*
 *	Šeí’è‹`
*/

#define PI 3.141592



float deg2rad(float degree){
	float radian = PI / 180.0 * degree;
	return radian;
}

float rad2deg(float radian){
	float degree = 180.0 / PI * radian;
	return degree;
}

float abs(float value)
{
	float result=0;

	if (value>=0){
	result=value;
	}
	else {
	result = -value;
	}
	
	return result;
}



