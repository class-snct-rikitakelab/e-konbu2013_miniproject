#include "BrightnessLPF.h"


S16 get_brightness_LPF(){
	static int brightness=0,brightness_buf=0;

	brightness=ecrobot_get_light_sensor(NXT_PORT_S3);

		/*•½ŠŠ‰»*/
	brightness=(brightness+brightness_buf)/2;
	brightness_buf=brightness;
	return brightness;
}
