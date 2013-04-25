#include "ecrobot_interface.h"


int RUN_button_touched(){
	static U8 button_state = 0;
	int result=0;
	if(button_state==1 && ecrobot_is_RUN_button_pressed()==0 ){
		result = 1;
	}
	else {
		result = 0;
	}
	
	button_state= ecrobot_is_RUN_button_pressed();

	return result;
}