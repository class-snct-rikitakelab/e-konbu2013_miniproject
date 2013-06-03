#ifndef _Section_
#define _Section_

#define SEC1_LENGTH 42.0
#define SEC2_LENGTH 35.8
#define SEC3_LENGTH 42.0
#define SEC4_LENGTH 71.6
#define SEC5_LENGTH 22.6
#define SEC6_LENGTH 71.6

#define SEC1_R 0.0
#define SEC2_R 22.2
#define SEC3_R 0.0
#define SEC4_R 22.2
#define SEC5_R 22.2
#define SEC6_R 22.2



typedef enum sample_course_section{
	SEC1,
	SEC2,
	SEC3,
	SEC4,
	SEC5,
	SEC6,
};

typedef struct sample_course_sections{
	enum sample_course_section name;
	float section_length;
	float R;
	struct sample_course_sections *next_section;
};


void section_devide();
void create_sample_corse_sections();
float get_current_section_R();
static int reach_next_section(float section_length);
static struct sample_course_sections* get_next_section(struct sample_course_sections *current_section);

#endif
