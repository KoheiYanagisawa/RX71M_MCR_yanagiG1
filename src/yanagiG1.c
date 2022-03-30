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
#include "r_smc_entry.h"  //�X�}�[�g�R���t�B�O���[�^�p�̃��C�u����
#include <stdio.h>
#include "I2c_LCD.h"
#include "IMU_ICM20648.h"
#include "timer.h"
#include "AD12.h"
#include "sw.h"
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
	inti_lcd();
	//�^�C�}���荞�݊J�n
	R_Config_CMT0_Start();
	// PWM�o�͊J�n
	R_Config_MTU4_Start();
	//A/D�ϊ��J�n
	R_Config_S12AD0_Start();
	R_Config_S12AD1_Start();
	printf("hello2");
	MTU4.TGRD = 5998;//�g���[�X�Z���T�[�pPWM
	led_out(0x1);
	while(1){
		if(cnt0 == 250){
			int num1 = 0,num2 = 0;
			num1  = getRotarysw();
			num2 = getTactsw();
			//printf(" %d | %d\n\r",num1,num2);
			printf(" %d | %d | %d | %d | %d\n\r",sensor1,sensor2,sensor3,sensor4,sensor5);

			cnt0 = 0;
		}




	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
