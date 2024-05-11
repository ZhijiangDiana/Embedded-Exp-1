/*!
 ******************************************************************************
 **
 ** \file lvd_fm3.h
 **
 ** \brief head file of low voltage detection driver
 **
 ** 
 **
 ** \author FSLA AE Team
 **
 ** \version V0.10
 **
 ** \date 2011-12-8
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
 
#ifndef _LVD_FM3_H_
#define _LVD_FM3_H_
 
/*---------------------------------------------------------------------------*/
/* include files                                                             */
/*---------------------------------------------------------------------------*/
#include "fm3_common.h"
 
 
 
/*---------------------------------------------------------------------------*/
/* constants and macros                                                      */
/*---------------------------------------------------------------------------*/

/*! \brief LVD interrupt voltage setting 2.8V */
#define LVD_VOL_VAL_2_8                      0 // 2.8V
/*! \brief LVD interrupt voltage setting 3.0V */
#define LVD_VOL_VAL_3_0                      1 // 3.0V
/*! \brief LVD interrupt voltage setting 3.2V */
#define LVD_VOL_VAL_3_2                      2 // 3.2V
/*! \brief LVD interrupt voltage setting 3.6V */
#define LVD_VOL_VAL_3_6                      3 // 3.6V
/*! \brief LVD interrupt voltage setting 3.7V */
#define LVD_VOL_VAL_3_7                      4 // 3.7V
/*! \brief LVD interrupt voltage setting 4.0V */
#define LVD_VOL_VAL_4_0                      7 // 4.0V
/*! \brief LVD interrupt voltage setting 4.1V */
#define LVD_VOL_VAL_4_1                      8 // 4.1V
/*! \brief LVD interrupt voltage setting 4.2V */
#define LVD_VOL_VAL_4_2                      9 // 4.2V  
/*! \brief Check parameter */
#define IS_LVD_VAL(LVDVal)                      ((LVDVal == LVD_VOL_VAL_2_8) \
                                                ||(LVDVal == LVD_VOL_VAL_3_0)\
                                                ||(LVDVal == LVD_VOL_VAL_3_2)\
                                                ||(LVDVal == LVD_VOL_VAL_3_6)\
                                                ||(LVDVal == LVD_VOL_VAL_3_7)\
                                                ||(LVDVal == LVD_VOL_VAL_4_0)\
                                                ||(LVDVal == LVD_VOL_VAL_4_1)\
                                                ||(LVDVal == LVD_VOL_VAL_4_2))



/*! \brief Disable write protection mode of LVD_CTL */
#define LVD_UNLOCK		                 ((uint32_t)0x1acce553)


/*!
 ******************************************************************************
 ** \brief LVD Interrupt callback function definition
 ******************************************************************************
 */
typedef void (LVD_IntHandlerCallbackT) (void);

                                                 
/*---------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

void LVD_EnableInt(LVD_IntHandlerCallbackT* IntCallback);
void LVD_DisableInt(void);
void LVD_SetDetectVolt(uint8_t VoltLevel);
IntStatusT LVD_GetIntFlag(void);
FlagStatusT LVD_ClrIntRdyStat(void);
void LVD_UnlockCtrlReg(void);
void LVD_LockCtrlReg(void);

#ifdef __cplusplus
}
#endif


#endif /* _LVD_FM3_H_ */
/*****************************************************************************/
/* END OF FILE */
 
