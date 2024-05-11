/*!
 ******************************************************************************
 **
 ** \file mb9bf50x_lib.h
 **
 ** \brief Driver head define
 **
 ** \author FSLA AE Team 
 **
 ** \version V0.10
 **
 ** \date 2001-01-19
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

#ifndef _MB9BF50X_LIB_H_
#define _MB9BF50X_LIB_H_

/*---------------------------------------------------------------------------*/
/* constants and macros                                                      */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* include files                                                             */
/*---------------------------------------------------------------------------*/
#include "fm3_common.h"

/* Driver head files include switch*/

/* #define ADC12 */
/* #define BT */
/* #define CLOCK */
/* #define CR */
/* #define CRC */
/* #define CSV */
/* #define DMAC */
/* #define DT */
/* #define EXTINT */
/* #define INT */
#define IO 
/* #define LPCM */
/* #define LVD */
#define MFS
#define MFS_UART
#define MFS_CSIO
/* #define MFT_FRT */
/* #define MFT_OCU */
/* #define MFT_WFG */
/* #define MFT_ADCMP */
/* #define QPRC */
/* #define WC */
/* #define WD */

/* peripheral driver head files */
#ifdef ADC12
#include "..\driver\adc\adc12_fm3.h"
#endif

#ifdef BT
#include "..\driver\bt\bt_fm3.h"
#endif

#ifdef CLOCK
#include "..\driver\clock\clock_fm3.h"
#endif

#ifdef CR
#include "..\driver\cr\cr_fm3.h"
#endif

#ifdef CRC
#include "..\driver\crc\crc_fm3.h"
#endif

#ifdef CSV
#include "..\driver\cs\csv_fm3.h"
#endif

#ifdef DMAC
#include "..\driver\dmac\dmac_fm3.h"
#endif

#ifdef DT
#include "..\driver\dt\dt_fm3.h"
#endif

#ifdef EXTINT
#include "..\driver\extint\extint_fm3.h"
#endif

#ifdef INT
#include "..\driver\int\int_fm3.h"
#endif

#ifdef IO
#include "..\driver\io\io_fm3.h"
#endif

#ifdef LPCM
#include "..\driver\lpcm\lpcm_fm3.h"
#endif

#ifdef LVD
#include "..\driver\lvd\lvd_fm3.h"
#endif

#ifdef MFS
#include "..\driver\mfs\mfs_fm3.h"
#endif

#ifdef MFS_UART
#include "..\driver\mfs\uart\uart_fm3.h"
#endif

#ifdef MFS_CSIO
#include "..\driver\mfs\csio\csio_fm3.h"
#endif

#ifdef MFT_FRT
#include "..\driver\mft\mft_frt_fm3.h"
#endif

#ifdef MFT_OCU
#include "..\driver\mft\mft_ocu_fm3.h"
#endif

#ifdef MFT_WFG
#include "..\driver\mft\mft_wfg_fm3.h"
#endif

#ifdef MFT_ADCMP
#include "..\driver\mft\mft_adcmp_fm3.h"
#endif

#ifdef QPRC
#include "..\driver\qprc\qprc_fm3.h"
#endif

#ifdef WC
#include "..\driver\wc\wc_fm3.h"
#endif

#ifdef WD
#include "..\driver\wd\wd_fm3.h"
#endif


#endif /* _MB9BF50X_LIB_H_ */

/*****************************************************************************/
/* END OF FILE */
