/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : Pin.c
* Version      : 1.0.2
* Device(s)    : R5F571MFCxFP
* Description  : This file implements SMC pin code generation.
* Creation Date: 2022-04-09
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Pins_Create
* Description  : This function initializes Smart Configurator pins
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Pins_Create(void)
{
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC);

    /* Set AN002 pin */
    MPC.P42PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0xFBU;
    PORT4.PDR.BYTE &= 0xFBU;

    /* Set AN003 pin */
    MPC.P43PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0xF7U;
    PORT4.PDR.BYTE &= 0xF7U;

    /* Set AN004 pin */
    MPC.P44PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0xEFU;
    PORT4.PDR.BYTE &= 0xEFU;

    /* Set AN005 pin */
    MPC.P45PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0xDFU;
    PORT4.PDR.BYTE &= 0xDFU;

    /* Set AN006 pin */
    MPC.P46PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0xBFU;
    PORT4.PDR.BYTE &= 0xBFU;

    /* Set AN007 pin */
    MPC.P47PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0x7FU;
    PORT4.PDR.BYTE &= 0x7FU;

    /* Set AN108 pin */
    MPC.PD0PFS.BYTE = 0x80U;
    PORTD.PMR.BYTE &= 0xFEU;
    PORTD.PDR.BYTE &= 0xFEU;

    /* Set AN109 pin */
    MPC.PD1PFS.BYTE = 0x80U;
    PORTD.PMR.BYTE &= 0xFDU;
    PORTD.PDR.BYTE &= 0xFDU;

    /* Set MTIOC0A pin */
    MPC.PB3PFS.BYTE = 0x01U;
    PORTB.PMR.BYTE |= 0x08U;

    /* Set MTIOC0C pin */
    MPC.PB1PFS.BYTE = 0x01U;
    PORTB.PMR.BYTE |= 0x02U;

    /* Set MTIOC3A pin */
    MPC.PC1PFS.BYTE = 0x01U;
    PORTC.PMR.BYTE |= 0x02U;

    /* Set MTIOC3C pin */
    MPC.PC0PFS.BYTE = 0x01U;
    PORTC.PMR.BYTE |= 0x01U;

    /* Set MTIOC4C pin */
    MPC.PE5PFS.BYTE = 0x01U;
    PORTE.PMR.BYTE |= 0x20U;

    /* Set RXD1 pin */
    MPC.P30PFS.BYTE = 0x0AU;
    PORT3.PMR.BYTE |= 0x01U;

    /* Set SCK2 pin */
    MPC.P51PFS.BYTE = 0x0AU;
    PORT5.PMR.BYTE |= 0x02U;

    /* Set SMISO2 pin */
    MPC.P52PFS.BYTE = 0x0AU;
    PORT5.PMR.BYTE |= 0x04U;

    /* Set SMOSI2 pin */
    MPC.P50PFS.BYTE = 0x0AU;
    PORT5.PMR.BYTE |= 0x01U;

    /* Set SSCL12 pin */
    MPC.PE2PFS.BYTE = 0x0CU;
    PORTE.PMR.BYTE |= 0x04U;

    /* Set SSDA12 pin */
    MPC.PE1PFS.BYTE = 0x0CU;
    PORTE.PMR.BYTE |= 0x02U;

    /* Set TXD1 pin */
    PORT2.PODR.BYTE |= 0x40U;
    MPC.P26PFS.BYTE = 0x0AU;
    PORT2.PDR.BYTE |= 0x40U;
    // PORT2.PMR.BIT.B6 = 1U; // Please set the PMR bit after TE bit is set to 1.

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
}

