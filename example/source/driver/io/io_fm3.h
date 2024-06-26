/*!
 ******************************************************************************
 **
 ** \file io_fm3.h
 **
 ** \brief head file of io  driver
 **
 ** 
 **
 ** \author FSLA AE Team
 **
 ** \version V0.21
 **
 ** \date 2012-08-07
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
 
#ifndef _IO_FM3_H_
#define _IO_FM3_H_
 
/*---------------------------------------------------------------------------*/
/* include files                                                             */
/*---------------------------------------------------------------------------*/
#include "fm3_common.h"
 
 
/*---------------------------------------------------------------------------*/
/* constants and macros                                                      */
/*---------------------------------------------------------------------------*/
/* IO port index definition */
/*! \brief IO port0 */ 
#define IO_PORT0          (0x00u)
/*! \brief IO port1 */ 
#define IO_PORT1          (0x01u)
/*! \brief IO port2 */ 
#define IO_PORT2          (0x02u)
/*! \brief IO port3 */ 
#define IO_PORT3          (0x03u)
/*! \brief IO port4 */ 
#define IO_PORT4          (0x04u)
/*! \brief IO port5 */ 
#define IO_PORT5          (0x05u)
/*! \brief IO port6 */ 
#define IO_PORT6          (0x06u)
/*! \brief IO port7 */ 
#define IO_PORT7          (0x07u)
/*! \brief IO port8 */ 
#define IO_PORT8          (0x08u)
/*! \brief IO port9 */ 
#define IO_PORT9          (0x09u)
/*! \brief IO portA */ 
#define IO_PORTA          (0x0Au)
/*! \brief IO portB */ 
#define IO_PORTB          (0x0Bu)
/*! \brief IO portC */ 
#define IO_PORTC          (0x0Cu)
/*! \brief IO portD */ 
#define IO_PORTD          (0x0Du)
/*! \brief IO portE */ 
#define IO_PORTE          (0x0Eu)
/*! \brief IO portF */ 
#define IO_PORTF          (0x0Fu)

/* IO pin index definition */
/*! \brief IO Pin0 */ 
#define IO_PINx0          (1ul<<0)
/*! \brief IO Pin1 */ 
#define IO_PINx1          (1ul<<1)
/*! \brief IO Pin2 */ 
#define IO_PINx2          (1ul<<2)
/*! \brief IO Pin3 */ 
#define IO_PINx3          (1ul<<3)
/*! \brief IO Pin4 */ 
#define IO_PINx4          (1ul<<4)
/*! \brief IO Pin5 */ 
#define IO_PINx5          (1ul<<5)
/*! \brief IO Pin6 */ 
#define IO_PINx6          (1ul<<6)
/*! \brief IO Pin7 */ 
#define IO_PINx7          (1ul<<7)
/*! \brief IO Pin8 */ 
#define IO_PINx8          (1ul<<8)
/*! \brief IO Pin9 */ 
#define IO_PINx9          (1ul<<9)
/*! \brief IO PinA */ 
#define IO_PINxA          (1ul<<10)
/*! \brief IO PinB */ 
#define IO_PINxB          (1ul<<11)
/*! \brief IO PinC */ 
#define IO_PINxC          (1ul<<12)
/*! \brief IO PinD */ 
#define IO_PINxD          (1ul<<13)
/*! \brief IO PinE */ 
#define IO_PINxE          (1ul<<14)
/*! \brief IO PinF */ 
#define IO_PINxF          (1ul<<15)

/* IO pin direction definition */
/*! \brief IO input */ 
#define IO_DIR_INPUT       (0)
/*! \brief IO output */ 
#define IO_DIR_OUTPUT      (1)

/* IO pin pull-up register selection */
/*! \brief IO pull-up register disconnection */ 
#define IO_PULLUP_OFF      (0)
/*! \brief IO pull-up register connection */ 
#define IO_PULLUP_ON       (1)

/* IO pin set definition */
/*! \brief IO pin clear */ 
#define IO_BIT_CLR         (0)
/*! \brief IO pin set */ 
#define IO_BIT_SET         (1)

/* IO state definition */
/*! \brief IO state disable */ 
#define IO_STATE_DISABLE       (0)
/*! \brief IO state enable */ 
#define IO_STATE_ENABLE        (1)

/* ------------------------- MFT pin definition ------------------------------*/
/* MFT Channel definition */
/*! \brief MFT channel 0 */ 
#define IO_MFT_CH0        (0)
/*! \brief MFT channel 1 */ 
#define IO_MFT_CH1        (1)

/*!
 ******************************************************************************
 ** \brief MFT ICx3 pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFT_ICx3_ICx3_INIT = 0, //!< initial setting, input from ICx3_0
    IO_MFT_ICx3_ICx3_0,        //!< input from ICx3_0
    IO_MFT_ICx3_ICx3_1,        //!< input from ICx3_1
    IO_MFT_ICx3_ICx3_2,        //!< input from ICx3_2
    IO_MFT_ICx3_MFSCH3LSYN,    //!< input from LSYN of MFS Ch3
    IO_MFT_ICx3_MFSCH7LSYN,    //!< input from LSYN of MFS Ch7
    IO_MFT_ICx3_CRTRIM,        //!< input from CR trimming pin
    
}IO_MFTICx3PinT;

/*!
 ******************************************************************************
 ** \brief MFT ICx2 pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFT_ICx2_ICx2_INIT = 0, //!< initial setting, input from ICx2_0
    IO_MFT_ICx2_ICx2_0,        //!< input from ICx2_0
    IO_MFT_ICx2_ICx2_1,        //!< input from ICx2_1
    IO_MFT_ICx2_ICx2_2,        //!< input from ICx2_2
    IO_MFT_ICx2_MFSCH2LSYN,    //!< input from LSYN of MFS Ch2
    IO_MFT_ICx2_MFSCH6LSYN,    //!< input from LSYN of MFS Ch6
    
}IO_MFTICx2PinT;

/*!
 ******************************************************************************
 ** \brief MFT ICx1 pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFT_ICx1_ICx1_INIT = 0, //!< initial setting, input from ICx1_0
    IO_MFT_ICx1_ICx1_0,        //!< input from ICx1_0
    IO_MFT_ICx1_ICx1_1,        //!< input from ICx1_1
    IO_MFT_ICx1_ICx1_2,        //!< input from ICx1_2
    IO_MFT_ICx1_MFSCH1LSYN,    //!< input from LSYN of MFS Ch1
    IO_MFT_ICx1_MFSCH5LSYN,    //!< input from LSYN of MFS Ch5
    
}IO_MFTICx1PinT;

/*!
 ******************************************************************************
 ** \brief MFT ICx0 pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFT_ICx0_ICx0_INIT = 0, //!< initial setting, input from ICx0_0
    IO_MFT_ICx0_ICx0_0,        //!< input from ICx0_0
    IO_MFT_ICx0_ICx0_1,        //!< input from ICx0_1
    IO_MFT_ICx0_ICx0_2,        //!< input from ICx0_2
    IO_MFT_ICx0_MFSCH0LSYN,    //!< input from LSYN of MFS Ch0
    IO_MFT_ICx0_MFSCH4LSYN,    //!< input from LSYN of MFS Ch4
    
}IO_MFTICx0PinT;

/*!
 ******************************************************************************
 ** \brief MFT FRCKx pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFT_FRCKx_FRCKx_INIT = 0, //!< initial setting, input from FRCKx_0
    IO_MFT_FRCKx_FRCKx_0,        //!< input from FRCKx_0
    IO_MFT_FRCKx_FRCKx_1,        //!< input from FRCKx_1
    IO_MFT_FRCKx_FRCKx_2,        //!< input from FRCKx_2
    
}IO_MFTFRCKxPinT;

/*!
 ******************************************************************************
 ** \brief MFT DTTIXx pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFT_DTTIXx_DTTIXx_INIT = 0, //!< initial setting, input from DTTIXx_0
    IO_MFT_DTTIXx_DTTIXx_0,        //!< input from DTTIXx_0
    IO_MFT_DTTIXx_DTTIXx_1,        //!< input from DTTIXx_1
    
}IO_MFTDTTIXxPinT;

/*!
 ******************************************************************************
 ** \brief MFT DTIF function selection enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFT_DTIF_SWITCH_OFF = 0, //!< DTIF function off
    IO_MFT_DTIF_SWITCH_ON,      //!< DTIF function on
    
}IO_MFTDTIFSwitchSelT;

/* RT Channel definition */
/*! \brief RT Channel 0 */ 
#define IO_MFT_RT_CH0         (0)
/*! \brief RT Channel 1 */ 
#define IO_MFT_RT_CH1         (1)
/*! \brief RT Channel 2 */ 
#define IO_MFT_RT_CH2         (2)
/*! \brief RT Channel 3 */ 
#define IO_MFT_RT_CH3         (3)
/*! \brief RT Channel 4 */ 
#define IO_MFT_RT_CH4         (4)
/*! \brief RT Channel 5 */ 
#define IO_MFT_RT_CH5         (5)

/*!
 ******************************************************************************
 ** \brief MFT RTxy pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFT_RTOxy_RTOxy_INIT = 0, //!< initial setting, output disable
    IO_MFT_RTOxy_RTOxy_0,        //!< output from RTOxy_0
    IO_MFT_RTOxy_RTOxy_1,        //!< output from RTOxy_1
    
}IO_MFTRTOxyPinT;

/* ------------------------- BT pin definition ------------------------------*/
/* BT Channel definition */
/*! \brief BT Channel 0 */ 
#define IO_BT_CH0             (0)
/*! \brief BT Channel 1 */ 
#define IO_BT_CH1             (1)
/*! \brief BT Channel 2 */ 
#define IO_BT_CH2             (2)
/*! \brief BT Channel 3 */ 
#define IO_BT_CH3             (3)
/*! \brief BT Channel 4 */ 
#define IO_BT_CH4             (4)
/*! \brief BT Channel 5 */ 
#define IO_BT_CH5             (5)
/*! \brief BT Channel 6 */ 
#define IO_BT_CH6             (6)
/*! \brief BT Channel 7 */ 
#define IO_BT_CH7             (7)

/*!
 ******************************************************************************
 ** \brief BT TIOBx input pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_BT_TIOBx_INPUT_INIT = 0, //!<  initial setting, input from TIOBx_0
    IO_BT_TIOBx_INPUT_TIOBx_0,  //!<  input from TIOBx_0
    IO_BT_TIOBx_INPUT_TIOBx_1,  //!<  input from TIOBx_1
    IO_BT_TIOBx_INPUT_TIOBx_2,  //!<  input from TIOBx_2
  
}IO_BTTIOBxInputPinT;

/*!
 ******************************************************************************
 ** \brief BT TIOA output pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_BT_TIOAx_OUTPUT_INIT = 0, //!<  initial setting, output disable
    IO_BT_TIOAx_OUTPUT_TIOAx_0,  //!<  output from TIOAx_0
    IO_BT_TIOAx_OUTPUT_TIOAx_1,  //!<  output from TIOAx_1
    IO_BT_TIOAx_OUTPUT_TIOAx_2,  //!<  output from TIOAx_2
    
}IO_BTTIOAxOutputPinT;

/*!
 ******************************************************************************
 ** \brief BT TIOA input pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_BT_TIOAx_INPUT_INIT = 0,    //!<  initial setting, input from TIOAx_0
    IO_BT_TIOAx_INPUT_TIOAx_0 = 1, //!<  input from TIOAx_0
    IO_BT_TIOAx_INPUT_TIOAx_1,     //!<  input from TIOAx_1
    IO_BT_TIOAx_INPUT_TIOAx_2,     //!<  input from TIOAx_2
    
}IO_BTTIOAxInputPinT;

/* ------------------------- Ext Int pin definition --------------------------*/
/* Ext Int Channel definition */
/*! \brief Ext Int Channel 0 */ 
#define IO_EXT_INT_CH0            (0)
/*! \brief Ext Int Channel 1 */ 
#define IO_EXT_INT_CH1            (1)
/*! \brief Ext Int Channel 2 */ 
#define IO_EXT_INT_CH2            (2)
/*! \brief Ext Int Channel 3 */ 
#define IO_EXT_INT_CH3            (3)
/*! \brief Ext Int Channel 4 */ 
#define IO_EXT_INT_CH4            (4)
/*! \brief Ext Int Channel 5 */ 
#define IO_EXT_INT_CH5            (5)
/*! \brief Ext Int Channel 6 */ 
#define IO_EXT_INT_CH6            (6)
/*! \brief Ext Int Channel 7 */ 
#define IO_EXT_INT_CH7            (7)
/*! \brief Ext Int Channel 8 */ 
#define IO_EXT_INT_CH8            (8)
/*! \brief Ext Int Channel 9 */ 
#define IO_EXT_INT_CH9            (9)
/*! \brief Ext Int Channel 10 */ 
#define IO_EXT_INT_CH10           (10)
/*! \brief Ext Int Channel 11 */ 
#define IO_EXT_INT_CH11           (11)
/*! \brief Ext Int Channel 12 */ 
#define IO_EXT_INT_CH12           (12)
/*! \brief Ext Int Channel 13 */ 
#define IO_EXT_INT_CH13           (13)
/*! \brief Ext Int Channel 14 */ 
#define IO_EXT_INT_CH14           (14)
/*! \brief Ext Int Channel 15 */ 
#define IO_EXT_INT_CH15           (15)

/*!
 ******************************************************************************
 ** \brief Ext Int input pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_INTx_INIT = 0,  //!<  initial setting, input from INTx_0
    IO_INTx_INTx_0,    //!<  input from INTx_0
    IO_INTx_INTx_1,    //!<  input from INTx_1
    IO_INTx_INTx_2,    //!<  input from INTx_2
  
}IO_INTxPinT;

/* ------------------------- MFS pin definition ------------------------------*/
/* MFS Channel definition */
/*! \brief MFS Channel 0 */
#define IO_MFS_CH0                (0)
/*! \brief MFS Channel 1 */
#define IO_MFS_CH1                (1)
/*! \brief MFS Channel 2 */
#define IO_MFS_CH2                (2)
/*! \brief MFS Channel 3 */
#define IO_MFS_CH3                (3)
/*! \brief MFS Channel 4 */
#define IO_MFS_CH4                (4)
/*! \brief MFS Channel 5 */
#define IO_MFS_CH5                (5)
/*! \brief MFS Channel 6 */
#define IO_MFS_CH6                (6)
/*! \brief MFS Channel 7 */
#define IO_MFS_CH7                (7)

/*!
 ******************************************************************************
 ** \brief MFS SCKx pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFS_SCKx_SCKx_INIT = 0, //!<  initial setting, output dsiable
    IO_MFS_SCKx_SCKx_0,        //!<  output from SCKx_0
    IO_MFS_SCKx_SCKx_1,        //!<  output from SCKx_1 
    IO_MFS_SCKx_SCKx_2,        //!<  output from SCKx_2
}IO_MFSSCKxPinT;

/*!
 ******************************************************************************
 ** \brief MFS SOTx pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFS_SOTx_SOTx_INIT = 0, //!<  initial setting, output dsiable
    IO_MFS_SOTx_SOTx_0,        //!<  output from SOTx_0
    IO_MFS_SOTx_SOTx_1,        //!<  output from SOTx_1
    IO_MFS_SOTx_SOTx_2,        //!<  output from SOTx_2
}IO_MFSSOTxPinT;

/*!
 ******************************************************************************
 ** \brief MFS SINx pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFS_SINx_INIT = 0,      //!<  initial setting, input from SINx_0
    IO_MFS_SINx_SINx_0,        //!<  input from SINx_0
    IO_MFS_SINx_SINx_1,        //!<  input from SINx_1
    IO_MFS_SINx_SINx_2,        //!<  input from SINx_2
}IO_MFSSINxPinT;

/*!
 ******************************************************************************
 ** \brief MFS CTS4 pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFS_CTS4_INIT = 0,      //!<  initial setting, input from CTS4_0
    IO_MFS_CTS4_CTS4_0,        //!<  input from CTS4_0
    IO_MFS_CTS4_CTS4_1,        //!<  input from CTS4_1
    IO_MFS_CTS4_CTS4_2,        //!<  input from CTS4_2
    
}IO_MFSCTSPinT;

/*!
 ******************************************************************************
 ** \brief MFS RST4 pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_MFS_RTS4_INIT = 0,      //!<  initial setting, output disable
    IO_MFS_RTS4_RTS4_0,        //!<  output from RTS4_0
    IO_MFS_RTS4_RTS4_1,        //!<  output from RTS4_1
    IO_MFS_RTS4_RTS4_2,        //!<  output from RTS4_2
    
}IO_MFSRTSPinT;

/* ------------------------- CAN pin definition ------------------------------*/
/* CAN Channel definition */
/*! \brief CAN Channel 0 */
#define IO_CAN_CH0          (0)
/*! \brief CAN Channel 1 */
#define IO_CAN_CH1          (1)

/*!
 ******************************************************************************
 ** \brief CAN TXx pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_CAN_TXx_INIT = 0,       //!<  initial setting, output disable
    IO_CAN_TXx_TXx_0,          //!<  output from TXx_0
    IO_CAN_TXx_TXx_1,          //!<  output from TXx_1
    IO_CAN_TXx_TXx_2,          //!<  output from TXx_2
}IO_CANTXxPinT;

/*!
 ******************************************************************************
 ** \brief CAN RXx pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_CAN_RXx_INIT = 0,       //!<  initial setting, input from RXx_0
    IO_CAN_RXx_RXx_0,          //!<  input from RXx_0
    IO_CAN_RXx_RXx_1,          //!<  input from RXx_1
    IO_CAN_RXx_RXx_2,          //!<  input from RXx_2
}IO_CANRXxPinT;

/* ------------------------- ADC pin definition ------------------------------*/
/* ADC Channel definition */
/*! \brief ADC Channel 0 */
#define  IO_ADC_UNIT0               (0)
/*! \brief ADC Channel 1 */
#define  IO_ADC_UNIT1               (1)
/*! \brief ADC Channel 2 */
#define  IO_ADC_UNIT2               (2)

/*!
 ******************************************************************************
 ** \brief ADC ADTGx pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_ADTGx_INIT = 0,       //!<  initial setting, input from ADTGx_0
    IO_ADTGx_ADTGx_0,        //!<  input from ADTGx_0
    IO_ADTGx_ADTGx_1,        //!<  input from ADTGx_1
    IO_ADTGx_ADTGx_2,        //!<  input from ADTGx_2
    IO_ADTGx_ADTGx_3,        //!<  input from ADTGx_3
    IO_ADTGx_ADTGx_4,        //!<  input from ADTGx_4
    IO_ADTGx_ADTGx_5,        //!<  input from ADTGx_5
    IO_ADTGx_ADTGx_6,        //!<  input from ADTGx_6
    IO_ADTGx_ADTGx_7,        //!<  input from ADTGx_7
    IO_ADTGx_ADTGx_8,        //!<  input from ADTGx_8
    
}IO_ADTGxPinT;

/* QPRC Channel definition */
/*! \brief QPRC Channel 0 */
#define IO_QPRC_CH0             (0)
/*! \brief QPRC Channel 1 */
#define IO_QPRC_CH1             (1)

/*!
 ******************************************************************************
 ** \brief QPRC ZINx pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_QPRC_ZINx_INIT = 0,  //!<  initial setting, input from ZINx_0
    IO_QPRC_ZINx_ZINx_0,    //!<  input from ZINx_0
    IO_QPRC_ZINx_ZINx_1,    //!<  input from ZINx_1
    IO_QPRC_ZINx_ZINx_2,    //!<  input from ZINx_2
  
}IO_QPRCZINxPinT;

/*!
 ******************************************************************************
 ** \brief QPRC AINx pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_QPRC_AINx_INIT = 0,  //!<  initial setting, input from AINx_0
    IO_QPRC_AINx_AINx_0,    //!<  input from AINx_0
    IO_QPRC_AINx_AINx_1,    //!<  input from AINx_0
    IO_QPRC_AINx_AINx_2,    //!<  input from AINx_0
  
}IO_QPRCAINxPinT;

/*!
 ******************************************************************************
 ** \brief QPRC BINx pin location enumeration
 ******************************************************************************
 */
typedef enum
{
    IO_QPRC_BINx_INIT = 0,  //!<  initial setting, input from BINx_0
    IO_QPRC_BINx_BINx_0,    //!<  input from BINx_0
    IO_QPRC_BINx_BINx_1,    //!<  input from BINx_1
    IO_QPRC_BINx_BINx_2,    //!<  input from BINx_2
  
}IO_QPRCBINxPinT;

/* -------------------- External bus pin definition --------------------------*/
/* CS signal channel */
/*! \brief CS Channel 0 */
#define IO_EXT_BUS_MCS0          (0)
/*! \brief CS Channel 1 */
#define IO_EXT_BUS_MCS1          (1)
/*! \brief CS Channel 2 */
#define IO_EXT_BUS_MCS2          (2)
/*! \brief CS Channel 3 */
#define IO_EXT_BUS_MCS3          (3)
/*! \brief CS Channel 4 */
#define IO_EXT_BUS_MCS4          (4)
/*! \brief CS Channel 5 */
#define IO_EXT_BUS_MCS5          (5)
/*! \brief CS Channel 6 */
#define IO_EXT_BUS_MCS6          (6)
/*! \brief CS Channel 7 */
#define IO_EXT_BUS_MCS7          (7)
 
/* Addr signal channel */
/*! \brief Address pin 0 */
#define IO_EXT_BUS_ADDR0          (0)
/*! \brief Address pin 1 */
#define IO_EXT_BUS_ADDR1          (1)
/*! \brief Address pin 2 */
#define IO_EXT_BUS_ADDR2          (2)
/*! \brief Address pin 3 */
#define IO_EXT_BUS_ADDR3          (3)
/*! \brief Address pin 4 */
#define IO_EXT_BUS_ADDR4          (4)
/*! \brief Address pin 5 */
#define IO_EXT_BUS_ADDR5          (5)
/*! \brief Address pin 6 */
#define IO_EXT_BUS_ADDR6          (6)
/*! \brief Address pin 7 */
#define IO_EXT_BUS_ADDR7          (7)
/*! \brief Address pin 8 */
#define IO_EXT_BUS_ADDR8          (8)
/*! \brief Address pin 9 */
#define IO_EXT_BUS_ADDR9          (9)
/*! \brief Address pin 10 */
#define IO_EXT_BUS_ADDR10         (10)
/*! \brief Address pin 11 */
#define IO_EXT_BUS_ADDR11         (11)
/*! \brief Address pin 12 */
#define IO_EXT_BUS_ADDR12         (12)
/*! \brief Address pin 13 */
#define IO_EXT_BUS_ADDR13         (13)
/*! \brief Address pin 14 */
#define IO_EXT_BUS_ADDR14         (14)
/*! \brief Address pin 15 */
#define IO_EXT_BUS_ADDR15         (15)
/*! \brief Address pin 16 */
#define IO_EXT_BUS_ADDR16         (16)
/*! \brief Address pin 17 */
#define IO_EXT_BUS_ADDR17         (17)
/*! \brief Address pin 18 */
#define IO_EXT_BUS_ADDR18         (18)
/*! \brief Address pin 19 */
#define IO_EXT_BUS_ADDR19         (19)
/*! \brief Address pin 20 */
#define IO_EXT_BUS_ADDR20         (20)
/*! \brief Address pin 21 */
#define IO_EXT_BUS_ADDR21         (21)
/*! \brief Address pin 22 */
#define IO_EXT_BUS_ADDR22         (22)
/*! \brief Address pin 23 */
#define IO_EXT_BUS_ADDR23         (23)
/*! \brief Address pin 24 */
#define IO_EXT_BUS_ADDR24         (24)

/* Addr signal channel */
/*! \brief Data pin 0 */
#define IO_EXT_BUS_DATA0           (0)
/*! \brief Data pin 1 */
#define IO_EXT_BUS_DATA1           (1)
/*! \brief Data pin 2 */
#define IO_EXT_BUS_DATA2           (2)
/*! \brief Data pin 3 */
#define IO_EXT_BUS_DATA3           (3)
/*! \brief Data pin 4 */
#define IO_EXT_BUS_DATA4           (4)
/*! \brief Data pin 5 */
#define IO_EXT_BUS_DATA5           (5)
/*! \brief Data pin 6 */
#define IO_EXT_BUS_DATA6           (6)
/*! \brief Data pin 7 */
#define IO_EXT_BUS_DATA7           (7)
/*! \brief Data pin 8 */
#define IO_EXT_BUS_DATA8           (8)
/*! \brief Data pin 9 */
#define IO_EXT_BUS_DATA9           (9)
/*! \brief Data pin 10 */
#define IO_EXT_BUS_DATA10          (10)
/*! \brief Data pin 11 */
#define IO_EXT_BUS_DATA11          (11)
/*! \brief Data pin 12 */
#define IO_EXT_BUS_DATA12          (12)
/*! \brief Data pin 13 */
#define IO_EXT_BUS_DATA13          (13)
/*! \brief Data pin 14 */
#define IO_EXT_BUS_DATA14          (14)
/*! \brief Data pin 15 */
#define IO_EXT_BUS_DATA15          (15)

/*--------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
	
#endif

/* 1. Analog input setting */
void IO_EnableAnalogInput(uint32_t Pin);
void IO_DisableAnalogInput(uint32_t Pin);
/* 2. Function setting */
void IO_EnableFunc(uint8_t Port, uint32_t Pin);
void IO_DisableFunc(uint8_t Port, uint32_t Pin);
/* 2.1 GPIO setting */
void IO_ConfigGPIOPin(uint8_t Port, uint32_t Pin, uint8_t Dir, uint8_t Pullup);
void IO_WriteGPIOPin(uint8_t Port, uint32_t Pin, uint8_t Data );
uint8_t IO_ReadGPIOPin(uint8_t Port, uint32_t Pin);
/* 2.2. Function configuration */
/* 2.2.1 MFT */
void IO_ConfigFuncMFTICx3Pin(uint8_t MFTCh, IO_MFTICx3PinT PinType);
void IO_ConfigFuncMFTICx2Pin(uint8_t MFTCh, IO_MFTICx2PinT PinType);
void IO_ConfigFuncMFTICx1Pin(uint8_t MFTCh, IO_MFTICx1PinT PinType);
void IO_ConfigFuncMFTICx0Pin(uint8_t MFTCh, IO_MFTICx0PinT PinType);
void IO_ConfigFuncMFTFRCKxPin(uint8_t MFTCh, IO_MFTFRCKxPinT PinType);
void IO_ConfigFuncMFTDTTIXxPin(uint8_t MFTCh, IO_MFTDTTIXxPinT PinType);
void IO_ConfigFuncMFTDTIFSwitchSel(uint8_t MFTCh, 
                                   IO_MFTDTIFSwitchSelT SwitchSel);
void IO_ConfigFuncMFTRTxyPin(uint8_t MFTCh,  
                             uint8_t RTCh, 
                             IO_MFTRTOxyPinT PinType);
/* 2.2.2 BT */
void IO_ConfigFuncBTTIOBxInputPin(uint8_t BTCh, IO_BTTIOBxInputPinT PinType);
void IO_ConfigFuncBTTIOAxOuputPin(uint8_t BTCh, IO_BTTIOAxOutputPinT PinType);
void IO_ConfigFuncBTTIOAxInputPin(uint8_t BTCh, IO_BTTIOAxInputPinT PinType);
/* 2.2.3 Ext Int */
void IO_ConfigFuncINTxPin(uint8_t ExtIntCh, IO_INTxPinT PinType);

/* 2.2.4 MFS */
void IO_ConfigFuncMFSSCKxPin(uint8_t MFSCh, IO_MFSSCKxPinT PinType);
void IO_ConfigFuncMFSSOTxPin(uint8_t MFSCh, IO_MFSSOTxPinT PinType);
void IO_ConfigFuncMFSSINxPin(uint8_t MFSCh, IO_MFSSINxPinT PinType);
void IO_ConfigFuncMFSCh4CTSPin(IO_MFSCTSPinT PinType);
void IO_ConfigFuncMFSCh4RTSPin(IO_MFSRTSPinT PinType);
/* 2.2.5 CAN */
void IO_ConfigFuncCANTXxPin(uint8_t CANCh, IO_CANTXxPinT PinType);
void IO_ConfigFuncCANRXxPin(uint8_t CANCh, IO_CANRXxPinT PinType);
/* 2.2.6 ADC Trigger */
void IO_ConfigFuncADTGxPin(uint8_t ADCUnit, IO_ADTGxPinT PinType);
/* 2.2.7 QPRC */
void IO_ConfigFuncQPRCZINxPin(uint8_t QPRCCh, IO_QPRCZINxPinT PinType);
void IO_ConfigFuncQPRCAINxPin(uint8_t QPRCCh, IO_QPRCAINxPinT PinType);
void IO_ConfigFuncQPRCBINxPin(uint8_t QPRCCh, IO_QPRCBINxPinT PinType);
/* 2.2.8 Ext Bus */
/* 2.2.8.1 Collectly setting */
void IO_ConfigFuncExtBusColSetting1(uint8_t OutputState);
void IO_ConfigFuncExtBusColSetting2(uint8_t OutputState);
/* 2.2.8.2 CS control */
void IO_ConfigFuncExtBusMCSxPin(uint8_t MCSxPin, uint8_t OutputState);
/* 2.2.8.3 Data bus */
void IO_ConfigFuncExtBusMDATAxPin(uint32_t MDATAPin, uint8_t OutputState);
/* 2.2.8.4 Address bus */
void IO_ConfigFuncExtBusMADxPin(uint32_t MADPin, uint8_t OutputState);
/* 2.2.8.5 Control signal */
void IO_ConfigFuncExtBusNandCtrlPin(uint32_t OutputState);
void IO_ConfigFuncExtBusMOEXPin(uint32_t OutputState);
void IO_ConfigFuncExtBusMDQMxPin(uint32_t OutputState);
void IO_ConfigFuncExtBusMWEXPin(uint32_t OutputState);
void IO_ConfigFuncExtBusMCLKOUTPin(uint32_t OutputState);
void IO_ConfigFuncExtBusMALEPin(uint32_t OutputState);
/* 2.2.9 System */
void IO_ConfigFuncTracePin(uint8_t PinState0, uint8_t PinState1);
void IO_ConfigFuncJtagPin(uint8_t PinState0, uint8_t PinState1);
void IO_ConfigFuncUSBHCONTX(uint8_t PinState);
void IO_ConfigFuncCROUTPin(uint32_t PinState);
void IO_ConfigFuncNMIPin(uint32_t PinState);
/* 2.2.10 Special */
void IO_ConfigFuncUSBPin(uint8_t PinState);
void IO_ConfigFuncMClkPin(uint8_t PinState);
void IO_ConfigFuncSClkPin(uint8_t PinState);

#ifdef __cplusplus
}
#endif


#endif /* _IO_FM3_H_ */
/*****************************************************************************/
/* END OF FILE */
 
