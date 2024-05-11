/*!
 ******************************************************************************
 **
** \file lpcm_fm3.h
 **
 ** \brief head file of low power consumption drivers
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
 
/*!
 ******************************************************************************
 ** \brief Low Power Mode type structure
 ******************************************************************************
 */

#ifndef _LPCM_FM3_H_
#define _LPCM_FM3_H_

#include "fm3_common.h"

/* IO Status */  
/*! \brief LPCM IO keep status */
#define  LPCM_IO_REMAIN   0
/*! \brief LPCM IO high impendence */
#define  LPCM_IO_HIZ      1
  
/*!
******************************************************************************
 ** \brief define standby mode type
******************************************************************************
*/
typedef enum
{
    STB_SlpMode=1,    //!< standby sleep mode
    STB_TimerMode,    //!< standby timer mode
    STB_StopMode,     //!< standby stop mode
} LPCM_StandbyModeT;

/*
******************************************************************************
 ** go to standby mode
******************************************************************************
*/
#ifdef __cplusplus
extern "C" {
#endif
  
void LPCM_GoToStandbyMode(LPCM_StandbyModeT Type, uint8_t IOStat);

#ifdef __cplusplus
}
#endif

#endif
