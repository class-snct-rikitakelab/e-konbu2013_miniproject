
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h"
#include "logSend.h"
#include "math.h"
#include "tyreal_light_ver.h"

/*
 *	�e��ϐ���`
 */

//���C���g���[�X�p�ڕW�l
static unsigned int BLACK_VALUE;	//���l
static unsigned int WHITE_VALUE;	//���l
static unsigned int GRAY_VALUE;		//�D�F�l�i���݂͍��Ɣ��̕��ϒl�j

//�W���C���I�t�Z�b�g�l
static unsigned int GYRO_OFFSET;	

//�K���ݒ�p�x
#define ANGLEOFDOWN 95			//�~���ڕW�p�x
#define ANGLEOFUP 5				//�㏸�ڕW�p�x
#define ANGLEOFPUSH 115 			//���s�̒��ˏグ�ڕW�p�x
#define ANGLEOFSTAND 106		//�����ڕW�p�x

//���x���ߌW��
#define SPEED_COUNT 10

//�o�b�e���~���l
#define STEP_BATTERY 250		//�i�����m��
#define STOP_BATTERY 400

//�W���C���U���l
#define PM_GYRO 65				

//�ԗւ̉~��[cm]
#define CIRCUMFERENCE 25.8			//�ԗւ̉~��

#define CMD_START '1'    			//�����[�g�X�^�[�g�R�}���h(�ύX�֎~)
#define rapid_SPEED_UP_SIGNAL '3'

#define POSITION_X0 0
#define POSITION_Y0 0
#define THETA_0 0

#define WHEEL_R		41
#define MACHINE_W	162

#define RIGHT_ANGLE_LIGHT_VALUE GRAY_VALUE * 0.96		//���C������E�����ۂ̌��Z���T�̒l(570)
#define RIGHT_ANGLE_AIM 120				//��]�p�x(160)

/*
 *	��Ԓ�`
 */

//�V�X�e���S�̂̏��
typedef enum{
	RN_MODE_INIT, 					//�������
	RN_MODE_BALANCE,				//�|������ON
	RN_MODE_BALANCEOFF,				//�|������OFF
} RN_MODE;


typedef enum{
	RN_SETTINGMODE_START,		//�������
	RN_RUN,						//��{���s�i���C���g���[�X�j
	RN_STOP,					//��~
	RN_STEP_RAPID,
	RN_STEP_SHOCK,
	RN_STEP_SLOW,
	RN_STEP_STAY,
	RN_STEP_SECOND,
	RN_STEP_TURN_START,
	RN_STEP_TURN_LEFT,
	RN_STEP_TURN_FORWARD,
	RN_STEP_TURN_TAILUP,
	TYREAL,
	RN,
} RN_SETTINGMODE;


//�K���̏��
typedef enum{
	RN_TAILDOWN,				//�K���~��
	RN_TAILUP,					//�K���㏸
	RN_TAILPUSH,				//���s�̎����グ
	RN_TAILSTAND,				//���s�̒���
} RN_TAILMODE;

//�������
RN_MODE runner_mode = RN_MODE_INIT;
RN_SETTINGMODE setting_mode = RN_SETTINGMODE_START;
//RN_SETTINGMODE setting_mode = TYREAL;
RN_TAILMODE tail_mode = RN_TAILDOWN;