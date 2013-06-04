#include "Section.h"
#include "MoveDistance.h"
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "stdlib.h"

static enum sample_course_section sample_sections;
static struct sample_course_sections *current_section;
static struct sample_course_sections sec1;
static struct sample_course_sections sec2;
static struct sample_course_sections sec3;
static struct sample_course_sections sec4;
static struct sample_course_sections sec5;
static struct sample_course_sections sec6;

void create_sample_corse_sections(){
	current_section = &sec1;

	sec1.name=SEC1;
	sec1.next_section = &sec2;
	sec1.section_length = SEC1_LENGTH;
	sec1.R  = SEC1_R;
	
	sec2.name=SEC2;
	sec2.next_section = &sec3;
	sec2.section_length = SEC2_LENGTH;
	sec2.R  = SEC2_R;
	
	sec3.name=SEC3;
	sec3.next_section = &sec4;
	sec3.section_length = SEC3_LENGTH;
	sec3.R  = SEC2_R;
	
	sec4.name=SEC4;
	sec4.next_section = &sec5;
	sec4.section_length = SEC4_LENGTH;
	sec4.R  = SEC4_R;
	
	sec5.name=SEC5;
	sec5.next_section = &sec6;
	sec5.section_length = SEC5_LENGTH;
	sec5.R  = SEC5_R;
	
	sec6.name=SEC6;
	sec6.next_section = &sec1;
	sec6.section_length = SEC6_LENGTH;
	sec6.R  = SEC6_R;
	
}
void section_devide(void){
	
	if(reach_next_section(current_section->section_length)){
		//‰¹–Â‚ç‚·
		current_section = get_next_section(current_section);
	}
	
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

static struct sample_course_sections* get_next_section(struct sample_course_sections *current_section){
	return current_section->next_section;
}

float get_current_section_R(){
	return current_section->R;
}