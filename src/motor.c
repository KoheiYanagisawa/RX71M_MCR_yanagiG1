//=====================================
// �C���N���[�h
//=====================================
#include "motor.h"
//=====================================
// �O���[�o���ϐ��̐錾
//=====================================//
int8_t	accele_fR;		// �E�O���[�^�[PWM�l
int8_t	accele_fL;		// ���O���[�^�[PWM�l
int8_t	accele_rR;		// �E�ヂ�[�^�[PWM�l
int8_t	accele_rL;		// ���ヂ�[�^�[PWM�l
int8_t	sPwm;		    // �T�[�{���[�^�[PWM�l

///////////////////////////////////////////////////////////////////////////
// ���W���[���� motor_R_mode
// �����T�v     �O�փu���[�L��t���[���[�h�̐؂�ւ�
// ����         rl, rr(0:�t���[���[�h  1:�u���[�L���[�h)
// �߂�l       �Ȃ�
///////////////////////////////////////////////////////////////////////////
void motor_R_mode(uint8_t rl, uint8_t rr )
{
	SR_RL = rl;
	SR_RR = rr;
}
///////////////////////////////////////////////////////////////////////////
// ���W���[���� motor_F_mode
// �����T�v     ��փu���[�L��t���[���[�h�̐؂�ւ�
// ����         fl, fr(0:�t���[���[�h  1:�u���[�L���[�h)
// �߂�l       �Ȃ�
///////////////////////////////////////////////////////////////////////////
void motor_F_mode(uint8_t fl, uint8_t fr )
{
	SR_FL = fl;
	SR_FR = fr;
}


///////////////////////////////////////////////////////////////////////////
// ���W���[���� motor_r
// �����T�v     ��փ��[�^�[��PWM�̕ύX
// ����         acelerL, accelerR(PWM��1�`100%�Ŏw��)
// �߂�l       �Ȃ�
///////////////////////////////////////////////////////////////////////////
void motor_r( int8_t accelerL, int8_t accelerR )
{
	uint16_t pwmrl, pwmrr;

	accele_rR = accelerR;
	accele_rL = accelerL;
	
	pwmrl = TGR_MOTOR * accelerL / 100;
	pwmrr = TGR_MOTOR * accelerR / 100;
	
	// �����
	if( accelerL >= 0 ) {				
		DIR_RL = FORWARD;   // ���]
	} else {						
		pwmrl = -pwmrl;
		DIR_RL = REVERSE;   // �t�]
	}
	PWM_RL_OUT;
	
	// �E���
	if( accelerR >= 0 ) {					
		DIR_RR = FORWARD;   // ���]
	} else {					
		pwmrr = -pwmrr;
		DIR_RR = REVERSE;   // �t�]
	}
	PWM_RR_OUT;
}
///////////////////////////////////////////////////////////////////////////
// ���W���[���� motor_f
// �����T�v     ��փ��[�^�[��PWM�̕ύX
// ����         acelerL, accelerR(PWM��1�`100%�Ŏw��)
// �߂�l       �Ȃ�
///////////////////////////////////////////////////////////////////////////
void motor_f( int8_t accelefL, int8_t accelefR )
{
	uint16_t pwmfl, pwmfr;

	accele_fR = accelefR;
	accele_fL = accelefL;
	
	pwmfl = TGR_MOTOR * accelefL / 100;
	pwmfr = TGR_MOTOR * accelefR / 100;
	
	// �����
	if( accelefL >= 0 ) {				
		DIR_FL = FORWARD;   // ���]
	} else {						
		pwmfl = -pwmfl;
		DIR_FL = REVERSE;   // �t�]
	}
	PWM_FL_OUT;
	
	// �E���
	if( accelefR >= 0 ) {					
		DIR_FR = FORWARD;   // ���]
	} else {					
		pwmfr = -pwmfr;
		DIR_FR = REVERSE;   // �t�]
	}
	PWM_FR_OUT;
}
///////////////////////////////////////////////////////////////////////////
// ���W���[���� motorPwmOut
// �����T�v     ���[�^�[��PWM�̕ύX
// ����         accelefL, accelefR(PWM��1�`100%�Ŏw��)
// �߂�l       �Ȃ�
///////////////////////////////////////////////////////////////////////////
void motorPwmOut( int8_t accelefL, int8_t accelefR, int8_t accelerL, int8_t accelerR )
{
	motor_f(accelefL, accelefR );
	motor_r(accelerL, accelerR );
}
///////////////////////////////////////////////////////////////////////////
// ���W���[���� servoPwmOut
// �����T�v     �����g���[�X���T�[�{��PWM�̕ύX
// ����         spwm
// �߂�l       �Ȃ�
///////////////////////////////////////////////////////////////////////////
void servoPwmOut( signed char servopwm )
{
	uint16_t pwm;
	short angle;
	
	sPwm = servopwm;		// ���O�p�ϐ��ɑ��
	
	angle = getServoAngle();
	
	// �p�x�ɂ�郊�~�b�g����
	if ( angle >= SERVO_LIMIT ) servopwm = -15;
	if ( angle <= -SERVO_LIMIT ) servopwm = 15;
	
	// �|�e���V�������[�^�[���O��Ă����琧�䂵�Ȃ�
	if ( angle > SERVO_LIMIT + 100 ) servopwm = 0;
	if ( angle < -SERVO_LIMIT - 100 ) servopwm = 0;

	pwm = (uint16_t)TGR_SERVO * servopwm / 100;
	// �T�[�{���[�^����
	if( servopwm > 0) {				
		// ���]
		DIR_SERVO = FORWARD;
	} else {				
		// �t�]
		pwm = -pwm;
		DIR_SERVO = REVERSE;
	}
	PWM_SERVO_OUT;
}