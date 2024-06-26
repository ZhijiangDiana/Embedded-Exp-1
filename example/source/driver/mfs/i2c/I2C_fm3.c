/*!
 ******************************************************************************
 **
 ** \file I2C_fm3.c
 **
 ** \brief I2C drivers
 **
 ** \author FSLA AE Team
 **
 ** \version V0.10
 **
 ** \date 2012-02-09
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
 
/*---------------------------------------------------------------------------*/
/* include files                                                             */
/*---------------------------------------------------------------------------*/
#include "I2C_fm3.h"

/*---------------------------------------------------------------------------*/
/* Bit definition                                                            */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* local datatypes                                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static FM3_MFS03_I2C_TypeDef* pMFS_I2C_REG_07[8] = 
{
    (FM3_MFS03_I2C_TypeDef*)(FM3_MFS0_I2C),
    (FM3_MFS03_I2C_TypeDef*)(FM3_MFS1_I2C),
    (FM3_MFS03_I2C_TypeDef*)(FM3_MFS2_I2C),
    (FM3_MFS03_I2C_TypeDef*)(FM3_MFS3_I2C),
    (FM3_MFS03_I2C_TypeDef*)(FM3_MFS4_I2C),
    (FM3_MFS03_I2C_TypeDef*)(FM3_MFS5_I2C),
    (FM3_MFS03_I2C_TypeDef*)(FM3_MFS6_I2C),
    (FM3_MFS03_I2C_TypeDef*)(FM3_MFS7_I2C),
};
static FM3_MFS47_I2C_TypeDef* pMFS_I2C_REG_47[8] = 
{
    (FM3_MFS47_I2C_TypeDef*)(0),
    (FM3_MFS47_I2C_TypeDef*)(0),
    (FM3_MFS47_I2C_TypeDef*)(0),
    (FM3_MFS47_I2C_TypeDef*)(0),
    (FM3_MFS47_I2C_TypeDef*)(FM3_MFS4_I2C),
    (FM3_MFS47_I2C_TypeDef*)(FM3_MFS5_I2C),
    (FM3_MFS47_I2C_TypeDef*)(FM3_MFS6_I2C),
    (FM3_MFS47_I2C_TypeDef*)(FM3_MFS7_I2C),
};
/*---------------------------------------------------------------------------*/
/* local functions prototypes                                                */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* global data                                                               */
/*---------------------------------------------------------------------------*/
extern MFS_CallbackT g_pMFSIRQCallback[16];

/*---------------------------------------------------------------------------*/
/* global functions                                                          */
/*---------------------------------------------------------------------------*/

/*!
 ******************************************************************************
 ** \brief Config the I2C baud rate
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \param baudrate
 ** \param unsigned int
 ** \arg   Baud rate value
 **         
 ** \retval None
 **
 ******************************************************************************
 */
void MFS_I2CConfigBaudrate(uint8_t Ch, uint32_t baudrate)
{
    uint16_t tBGR;
    uint32_t tSysFrePCLK2;
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    tSysFrePCLK2 = SystemCoreClock/(1<<((FM3_CRG->APBC2_PSR&0x03)));  //8div
    tBGR = (uint16_t)(((tSysFrePCLK2 + (baudrate / 2)) / (uint32_t)baudrate) - 1);
    pMFS_I2C_REG_07[Ch]->BGR = tBGR;
    return;
}

/*!
 ******************************************************************************
 ** \brief Config the I2C mode
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CConfigI2CMode(uint8_t Ch)
{
    uint8_t tSMR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tSMR = pMFS_I2C_REG_07[Ch]->SMR;
    tSMR = tSMR | MFS_MODE_I2C;
    pMFS_I2C_REG_07[Ch]->SMR = tSMR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Config Master mode
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CConfigMasterMode(uint8_t Ch)
{
    uint8_t tIBCR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR | I2C_IBCR_MSS;
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Config Slave mode
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CConfigSlaveMode(uint8_t Ch)
{
    uint8_t tIBCR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR & (~I2C_IBCR_MSS);
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Clear SCC
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CClrSCC(uint8_t Ch)
{
    uint8_t tIBCR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR & (~I2C_IBCR_SCC);
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Set SCC
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CSetSCC(uint8_t Ch)
{
    uint8_t tIBCR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR | I2C_IBCR_SCC;
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Clear MSS
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CClrMSS(uint8_t Ch)
{
    uint8_t tIBCR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR & (~I2C_IBCR_MSS);
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Enable I2C Bus
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CEnableI2C(uint8_t Ch)
{
    uint8_t tISMK = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tISMK = pMFS_I2C_REG_07[Ch]->ISMK;
    tISMK = tISMK | I2C_ISMK_EN;
    pMFS_I2C_REG_07[Ch]->ISMK = tISMK;
    return;
}
/*!
 ******************************************************************************
 ** \brief Disable I2C Bus
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CDisableI2C(uint8_t Ch)
{
    uint8_t tISMK = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tISMK = pMFS_I2C_REG_07[Ch]->ISMK;
    tISMK = tISMK & (~I2C_ISMK_EN);
    pMFS_I2C_REG_07[Ch]->ISMK = tISMK;
    return;
}
/*!
 ******************************************************************************
 ** \brief Clear INT
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CClrINT(uint8_t Ch)
{
    uint8_t tIBCR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR & (~I2C_IBCR_INT);
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Clear SPC
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CClrSPC(uint8_t Ch)
{
    uint8_t tIBSR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tIBSR = pMFS_I2C_REG_07[Ch]->IBSR;
    tIBSR = tIBSR & (~I2C_IBSR_SPC);
    pMFS_I2C_REG_07[Ch]->IBSR = tIBSR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Clear RSC
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CClrRSC(uint8_t Ch)
{
    uint8_t tIBSR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tIBSR = pMFS_I2C_REG_07[Ch]->IBSR;
    tIBSR = tIBSR & (~I2C_IBSR_RSC);
    pMFS_I2C_REG_07[Ch]->IBSR = tIBSR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Set WSEL as 0
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CWSEL9(uint8_t Ch)
{
    uint8_t tIBCR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR & (~I2C_IBCR_WSEL);
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Set WSEL as 1
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CWSEL8(uint8_t Ch)
{
    uint8_t tIBCR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR | I2C_IBCR_WSEL;
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Check INT Status
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetINTStatus(uint8_t Ch)
{
    ASSERT(Ch <= I2C_Ch_MAX);
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->IBCR & I2C_IBCR_INT) == I2C_IBCR_INT));
}
/*!
 ******************************************************************************
 ** \brief Check TDRE Status
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetTDREStatus(uint8_t Ch)
{
    ASSERT(Ch <= I2C_Ch_MAX);
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->SSR & I2C_SSR_TDRE) == I2C_SSR_TDRE));
}
/*!
 ******************************************************************************
 ** \brief Check RDRF Status
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetRDRFStatus(uint8_t Ch)
{
    ASSERT(Ch <= I2C_Ch_MAX);
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->SSR & I2C_SSR_RDRF) == I2C_SSR_RDRF));
}
/*!
 ******************************************************************************
 ** \brief Check SPC Status
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetSPCStatus(uint8_t Ch)
{
    ASSERT(Ch <= I2C_Ch_MAX);
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->IBSR & I2C_IBSR_SPC) == I2C_IBSR_SPC));
}

/*!
 ******************************************************************************
 ** \brief Enable ACKE
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CEnableACKE(uint8_t Ch)
{
    uint8_t tIBCR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR | I2C_IBCR_ACKE;
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Disable ACKE
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CDisableACKE(uint8_t Ch)
{
    uint8_t tIBCR = 0;

    ASSERT(Ch <= I2C_Ch_MAX);

    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR & (~I2C_IBCR_ACKE);
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}

/*!
 ******************************************************************************
 ** \brief Config the I2C FIFO
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \param FIFO initialization data
 ** \arg   FIFO config info
 **         
 ** \return None
 **
 ******************************************************************************
 */
void MFS_I2CConfigFIFO(uint8_t Ch, MFS_I2CFIFOConfigT *pFIFOConfig)
{
    uint8_t tFCR1 = 0;
    uint8_t tFCR0 = 0;
    /* Check Cfg parameter */
    ASSERT((Ch <= I2C_Ch_MAX) && (Ch >= I2C_Ch_FIFOMIN));
    
    if(pFIFOConfig->FIFOSel == I2C_FIFO1_TX)
    {
        tFCR1 = tFCR1 & (~I2C_FCR1_FSEL);
    }
    else
    {
        tFCR1 = tFCR1 | I2C_FCR1_FSEL;
    }
    /* reset FIFO1 and FIFO2*/
    tFCR0 = tFCR0 | I2C_FCR0_FCL2 | I2C_FCR0_FCL1 ;

    pMFS_I2C_REG_47[Ch]->FCR1 = tFCR1;
    pMFS_I2C_REG_47[Ch]->FCR0 = tFCR0 | I2C_FCR0_FE1 | I2C_FCR0_FE2;
   
    return;
}

/*!
 ******************************************************************************
 ** \brief Get MSS bit Status
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return State of MSS
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetMSSStatus(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->IBCR & I2C_IBCR_MSS) == I2C_IBCR_MSS));
}
/*!
 ******************************************************************************
 ** \brief Get ACT bit Status
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return State of ACT
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetACTStatus(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->IBCR & I2C_IBCR_ACT) == I2C_IBCR_ACT));
}

/*!
 ******************************************************************************
 ** \brief Enable condition detection interrupt
 **         
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **
 ** \return none
 **
 ******************************************************************************
 */
 void MFS_I2CEnableCND(uint8_t Ch)
{
    uint8_t tIBCR;
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR | I2C_IBCR_CNDE;
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Disable condition detection interrupt
 **         
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **
 ** \return none
 **
 ******************************************************************************
 */
 void MFS_I2CDisableCND(uint8_t Ch)
{
    uint8_t tIBCR;
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR & (~I2C_IBCR_CNDE);
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}

/*!
 ******************************************************************************
 ** \brief Enable INT interrupt (data transmission/reception/bus error)
 **         
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **
 ** \return none
 **
 ******************************************************************************
 */
 void MFS_I2CEnableINT(uint8_t Ch)
{
    uint8_t tIBCR;
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR | I2C_IBCR_INTE;
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Disable INT interrupt (data transmission/reception/bus error)
 **         
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **
 ** \return none
 **
 ******************************************************************************
 */
 void MFS_I2CDisableINT(uint8_t Ch)
{
    uint8_t tIBCR;
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR & (~I2C_IBCR_INTE);
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Clear interrupt requirement.
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return none
 **         
 ******************************************************************************
 */
void MFS_I2CClrInt(uint8_t Ch)
{
    uint8_t tIBCR;
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    tIBCR = pMFS_I2C_REG_07[Ch]->IBCR;
    tIBCR = tIBCR & (~I2C_IBCR_INT);
    pMFS_I2C_REG_07[Ch]->IBCR = tIBCR;
    return;
}

/*!
 ******************************************************************************
 ** \brief Get Bus Error status
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return Status of bus
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetBusErrStatus(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->IBCR & I2C_IBCR_BER) == I2C_IBCR_BER));
}

/*!
 ******************************************************************************
 ** \brief Enable receive interrupt
 **         
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CEnableRIE(uint8_t Ch)
{
    uint8_t tSMR;
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    tSMR = pMFS_I2C_REG_07[Ch]->SMR;
    tSMR = tSMR | I2C_SMR_RIE;
    pMFS_I2C_REG_07[Ch]->SMR = tSMR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Disable receive interrupt
 **         
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CDisableRIE(uint8_t Ch)
{
    uint8_t tSMR;
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    tSMR = pMFS_I2C_REG_07[Ch]->SMR;
    tSMR = tSMR & (~I2C_SMR_RIE);
    pMFS_I2C_REG_07[Ch]->SMR = tSMR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Enable transmit interrupt
 **         
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CEnableTIE(uint8_t Ch)
{
    uint8_t tSMR;
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    tSMR = pMFS_I2C_REG_07[Ch]->SMR;
    tSMR = tSMR | I2C_SMR_TIE;
    pMFS_I2C_REG_07[Ch]->SMR = tSMR;
    return;
}
/*!
 ******************************************************************************
 ** \brief Disable transmit interrupt
 **         
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CDisableTIE(uint8_t Ch)
{
    uint8_t tSMR;
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    tSMR = pMFS_I2C_REG_07[Ch]->SMR;
    tSMR = tSMR & (~I2C_SMR_TIE);
    pMFS_I2C_REG_07[Ch]->SMR = tSMR;
    return;
}

/*!
 ******************************************************************************
 ** \brief Get status of first byte condition
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return State of first byte
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetFstByteStatus(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->IBSR & I2C_IBSR_FBT) == I2C_IBSR_FBT));
}

/*!
 ******************************************************************************
 ** \brief Get ACK status
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return State of ACK
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetAckStatus(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->IBSR & I2C_IBSR_RACK) == I2C_IBSR_RACK));
}

/*!
 ******************************************************************************
 ** \brief Get data direction status
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return Direction of data (0: rec; 1: trs)
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetDataDirStatus(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->IBSR & I2C_IBSR_TRX) == I2C_IBSR_TRX));
}

/*!
 ******************************************************************************
 ** \brief Get arbitration lost status
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return Lost or not
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetArbitLostStatus(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->IBSR & I2C_IBSR_AL) == I2C_IBSR_AL));
}

/*!
 ******************************************************************************
 ** \brief Get iteration start status
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return State of iteration start
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetIterStartStatus(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->IBSR & I2C_IBSR_RSC) == I2C_IBSR_RSC));
}

/*!
 ******************************************************************************
 ** \brief Get I2C bus status
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return State of I2C bus
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetBusStatus(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->IBSR & I2C_IBSR_BB) == I2C_IBSR_BB));
}

/*!
 ******************************************************************************
 ** \brief Clear receive error flag (ORE)
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CClrRcvErrFlag(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    //pMFS_I2C_REG_07[Ch]->SSR_f.REC = TRUE;
}

/*!
 ******************************************************************************
 ** \brief Get over run status
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return State of over run
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetOverRunErrStatus(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->SSR & I2C_SSR_ORE) == I2C_SSR_ORE));
}

/*!
 ******************************************************************************
 ** \brief Get transmit bus idle status
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return State of trasmit bus idle
 **
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetTBIStatus(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->SSR & I2C_SSR_TBI) == I2C_SSR_TBI));
}

/*!
 ******************************************************************************
 ** \brief read a date from RDR.
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return Data in RDR register(16bit)
 **         
 ******************************************************************************
 */
uint8_t MFS_I2CReadAData(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return pMFS_I2C_REG_07[Ch]->RDR;
}

/*!
 ******************************************************************************
 ** \brief Write a date to TDR.
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \param Data requir to write data
 ** \arg   16bit data
 **
 ** \return none
 **         
 ******************************************************************************
 */
void MFS_I2CWriteAData(uint8_t Ch, uint16_t Data)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    pMFS_I2C_REG_07[Ch]->TDR = Data;
}

/*!
 ******************************************************************************
 ** \brief Check I2C interface is enabled or disabled
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 **
 ** \return TRUE  - enable
 **         FALSE - disable
 ******************************************************************************
 */
FlagStatusT MFS_I2CGetI2CENStatus(uint8_t Ch)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    return ((FlagStatusT)((pMFS_I2C_REG_07[Ch]->ISMK & I2C_ISMK_EN) == I2C_ISMK_EN));
}

/*!
 ******************************************************************************
 ** \brief Set mask bit for I2C slave address
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \param MaskBits - A byte to mask slave address, every bit=1 will be masked
 ** \arg  
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CSetMaskSlaveAddrBits(uint8_t Ch, uint8_t MaskBits)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    ASSERT(MaskBits <= 127);
    
    pMFS_I2C_REG_07[Ch]->ISMK = (pMFS_I2C_REG_07[Ch]->ISMK & 0x80) | MaskBits;
    return;
}

/*!
 ******************************************************************************
 ** \brief Enable slave address
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \param En - Enable or Disable
 ** \arg   Valid value is [TRUE, FALSE]
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CEnableSlaveAddr(uint8_t Ch)
{
    uint8_t tISBA;
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    tISBA = pMFS_I2C_REG_07[Ch]->ISBA;
    tISBA = tISBA | I2C_ISBA_SAEN;
    pMFS_I2C_REG_07[Ch]->ISBA = tISBA;
    return;
}
/*!
 ******************************************************************************
 ** \brief Disable slave address
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \param En - Enable or Disable
 ** \arg   Valid value is [TRUE, FALSE]
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CDisableSlaveAddr(uint8_t Ch)
{
    uint8_t tISBA;
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    
    tISBA = pMFS_I2C_REG_07[Ch]->ISBA;
    tISBA = tISBA & (~I2C_ISBA_SAEN);
    pMFS_I2C_REG_07[Ch]->ISBA = tISBA;
    return;
}

/*!
 ******************************************************************************
 ** \brief Configure I2C slave address.
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \param SlaveAddr - slave address
 ** \arg  
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CConfigSlaveAddr(uint8_t Ch, uint8_t SlaveAddr)
{
    /* Check Cfg parameter */
    ASSERT(Ch <= I2C_Ch_MAX);
    ASSERT(SlaveAddr <= 127);
    
    pMFS_I2C_REG_07[Ch]->ISBA = (pMFS_I2C_REG_07[Ch]->ISBA & 0x80) | SlaveAddr;
}

/*!
 ******************************************************************************
 ** \brief Enable FIFO1
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch4-MFS_Ch7
 **         
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CEnableFIFO1(uint8_t Ch)
{
    uint8_t tFCR0;
    /* Check Cfg parameter */
    ASSERT((Ch >= I2C_Ch_FIFOMIN) && (Ch <= I2C_Ch_FIFOMAX));
    
    tFCR0 = pMFS_I2C_REG_47[Ch]->FCR0;
    tFCR0 = tFCR0 | I2C_FCR0_FE1;
    pMFS_I2C_REG_47[Ch]->FCR0 = tFCR0;
}
/*!
 ******************************************************************************
 ** \brief Disable FIFO1
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch4-MFS_Ch7
 **         
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CDisableFIFO1(uint8_t Ch)
{
    uint8_t tFCR0;
    /* Check Cfg parameter */
    ASSERT((Ch >= I2C_Ch_FIFOMIN) && (Ch <= I2C_Ch_FIFOMAX));
    
    tFCR0 = pMFS_I2C_REG_47[Ch]->FCR0;
    tFCR0 = tFCR0 & (~I2C_FCR0_FE1);
    pMFS_I2C_REG_47[Ch]->FCR0 = tFCR0;
}
/*!
 ******************************************************************************
 ** \brief Enable FIFO2
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch4-MFS_Ch7
 **         
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CEnableFIFO2(uint8_t Ch)
{
    uint8_t tFCR0;
    /* Check Cfg parameter */
    ASSERT((Ch >= I2C_Ch_FIFOMIN) && (Ch <= I2C_Ch_FIFOMAX));
    
    tFCR0 = pMFS_I2C_REG_47[Ch]->FCR0;
    tFCR0 = tFCR0 | I2C_FCR0_FE2;
    pMFS_I2C_REG_47[Ch]->FCR0 = tFCR0;
}
/*!
 ******************************************************************************
 ** \brief Disable FIFO2
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch4-MFS_Ch7
 **         
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CDisableFIFO2(uint8_t Ch)
{
    uint8_t tFCR0;
    /* Check Cfg parameter */
    ASSERT((Ch >= I2C_Ch_FIFOMIN) && (Ch <= I2C_Ch_FIFOMAX));
    
    tFCR0 = pMFS_I2C_REG_47[Ch]->FCR0;
    tFCR0 = tFCR0 & (~I2C_FCR0_FE2);
    pMFS_I2C_REG_47[Ch]->FCR0 = tFCR0;
}
/*!
 ******************************************************************************
 ** \brief set FIFO1 data depth
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch4-MFS_Ch7
 **         
 ** \param length
 ** \arg   data
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CSetFIFO1Length(uint8_t Ch, uint32_t Length)
{
    /* Check Cfg parameter */
    ASSERT((Ch >= I2C_Ch_FIFOMIN) && (Ch <= I2C_Ch_FIFOMAX));
    ASSERT(Length<=I2C_FIFO_MAX_DEPTH);
    
    pMFS_I2C_REG_47[Ch]->FBYTE1 = Length;
}

/*!
 ******************************************************************************
 ** \brief set FIFO2 data depth
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch4-MFS_Ch7
 **         
 ** \param length
 ** \arg   data
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CSetFIFO2Length(uint8_t Ch, uint32_t Length)
{
    /* Check Cfg parameter */
    ASSERT((Ch >= I2C_Ch_FIFOMIN) && (Ch <= I2C_Ch_FIFOMAX));
    ASSERT(Length<=I2C_FIFO_MAX_DEPTH);
    
    pMFS_I2C_REG_47[Ch]->FBYTE2 = Length;
}
/*!
 ******************************************************************************
 ** \brief Clear FIFO send interrupt requirement
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch4-MFS_Ch7
 **
 **
 ** \return none
 **
 ******************************************************************************
 */
 void MFS_I2CClrFIFOSendReq(uint8_t Ch)
{
    uint8_t tFCR1;
    /* Check Cfg parameter */
    ASSERT((Ch >= I2C_Ch_FIFOMIN) && (Ch <= I2C_Ch_FIFOMAX));
   
    tFCR1 = pMFS_I2C_REG_47[Ch]->FCR1;
    tFCR1 = tFCR1 & (~I2C_FCR1_FDRQ);
    pMFS_I2C_REG_47[Ch]->FCR1 = tFCR1;
}

/*!
 ******************************************************************************
 ** \brief Set FIFO send request 
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch4-MFS_Ch7
 **
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CSetFIFOSendReq(uint8_t Ch)
{
    uint8_t tFCR1;
    /* Check Cfg parameter */
    ASSERT((Ch >= I2C_Ch_FIFOMIN) && (Ch <= I2C_Ch_FIFOMAX));
   
    tFCR1 = pMFS_I2C_REG_47[Ch]->FCR1;
    tFCR1 = tFCR1 | I2C_FCR1_FDRQ;
    pMFS_I2C_REG_47[Ch]->FCR1 = tFCR1;
}

/*!
 ******************************************************************************
 ** \brief Enable FIFO transmit interrupt 
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch4-MFS_Ch7
 **
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CEnableFIFOTrsINT(uint8_t Ch)
{
    uint8_t tFCR1;
    /* Check Cfg parameter */
    ASSERT((Ch >= I2C_Ch_FIFOMIN) && (Ch <= I2C_Ch_FIFOMAX));
   
    tFCR1 = pMFS_I2C_REG_47[Ch]->FCR1;
    tFCR1 = tFCR1 | I2C_FCR1_FTIE;
    pMFS_I2C_REG_47[Ch]->FCR1 = tFCR1;
}
/*!
 ******************************************************************************
 ** \brief Disable FIFO transmit interrupt 
 **  
 ** \param Ch Requested channel
 ** \arg   MFS_Ch4-MFS_Ch7
 **
 **
 ** \return none
 **
 ******************************************************************************
 */
void MFS_I2CDisableFIFOTrsINT(uint8_t Ch)
{
    uint8_t tFCR1;
    /* Check Cfg parameter */
    ASSERT((Ch >= I2C_Ch_FIFOMIN) && (Ch <= I2C_Ch_FIFOMAX));
   
    tFCR1 = pMFS_I2C_REG_47[Ch]->FCR1;
    tFCR1 = tFCR1 & (~I2C_FCR1_FTIE);
    pMFS_I2C_REG_47[Ch]->FCR1 = tFCR1;
}
