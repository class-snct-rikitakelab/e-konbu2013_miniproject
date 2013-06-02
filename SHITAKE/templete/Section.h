#ifndef _Section_
#define _Section_

#define SEC1_LENGTH 42.0
#define SEC2_LENGTH 35.8
#define SEC3_LENGTH 42.0
#define SEC4_LENGTH 71.6
#define SEC5_LENGTH 22.6
#define SEC6_LENGTH 71.6

typedef enum sample_course_section{
	SEC1,
	SEC2,
	SEC3,
	SEC4,
	SEC5,
	SEC6,
};



void section_devide();
static int reach_next_section(float section_length);

#endif