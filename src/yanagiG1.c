/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"
#include "r_smc_entry.h"  //スマートコンフィグレータ用のライブラリ
#include <stdio.h>
#include "I2c_LCD.h"
#include "IMU_ICM20648.h"
#include "timer.h"
#include "AD12.h"
#include "sw.h"
#include "motor.h"
#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void)
{
	// LCD
	R_Config_SCI12_Start();
	init_lcd();
	//タイマ割り込み開始
	R_Config_CMT0_Start();
	// PWM出力開始
	R_Config_MTU2_Start();
	//R_Config_MTU4_Start();
	R_Config_MTU3_Start();
	R_Config_MTU0_Start();
	//A/D変換開始
	init_AD();
	R_Config_S12AD0_Start();
	R_Config_S12AD1_Start();
	printf("hello");
	
	
	motor_F_mode(0,0);
	
	while(1){
		
		int num1 = 0,num2 = 0;
		int spd = 0;
		num1  = getRotarysw();
		num2 = getTactsw();
		lcdPosition( 0, 1 );
		lcdPrintf("tc%d ro%x",num2,num1);

		spd = 5;

		if(num2 == 0){
			led_out(0x1);
			motor_f(0,0);
			motor_r(0,0);
		}
		else if(num2 == DOWN){
			led_out(0x2);
			motor_f(spd,spd);
			motor_r(spd,spd);
		}
		else if(num2 == UP){
			led_out(0x4);
			motor_f(-spd,-spd);
			motor_r(-spd,-spd);
		}
		else if(num2 == LEFT){
			led_out(0x5);
			motor_f(spd,0);
			motor_r(spd,0);
		}
		else if(num2 == RIGHT){
			led_out(0x6);
			motor_f(0,spd);
			motor_r(0,spd);
		}

		


	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
