#include "Section.h"
#include "MoveDistance.h"
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

static enum sample_course_section sample_sections;


void create_sample_corse_sections(){


}
void section_devide(void){
	
	

	switch(sample_sections) {
	
	case SEC1:
		if(reach_next_section(SEC1_LENGTH)){
			sample_sections = SEC2;
		}
		break;
	case SEC2:
			if(reach_next_section(SEC2_LENGTH)){
			sample_sections = SEC3;
		}
		break;
	case SEC3:
			if(reach_next_section(SEC3_LENGTH)){
			sample_sections = SEC4;
		}
		break;
	case SEC4:
			if(reach_next_section(SEC4_LENGTH)){
				
			sample_sections = SEC5;
		}
		break;
	case SEC5:
			if(reach_next_section(SEC5_LENGTH)){
			sample_sections = SEC6;
		}
		break;
	case SEC6:
			if(reach_next_section(SEC6_LENGTH)){
			sample_sections = SEC1;
		}
	break;
	
	};

}
int reach_next_section(float section_length){

	if(section_length  <  MoveDistance_detect_move_distance()){
		MoveDistance_reset_move_distance_measurement();
		ecrobot_sound_tone(440,30,30);
		return 1;
	}
	else {
		return 0;
	}
}
		