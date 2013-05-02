#define VOL 20
#define ADJUST_FLOAT_STEP 0.01 //’l‚Ì‘Œ¸’l‚Ìw’è
#define VALUE_CHANGE_SPEED 150

extern void do_tyreal(float *Kp_t,float *Ki_t,float *Kd_t);
extern int tyreal_trigger();

void display_show_string(char* string,int x,int y);
int get_int_digit(int val);
//int change_int_param(int param);
float change_float_param(float param);
//void int_to_string(int int_val,char *int_string);
void float_to_string(float float_val,char *string);
void make_printf_string(char* val_string,char* text_msg,char *string);

float my_pow(float val,float beki);
