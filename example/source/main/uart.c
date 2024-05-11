#include "uart.h"
#include "mb9bf50x_lib.h"
#include "..\driver\io\io_fm3.h"
#include "..\driver\mfs\uart\uart_fm3.h"
/*---------------------------------------------------------------------------*/
/* Macros                                                                    */
/*---------------------------------------------------------------------------*/
#define InUseCh     MFS_Ch2
#define TestSize    10
/* UART TX State */
#define TXSTART     0
#define TXONGOING   1
#define TXFINISH    2
/* UART RX State */
#define RXSTART     0
#define RXONGOING   1
#define RXFINISH    2
#define RXERROR     3

/*---------------------------------------------------------------------------*/
/* IO definition                                                             */
/*---------------------------------------------------------------------------*/
/*! \brief IO MFS channel */
#define   IO_MFS_CH             (InUseCh)
/*! \brief IO MFS port */
#define   IO_MFS_PORT           (IO_PORT2)	//	 IO_PORT2
/*! \brief IO MFS SOT pin */
#define   IO_MFS_SOT_PIN        (IO_PINx5) 
/*! \brief IO MFS SIN pin */
#define   IO_MFS_SIN_PIN        (IO_PINx4)
///*! \brief IO MFS SOT pin location */
#define   IO_MFS_SOT_PIN_LOC    (IO_MFS_SOTx_SOTx_1)
/*! \brief IO MFS SIN pin location */
#define   IO_MFS_SIN_PIN_LOC    (IO_MFS_SINx_SINx_1)

/*! \brief IO MFS port */
#define   IO_MFS2_PORT           (IO_PORT2)

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static MFS_UARTModeConfigT tUARTModeConfigT = 
{
    115200,
    UART_DATABITS_8,
    UART_STOPBITS_1,
    UART_PARITY_NONE,
    UART_BITORDER_LSB,
    UART_NRZ,
};

extern  FM3_MFS03_UART_TypeDef* pMFS_UART_REG_07[8] = 
{
    (FM3_MFS03_UART_TypeDef*)(FM3_MFS0_UART),
    (FM3_MFS03_UART_TypeDef*)(FM3_MFS1_UART),
    (FM3_MFS03_UART_TypeDef*)(FM3_MFS2_UART),
    (FM3_MFS03_UART_TypeDef*)(FM3_MFS3_UART),
    (FM3_MFS03_UART_TypeDef*)(FM3_MFS4_UART),
    (FM3_MFS03_UART_TypeDef*)(FM3_MFS5_UART),
    (FM3_MFS03_UART_TypeDef*)(FM3_MFS6_UART),
    (FM3_MFS03_UART_TypeDef*)(FM3_MFS7_UART),
};

void UART0IrqRXCallback(void);
void UART1IrqRXCallback(void);
void UART2IrqRXCallback(void);
void UART0IrqTXCallback(void);
void UART1IrqTXCallback(void);
void UART2IrqTXCallback(void);
void UARTConfigMode(uint8_t Ch, MFS_UARTModeConfigT *pModeConfig);

#define USART_NUMBER		3
static char sndbuf[UART_TX_BUFSIZE];
static char rcvbuf[UART_RX_BUFSIZE];
static TUartContext gPortContext[USART_NUMBER] = 
					{{sndbuf,rcvbuf,0,0,0,0,0},
					 {sndbuf,rcvbuf,0,0,0,0,0},
					 {sndbuf,rcvbuf,0,0,0,0,0}
				//	 {sndbuf,rcvbuf,0,0,0,0,0}
					};
//static void *IRQRXCallBack[USART_NUMBER] = {UART0IrqRXCallback,UART1IrqRXCallback,UART2IrqRXCallback};
//static void *IRQTXCallBack[USART_NUMBER] = {UART0IrqTXCallback,UART1IrqTXCallback,UART2IrqTXCallback};
																//LiLiang add
/*!
 ******************************************************************************
 ** \brief  Initialize the I/O port for UART: select MFS ch2/SIN2_1 and SOT2_1
 **
 ** \param  none
 **
 ** \return none
 ******************************************************************************
 */
static void InitPort(void)
{    
       
   /* Set Uart Ch2 Port, SIN2_1, SOT2_1 */
    FM3_GPIO->PFR2 = FM3_GPIO->PFR2 | 0x0030;
    FM3_GPIO->EPFR07 = FM3_GPIO->EPFR07 | 0x000a0000;
}

void InitUart0(void)
{
  // Initialize ports for UART0
  FM3_GPIO->PFR2 |= (1 << 0x01) | (1 << 0x02);    // P21->SIN1_0, P22->SOT0_0
  FM3_GPIO->EPFR07 |= (1 << 6);                  // Use SIN0_0, SOT0_0  

  // Initialize UART asynchronous mode
  FM3_MFS0_UART->SCR =  0x80;   // UART0 reset
  FM3_MFS0_UART->SMR =  0x01;   // serial data output enable, operation mode 0
  FM3_MFS0_UART->SSR =  0x00;   // 0x80 = clear receive error flag
  FM3_MFS0_UART->ESCR = 0x00;          
 
  //FM3_MFS0_UART->BGR = 40000000 / 9600 - 1;    // 9.6kbaud @ 40 MHZ
  //FM3_MFS0_UART->BGR = 40000000 / 19200 - 1;   // 19.2kbaud @ 40 MHZ
  //FM3_MFS0_UART->BGR = 40000000 / 38400 - 1;   // 38.4kbaud @ 40 MHZ
 // FM3_MFS0_UART->BGR = 40000000 / 115200 - 1;  // 115.2kbaud @ 40 MHz
 //-->Change LiLiang
    FM3_MFS0_UART->BGR = 36000000 / 115200 - 1;  // 115.2kbaud @ 40 MHz

  FM3_MFS0_UART->SCR |= 0x03;   // RX, TX enable

  // UART0 interrupt settings
  NVIC_ClearPendingIRQ(MFS0RX_IRQn);
  NVIC_EnableIRQ(MFS0RX_IRQn);
  NVIC_SetPriority(MFS0RX_IRQn, 2);

  NVIC_EnableIRQ(MFS0TX_IRQn);

  UARTConfigMode(0,&tUARTModeConfigT);
  MFS_UARTEnableTX(0);
  MFS_UARTEnableRX(0);
  UART0IrqRXCallback();
}


void InitUart1(void)
{
//P50/AN22/INT00_0/AIN0_2/SIN3_1
//P51/AN23/INT01_0/BIN0_2/SOT3_1

  FM3_GPIO->PFR1|=(1<<0x01)|(1<<0x02);    //P11,SIN1_1 P12 SOT1_1 // P50->SIN3_1, P51->SOT3_1
  //FM3_GPIO->EPFR07 &=(~(2<<10))|(~(2<<12));//|=(2<<10)|(2<<12);       //P11, P12 // Use SIN1_1, SOT1_1  
  //		这里参考了Regan的建议，如下更改EPFR07的几位配置，同时由于这个管脚和AN1,AN2模拟复用，所以必须关掉模拟的功能。//
  // 参考：Analog Input Setting Register (ADE)：0 Uses an external pin not as analog input but digital input/output.
  //1:Uses an external pin as analog input.(An I/O cell will be in a state of input direction, input cut-off, and pull-up
  //disconnection.)		 //For TYPE9 products, do not set "0" to 3rd bit of ADE.我们的MB9BF124K属于Type9系列
  bFM3_GPIO_ADE_AN2=0;
  bFM3_GPIO_ADE_AN1=0;
  bFM3_GPIO_EPFR07_SIN1S1=1;
  bFM3_GPIO_EPFR07_SIN1S0=0;
  bFM3_GPIO_EPFR07_SOT1B1=1;
  bFM3_GPIO_EPFR07_SOT1B0=0;
  FM3_GPIO->ADE = 0x0; 				  // ADE not 00				//  qing
  // Initialize ports for UART2
  //FM3_GPIO->PFR2 |= (1 << 0x04) | (1 << 0x05);    // P21->SIN1_0, P22->SOT0_0-->P24,P25
 // FM3_GPIO-> EPFR07 |= (2 << 16)|(2<<18) ;                  // Use SIN0_0, SOT0_0  
  //  Use SOT2_1, SIN2_1

  // Initialize UART asynchronous mode
  FM3_MFS1_UART->SCR =  0x80;   // UART0 reset
  FM3_MFS1_UART->SMR =  0x01;   // serial data output enable, operation mode 0
  FM3_MFS1_UART->SSR =  0x00;   // 0x80 = clear receive error flag
  FM3_MFS1_UART->ESCR = 0x00;          
 
  //FM3_MFS2_UART->BGR = 40000000 / 9600 - 1;    // 9.6kbaud @ 40 MHZ
  //FM3_MFS0_UART->BGR = 40000000 / 19200 - 1;   // 19.2kbaud @ 40 MHZ
  //FM3_MFS0_UART->BGR = 40000000 / 38400 - 1;   // 38.4kbaud @ 40 MHZ
  FM3_MFS1_UART->BGR = 36000000 / 115200 - 1;  // 115.2kbaud @ 40 MHz
 
  FM3_MFS1_UART->SCR |= 0x03;   // RX, TX enable

  // UART1 interrupt settings
  NVIC_ClearPendingIRQ(MFS1RX_IRQn);
  NVIC_EnableIRQ(MFS1RX_IRQn);
  NVIC_SetPriority(MFS1RX_IRQn, 1);

  NVIC_EnableIRQ(MFS1TX_IRQn);

  UARTConfigMode(1,&tUARTModeConfigT);
  MFS_UARTEnableTX(1);
  MFS_UARTEnableRX(1);
  UART1IrqRXCallback();
}

void InitUart2(void)
{
  // Initialize ports for UART2
  FM3_GPIO->PFR2 |= (1 << 0x04) | (1 << 0x05);    // P21->SIN1_0, P22->SOT0_0-->P24,P25
  FM3_GPIO-> EPFR07 |= (2 << 16)|(2<<18) ;                  // Use SIN0_0, SOT0_0  
  //  Use SOT2_1, SIN2_1

  // Initialize UART asynchronous mode
  FM3_MFS2_UART->SCR =  0x80;   // UART0 reset
  FM3_MFS2_UART->SMR =  0x01;   // serial data output enable, operation mode 0
  FM3_MFS2_UART->SSR =  0x00;   // 0x80 = clear receive error flag
  FM3_MFS2_UART->ESCR = 0x00;          
 
  //FM3_MFS2_UART->BGR = 40000000 / 9600 - 1;    // 9.6kbaud @ 40 MHZ
  //FM3_MFS0_UART->BGR = 40000000 / 19200 - 1;   // 19.2kbaud @ 40 MHZ
  //FM3_MFS0_UART->BGR = 40000000 / 38400 - 1;   // 38.4kbaud @ 40 MHZ
  FM3_MFS2_UART->BGR = 36000000 / 115200 - 1;  // 115.2kbaud @ 40 MHz
 
  FM3_MFS2_UART->SCR |= 0x03;   // RX, TX enable

  // UART2 interrupt settings
  NVIC_ClearPendingIRQ(MFS2RX_IRQn);
  NVIC_EnableIRQ(MFS2RX_IRQn);
  NVIC_SetPriority(MFS2RX_IRQn, 3);

  NVIC_EnableIRQ(MFS2TX_IRQn);

  UARTConfigMode(2,&tUARTModeConfigT);
  MFS_UARTEnableTX(2);
  MFS_UARTEnableRX(2);
  UART2IrqRXCallback();
}

//LiLiang add it:
   /*
void PutCharUart1(uint8_t u8Char)
{
  while (!(FM3_MFS1_UART->SSR & (1 << 1)));   // wait for transmit buffer empty 
  FM3_MFS1_UART->TDR = u8Char;                // put u8Char into buffer
  
  if ('\n' == u8Char)
  {
    while (!(FM3_MFS1_UART->SSR & (1 << 1))); // wait for transmit buffer empty 
    FM3_MFS1_UART->TDR = '\r';                // put '\r' into buffer
  }
}

void PutStringUart1(uint8_t *pu8Buffer)              
{
  while (*pu8Buffer != '\0')
  { 
    PutCharUart1(*pu8Buffer++);        // send every char of string
  }
}

void MFS1_R_IRQHandler(void)
{
  uint8_t u8Char;
  
  if ((FM3_MFS1_UART->SSR & 0x38) != 0)  //0xE0-->38 Check for errors PE, ORE, FRE
  {
    FM3_MFS1_UART->SSR |= (1 << 7);      // Clear error flags 
    u8Char = FM3_MFS1_UART->RDR;         // Flush RDR
  }
  else if (FM3_MFS1_UART->SSR & 0x04)    // RDRF?
  {
    u8Char = FM3_MFS1_UART->RDR;
    PutCharUart1(u8Char);
    
    if ('\r' == u8Char)
    {
      PutCharUart1('\n');
    }
  }
}

*/

/*!
 ******************************************************************************
 ** \brief Config the UART mode
 **
 ** \param Ch Requested channel
 ** \arg   MFS_Ch0-MFS_Ch7
 **         
 ** \param  Mode initialization data
 ** \param MFS_UARTModeConfigT
 ** \arg   Mode info
 **
 ** \retval None
 **
 ******************************************************************************
 */
void UARTConfigMode(uint8_t Ch, MFS_UARTModeConfigT *pModeConfig)
{
    /* Config the MOD as UART */
    MFS_UARTSetUARTMode(Ch);
    /* Enable Output */
    MFS_UARTEnableSOE(Ch);
    /* LSB or MSB */
    if(pModeConfig->Bitorder == UART_BITORDER_MSB)
    {
        MFS_UARTConfigMSB(Ch);
    }
    if(pModeConfig->Bitorder == UART_BITORDER_LSB)
    {
        MFS_UARTConfigLSB(Ch);
    }
    /* Stop bit */
    MFS_UARTConfigST(Ch, pModeConfig);
    /* Parity */
    if(pModeConfig->Parity == UART_PARITY_NONE)
    {
        MFS_UARTDisableParity(Ch);
    }
    else 
    {
        if(pModeConfig->Parity == UART_PARITY_ODD)
        {
            MFS_UARTConfigOddParity(Ch);
            MFS_UARTEnableParity(Ch);
        }
        if(pModeConfig->Parity == UART_PARITY_EVEN)
        {
            MFS_UARTConfigEvenParity(Ch);
            MFS_UARTEnableParity(Ch);
        }
    }
    /* Data bits */
    MFS_UARTConfigDT(Ch, pModeConfig);
    /* INV */
    if(pModeConfig->NRZ == UART_NRZ)
    {
        MFS_UARTConfigNoInv(Ch);
    }
    if(pModeConfig->NRZ == UART_INV_NRZ)
    {
        MFS_UARTConfigInv(Ch);
    }
    MFS_UARTConfigBaudrate(Ch, pModeConfig->Baudrate);
    return;
}

/*!
 ******************************************************************************
 ** \brief  User defined TX ISR Callback function
 **
 ** \param  none
 **
 ** \return none
 ******************************************************************************
 */
void UART0IrqTXCallback(void)
{
	StartToSend(0);
}
/*!
 ******************************************************************************
 ** \brief  User defined RX ISR Callback function
 **
 ** \param  none
 **
 ** \return none
 ******************************************************************************
 */
void UART0IrqRXCallback(void)
{
	DataArrived(0,MFS_UARTRXOneData(0));
}
//uart1 
void UART1IrqTXCallback(void)
{
	StartToSend(1);
}
void UART1IrqRXCallback(void)
{
	DataArrived(1,MFS_UARTRXOneData(1));
}
//	uart2
void UART2IrqTXCallback(void)
{
	StartToSend(2);
}
/*
 ******************************************************************************
 ** \brief  User defined RX ISR Callback function
 **
 ** \param  none
 **
 ** \return none
 ******************************************************************************
 */
void UART2IrqRXCallback(void)
{
	DataArrived(2,MFS_UARTRXOneData(2));
}

void DataArrived(unsigned int iCOM,char c)
{
	gPortContext[iCOM].rcvbuf[gPortContext[iCOM].rcvend ++] = c;
	gPortContext[iCOM].rcvend %= UART_RX_BUFSIZE;
}

unsigned long UART_ReadBuf(unsigned int iCOM, char *pt, unsigned long len)
{
	unsigned long i = 0;
	iCOM %= USART_NUMBER;
	while(i < len)
	{
		if(gPortContext[iCOM].rcvstart == gPortContext[iCOM].rcvend)
			return i;
		pt[i++] = gPortContext[iCOM].rcvbuf[gPortContext[iCOM].rcvstart++];
		gPortContext[iCOM].rcvstart %= UART_RX_BUFSIZE;
	}
	return i;
}

void StartToSend(unsigned int iCOM)
{ 
	if(gPortContext[iCOM].sndstart == gPortContext[iCOM].sndend)
	{
		gPortContext[iCOM].sndflag = 0;
      	/* Disable the EVAL_COM1 Transmit interrupt */
      	//USART_ITConfig(COM_USART_MAP[iCOM], USART_IT_TXE, DISABLE);
		MFS_UARTDisableTXInt(iCOM);
	}
	else
	{
		MFS_UARTTXOneData(iCOM, gPortContext[iCOM].sndbuf[gPortContext[iCOM].sndstart]);
		//USART_SendData(COM_USART_MAP[iCOM], gPortContext[iCOM].sndbuf[gPortContext[iCOM].sndstart]);
		gPortContext[iCOM].sndstart++;
		gPortContext[iCOM].sndstart %= UART_TX_BUFSIZE;
	}	
}

unsigned long UART_WriteBuf(unsigned int iCOM, char *pt, unsigned long len)
{
	unsigned long i = 0;
	
	while(i < len)
	{
				
		if(MFS_UARTGetTXRegEmptyStatus(iCOM))
                {
			MFS_UARTTXOneData(iCOM, pt[i]);
                        i++;
                        
                }
	}	
}
