#include "LightSensorLPF.h"

U16 smoothed_ligh_sensor_value(){

	static U16 light_sensor_value=0,light_sensor_value_buf=0;
	U16 smoothed_light_sensor_value=0;
	light_sensor_value=ecrobot_get_light_sensor(NXT_PORT_S3);
	smoothed_light_sensor_value=(light_sensor_value+light_sensor_value_buf)/2;
	light_sensor_value_buf=light_sensor_value;

}
