#ifndef MOTOR_H
#define MOTOR_H
//====================================//
// インクルード                        //
//====================================//
#include "r_smc_entry.h"
//====================================//
// シンボル定義						   //
//====================================//
#define SERVO_LIMIT		430		    // サーボリミットAD値±
#define TGR_MOTOR       5998		// ジェネラルレジスタ初期値(駆動モータ)
#define TGR_SERVO       5998		// ジェネラルレジスタ初期値(サーボ)

#define FORWARD			0		// 正転
#define REVERSE			1		// 逆転
#define BRAKE           0		// ブレーキモード
#define FREE            1		// フリーモード

// 左後輪(pwm3,MTIOC0A)
#define DIR_RL			PORTC.PODR.BIT.B4		// モータ回転方向(0:正転 1:逆転)
#define SR_RL			PORTC.PODR.BIT.B5		// 0:フリーモード  1:ブレーキモード
#define PWM_RL_OUT	    MTU3.TGRA = pwmrl		// PWM出力
// 右後輪(pwm4,MTIOC0C)
#define DIR_RR			PORTC.PODR.BIT.B2
#define SR_RR			PORTC.PODR.BIT.B3
#define PWM_RR_OUT	    MTU3.TGRC = pwmrr
//ここから↓要変更
// 左前輪
#define DIR_FL			PORTE.PODR.BIT.B6
#define SR_FL			PORTE.PODR.BIT.B7
#define PWM_FL_OUT	    MTU0.TGRB = pwmfl
// 右前輪
#define DIR_FR			PORTA.PODR.BIT.B6
#define SR_FR			PORTA.PODR.BIT.B7
#define PWM_FR_OUT	    MTU0.TGRD = pwmfr
//====================================//
// グローバル変数の宣言					//
//====================================//
// モーター関連
extern int8_t	accele_fR;		// 右前モーターPWM値
extern int8_t	accele_fL;		// 左前モーターPWM値
extern int8_t	accele_rR;		// 右後モーターPWM値
extern int8_t	accele_rL;		// 左後モーターPWM値
extern int8_t	sPwm;		    // サーボモーターPWM値
//====================================//
// プロトタイプ宣言					   //
//====================================//
// モーター関連
void motor_R_mode(uint8_t rl, uint8_t rr );
void motor_F_mode(uint8_t fl, uint8_t fr );
void motor_f( int8_t accelefL, int8_t accelefR );
void motor_r( int8_t accelerL, int8_t accelerR );

// サーボ関連
void servoPwmOut( int8_t pwm );
#endif