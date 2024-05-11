/*!
 ******************************************************************************
 **
** \file lpcm_fm3.c
 **
 ** \brief this file provides all low power consumption mode drivers
 **
 ** \author FSLA AE Team
 **
 ** \version V0.10
 **
 ** \date 2011-12-18
 **
 ** \attention THIS SAMPLE CODE IS PROVIDED AS IS. FUJITSU SEMICONDUCTOR
 **            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
 **            OMMISSIONS.
 **
 ** (C) Copyright 200x-201x by Fujitsu Semiconductor(Shanghai) Co.,Ltd.
 **
 ******************************************************************************
 */

/*---------------------------------------------------------------------------*/
/* include files                                                             */
/*---------------------------------------------------------------------------*/

#include "lpcm_fm3.h"

/*!
 ******************************************************************************
 ** \brief define SCR address
 ******************************************************************************
 */
#define CM3_Core_CSR  *((volatile uint32_t*)(0xE000ED10ul))

/*---------------------------------------------------------------------------*/
/* local datatypes                                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* global data                                                               */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* global functions                                                          */
/*---------------------------------------------------------------------------*/


/*!
 ******************************************************************************
 ** \brief go to standby mode
 **
 ** \param tp the one type of standby mode.
 **        This parameter can be one of the following values:
 ** \arg   STB_SlpMode sleep mode
 ** \arg   STB_TimerMode timer mode
 ** \arg   STB_StopMode Stop mode
 **
 ** \param io_stus set io status when enter standby mode.
 **        This parameter can be one of the following values:
 ** \arg   LPCM_IO_REMAIN keep io tatus
 **        LPCM_IO_HIZ keep hi-z
 **
 ** \retval None
 **
 ******************************************************************************
 */
void LPCM_GoToStandbyMode(LPCM_StandbyModeT Type, uint8_t IOStat)
{
    switch (Type)
    {
        case STB_SlpMode:
            CM3_Core_CSR &= 0xFFFFFFFFB;
            __WFI();
            break;
        case STB_TimerMode:
            if( IOStat == LPCM_IO_REMAIN )
            {
                FM3_CRG->STB_CTL = 0x1ACC0000;
            }
            else
            {
                FM3_CRG->STB_CTL = 0x1ACC0010;
            }
            CM3_Core_CSR |= 0x00000004;
            __WFI();
            break;
        case STB_StopMode:
            if( IOStat == LPCM_IO_REMAIN )
            {
                FM3_CRG->STB_CTL = 0x1ACC0002;
            }
            else
            {
                FM3_CRG->STB_CTL = 0x1ACC0012;
            }
            CM3_Core_CSR &= 0xFFFFFFFFB;
            __WFI();
            break;
        default:
            break;
    }
}
