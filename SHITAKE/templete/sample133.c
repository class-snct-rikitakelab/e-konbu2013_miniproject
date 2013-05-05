/*
 * sample133.c
 *
 * �o�����X���ė����A���C���g���[�X����APID����
 * (c) COPYRIGHT 2010 Afrel., Inc.
 * All rights reserved
 */

#include "sample133.h"
#include "MoveDistance.h"





static float hensa = 0;

/* ���Ȉʒu����p�@�ϐ��錾 */
float d_theta_r;					/* ���݂̉E���[�^��]�p�x [rad] */
float d_theta_l;					/* ���݂̍����[�^��]�p�x [rad] */
static float d_theta_r_t;			/* 1 �X�e�b�v�O�̉E���[�^��]�p�x [rad] */
static float d_theta_l_t;			/* 1 �X�e�b�v�O�̍����[�^��]�p�x [rad] */
float velocity_r;					/* �E�ԗֈړ����x [cm/s] */
float velocity_l;					/* ���ԗֈړ����x [cm/s] */
float velocity;						/* ���{�b�g�̈ړ����x [cm/s] */
float omega;						/* ���{�b�g�̉�]�p�p�x [rad/s] */
//static float position_x = POSITION_X0; /* ���{�b�g�� x ���W */
//static float position_y = POSITION_Y0; /* ���{�b�g�� y ���W */
//static float theta = THETA_0;		/* ���{�b�g�̎p���p */
unsigned short int l_val;			/* ���Z���T�l */
int temp_x;							/* ���{�b�g�� x ���W�i�o�͏����p�j */
int temp_y;							/* ���{�b�g�� y ���W�i�o�͏����p�j */
static double omega_r;			//�E�ԗւ̉�]�p���x
static double omega_l;			//���ԗւ̉�]�p���x
unsigned char tx_buf[256]; /* ���M�o�b�t�@ */



int light_white,light_black,color_gray;
/*
 * �V�X�e���S�̂̏��
 */
typedef enum{
	RN_MODE_INIT, 		/* system initialize mode */
	RN_MODE_CONTROL,		/* control mode */
	RN_MODE_STOP /* control mode */
} RN_MODE;


/*
 * �L�����u���[�V�����̏��
 */
typedef enum{
	RN_SETTINGMODE_GYRO_START,
	RN_SETTINGMODE_GYRO,
	RN_SETTINGMODE_GYRO_END,
	RN_SETTINGMODE_OK,
	RN_SETTINGMODE_OK_END,
	RN_SETTINGMODE_END,
	RN_SETTING_BLACK,
	RN_SETTING_WHITE
} RN_SETTINGMODE;


/*
 *�������
 */

RN_MODE runner_mode = RN_MODE_INIT;					/* NXTway-GS mode */
RN_SETTINGMODE setting_mode = RN_SETTINGMODE_GYRO_START;/* �L�����u���[�V�����̏�� */


/*
 * �W���C���Z���T�I�t�Z�b�g�v�Z�p�ϐ�
 */
static U32	gyro_offset = 0;    /* gyro sensor offset value */
static U32	avg_cnt = 0;		/* average count to calc gyro offset */
static U32	cal_start_time;		/* calibration start time */


/* �o�����X�R���g���[���֓n���R�}���h�p�ϐ� */
S8  cmd_forward, cmd_turn;
/* �o�����X�R���g���[������Ԃ���郂�[�^����p�ϐ� */
S8	pwm_l, pwm_r;
	
	
/*
 * �L�����u���[�V�����p�̃v���C�x�[�g�֐�
 */
void RN_setting();
void RN_set_gyro_start();
void RN_set_gyro();
void RN_set_gyro_end();
void RN_set_ok();
void RN_set_ok_end();
void RN_set_color_black();
void RN_set_color_white();


/*
 * ���{�b�g����p�̃v���C�x�[�g�֐�
 */
int RN_move();

/*
 *�J�E���^�̐錾
 */
DeclareCounter(SysTimerCnt);


/*
 *�^�X�N�̐錾
 */
DeclareTask(ActionTask);
DeclareTask(ActionTask2);
DeclareTask(DisplayTask);
DeclareTask(LogTask);


/*
 *�t���f�B�X�v���C�ɕ\������V�X�e�����ݒ�
 */
const char target_subsystem_name[] = "SHITAKE";


/*
 *��������
 */
void ecrobot_device_initialize(void)
{
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
	ecrobot_set_motor_rev(NXT_PORT_A,0);
	ecrobot_set_motor_rev(NXT_PORT_B,0);
	ecrobot_set_motor_rev(NXT_PORT_C,0);

	ecrobot_init_bt_slave("LEJOS-OSEK");
}


/*
 *��n������
 */
void ecrobot_device_terminate(void)
{
	ecrobot_set_motor_speed(NXT_PORT_B, 0);
	ecrobot_set_motor_speed(NXT_PORT_C, 0);
	ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
	ecrobot_term_bt_connection();
}


/*--------------------------------------------------------------------------*/
/* OSEK hooks                                                               */
/*--------------------------------------------------------------------------*/
void StartupHook(void){}
void ShutdownHook(StatusType ercd){}
void PreTaskHook(void){}
void PostTaskHook(void){}
void ErrorHook(StatusType ercd){}


/*--------------------------------------------------------------------------*/
/* Function to be invoked from a category 2 interrupt                       */
/*--------------------------------------------------------------------------*/
void user_1ms_isr_type2(void){
	StatusType ercd;
	/*
	 *  Increment OSEK Alarm System Timer Count
     */
	ercd = SignalCounter( SysTimerCnt );
	if( ercd != E_OK ){
		ShutdownOS( ercd );
	}
}


/*
 *�^�X�N1�p�̊֐�
 */
TASK(ActionTask)
{

	switch (runner_mode){
		case (RN_MODE_INIT):
			RN_setting();
		
			cmd_forward = 0;
			cmd_turn = 0;

			break;

		case (RN_MODE_CONTROL):
			balance_control(
				(F32)cmd_forward,
				(F32)cmd_turn,
				(F32)ecrobot_get_gyro_sensor(NXT_PORT_S1),
				(F32)gyro_offset,
				(F32)nxt_motor_get_count(NXT_PORT_C),
				(F32)nxt_motor_get_count(NXT_PORT_B),
				(F32)ecrobot_get_battery_voltage(),
				&pwm_l,
				&pwm_r);
			nxt_motor_set_speed(NXT_PORT_C, pwm_l, 1);
			nxt_motor_set_speed(NXT_PORT_B, pwm_r, 1);
			break;

		default:
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
			break;
	}
	TerminateTask();
}


/*
 *�\���p�̊֐�
 */
TASK(DisplayTask)
{
	/* ���j�^�ɃV�X�e������\������ */
	ecrobot_status_monitor(target_subsystem_name);

	/* ���^�X�N�̏I�� */
	/* ��̓I�ɂ́C���^�X�N�����s��Ԃ���x�~��ԂɈڍs�����C*/
	/* �^�X�N�̏I�����ɍs���ׂ��������s�� */
	TerminateTask();
}



/*
 *�^�X�N1�p�̊֐�
 */
TASK(ActionTask2)
{
	
	static const float Kp = 5.0;
	//static float hensa = 0;
	static float speed = 0;

	cmd_forward = 50;
	
	color_gray=(light_white + light_black)/2;

	hensa = (color_gray) - ecrobot_get_light_sensor(NXT_PORT_S3);
	//hensa = LIGHT_THRESHOLD - ecrobot_get_light_sensor(NXT_PORT_S3);
	/* �����Ɓ{�l */
	/* �����Ɓ|�l */

	cmd_turn = Kp*hensa;
	if (cmd_turn < -100) {
		cmd_turn = -100;
	}else if (cmd_turn > 100) {
		cmd_turn = 100;
	}

	/* ���^�X�N�̏I�� */
	/* ��̓I�ɂ́C���^�X�N�����s��Ԃ���x�~��ԂɈڍs�����C*/
	/* �^�X�N�̏I�����ɍs���ׂ��������s�� */
	//logSend(0,0,0,hensa,0,0,0,0);

	BLNU_turn(cmd_turn);


	TerminateTask();
}

TASK(LogTask)
{
	logSend(0,0,gyro_offset,cmd_turn,hensa,0,0,0);		//���O���
	TerminateTask();
}


/*
 *�v���C�x�[�g�֐��̎���
 */
void RN_setting()
{
	switch (setting_mode){
		case (RN_SETTINGMODE_GYRO_START):
			RN_set_gyro_start();
			break;

		case (RN_SETTINGMODE_GYRO):
			RN_set_gyro();
			break;

		case (RN_SETTINGMODE_GYRO_END):
			RN_set_gyro_end();
			break;

		case (RN_SETTINGMODE_OK):
			RN_set_ok();
			break;

		case (RN_SETTINGMODE_OK_END):
			RN_set_ok_end();
			break;

		case (RN_SETTINGMODE_END):
			runner_mode = RN_MODE_CONTROL;
			break;

		case (RN_SETTING_BLACK):
			RN_set_color_black();
			break;

		case (RN_SETTING_WHITE):
			RN_set_color_white();
			break;
		default:
			break;
	}
}


void RN_set_gyro_start()
{
	/* �W���C���Z���T�̐ݒ���n�߂� */
	if (ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE) {
		ecrobot_sound_tone(880, 512, 30);

		/* �W���C���Z���T�̒l���v�Z���邽�߂̊J�n���Ԃ��Z�b�g���� */
		cal_start_time = ecrobot_get_systick_ms();
		setting_mode = RN_SETTINGMODE_GYRO;
	}
}




void RN_set_gyro()
{
	/* �W���C���Z���T�̐ݒ������ */
	gyro_offset += (U32)ecrobot_get_gyro_sensor(NXT_PORT_S1);
	avg_cnt++;
	
	/* 1�b�o�߂�����A�W���C���Z���T�̃I�t�Z�b�g�l�̕��ϒl���v�Z���A���̏�ԂɑJ�ڂ���B */
	if ((ecrobot_get_systick_ms() - cal_start_time) >= 1000U) {
		gyro_offset /= avg_cnt;

		ecrobot_sound_tone(440U, 500U, 30U);

		setting_mode = RN_SETTINGMODE_GYRO_END;
	}

	if ((ecrobot_get_systick_ms() - cal_start_time) >= 1000U) {
	
			
		ecrobot_sound_tone(440U, 500U, 30U);

		setting_mode = RN_SETTINGMODE_GYRO_END;
	}
}


void RN_set_gyro_end()
{
	/* �o���p�𗣂��Ǝ��̏�ԂɑJ�ڂ��� */
	if (ecrobot_get_touch_sensor(NXT_PORT_S4) != TRUE) {
		setting_mode = RN_SETTING_BLACK;
	}
}

void RN_set_color_black()
{
	/*if(ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE){
		light_black=ecrobot_get_light_sensor(NXT_PORT_S3);
		ecrobot_sound_tone(880, 512, 30);
		systick_wait_ms(500);
		setting_mode = RN_SETTING_WHITE;
	}*/
	while(1){
		if(ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE)
		{
			ecrobot_sound_tone(906, 512, 30);
			light_black=ecrobot_get_light_sensor(NXT_PORT_S3);
			systick_wait_ms(500);
			break;
		}
	}
	setting_mode = RN_SETTING_WHITE;

}

void RN_set_color_white()
{
	/*if(ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE){
		light_white=ecrobot_get_light_sensor(NXT_PORT_S3);
		ecrobot_sound_tone(880, 512, 30);
		systick_wait_ms(500);
		setting_mode = RN_SETTINGMODE_OK;
	}*/

	while(1){
		if(ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE)
		{
			ecrobot_sound_tone(906, 512, 30);
			light_white=ecrobot_get_light_sensor(NXT_PORT_S3);
			systick_wait_ms(500);
			break;
		}
	}
	setting_mode = RN_SETTINGMODE_OK;

}


void RN_set_ok()
{	
	/* �X�^�[�g�ʒu�Ƀ��{�b�g��u���A�o���p�������Ǝ��̏�ԂɑJ�ڂ���B */
	if (ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE) {
		ecrobot_sound_tone(880, 512, 30);
		setting_mode = RN_SETTINGMODE_OK_END;
	}
}


void RN_set_ok_end()
{
	/* �o���p�𗣂��Ǝ��̏�ԂɑJ�ڂ���(�ݒ胂�[�h���I������j*/
	if (ecrobot_get_touch_sensor(NXT_PORT_S4) != TRUE) {
		ecrobot_sound_tone(880, 512, 30);
		setting_mode = RN_SETTINGMODE_END;
	}
}

/******************************** END OF FILE ********************************/
