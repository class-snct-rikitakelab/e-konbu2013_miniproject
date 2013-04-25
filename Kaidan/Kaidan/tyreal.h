#define VOL 20
#define SET_PARAM_SPEED 100
#define INT_EXPRESS_RENGE 11
#define FLOAT_EXPRESS_RENGE 5
#define TYRE_ANGLE_CHAR_NUM 8
#define ADJUST_INT_STEP 1
#define ADJUST_FLOAT_STEP 1


extern void do_tyreal();
extern int tyreal_trigger();

void display_show_string(char* string,int x,int y);
int get_int_digit(int val);
int change_int_param(int param);
float change_float_param(float param);
void int_to_string(int int_val,char *int_string);
void float_to_string(float float_val,char *string);
void make_printf_string(char* val_string,char* text_msg,char *string);

