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
* Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : Config_MTU1.c
* Version      : 2.1.1
* Device(s)    : R5F571MFCxFP
* Description  : This file implements device driver for Config_MTU1.
* Creation Date: 2022-05-21
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
#include "Config_MTU1.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_MTU1_Create
* Description  : This function initializes the MTU1 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_MTU1_Create(void)
{
    /* Release MTU channel 1 from stop state */
    MSTP(MTU1) = 0U;

    /* Stop MTU channel 1 counter */
    MTU.TSTRA.BIT.CST1 = 0U;

    /* Set external clock noise filter */
    MTU0.NFCRC.BIT.NFAEN = 0U;
    MTU0.NFCRC.BIT.NFBEN = 0U;

    /* Set TGIA1 interrupt priority level */
    ICU.SLIAR208.BYTE = 0x08U;
    IPR(PERIA, INTA208) = _0C_MTU_PRIORITY_LEVEL12;

    /* Set TGIB1 interrupt priority level */
    ICU.SLIAR216.BYTE = 0x09U;
    IPR(PERIA, INTA216) = _0C_MTU_PRIORITY_LEVEL12;

    /* MTU channel 1 is used as phase counting mode */
    MTU1.TMDR1.BYTE = _04_MTU_COT1;
    MTU.TSYRA.BIT.SYNC1 = 0U;
    MTU1.TCR.BYTE = _00_MTU_CKCL_DIS;
    MTU1.TIER.BYTE = _01_MTU_TGIEA_ENABLE | _02_MTU_TGIEB_ENABLE | _00_MTU_TCIEV_DISABLE | _00_MTU_TCIEU_DISABLE | 
                     _00_MTU_TTGE_DISABLE;
    MTU1.TIOR.BYTE = _00_MTU_IOA_DISABLE | _00_MTU_IOB_DISABLE;
    MTU1.TGRA = _0063_TGRA1_VALUE;
    MTU1.TGRB = _0063_TGRB1_VALUE;

    /* Set MTCLKA pin */
    MPC.P24PFS.BYTE = 0x02U;
    PORT2.PMR.BYTE |= 0x10U;

    /* Set MTCLKB pin */
    MPC.P25PFS.BYTE = 0x02U;
    PORT2.PMR.BYTE |= 0x20U;

    R_Config_MTU1_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_MTU1_Start
* Description  : This function starts the MTU1 channel counter
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_MTU1_Start(void)
{
    /* Enable TGIA1 interrupt in ICU */
    IEN(PERIA, INTA208) = 1U;
    
    /* Enable TGIB1 interrupt in ICU */
    IEN(PERIA, INTA216) = 1U;
    
    /* Start MTU channel 1 counter */
    MTU.TSTRA.BIT.CST1 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_MTU1_Stop
* Description  : This function stops the MTU1 channel counter
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_MTU1_Stop(void)
{
    /* Disable TGIA1 interrupt in ICU */
    IEN(PERIA, INTA208) = 0U;
    
    /* Disable TGIB1 interrupt in ICU */
    IEN(PERIA, INTA216) = 0U;
    
    /* Stop MTU channel 1 counter */
    MTU.TSTRA.BIT.CST1 = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
