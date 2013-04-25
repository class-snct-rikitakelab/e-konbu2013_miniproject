#include "ecrobot_interface.h"
#include "tyreal_light_ver.h"
#include "NXTButton.h"

static	 
	char float_string[9];

typedef enum {
	ADJUST_Kp_VAL,ADJUST_Ki_VAL,ADJUST_Kd_VAL,
} ADJUST_PARAM_STATE;

static ADJUST_PARAM_STATE adjust_param_state = ADJUST_Kd_VAL;


float round_n(float val,int n){
	float result=0;
	int temp=0;

	temp =(int)(val*my_pow(10,n));
	result=(float)temp/my_pow(10,n);
	
	return result;

}

float my_pow(float val,float beki){
	float result=1;
	int i=0;
	if(beki<0){
	beki*=-1;
		for(i=0;i<beki;++i){
		result/=val;
		}
	}
	else{
		for(i=0;i<beki;++i){
		result*=val;
	}
	}
	return result;

}


void display_show_string(char* string,int x,int y){

	display_goto_xy(x, y);
	display_string(string);
	display_update();
	
}


float change_float_param(float param){
	
	static int temp =0;

if((int)nxt_motor_get_count(NXT_PORT_C) - temp>0){
	
	
	param=param+ADJUST_FLOAT_STEP;	
   	}
   	else if((int)nxt_motor_get_count(NXT_PORT_C) - temp<0){
   	param=param-ADJUST_FLOAT_STEP;	
   	}
	systick_wait_ms(VALUE_CHANGE_SPEED);
	temp=(int)nxt_motor_get_count(NXT_PORT_C);
   	
	param= round_n(param,3);
	




return param;
}



void float_to_string(float float_val,char *string){
int seisu_len=0;
int int_val=0;
int divisor =0;
int i;

seisu_len = get_int_digit((int)float_val);
int_val = (float_val*100);
divisor = my_pow(10,seisu_len+1);
	
	
if (int_val >= 0)
string[0] = ' ';
else {
string[0] = '-';
int_val *= -1;
}

for(i=1;i<=seisu_len+3;++i){
	if(i==seisu_len+1){
		string[i]='.';
	}
	else {
	string[i] = (unsigned char)(int_val / divisor) + '0';
	int_val %= divisor;
	divisor /=10;
	}
}
string[i] = '\0';


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

	
int tyreal_trigger(){
	int result=0;

	if (ecrobot_is_RUN_button_pressed() == 1) {
				systick_wait_ms(100);
				result = 1;
			}
	return result;
}



void do_tyreal(float *Kp_t,float *Ki_t,float *Kd_t){

	//ó‘Ô‘JˆÚ
  	if ( RUN_button_touched() == 1) {
		ecrobot_sound_tone(932, 512, VOL);
		systick_wait_ms(100);
		
		if(adjust_param_state==ADJUST_Kp_VAL){
			adjust_param_state=ADJUST_Ki_VAL;
			}
  		else if(adjust_param_state==ADJUST_Ki_VAL){
			adjust_param_state=ADJUST_Kd_VAL;	
			}
		else if(adjust_param_state==ADJUST_Kd_VAL){
			adjust_param_state=ADJUST_Kp_VAL;	
			}
  	}

	
   	switch(adjust_param_state) {
   	case  (ADJUST_Kp_VAL): *Kp_t=change_float_param(*Kp_t);
		display_clear(0);

		float_to_string(*Kp_t,float_string);
		display_show_string("Kp seleted",0,0);
		display_show_string(float_string,0,1);

		float_to_string(*Ki_t,float_string);
		display_show_string("Ki",0,2);
		display_show_string(float_string,0,3);


		float_to_string(*Kd_t,float_string);
		display_show_string("Kd",0,4);
 		display_show_string(float_string,0,5);	


   			break;
   	case  (ADJUST_Ki_VAL): *Ki_t=change_float_param(*Ki_t);
		display_clear(0);
		float_to_string(*Kp_t,float_string);
		display_show_string("Kp",0,0);
		display_show_string(float_string,0,1);

		float_to_string(*Ki_t,float_string);
		display_show_string("Ki selected ",0,2);
		display_show_string(float_string,0,3);

		float_to_string(*Kd_t,float_string);
		display_show_string("Kd",0,4);
 		display_show_string(float_string,0,5);	


   			break;
	case  (ADJUST_Kd_VAL): *Kd_t=change_float_param(*Kd_t);
   		display_clear(0);

		float_to_string(*Kp_t,float_string);
		display_show_string("Kp",0,0);
		display_show_string(float_string,0,1);

		float_to_string(*Ki_t,float_string);
		display_show_string("Ki",0,2);
		display_show_string(float_string,0,3);

		float_to_string(*Kd_t,float_string);
		display_show_string("Kd selected ",0,4);
 		display_show_string(float_string,0,5);
	
		break;

   	default:
   		break;
   	}
	
	

	
}
