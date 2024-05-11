/*!
 ******************************************************************************
 **
 ** \file lvd_fm3.c
 **
 ** \brief low voltage detection function driver
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
 
/*---------------------------------------------------------------------------*/
/* include files                                                             */
/*---------------------------------------------------------------------------*/
#include "Lvd_fm3.h"

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
/*! \brief Watch counter Callback function */
static LVD_IntHandlerCallbackT *pLVD_IntCallback = NULL;
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
 ** \brief Enable Low voltage detection interrupt
 **
 ** \param None
 ** 
 ** \retval None
 **
 ******************************************************************************
 */
void LVD_EnableInt(LVD_IntHandlerCallbackT* IntCallback)
{
    ASSERT(IntCallback != NULL);
    pLVD_IntCallback = IntCallback;
    bFM3_LVD_LVD_CTL_LVDIE = 1;
    return;
}


/*!
 ******************************************************************************
 ** \brief Disable Low voltage detection interrupt
 **
 ** \param None
 ** 
 ** \retval None
 **
 ******************************************************************************
 */
void LVD_DisableInt(void)
{
    bFM3_LVD_LVD_CTL_LVDIE = 0;
    return;
}
 
 /*!
 ******************************************************************************
 ** \brief Clear Low voltage detection interrupt
 **
 ** \param None
 ** 
 ** \retval None
 **
 ******************************************************************************
 */
 void LVD_ClrInt(void)
{
    bFM3_LVD_LVD_CLR_LVDCL = 0; 
    return; 
}
 
 /*!
 ******************************************************************************
 ** \brief  Release write protection mode 
 **
 ** \param None
 ** 
 ** \retval None
 **
 ******************************************************************************
 */
void LVD_UnlockCtrlReg(void)
{
    FM3_LVD->LVD_RLR = LVD_UNLOCK;
    return;
}

 /*!
 ******************************************************************************
 ** \brief Enable writing protection mode
 **
 ** \param None
 ** 
 ** \retval None
 **
 ******************************************************************************
 */
void LVD_LockCtrlReg(void)
{
    FM3_LVD->LVD_RLR = 0;
    return;
}

 /*!
 ******************************************************************************
 ** \brief Get low voltage detection interrupt cause 
 **
 ** \param None
 ** 
 ** \return Interrupt cause
 ** \retval RESET
 ** \retval SET       			
 **
 ******************************************************************************
 */
IntStatusT LVD_GetIntFlag (void)
{
    return (IntStatusT)bFM3_LVD_LVD_STR_LVDIR;
}
 
/*!
 ******************************************************************************
 ** \brief Get the operation status of LVD interrupt
 **
 ** \param None
 ** 
 ** \return Interrupt cause
 ** 
 **           			
 **
 ******************************************************************************
 */
FlagStatusT LVD_ClrIntRdyStat(void)
{
    return (IntStatusT)bFM3_LVD_LVD_STR2_LVDIRDY;
}
 
/*!
 ******************************************************************************
 ** \brief Set the detect voltage
 **
 ** \param VoltLevel detect voltage level
 **         
 ** \retval None
 ** 
 **
 ******************************************************************************
 */ 
void LVD_SetDetectVolt(uint8_t VoltLevel)
{
    /* Check the parameter */
    ASSERT(IS_LVD_VAL(VoltLevel));
    FM3_LVD->LVD_CTL &= ~(15ul<<2);
    FM3_LVD->LVD_CTL |= (VoltLevel<<2);
    return;
}


/*!
 ******************************************************************************
 ** \brief LVD interrupt handler
 **
 ** \param None
 **         
 ** \retval None
 ** 
 **
 ******************************************************************************
 */ 
void LVD_Handler(void)
{
    if(bFM3_LVD_LVD_STR_LVDIR)
    {
        bFM3_LVD_LVD_CLR_LVDCL = 0; 
        if(pLVD_IntCallback != NULL) 
        {
            pLVD_IntCallback();
        }
    }

}



 /*****************************************************************************/
/* END OF FILE */
