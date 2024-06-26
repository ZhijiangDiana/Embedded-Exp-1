/*!
 ******************************************************************************
 **
 ** \file extint_fm3.h
 **
 ** \brief external interrupt drivers head file
 **
 ** \author FSLA AE Team
 **
 ** \version V0.10
 **
 ** \date 2011-11-29
 **
 ** \attention THIS SAMPLE CODE IS PROVIDED AS IS. FUJITSU SEMICONDUCTOR
 **            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
 **            OMMISSIONS.
 **
 ** (C) Copyright 200x-201x by Fujitsu Semiconductor(Shanghai) Co.,Ltd.
 **
 ******************************************************************************
 **
 ** \note Other information.
 **
 ******************************************************************************
 */
 
#ifndef _extint_FM3_H_
#define _extint_FM3_H_


/*---------------------------------------------------------------------------*/
/* include files                                                             */
/*---------------------------------------------------------------------------*/
#include "fm3_common.h"

/*---------------------------------------------------------------------------*/
/* constants and macros                                                      */
/*---------------------------------------------------------------------------*/
/* External interrupt channel definition */
/*! \brief External interrupt channel 0 */
#define EXTI_CH0                    (0)
/*! \brief External interrupt channel 1 */
#define EXTI_CH1                    (1)
/*! \brief External interrupt channel 2 */
#define EXTI_CH2                    (2)
/*! \brief External interrupt channel 3 */
#define EXTI_CH3                    (3)
/*! \brief External interrupt channel 4 */
#define EXTI_CH4                    (4)
/*! \brief External interrupt channel 5 */
#define EXTI_CH5                    (5)
/*! \brief External interrupt channel 6 */
#define EXTI_CH6                    (6)
/*! \brief External interrupt channel 7 */
#define EXTI_CH7                    (7)
/*! \brief External interrupt channel 8 */
#define EXTI_CH8                    (8)
/*! \brief External interrupt channel 9 */
#define EXTI_CH9                    (9)
/*! \brief External interrupt channel 10 */
#define EXTI_CH10                   (10)
/*! \brief External interrupt channel 11 */
#define EXTI_CH11                   (11)
/*! \brief External interrupt channel 12 */
#define EXTI_CH12                   (12)
/*! \brief External interrupt channel 13 */
#define EXTI_CH13                   (13)
/*! \brief External interrupt channel 14 */
#define EXTI_CH14                   (14)
/*! \brief External interrupt channel 15 */
#define EXTI_CH15                   (15)

/*!
******************************************************************************
 ** \brief external interrupt callback function type definition
******************************************************************************
*/
typedef void EXTI_IntCallBackT(void);
/*!
******************************************************************************
 ** \brief NMI callback function type definition
******************************************************************************
*/
typedef void NMI_IntCallBackT(void);

/*!
******************************************************************************
 ** \brief external interrupt detect mode enumeration
******************************************************************************
*/
typedef enum 
{
    EXTI_LEVEL_LOW_DETECT= 0,
    EXTI_LEVEL_HIGH_DETECT,
    EXTI_EDGE_RISING,
    EXTI_EDGE_FALLING,
  
}EXTI_DetectModeT;


/*---------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
/* external interrupt */
void EXTI_EnableInt(uint8_t Ch, EXTI_IntCallBackT IntCallBack);
void EXTI_DisableInt(uint8_t Ch);
FlagStatusT EXTI_GetIntFlag(uint8_t Ch);
void EXTI_ClrIntFlag(uint8_t Ch);
void EXTI_SetIntDetectMode(uint8_t Ch, EXTI_DetectModeT);
EXTI_DetectModeT EXTI_GetIntDetectMode(uint8_t Ch);

/* NMI */
FlagStatusT EXTI_NMIGetIntFlag(void);
void EXTI_NMIClrIntFlag(void);
void EXTI_NMISetIntCallback(NMI_IntCallBackT* IntCallback);
void EXTI_NMIIntHandler(void);


#ifdef __cplusplus
}
#endif


#endif /* _extint_FM3_H_ */
/*****************************************************************************/
/* END OF FILE */

