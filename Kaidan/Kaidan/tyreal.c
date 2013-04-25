#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ecrobot_interface.h"
#include "tyreal.h"


static	 int fw=50;
	int tn=0;
	int tail_angle=0;
	float Kp_a=3.212;
	float Ki_b=2.223;
	char int_string[INT_EXPRESS_RENGE];
	char float_string[25];
	char print_string[25];

typedef enum {
	ADJUST_FORWARD, ADJUST_TURN, ADJUST_TAIL_ANGLE,ADJUST_Kp_VAL,ADJUST_Ki_VAL,
} ADJUST_PARAM_STATE;

static ADJUST_PARAM_STATE adjust_param_state;



void display_show_string(char* string,int x,int y){

	display_goto_xy(x, y);
	display_string(string);
	display_update();
	
}


int get_int_digit(int val){
	int n=0;
	
	if(val<0){
	n=1;	
	}
	else{
	n=0;	
	}
	
	for(n; val != 0; n++){
		val= val / 10;
	}
	if(n==0){
	n=1;
	}
	
	return n; 
}

int change_int_param(int param){
	
	static int temp =0;
	
if((int)nxt_motor_get_count(NXT_PORT_C) - temp>0){
   		param=param+ADJUST_INT_STEP;
   	}
   	else if((int)nxt_motor_get_count(NXT_PORT_C) - temp<0){
   		param=param-ADJUST_INT_STEP;
   	}
   	
	temp=(int)nxt_motor_get_count(NXT_PORT_C);
   	
   	
   	systick_wait_ms(SET_PARAM_SPEED); /* 100msec */

return param;
}


float change_float_param(float param){
	
	static int temp =0;
	
	

if((int)nxt_motor_get_count(NXT_PORT_C) - temp>0){
	param=param+ADJUST_FLOAT_STEP/*0.001*/;	
//	param=(param+0.1)/*(float)ADJUST_FLOAT_STEP*/;
   	}
   	else if((int)nxt_motor_get_count(NXT_PORT_C) - temp<0){
   	param=param-ADJUST_FLOAT_STEP/*0.001*/;	
   		//param=param-0.1;/*(float)ADJUST_FLOAT_STEP);*/
   	}
   	
	temp=(int)nxt_motor_get_count(NXT_PORT_C);
   	
   	
   	systick_wait_ms(SET_PARAM_SPEED); // 100msec

return param;
}

void int_to_string(int int_val,char *int_string){
	
	int int_len=0;
	int_len=get_int_digit(int_val);
	sprintf(int_string,"%d",int_val);	
}



void float_to_string(float float_val,char *string){
int float_seisu_len=0;
int float_syosu_len=0;	
int seisu_val=0;	
int syosu_val=0;	


	
	seisu_val=(int)float_val;
	float_seisu_len =get_int_digit(seisu_val);
	
	
	syosu_val=abs((int)((float_val- (float)seisu_val)*1000));

	
	if(float_val>=0){
	sprintf(string,"%d.%-3d",abs(seisu_val),abs(syosu_val));
	
	
	}
	else{
	sprintf(string,"-%d.%-3d",abs(seisu_val),abs(syosu_val));

	
	}
}
	
void make_printf_string(char* val_string,char* text_msg,char *string){

	
	sprintf(string,"%s%s",text_msg,val_string);
}
	
int tyreal_trigger(){
	int result=0;

	if (ecrobot_is_RUN_button_pressed() == 1) {
				systick_wait_ms(100);
				result = 1;
			}
	return result;
}



void do_tyreal(){


  	if (ecrobot_is_RUN_button_pressed() == 1) {
		ecrobot_sound_tone(932, 512, VOL);
				systick_wait_ms(100);
				ecrobot_sound_tone(466, 256, VOL);
				systick_wait_ms(10);	
  		systick_wait_ms(10);
			if(adjust_param_state==ADJUST_FORWARD){
			adjust_param_state=ADJUST_TURN;	
			}
			else if(adjust_param_state==ADJUST_TURN){
			adjust_param_state=ADJUST_TAIL_ANGLE;	
			}
  		else if(adjust_param_state==ADJUST_TAIL_ANGLE){
			adjust_param_state=ADJUST_Kp_VAL;	
			}
   		else if(adjust_param_state==ADJUST_Kp_VAL){
			adjust_param_state=ADJUST_Ki_VAL;	
			}
  		else if(adjust_param_state==ADJUST_Ki_VAL){
			adjust_param_state=ADJUST_FORWARD;	
			}
  	}
  
   	switch(adjust_param_state) {
   		
   	case (ADJUST_FORWARD):	fw=change_int_param(fw);
  		break;
   	case  (ADJUST_TURN): tn=change_int_param(tn);
   			break;
   	case  (ADJUST_TAIL_ANGLE):  tail_angle=change_int_param(tail_angle);
   			break;
   		
   	case  (ADJUST_Kp_VAL): Kp_a=change_float_param(Kp_a);
   			break;
   	case  (ADJUST_Ki_VAL): Ki_b=change_float_param(Ki_b);
   			break;
   	default:
   		break;
   	}

   	display_clear(1);
   	int_to_string(fw,int_string);
   	make_printf_string(int_string,"FORWARD:",print_string);
   	display_show_string(print_string,0,0);
   	/*
   	int_to_string(tn,int_string);
   	make_printf_string(int_string,"TURN:",print_string);
   	display_show_string(print_string,0,1);
    
   	int_to_string(tail_angle,int_string);
   	make_printf_string(int_string,"TAIL_ANGLE:",print_string);
   	display_show_string(print_string,0,2);
    
  	
   	float_to_string(Kp_a,float_string);
   	make_printf_string(float_string,"Kp:",print_string);
   	display_show_string(print_string,0,3);
    
   	float_to_string(Ki_b,float_string);
   	make_printf_string(float_string,"Ki:",print_string);
   	display_show_string(print_string,0,4);
	*/
}
