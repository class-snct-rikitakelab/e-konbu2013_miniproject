#include "section.h"

void section(){

set_distance(MoveDistance_detect_move_distance(&moveDistance));

switch (section_info) {

	case  SECTION_ONE_BEFORE_GRAY : 
		if(12 <	MoveDistance_detect_move_distance(&moveDistance)){
			ecrobot_sound_tone(880, 512, 30);
			change_target_light_value(0);
			MoveDistance_reset_move_distance_measurement(&moveDistance);
			section_info = SECTION_ONE_ON_GRAY;
		}
	case SECTION_ONE_ON_GRAY:
		if(15 <	MoveDistance_detect_move_distance(&moveDistance)){
			ecrobot_sound_tone(880, 512, 30);
			change_target_light_value(1);
			MoveDistance_reset_move_distance_measurement(&moveDistance);
			section_info = SECTION_ONE_AFTER_GRAY;
		}
	case SECTION_ONE_AFTER_GRAY:
		if(60 <	MoveDistance_detect_move_distance(&moveDistance)){
			ecrobot_sound_tone(880, 512, 30);
			change_target_light_value(0);
			MoveDistance_reset_move_distance_measurement(&moveDistance);
			section_info = SECTION_ONE_AFTER_GRAY;
			
		
	break;

	
}

/*
						if(15 <	MoveDistance_detect_move_distance(&moveDistance)){
						break;
				}
				color_gray = (light_white*0.5)+(light_black*0.5);
*/


return 0;
}




}