//=====================================
// インクルード
//=====================================
#include "motor.h"
//=====================================
// グローバル変数の宣言
//=====================================//
int8_t	accele_fR;		// 右前モーターPWM値
int8_t	accele_fL;		// 左前モーターPWM値
int8_t	accele_rR;		// 右後モーターPWM値
int8_t	accele_rL;		// 左後モーターPWM値
int8_t	sPwm;		    // サーボモーターPWM値

///////////////////////////////////////////////////////////////////////////
// モジュール名 motor_R_mode
// 処理概要     前輪ブレーキ､フリーモードの切り替え
// 引数         rl, rr(0:フリーモード  1:ブレーキモード)
// 戻り値       なし
///////////////////////////////////////////////////////////////////////////
void motor_R_mode(uint8_t rl, uint8_t rr )
{
	SR_RL = rl;
	SR_RR = rr;
}
///////////////////////////////////////////////////////////////////////////
// モジュール名 motor_F_mode
// 処理概要     後輪ブレーキ､フリーモードの切り替え
// 引数         fl, fr(0:フリーモード  1:ブレーキモード)
// 戻り値       なし
///////////////////////////////////////////////////////////////////////////
void motor_F_mode(uint8_t fl, uint8_t fr )
{
	SR_FL = fl;
	SR_FR = fr;
}


///////////////////////////////////////////////////////////////////////////
// モジュール名 motor_r
// 処理概要     後輪モーターのPWMの変更
// 引数         acelerL, accelerR(PWMを1～100%で指定)
// 戻り値       なし
///////////////////////////////////////////////////////////////////////////
void motor_r( int8_t accelerL, int8_t accelerR )
{
	uint16_t pwmrl, pwmrr;

	accele_rR = accelerR;
	accele_rL = accelerL;
	
	pwmrl = TGR_MOTOR * accelerL / 100;
	pwmrr = TGR_MOTOR * accelerR / 100;
	
	// 左後輪
	if( accelerL >= 0 ) {				
		DIR_RL = FORWARD;   // 正転
	} else {						
		pwmrl = -pwmrl;
		DIR_RL = REVERSE;   // 逆転
	}
	PWM_RL_OUT;
	
	// 右後輪
	if( accelerR >= 0 ) {					
		DIR_RR = FORWARD;   // 正転
	} else {					
		pwmrr = -pwmrr;
		DIR_RR = REVERSE;   // 逆転
	}
	PWM_RR_OUT;
}
///////////////////////////////////////////////////////////////////////////
// モジュール名 motor_f
// 処理概要     後輪モーターのPWMの変更
// 引数         acelerL, accelerR(PWMを1～100%で指定)
// 戻り値       なし
///////////////////////////////////////////////////////////////////////////
void motor_f( int8_t accelefL, int8_t accelefR )
{
	uint16_t pwmfl, pwmfr;

	accele_fR = accelefR;
	accele_fL = accelefL;
	
	pwmfl = TGR_MOTOR * accelefL / 100;
	pwmfr = TGR_MOTOR * accelefR / 100;
	
	// 左後輪
	if( accelefL >= 0 ) {				
		DIR_FL = FORWARD;   // 正転
	} else {						
		pwmfl = -pwmfl;
		DIR_FL = REVERSE;   // 逆転
	}
	PWM_FL_OUT;
	
	// 右後輪
	if( accelefR >= 0 ) {					
		DIR_FR = FORWARD;   // 正転
	} else {					
		pwmfr = -pwmfr;
		DIR_FR = REVERSE;   // 逆転
	}
	PWM_FR_OUT;
}
///////////////////////////////////////////////////////////////////////////
// モジュール名 motorPwmOut
// 処理概要     モーターのPWMの変更
// 引数         accelefL, accelefR(PWMを1～100%で指定)
// 戻り値       なし
///////////////////////////////////////////////////////////////////////////
void motorPwmOut( int8_t accelefL, int8_t accelefR, int8_t accelerL, int8_t accelerR )
{
	motor_f(accelefL, accelefR );
	motor_r(accelerL, accelerR );
}
///////////////////////////////////////////////////////////////////////////
// モジュール名 servoPwmOut
// 処理概要     白線トレース時サーボのPWMの変更
// 引数         spwm
// 戻り値       なし
///////////////////////////////////////////////////////////////////////////
void servoPwmOut( signed char servopwm )
{
	uint16_t pwm;
	short angle;
	
	sPwm = servopwm;		// ログ用変数に代入
	
	angle = getServoAngle();
	
	// 角度によるリミット制御
	if ( angle >= SERVO_LIMIT ) servopwm = -15;
	if ( angle <= -SERVO_LIMIT ) servopwm = 15;
	
	// ポテンションメーターが外れていたら制御しない
	if ( angle > SERVO_LIMIT + 100 ) servopwm = 0;
	if ( angle < -SERVO_LIMIT - 100 ) servopwm = 0;

	pwm = (uint16_t)TGR_SERVO * servopwm / 100;
	// サーボモータ制御
	if( servopwm > 0) {				
		// 正転
		DIR_SERVO = FORWARD;
	} else {				
		// 逆転
		pwm = -pwm;
		DIR_SERVO = REVERSE;
	}
	PWM_SERVO_OUT;
}