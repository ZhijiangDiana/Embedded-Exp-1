/*!
 ******************************************************************************
 **
 ** \file mft_icu_fm3.h
 **
 ** \brief  Input Capture Unit drivers head file
 **
 ** \author FSLA AE Team
 **
 ** \version V0.1.0
 **
 ** \date 2012-1-16 10:50
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

#ifndef _MFT_ICU_H_
#define _MFT_ICU_H_

/*---------------------------------------------------------------------------*/
/* include files                                                             */
/*---------------------------------------------------------------------------*/
#include "fm3_common.h"

/*---------------------------------------------------------------------------*/
/* constants and macros                                                      */
/*---------------------------------------------------------------------------*/

/* ICU channel amount */
/*! \brief ICU channel amount */
#define ICU_AMOUNT 4

/*---------------------------------------------------------------------------*/
/* Channel number for input compare unit                                    */
/*---------------------------------------------------------------------------*/
/*! \brief Chip has how many MFT units */
#define MFT_AMOUNT 2

/*! \brief MFT unit0 */
#define MFT_UNIT0    0
/*! \brief MFT unit1 */
#define MFT_UNIT1    1

/* ICU channel */
/*! \brief ICU CH0 */
#define ICU_CH0 0
/*! \brief ICU CH1 */
#define ICU_CH1 1
/*! \brief ICU CH2 */
#define ICU_CH2 2
/*! \brief ICU CH3 */
#define ICU_CH3 3
/*! \brief ICU Channel none */
#define ICU_NONE -1

/* FRT channel */
/*! \brief FRT CH0 */
#define FRT_CH0 0
/*! \brief FRT CH1 */
#define FRT_CH1 1
/*! \brief FRT CH2 */
#define FRT_CH2 2
/*! \brief FRT Channel none */
#define FRT_NONE -1


/*---------------------------------------------------------------------------*/
/* types, enums and structures                                               */
/*---------------------------------------------------------------------------*/

/*!
 ******************************************************************************
 ** \brief Input capture unit interrupt callback function
 ******************************************************************************
 */
typedef void ICU_IntCallbackT (void);

/*!
 ******************************************************************************
 ** \brief valid edge of input capture unit
 ******************************************************************************
 */
typedef enum 
{
    ICU_VALID_EDGE_NULL = 0, //!<  None edge is valid
    ICU_VALID_EDGE_RISING,   //!<  Rising edge is valid
    ICU_VALID_EDGE_FALLING,  //!<  Falling edge is valid
    ICU_VALID_EDGE_BOTH,     //!<  Both edge is valid
      
}MFT_ICUValidEdgeT;

/*!
 ******************************************************************************
 ** \brief valid edge of input capture unit
 ******************************************************************************
 */
typedef enum 
{
    ICU_LAST_EDGE_FALLING = 0,  //!<  Last valid edge is falling edge
    ICU_LAST_EDGE_RISING,       //!<  Last valid edge is rising edge
      
}MFT_ICULastEdgeT;

/*---------------------------------------------------------------------------*/
/* declare functions                                                         */
/*---------------------------------------------------------------------------*/
#ifdef  __cplusplus
extern "C" {
#endif
void MFT_ICUSelFRTCh(uint8_t MFTUnit, uint8_t ICUCh, uint8_t FRTCh);
void MFT_ICUSetTrigMode(uint8_t MFTUnit, uint8_t ICUCh, MFT_ICUValidEdgeT ValidEdge);
void MFT_ICUEnableInt(uint8_t MFTUnit, uint8_t ICUCh, ICU_IntCallbackT* IntCallback);
void MFT_ICUDisableInt(uint8_t MFTUnit, uint8_t ICUCh);
IntStatusT MFT_ICUGetIntFlag(uint8_t MFTUnit, uint8_t ICUCh);
void MFT_ICUClrIntFlag(uint8_t MFTUnit, uint8_t ICUCh);
MFT_ICULastEdgeT MFT_ICUGetLastEdge(uint8_t MFTUnit, uint8_t ICUCh);
uint16_t MFT_ICUReadCaptureData(uint8_t MFTUnit, uint8_t ICUCh);

#ifdef  __cplusplus
}
#endif

#endif
/*****************************************************************************/
/* END OF FILE */
