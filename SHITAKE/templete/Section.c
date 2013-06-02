#include "Section.h"
#include "MoveDistance.h"
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "stdlib.h"

static enum sample_course_section sample_sections;
static struct sample_course_sections *current_section;


void create_sample_corse_sections(){
	struct sample_course_sections *p = (struct sample_course_sections*)malloc(sizeof(struct sample_course_sections));
	p->name = SEC1;
	p->section_length = SEC1_LENGTH;
	p->next_section = (struct sample_course_sections*)malloc(sizeof(struct sample_course_sections));
	
	current_section = p;

	p = current_section->next_section ;
	p->name = SEC2;
	p->section_length = SEC2_LENGTH;
	p->next_section = (struct sample_course_sections*)malloc(sizeof(struct sample_course_sections));
	



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