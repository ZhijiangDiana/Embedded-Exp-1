/*!
 ******************************************************************************
 **
 ** \file io_fm3.c
 **
 ** \brief IO driver
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
 
/*---------------------------------------------------------------------------*/
/* include files                                                             */
/*---------------------------------------------------------------------------*/
#include "Io_fm3.h"

/*---------------------------------------------------------------------------*/
/* local Definition                                                          */
/*---------------------------------------------------------------------------*/
#define GPIO_PFR_BASE_ADDR      (volatile uint32_t*)(&FM3_GPIO->PFR0)
#define GPIO_DDR_BASE_ADDR      (volatile uint32_t*)(&FM3_GPIO->DDR0)
#define GPIO_PDOR_BASE_ADDR     (volatile uint32_t*)(&FM3_GPIO->PDOR0)
#define GPIO_PDIR_BASE_ADDR     (volatile uint32_t*)(&FM3_GPIO->PDIR0)
#define GPIO_PCR_BASE_ADDR      (volatile uint32_t*)(&FM3_GPIO->PCR0)

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* local functions prototypes                                                */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* global data                                                               */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* global functions                                                          */
/*---------------------------------------------------------------------------*/

/*!
 ******************************************************************************
 ** \brief Enable Analog input of ADC function
 **
 ** \param Pin Pin index
 ** \arg IO_PINx0
 ** \arg IO_PINx1
 ** \arg ...
 ** \arg IO_PINx14
 ** \arg IO_PINx15
 ** \return None
 ******************************************************************************
 */
void IO_EnableAnalogInput(uint32_t Pin)
{
    FM3_GPIO->ADE |= Pin;
    return;
}

/*!
 ******************************************************************************
 ** \brief Disable Analog input of ADC function
 **
 ** \param Pin Pin index
 ** \arg IO_PINx0
 ** \arg IO_PINx1
 ** \arg ...
 ** \arg IO_PINx14
 ** \arg IO_PINx15
 ** \return None
 ******************************************************************************
 */
void IO_DisableAnalogInput(uint32_t Pin)
{
    FM3_GPIO->ADE &= ~Pin;
    return;
}
 
/*!
 ******************************************************************************
 ** \brief Enable peripheral function setting for a specific pin
 **
 ** \param Port Port index
 ** \arg IO_PORT0
 ** \arg IO_PORT1
 ** \arg ...
 ** \arg IO_PORT14
 ** \arg IO_PORT15
 ** \param Pin Pin index
 ** \arg IO_PINx0
 ** \arg IO_PINx1
 ** \arg ...
 ** \arg IO_PINx14
 ** \arg IO_PINx15
 **
 ** \return None
 ******************************************************************************
 */
void IO_EnableFunc(uint8_t Port, uint32_t Pin)
{
    volatile uint32_t* ppfraddr;
    ppfraddr = GPIO_PFR_BASE_ADDR + Port;
    *ppfraddr |= Pin;
    return;
}

/*!
 ******************************************************************************
 ** \brief Disable peripheral function setting for a specific pin
 **
 ** \param Port Port index
 ** \arg IO_PORT0
 ** \arg IO_PORT1
 ** \arg ...
 ** \arg IO_PORT14
 ** \arg IO_PORT15
 ** \param Pin Pin index
 ** \arg IO_PINx0
 ** \arg IO_PINx1
 ** \arg ...
 ** \arg IO_PINx14
 ** \arg IO_PINx15
 **
 ** \return None
 ******************************************************************************
 */
void IO_DisableFunc(uint8_t Port, uint32_t Pin)
{
    volatile uint32_t* ppfraddr;
    ppfraddr = GPIO_PFR_BASE_ADDR + Port;
    *ppfraddr &= ~Pin;
    return;
}

/*!
 ******************************************************************************
 ** \brief Configure general purpose IO function setting for a specific pin
 **
 ** \param Port Port index
 ** \arg IO_PORT0
 ** \arg IO_PORT1
 ** \arg ...
 ** \arg IO_PORT14
 ** \arg IO_PORT15
 ** \param Pin Pin index
 ** \arg IO_PINx0
 ** \arg IO_PINx1
 ** \arg ...
 ** \arg IO_PINx14
 ** \arg IO_PINx15
 ** \param Dir IO direction
 ** \arg IO_DIR_INPUT
 ** \arg IO_DIR_OUTPUT
 ** \param Pulllup Pull-up register selection
 ** \arg IO_PULLUP_OFF
 ** \arg IO_PULLUP_ON
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigGPIOPin(uint8_t Port, uint32_t Pin, uint8_t Dir, uint8_t Pullup)
{
    volatile uint32_t *pddraddr, *ppcraddr;
    pddraddr = GPIO_DDR_BASE_ADDR + Port;
    ppcraddr = GPIO_PCR_BASE_ADDR + Port;
    if(Dir == IO_DIR_OUTPUT)
    {
        *pddraddr |= Pin;
    }
    else if(Dir == IO_DIR_INPUT)
    {
        *pddraddr &= ~Pin;
    }
    
    if(Pullup == IO_PULLUP_OFF)
    {
        *ppcraddr &= ~Pin;
    }
    else if(Pullup == IO_PULLUP_ON)
    {
        *ppcraddr |= Pin;
    }
    
    return;
}

/*!
 ******************************************************************************
 ** \brief Write the data to a specific pin
 **
 ** \param Port Port index
 ** \arg IO_PORT0
 ** \arg IO_PORT1
 ** \arg ...
 ** \arg IO_PORT14
 ** \arg IO_PORT15
 ** \param Pin Pin index
 ** \arg IO_PINx0
 ** \arg IO_PINx1
 ** \arg ...
 ** \arg IO_PINx14
 ** \arg IO_PINx15
 ** \param Data the data output to the IO pin
 ** \arg IO_BIT_CLR
 ** \arg IO_BIT_SET
 **
 ** \return None
 ******************************************************************************
 */
void IO_WriteGPIOPin(uint8_t Port, uint32_t Pin, uint8_t Data )
{
    volatile uint32_t *ppdoraddr;
    ppdoraddr = GPIO_PDOR_BASE_ADDR + Port;
    if(Data == IO_BIT_CLR)
    {
        *ppdoraddr &= ~Pin;
    }
    else if(Data == IO_BIT_SET)
    {
        *ppdoraddr |= Pin;
    }
    
    return;
}

/*!
 ******************************************************************************
 ** \brief Read the pin level of a specific pin
 **
 ** \param Port Port index
 ** \arg IO_PORT0
 ** \arg IO_PORT1
 ** \arg ...
 ** \arg IO_PORT14
 ** \arg IO_PORT15
 ** \param Pin Pin index
 ** \arg IO_PINx0
 ** \arg IO_PINx1
 ** \arg ...
 ** \arg IO_PINx14
 ** \arg IO_PINx15
 ** \param pData the data input from the IO pin
 **
 ** \return None
 ******************************************************************************
 */
uint8_t IO_ReadGPIOPin(uint8_t Port, uint32_t Pin)
{
    volatile uint32_t *ppdiraddr;
    uint8_t tempdata, cnt;
    ppdiraddr = GPIO_PDIR_BASE_ADDR + Port;
    for(cnt = 0; cnt<16; cnt++)
    {
        if(0 == (Pin>>cnt))
        {
           cnt = cnt -1;
           break;
        }
    }
    tempdata =  (*ppdiraddr & Pin) >> cnt; 
    
    return (tempdata & 0x01); 
}

/*!
 ******************************************************************************
 ** \brief Select the pin location of ICx3 of IC timer of MFT
 **
 ** \param MFTCh MFT channel
 ** \arg IO_MFT_CH0
 ** \arg IO_MFT_CH1
 ** \param PinType Pin Type
 ** \arg IO_MFT_ICx3_ICx3_INIT
 ** \arg IO_MFT_ICx3_ICx3_0
 ** \arg IO_MFT_ICx3_ICx3_1
 ** \arg IO_MFT_ICx3_ICx3_2
 ** \arg IO_MFT_ICx3_MFSCH3LSYN
 ** \arg IO_MFT_ICx3_MFSCH7LSYN
 ** \arg IO_MFT_ICx3_CRTRIM
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFTICx3Pin(uint8_t MFTCh, IO_MFTICx3PinT PinType)
{
    uint8_t setmap[7] = {0, 1, 2, 3, 4, 5, 7};
    volatile uint32_t *pepfraddr;
    
    if((MFTCh == IO_MFT_CH1) &&
       ((PinType == IO_MFT_ICx3_CRTRIM) || (PinType == IO_MFT_ICx3_ICx3_2)))
    {
        return;
    }
        
    if(MFTCh == IO_MFT_CH0)
    {
        pepfraddr = &FM3_GPIO->EPFR01;
    }
    else if(MFTCh == IO_MFT_CH1)
    {
        pepfraddr = &FM3_GPIO->EPFR02;
    }    
       
    *pepfraddr &= ~(7ul<<29);
    *pepfraddr |= (setmap[PinType]<<29);
    
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the pin location of ICx2 of IC timer of MFT
 **
 ** \param MFTCh MFT channel
 ** \arg IO_MFT_CH0
 ** \arg IO_MFT_CH1
 ** \param PinType Pin Type
 ** \arg IO_MFT_ICx2_ICx2_INIT
 ** \arg IO_MFT_ICx2_ICx2_0
 ** \arg IO_MFT_ICx2_ICx2_1
 ** \arg IO_MFT_ICx2_ICx2_2
 ** \arg IO_MFT_ICx2_MFSCH2LSYN
 ** \arg IO_MFT_ICx2_MFSCH6LSYN
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFTICx2Pin(uint8_t MFTCh, IO_MFTICx2PinT PinType)
{
    volatile uint32_t *pepfraddr;
    
    if((MFTCh == IO_MFT_CH1) &&
       (PinType == IO_MFT_ICx2_ICx2_2))
    {
        return;
    }
        
    if(MFTCh == IO_MFT_CH0)
    {
        pepfraddr = &FM3_GPIO->EPFR01;
    }
    else if(MFTCh == IO_MFT_CH1)
    {
        pepfraddr = &FM3_GPIO->EPFR02;
    } 
    else
    {
        return;
    }
       
    *pepfraddr &= ~(7ul<<26);
    *pepfraddr |= (PinType<<26);
     
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the pin location of ICx1 of IC timer of MFT
 **
 ** \param MFTCh MFT channel
 ** \arg IO_MFT_CH0
 ** \arg IO_MFT_CH1
 ** \param PinType Pin Type
 ** \arg IO_MFT_ICx1_ICx1_INIT
 ** \arg IO_MFT_ICx1_ICx1_0
 ** \arg IO_MFT_ICx1_ICx1_1
 ** \arg IO_MFT_ICx1_ICx1_2
 ** \arg IO_MFT_ICx1_MFSCH1LSYN
 ** \arg IO_MFT_ICx1_MFSCH5LSYN
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFTICx1Pin(uint8_t MFTCh, IO_MFTICx1PinT PinType)
{
    volatile uint32_t *pepfraddr;
    
    if((MFTCh == IO_MFT_CH1) &&
       (PinType == IO_MFT_ICx1_ICx1_2))
    {
        return;
    }
        
    if(MFTCh == IO_MFT_CH0)
    {
        pepfraddr = &FM3_GPIO->EPFR01;
    }
    else if(MFTCh == IO_MFT_CH1)
    {
        pepfraddr = &FM3_GPIO->EPFR02;
    }   
    else
    {
        return;
    }
       
    *pepfraddr &= ~(7ul<<23);
    *pepfraddr |= (PinType<<23);
    
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the pin location of ICx0 of IC timer of MFT
 **
 ** \param MFTCh MFT channel
 ** \arg IO_MFT_CH0
 ** \arg IO_MFT_CH1
 ** \param PinType Pin Type
 ** \arg IO_MFT_ICx0_ICx0_INIT
 ** \arg IO_MFT_ICx0_ICx0_0
 ** \arg IO_MFT_ICx0_ICx0_1
 ** \arg IO_MFT_ICx0_ICx0_2
 ** \arg IO_MFT_ICx0_MFSCH0LSYN
 ** \arg IO_MFT_ICx0_MFSCH4LSYN
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFTICx0Pin(uint8_t MFTCh, IO_MFTICx0PinT PinType)
{
    volatile uint32_t *pepfraddr;
    
    if((MFTCh == IO_MFT_CH1) &&
       (PinType == IO_MFT_ICx0_ICx0_2))
    {
        return;
    }
        
    if(MFTCh == IO_MFT_CH0)
    {
        pepfraddr = &FM3_GPIO->EPFR01;
    }
    else if(MFTCh == IO_MFT_CH1)
    {
        pepfraddr = &FM3_GPIO->EPFR02;
    }    
    else
    {
        return;
    }
       
    *pepfraddr &= ~(7ul<<20);
    *pepfraddr |= (PinType<<20);
    
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the pin location of FRCK of FRT of MFT
 **
 ** \param MFTCh MFT channel
 ** \arg IO_MFT_CH0
 ** \arg IO_MFT_CH1
 ** \param PinType Pin Type
 ** \arg IO_MFT_FRCKx_FRCKx_INIT
 ** \arg IO_MFT_FRCKx_FRCKx_0
 ** \arg IO_MFT_FRCKx_FRCKx_1
 ** \arg IO_MFT_FRCKx_FRCKx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFTFRCKxPin(uint8_t MFTCh, IO_MFTFRCKxPinT PinType)
{
    volatile uint32_t *pepfraddr;
    if(MFTCh == IO_MFT_CH0)
    {
        pepfraddr = &FM3_GPIO->EPFR01;
    }
    else if(MFTCh == IO_MFT_CH1)
    {
        pepfraddr = &FM3_GPIO->EPFR02;
    }    
    else
    {
        return;
    }
    *pepfraddr &= ~(3ul<<18);
    *pepfraddr |= (PinType<<18);
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the pin location of DTTIX of FRT of MFT
 **
 ** \param MFTCh MFT channel
 ** \arg IO_MFT_CH0
 ** \arg IO_MFT_CH1
 ** \param PinType Pin Type
 ** \arg IO_MFT_DTTIXx_DTTIXx_INIT
 ** \arg IO_MFT_DTTIXx_DTTIXx_0
 ** \arg IO_MFT_DTTIXx_DTTIXx_1
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFTDTTIXxPin(uint8_t MFTCh, IO_MFTDTTIXxPinT PinType)
{
    volatile uint32_t *pepfraddr;
    if(MFTCh == IO_MFT_CH0)
    {
        pepfraddr = &FM3_GPIO->EPFR01;
    }
    else if(MFTCh == IO_MFT_CH1)
    {
        pepfraddr = &FM3_GPIO->EPFR02;
    }    
    else
    {
        return;
    }
    *pepfraddr &= ~(3ul<<16);
    *pepfraddr |= (PinType<<16);
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the DTIF switch function of MFT
 **
 ** \param MFTCh MFT channel
 ** \arg IO_MFT_CH0
 ** \arg IO_MFT_CH1
 ** \param SwitchSel Switch function selection
 ** \arg IO_MFT_DTIF_SWITCH_OFF
 ** \arg IO_MFT_DTIF_SWITCH_ON
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFTDTIFSwitchSel(uint8_t MFTCh, 
                                   IO_MFTDTIFSwitchSelT SwitchSel)
{
    volatile uint32_t *pepfraddr;
    if(MFTCh == IO_MFT_CH0)
    {
        pepfraddr = &FM3_GPIO->EPFR01;
    }
    else if(MFTCh == IO_MFT_CH1)
    {
        pepfraddr = &FM3_GPIO->EPFR02;
    }    
    else
    {
        return;
    }
    *pepfraddr &= ~(1ul<<12);
    *pepfraddr |= (SwitchSel<<12);
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the pin location of RTxy of OCU of MFT.
 **
 ** \param MFTCh MFT channel
 ** \arg IO_MFT_CH0
 ** \arg IO_MFT_CH1
 ** \param RTCh OCU channel
 ** \arg IO_MFT_RT_CH0
 ** \arg IO_MFT_RT_CH1
 ** \arg IO_MFT_RT_CH2
 ** \arg IO_MFT_RT_CH3
 ** \arg IO_MFT_RT_CH4
 ** \arg IO_MFT_RT_CH5
 ** \param PinType Pin type
 ** \arg IO_MFT_RTOxy_RTOxy_INIT
 ** \arg IO_MFT_RTOxy_RTOxy_0
 ** \arg IO_MFT_RTOxy_RTOxy_1
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFTRTxyPin(uint8_t MFTCh,  
                             uint8_t RTCh, 
                             IO_MFTRTOxyPinT PinType)
{
    volatile uint32_t *pepfraddr;
    if(MFTCh == IO_MFT_CH0)
    {
        pepfraddr = &FM3_GPIO->EPFR01;
    }
    else if(MFTCh == IO_MFT_CH1)
    {
        pepfraddr = &FM3_GPIO->EPFR02;
    }    
    else
    {
        return;
    }
    *pepfraddr &= ~(3ul<<(RTCh*2));
    *pepfraddr |= (PinType<<(RTCh*2));
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the pin location of TIOB input of BT.
 **
 ** \param BTCh BT Channel
 ** \arg IO_BT_CH0
 ** \arg IO_BT_CH1
 ** \arg ...
 ** \arg IO_BT_CH6
 ** \arg IO_BT_CH7
 ** \param PinType Pin Type
 ** \arg IO_BT_TIOBx_INPUT_INIT
 ** \arg IO_BT_TIOBx_INPUT_TIOBx_0
 ** \arg IO_BT_TIOBx_INPUT_TIOBx_1
 ** \arg IO_BT_TIOBx_INPUT_TIOBx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncBTTIOBxInputPin(uint8_t BTCh, IO_BTTIOBxInputPinT PinType)
{
    volatile uint32_t *pepfraddr;
    if(BTCh <= IO_BT_CH3)
    {
        pepfraddr = &FM3_GPIO->EPFR04;
    }
    else if((BTCh >= IO_BT_CH4) && (BTCh <= IO_BT_CH7))
    {
        pepfraddr = &FM3_GPIO->EPFR05;
    }    
    else
    {
        return;
    }
    if(BTCh <= IO_BT_CH3)
    {
        *pepfraddr &= ~(3ul<<(4+8*BTCh));
        *pepfraddr |= (PinType<<(4+8*BTCh));
    }
    else
    {
        *pepfraddr &= ~(3ul<<(4+8*(BTCh-4)));
        *pepfraddr |= (PinType<<(4+8*(BTCh-4)));
    }
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the pin location of TIOA output of BT.
 **
 ** \param BTCh BT Channel
 ** \arg IO_BT_CH0
 ** \arg IO_BT_CH1
 ** \arg ...
 ** \arg IO_BT_CH6
 ** \arg IO_BT_CH7
 ** \param PinType Pin Type
 ** \arg IO_BT_TIOAx_OUTPUT_INIT
 ** \arg IO_BT_TIOAx_OUTPUT_TIOAx_0
 ** \arg IO_BT_TIOAx_OUTPUT_TIOAx_1
 ** \arg IO_BT_TIOAx_OUTPUT_TIOAx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncBTTIOAxOuputPin(uint8_t BTCh, IO_BTTIOAxOutputPinT PinType)
{
    volatile uint32_t *pepfraddr;
    if(BTCh <= IO_BT_CH3)
    {
        pepfraddr = &FM3_GPIO->EPFR04;
    }
    else if((BTCh >= IO_BT_CH4) && (BTCh <= IO_BT_CH7))
    {
        pepfraddr = &FM3_GPIO->EPFR05;
    }    
    else
    {
        return;
    }
    if(BTCh <= IO_BT_CH3)
    {
        *pepfraddr &= ~(3ul<<(2+8*BTCh));
        *pepfraddr |= (PinType<<(2+8*BTCh));
    }
    else
    {
        *pepfraddr &= ~(3ul<<(2+8*(BTCh-4)));
        *pepfraddr |= (PinType<<(2+8*(BTCh-4)));
    }
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the pin location of TIOA input of BT.
 **
 ** \param BTCh BT Channel
 ** \arg IO_BT_CH0
 ** \arg IO_BT_CH1
 ** \arg ...
 ** \arg IO_BT_CH6
 ** \arg IO_BT_CH7
 ** \param PinType Pin Type
 ** \arg IO_BT_TIOAx_INPUT_INIT
 ** \arg IO_BT_TIOAx_INPUT_TIOAx_0
 ** \arg IO_BT_TIOAx_INPUT_TIOAx_1
 ** \arg IO_BT_TIOAx_INPUT_TIOAx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncBTTIOAxInputPin(uint8_t BTCh, IO_BTTIOAxInputPinT PinType)
{
    volatile uint32_t *pepfraddr;
    if((BTCh == IO_BT_CH1) || (BTCh == IO_BT_CH3))
    {
        pepfraddr = &FM3_GPIO->EPFR04;
    }
    else if((BTCh == IO_BT_CH5) || (BTCh == IO_BT_CH7))
    {
        pepfraddr = &FM3_GPIO->EPFR05;
    }    
    else
    {
        return;
    }
    if(BTCh <= IO_BT_CH3)
    {
        *pepfraddr &= ~(3ul<<(0+8*BTCh));
        *pepfraddr |= (PinType<<(0+8*BTCh));
    }
    else
    {
        *pepfraddr &= ~(3ul<<(0+8*(BTCh-4)));
        *pepfraddr |= (PinType<<(0+8*(BTCh-4)));
    }
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the pin location of external interrupt.
 **
 ** \param ExtIntCh External interrupt channel
 ** \arg IO_EXT_INT_CH0
 ** \arg IO_EXT_INT_CH1
 ** \arg ...
 ** \arg IO_EXT_INT_CH14
 ** \arg IO_EXT_INT_CH15
 ** \param PinType Pin Type
 ** \arg IO_INTx_INIT
 ** \arg IO_INTx_INTx_0
 ** \arg IO_INTx_INTx_1
 ** \arg IO_INTx_INTx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncINTxPin(uint8_t ExtIntCh, IO_INTxPinT PinType)
{
    volatile uint32_t *pepfraddr;
    if(ExtIntCh <= IO_EXT_INT_CH15)
    {
        pepfraddr = &FM3_GPIO->EPFR06;
    }
    else
    {
        return;
    }
    
    *pepfraddr &= ~(3ul<<(0+ExtIntCh*2));
    *pepfraddr |= (PinType<<(0+ExtIntCh*2));
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the SCKx pin location of MFS.
 **
 ** \param MFSCh MFS Channel
 ** \arg IO_MFS_CH0
 ** \arg IO_MFS_CH1
 ** \arg ...
 ** \arg IO_MFS_CH6
 ** \arg IO_MFS_CH7
 ** \param PinType Pin Type
 ** \arg IO_MFS_SCKx_SCKx_INIT
 ** \arg IO_MFS_SCKx_SCKx_0
 ** \arg IO_MFS_SCKx_SCKx_1
 ** \arg IO_MFS_SCKx_SCKx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFSSCKxPin(uint8_t MFSCh, IO_MFSSCKxPinT PinType)
{
    volatile uint32_t *pepfraddr;
    if((MFSCh >= IO_MFS_CH4) && (MFSCh <= IO_MFS_CH7))
    {
        pepfraddr = &FM3_GPIO->EPFR08;
    }
    else if(MFSCh <= IO_MFS_CH3)
    {
        pepfraddr = &FM3_GPIO->EPFR07;
    }
    else
    {
        return;
    }
    
    if(MFSCh <= IO_MFS_CH3)
    {
        *pepfraddr &= ~(3ul<<(8+6*MFSCh));
        *pepfraddr |= (PinType<<(8+6*MFSCh));
    }
    else
    {
        *pepfraddr &= ~(3ul<<(8+6*(MFSCh-4)));
        *pepfraddr |= (PinType<<(8+6*(MFSCh-4)));
    }
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the SOTx pin location of MFS.
 **
 ** \param MFSCh MFS Channel
 ** \arg IO_MFS_CH0
 ** \arg IO_MFS_CH1
 ** \arg ...
 ** \arg IO_MFS_CH6
 ** \arg IO_MFS_CH7
 ** \param PinType Pin Type
 ** \arg IO_MFS_SOTx_SOTx_INIT
 ** \arg IO_MFS_SOTx_SOTx_0
 ** \arg IO_MFS_SOTx_SOTx_1
 ** \arg IO_MFS_SOTx_SOTx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFSSOTxPin(uint8_t MFSCh, IO_MFSSOTxPinT PinType)
{
    volatile uint32_t *pepfraddr;
    if((MFSCh >= IO_MFS_CH4) && (MFSCh <= IO_MFS_CH7))
    {
        pepfraddr = &FM3_GPIO->EPFR08;
    }
    else if(MFSCh <= IO_MFS_CH3)
    {
        pepfraddr = &FM3_GPIO->EPFR07;
    }
    else
    {
        return;
    }
    
    if(MFSCh <= IO_MFS_CH3)
    {
        *pepfraddr &= ~(3ul<<(6+6*MFSCh));
        *pepfraddr |= (PinType<<(6+6*MFSCh));
    }
    else
    {
        *pepfraddr &= ~(3ul<<(6+6*(MFSCh-4)));
        *pepfraddr |= (PinType<<(6+6*(MFSCh-4)));
    }
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the SINx pin location of MFS.
 **
 ** \param MFSCh MFS Channel
 ** \arg IO_MFS_CH0
 ** \arg IO_MFS_CH1
 ** \arg ...
 ** \arg IO_MFS_CH6
 ** \arg IO_MFS_CH7
 ** \param PinType Pin Type
 ** \arg IO_MFS_SINx_INIT
 ** \arg IO_MFS_SINx_SINx_0
 ** \arg IO_MFS_SINx_SINx_1
 ** \arg IO_MFS_SINx_SINx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFSSINxPin(uint8_t MFSCh, IO_MFSSINxPinT PinType)
{
    volatile uint32_t *pepfraddr;
    if((MFSCh >= IO_MFS_CH4) && (MFSCh <= IO_MFS_CH7))
    {
        pepfraddr = &FM3_GPIO->EPFR08;
    }
    else if(MFSCh <= IO_MFS_CH3)
    {
        pepfraddr = &FM3_GPIO->EPFR07;
    }
    else
    {
        return;
    }
    
    if(MFSCh <= IO_MFS_CH3)
    {
        *pepfraddr &= ~(3ul<<(4+6*MFSCh));
        *pepfraddr |= (PinType<<(4+6*MFSCh));
    }
    else
    {
        *pepfraddr &= ~(3ul<<(4+6*(MFSCh-4)));
        *pepfraddr |= (PinType<<(4+6*(MFSCh-4)));
    }
    return;
}

/*!
 ******************************************************************************
 ** \brief Select the CTS pin location of MFS Ch4.
 **
 ** \param PinType Pin Type
 ** \arg IO_MFS_CTS4_INIT
 ** \arg IO_MFS_CTS4_CTS4_0
 ** \arg IO_MFS_CTS4_CTS4_1
 ** \arg IO_MFS_CTS4_CTS4_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFSCh4CTSPin(IO_MFSCTSPinT PinType)
{
    volatile uint32_t *pepfraddr;
    pepfraddr = &FM3_GPIO->EPFR08;
    *pepfraddr &= ~(3ul<<2);
    *pepfraddr |= (PinType<<2);
}

/*!
 ******************************************************************************
 ** \brief Select the RTS pin location of MFS Ch4.
 **
 ** \param PinType Pin Type
 ** \arg IO_MFS_RTS4_INIT
 ** \arg IO_MFS_RTS4_RTS4_0
 ** \arg IO_MFS_RTS4_RTS4_1
 ** \arg IO_MFS_RTS4_RTS4_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMFSCh4RTSPin(IO_MFSRTSPinT PinType)
{
    volatile uint32_t *pepfraddr;
    pepfraddr = &FM3_GPIO->EPFR08;
    *pepfraddr &= ~(3ul);
    *pepfraddr |= (PinType);
}

/*!
 ******************************************************************************
 ** \brief Select TX pin location of CAN.
 **
 ** \param CANCh CAN Ch
 ** \arg IO_CAN_CH0
 ** \arg IO_CAN_CH1
 ** \param PinType Pin Type
 ** \arg IO_CAN_TXx_INIT
 ** \arg IO_CAN_TXx_TXx_0
 ** \arg IO_CAN_TXx_TXx_1
 ** \arg IO_CAN_TXx_TXx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncCANTXxPin(uint8_t CANCh, IO_CANTXxPinT PinType)
{
    volatile uint32_t *pepfraddr;
    pepfraddr = &FM3_GPIO->EPFR09;
    *pepfraddr &= ~(3ul<<(26+4*CANCh));
    *pepfraddr |= (PinType<<(26+4*CANCh));
    return;
}

/*!
 ******************************************************************************
 ** \brief Select RX pin location of CAN.
 **
 ** \param CANCh CAN Ch
 ** \arg IO_CAN_CH0
 ** \arg IO_CAN_CH1
 ** \param PinType Pin Type
 ** \arg IO_CAN_RXx_INIT
 ** \arg IO_CAN_RXx_RXx_0
 ** \arg IO_CAN_RXx_RXx_1
 ** \arg IO_CAN_RXx_RXx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncCANRXxPin(uint8_t CANCh, IO_CANRXxPinT PinType)
{
    volatile uint32_t *pepfraddr;
    pepfraddr = &FM3_GPIO->EPFR09;
    *pepfraddr &= ~(3ul<<(24+4*CANCh));
    *pepfraddr |= (PinType<<(24+4*CANCh));
    return;
}

/*!
 ******************************************************************************
 ** \brief Select ADTGx pin location of ADC trigger function.
 **
 ** \param ADCUnit ADC unit
 ** \arg ADC_UNIT0
 ** \arg ADC_UNIT1
 ** \arg ADC_UNIT2
 ** \param PinType Pin Type
 ** \arg IO_ADTGx_INIT
 ** \arg IO_ADTGx_ADTGx_0
 ** \arg IO_ADTGx_ADTGx_1
 ** \arg ...
 ** \arg IO_ADTGx_ADTGx_7
 ** \arg IO_ADTGx_ADTGx_8
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncADTGxPin(uint8_t ADCUnit, IO_ADTGxPinT PinType)
{
    volatile uint32_t *pepfraddr;
    pepfraddr = &FM3_GPIO->EPFR09;
    *pepfraddr &= ~(15ul<<(12+4*ADCUnit));
    *pepfraddr |= (PinType<<(12+4*ADCUnit));
    return;
}

/*!
 ******************************************************************************
 ** \brief Select ZINx pin location of QPRC.
 **
 ** \param QPRCCh QPRC Channel
 ** \arg IO_QPRC_CH0
 ** \arg IO_QPRC_CH1
 ** \param PinType Pin Type
 ** \arg IO_QPRC_ZINx_INIT
 ** \arg IO_QPRC_ZINx_ZINx_0
 ** \arg IO_QPRC_ZINx_ZINx_1
 ** \arg IO_QPRC_ZINx_ZINx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncQPRCZINxPin(uint8_t QPRCCh, IO_QPRCZINxPinT PinType)
{
    volatile uint32_t *pepfraddr;
    pepfraddr = &FM3_GPIO->EPFR09;
    *pepfraddr &= ~(3ul<<(4+6*QPRCCh));
    *pepfraddr |= (PinType<<(4+6*QPRCCh));
    return;
}

/*!
 ******************************************************************************
 ** \brief Select AINx pin location of QPRC.
 **
 ** \param QPRCCh QPRC Channel
 ** \arg IO_QPRC_CH0
 ** \arg IO_QPRC_CH1
 ** \param PinType Pin Type
 ** \arg IO_QPRC_AINx_INIT
 ** \arg IO_QPRC_AINx_AINx_0
 ** \arg IO_QPRC_AINx_AINx_1
 ** \arg IO_QPRC_AINx_AINx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncQPRCAINxPin(uint8_t QPRCCh, IO_QPRCAINxPinT PinType)
{
    volatile uint32_t *pepfraddr;
    pepfraddr = &FM3_GPIO->EPFR09;
    *pepfraddr &= ~(3ul<<(0+6*QPRCCh));
    *pepfraddr |= (PinType<<(0+6*QPRCCh));
    return;
}

/*!
 ******************************************************************************
 ** \brief Select BINx pin location of QPRC.
 **
 ** \param QPRCCh QPRC Channel
 ** \arg IO_QPRC_CH0
 ** \arg IO_QPRC_CH1
 ** \param PinType Pin Type
 ** \arg IO_QPRC_BINx_INIT
 ** \arg IO_QPRC_BINx_BINx_0
 ** \arg IO_QPRC_BINx_BINx_1
 ** \arg IO_QPRC_BINx_BINx_2
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncQPRCBINxPin(uint8_t QPRCCh, IO_QPRCBINxPinT PinType)
{
    volatile uint32_t *pepfraddr;
    pepfraddr = &FM3_GPIO->EPFR09;
    *pepfraddr &= ~(3ul<<(2+6*QPRCCh));
    *pepfraddr |= (PinType<<(2+6*QPRCCh));
    return;
}

/*!
 ******************************************************************************
 ** \brief Config MCSx pin function of external bus.
 **
 ** \param MCSxPin MCS pin index
 ** \arg IO_EXT_BUS_MCS1
 ** \arg IO_EXT_BUS_MCS2
 ** \arg ...
 ** \arg IO_EXT_BUS_MCS7
 ** \param OutputState Output state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncExtBusMCSxPin(uint8_t MCSxPin, uint8_t OutputState)
{
    volatile uint32_t *pepfraddr1;;
    pepfraddr1 = &FM3_GPIO->EPFR10;
    if(MCSxPin == IO_EXT_BUS_MCS0)
    {
        return;
    }
    else
    {
        *pepfraddr1 &= ~(1ul<<(7+(MCSxPin-1)));
        *pepfraddr1 |= (OutputState<<(7+(MCSxPin-1)));
    }
    return;
}

/*!
 ******************************************************************************
 ** \brief Collectly function setting for MDATA8-15 of external bus.
 **
 ** \param OutputState Output state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncExtBusColSetting1(uint8_t OutputState)
{
    volatile uint32_t *pepfraddr1;
    pepfraddr1 = &FM3_GPIO->EPFR10;
    *pepfraddr1 &= ~(1ul<<1);
    *pepfraddr1 |= OutputState<<1;
    return;
}

/*!
 ******************************************************************************
 ** \brief Collectly function setting for MAD1-7, MDATA0-7, MCS0 of external bus
 **
 ** \param OutputState Output state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncExtBusColSetting2(uint8_t OutputState)
{
    volatile uint32_t *pepfraddr1;
    pepfraddr1 = &FM3_GPIO->EPFR10;
    *pepfraddr1 &= ~(1ul<<0);
    *pepfraddr1 |= OutputState;
    return;
}

/*!
 ******************************************************************************
 ** \brief Config MADx pin function of external bus.
 **
 ** \param MADPin Address bus pin
 ** \arg IO_EXT_BUS_ADDR0
 ** \arg IO_EXT_BUS_ADDR8
 ** \arg ...
 ** \arg IO_EXT_BUS_ADDR15
 ** \param OutputState Output state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncExtBusMADxPin(uint32_t MADPin, uint8_t OutputState)
{
    volatile uint32_t *pepfraddr1;
    pepfraddr1 = &FM3_GPIO->EPFR10;
    if((MADPin >= IO_EXT_BUS_ADDR8) && (MADPin <= IO_EXT_BUS_ADDR24))
    {
        *pepfraddr1 &= ~(1ul<<(15+(MADPin-IO_EXT_BUS_ADDR8))) ;
        *pepfraddr1 |= (OutputState<<(15+(MADPin-IO_EXT_BUS_ADDR8)));
    }
    else if((MADPin >= IO_EXT_BUS_ADDR1) && (MADPin <= IO_EXT_BUS_ADDR7))
    {
         return;
    }
    else if(MADPin == IO_EXT_BUS_ADDR0)
    { 
        *pepfraddr1 &= ~(1ul<<14) ;
        *pepfraddr1 |= (OutputState<<14) ;
    }
    return;
}

/*!
 ******************************************************************************
 ** \brief Config Nand control pin function of external bus.
 **
 ** \param OutputState Output state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncExtBusNandCtrlPin(uint32_t OutputState)
{
    volatile uint32_t *pepfraddr1;
    pepfraddr1 = &FM3_GPIO->EPFR10;
    *pepfraddr1 &= ~(1ul<<6);
    *pepfraddr1 |= (OutputState<<6);
    return;
}

/*!
 ******************************************************************************
 ** \brief Config MOEX pin function of external bus.
 **
 ** \param OutputState Output state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncExtBusMOEXPin(uint32_t OutputState)
{
    volatile uint32_t *pepfraddr1;
    pepfraddr1 = &FM3_GPIO->EPFR10;
    *pepfraddr1 &= ~(1ul<<5);
    *pepfraddr1 |= (OutputState<<5);
    return;
}

/*!
 ******************************************************************************
 ** \brief Config MDQMx pin function of external bus.
 **
 ** \param OutputState Output state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncExtBusMDQMxPin(uint32_t OutputState)
{
    volatile uint32_t *pepfraddr1;
    pepfraddr1 = &FM3_GPIO->EPFR10;
    *pepfraddr1 &= ~(1ul<<4);
    *pepfraddr1 |= (OutputState<<4);
    return;
}

/*!
 ******************************************************************************
 ** \brief Config MWEX pin function of external bus.
 **
 ** \param OutputState Output state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncExtBusMWEXPin(uint32_t OutputState)
{
    volatile uint32_t *pepfraddr1;
    pepfraddr1 = &FM3_GPIO->EPFR10;
    *pepfraddr1 &= ~(1ul<<3);
    *pepfraddr1 |= (OutputState<<3);
    return;
}

/*!
 ******************************************************************************
 ** \brief Config MCLKOUT pin function of external bus.
 **
 ** \param OutputState Output state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncExtBusMCLKOUTPin(uint32_t OutputState)
{
    volatile uint32_t *pepfraddr1;
    pepfraddr1 = &FM3_GPIO->EPFR10;
    *pepfraddr1 &= ~(1ul<<2);
    *pepfraddr1 |= (OutputState<<2);
    return;
}

/*!
 ******************************************************************************
 ** \brief Config trace pin function of system.
 **
 ** \param PinState0 Pin state setting for CLK, D0, D1
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 ** \param PinState1 Pin state setting for D2, D3
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncTracePin(uint8_t PinState0, uint8_t PinState1)
{
    volatile uint32_t *pepfraddr;
    pepfraddr = &FM3_GPIO->EPFR00;
    if(PinState0 == IO_STATE_ENABLE)
    {
        *pepfraddr |= (1ul<<24);  
    }
    else if(PinState0 == IO_STATE_DISABLE)
    {
        *pepfraddr &= ~(1ul<<24);  
    }
    
    if(PinState1 == IO_STATE_ENABLE)
    {
        *pepfraddr |= (1ul<25);
    }
    else if(PinState1 == IO_STATE_DISABLE)
    {
        *pepfraddr &= ~(1ul<25);
    }
    
    return;
}

/*!
 ******************************************************************************
 ** \brief Config JTAG pin function of system.
 **
 ** \param PinState0 Pin state setting for TCK, TMS, TDO
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 ** \param PinState1 Pin state setting for TRSTX, DI
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncJtagPin(uint8_t PinState0, uint8_t PinState1)
{
    volatile uint32_t *pepfraddr;
    pepfraddr = &FM3_GPIO->EPFR00;
    if(PinState0 == IO_STATE_ENABLE)
    {
        *pepfraddr |= (1ul<<16);  
    }
    else if(PinState0 == IO_STATE_DISABLE)
    {
        *pepfraddr &= ~(1ul<<16);  
    }
    
    if(PinState1 == IO_STATE_ENABLE)
    {
        *pepfraddr |= (1ul<<17);  
    }
    else if(PinState0 == IO_STATE_DISABLE)
    {
        *pepfraddr &= ~(1ul<<17);  
    }
    return;
}

/*!
 ******************************************************************************
 ** \brief Config USB HCONTX pin function of system.
 **
 ** \param PinState Pin state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncUSBHCONTX(uint8_t PinState)
{
    volatile uint32_t *pepfraddr;
    
    pepfraddr = &FM3_GPIO->EPFR00;

    *pepfraddr &= ~(1ul<<9);
    *pepfraddr |= (PinState<<9);
    return;
}

/*!
 ******************************************************************************
 ** \brief Config CROUT pin function of system.
 **
 ** \param PinState Pin state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncCROUTPin(uint32_t PinState)
{
    volatile uint32_t *pepfraddr;
    pepfraddr = &FM3_GPIO->EPFR00;
    *pepfraddr &= ~(1ul<<1);
    *pepfraddr |= (PinState<<1);
    return;
}


/*!
 ******************************************************************************
 ** \brief Config NMI pin function of system.
 **
 ** \param PinState Pin state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncNMIPin(uint32_t PinState)
{
    volatile uint32_t *pepfraddr;
    pepfraddr = &FM3_GPIO->EPFR00;
    *pepfraddr &= ~(1ul<<0);
    *pepfraddr |= (PinState<<0);
    return;
}


/*!
 ******************************************************************************
 ** \brief Config USB pin function of system.
 **
 ** \param PinState Pin state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncUSBPin(uint8_t PinState)
{
    volatile uint32_t *pspsraddr;
    pspsraddr = &FM3_GPIO->SPSR;
    *pspsraddr &= ~(1ul<<4);
    *pspsraddr |= (PinState<<4);
    return;
}

/*!
 ******************************************************************************
 ** \brief Config main clock pin function of system.
 **
 ** \param PinState Pin state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncMClkPin(uint8_t PinState)
{
    volatile uint32_t *pspsraddr;
    pspsraddr = &FM3_GPIO->SPSR;
    *pspsraddr &= ~(1ul<<2);
    *pspsraddr |= (PinState<<2);
    return;
}

/*!
 ******************************************************************************
 ** \brief Config sub clock pin function of system.
 **
 ** \param PinState Pin state
 ** \arg IO_STATE_DISABLE
 ** \arg IO_STATE_ENABLE
 **
 ** \return None
 ******************************************************************************
 */
void IO_ConfigFuncSClkPin(uint8_t PinState)
{
    volatile uint32_t *pspsraddr;
    pspsraddr = &FM3_GPIO->SPSR;
    *pspsraddr &= ~(1ul<<0);
    *pspsraddr |= (PinState<<0);
    return;
}

 /*****************************************************************************/
/* END OF FILE */
 
 
