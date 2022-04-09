#ifndef MOTOR_H
#define MOTOR_H
//====================================//
// �C���N���[�h                        //
//====================================//
#include "r_smc_entry.h"
//====================================//
// �V���{����`						   //
//====================================//
#define SERVO_LIMIT		430		    // �T�[�{���~�b�gAD�l�}
#define TGR_MOTOR       5998		// �W�F�l�������W�X�^�����l(�쓮���[�^)
#define TGR_SERVO       5998		// �W�F�l�������W�X�^�����l(�T�[�{)

#define FORWARD			0		// ���]
#define REVERSE			1		// �t�]
#define BRAKE           0		// �u���[�L���[�h
#define FREE            1		// �t���[���[�h

// �����(pwm3,MTIOC0A)
#define DIR_RL			PORTC.PODR.BIT.B4		// ���[�^��]����(0:���] 1:�t�])
#define SR_RL			PORTC.PODR.BIT.B5		// 0:�t���[���[�h  1:�u���[�L���[�h
#define PWM_RL_OUT	    MTU3.TGRA = pwmrl		// PWM�o��
// �E���(pwm4,MTIOC0C)
#define DIR_RR			PORTC.PODR.BIT.B2
#define SR_RR			PORTC.PODR.BIT.B3
#define PWM_RR_OUT	    MTU3.TGRC = pwmrr
//�������火�v�ύX
// ���O��
#define DIR_FL			PORTE.PODR.BIT.B6
#define SR_FL			PORTE.PODR.BIT.B7
#define PWM_FL_OUT	    MTU0.TGRB = pwmfl
// �E�O��
#define DIR_FR			PORTA.PODR.BIT.B6
#define SR_FR			PORTA.PODR.BIT.B7
#define PWM_FR_OUT	    MTU0.TGRD = pwmfr
//====================================//
// �O���[�o���ϐ��̐錾					//
//====================================//
// ���[�^�[�֘A
extern int8_t	accele_fR;		// �E�O���[�^�[PWM�l
extern int8_t	accele_fL;		// ���O���[�^�[PWM�l
extern int8_t	accele_rR;		// �E�ヂ�[�^�[PWM�l
extern int8_t	accele_rL;		// ���ヂ�[�^�[PWM�l
extern int8_t	sPwm;		    // �T�[�{���[�^�[PWM�l
//====================================//
// �v���g�^�C�v�錾					   //
//====================================//
// ���[�^�[�֘A
void motor_R_mode(uint8_t rl, uint8_t rr );
void motor_F_mode(uint8_t fl, uint8_t fr );
void motor_f( int8_t accelefL, int8_t accelefR );
void motor_r( int8_t accelerL, int8_t accelerR );

// �T�[�{�֘A
void servoPwmOut( int8_t pwm );
#endif