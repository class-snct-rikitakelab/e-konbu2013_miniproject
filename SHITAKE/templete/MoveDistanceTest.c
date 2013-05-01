/*
 * sample08.c
 *
 * �o�����X���ė���
 * (c) COPYRIGHT 2010 Afrel., Inc.
 * All rights reserved
 */

#include "sample133.h"
#include "MoveDistance.h"
#include "Factory.h"

/*
 * �V�X�e���S�̂̏��
 */
typedef enum{
	RN_MODE_INIT, 		/* system initialize mode */
	RN_MODE_CONTROL,
	RN_MODE_STOP /* control mode */
} RN_MODE;


/*
 *�������
 */
RN_MODE runner_mode = RN_MODE_INIT;


/*
 *�J�E���^�̐錾
 */
DeclareCounter(SysTimerCnt);


/*
 *�^�X�N�̐錾
 */
DeclareTask(ActionTask);
DeclareTask(DisplayTask);


/*
 *�t���f�B�X�v���C�ɕ\������V�X�e�����ݒ�
 */
const char target_subsystem_name[] = "sample 133";


/*
 *��������
 */
void ecrobot_device_initialize(void)
{
	/* DO NOTHING*/ 
}


/*
 *��n������
 */
void ecrobot_device_terminate(void)
{
	ecrobot_set_motor_speed(NXT_PORT_B, 0);
	ecrobot_set_motor_speed(NXT_PORT_C, 0);
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
void user_1ms_isr_type2(void)
{
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
TASK(ActionTask)
{
	/* �W���C���Z���T�I�t�Z�b�g�p�ϐ� */
	static U32	gyro_offset = 0;
	/* �o�����X�R���g���[���֓n���R�}���h�p�ϐ� */
	S8  cmd_forward, cmd_turn;
	/* �o�����X�R���g���[������Ԃ���郂�[�^����p�ϐ� */
	S8	pwm_l, pwm_r;

	switch (runner_mode){
		case (RN_MODE_INIT):
			gyro_offset = (U32)ecrobot_get_gyro_sensor(NXT_PORT_S4);
			MoveDistance_init(&moveDistance);
			runner_mode = RN_MODE_CONTROL;
			break;

		case (RN_MODE_CONTROL):

			cmd_forward = 30;
			cmd_turn = 0;
		
			balance_control(
				(F32)cmd_forward,
				(F32)cmd_turn,
				(F32)ecrobot_get_gyro_sensor(NXT_PORT_S4),
				(F32)gyro_offset,
				(F32)nxt_motor_get_count(NXT_PORT_C),
				(F32)nxt_motor_get_count(NXT_PORT_B),
				(F32)ecrobot_get_battery_voltage(),
				&pwm_l,
				&pwm_r);
			nxt_motor_set_speed(NXT_PORT_C, pwm_l, 1);
			nxt_motor_set_speed(NXT_PORT_B, pwm_r, 1);
	
			if(MoveDistance_detect_move_distance(&moveDistance)> 30){
				ecrobot_sound_tone(440U, 500U,70U);
			}
			break;

		case (RN_MODE_STOP):
			cmd_forward = 0;
			cmd_turn = 0;
		
			balance_control(
				(F32)cmd_forward,
				(F32)cmd_turn,
				(F32)ecrobot_get_gyro_sensor(NXT_PORT_S4),
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

TASK(ActionTask2)
{
}


/******************************** END OF FILE ********************************/
