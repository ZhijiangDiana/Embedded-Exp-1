/*******************************************************************************
* File Name          : adc.h
* Version            : V1.0.0
* Date               : 11/13/2010
* Description        : This file contains all the functions prototypes for the
*                      ADC and PWM driver.
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "mb9bf506r.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/*************************************************************************
 * Function Name: Init_ADC
 * Description: Init ADC.
 *************************************************************************/
void Init_ADC(void)
{
	/* I/O setting AN08 - P18 */
	FM3_GPIO->ADE |= 0x80;
  	FM3_GPIO->PFR1 = 0x80;    
	
	/* A/DC setting */
        /* Added to support MB9bF506 */
        FM3_ADC0->ADCEN |= 0x01;	 
        while((IOREG_ADCEN_U0 & 0x02) != 0x02);

	FM3_ADC0->SCIS0 = 0x80;	           
	FM3_ADC0->ADSS1 = 0x00;	/* sampling timming ADST0 */
	FM3_ADC0->ADST0 = 0x43;             
	FM3_ADC0->ADCT  = 0x02;            
	FM3_ADC0->SCCR  = 0x10;	           /* FIFO clear,single mode */
	FM3_ADC0->CMPCR = 0x00;	/* disable comparator */
	FM3_ADC0->SCCR |= 0x01;	/* starting A/DC */
        
	
}

/*************************************************************************
 * Function Name: Init_PWM
 * Description: Init pwm output.
 *************************************************************************/
void Init_PWM(void)
{
  /* Base Timer CH.0,1,2 setting */
  /* Use PWM timer mode */
  /* Bus clk = 40MHz,count clk = 1/512,Down count = 1562,Duty count = 16 */
  /* 40*10^6 / 512 / 1562 = 50Hz = 20ms per */

  /* rerocation port TIOA0_1,TIOA1_1,TIOA2_1 use enable */
  IOREG_PFR3 = 0x1C00;
  IOREG_EPFR4 = 0x00080808;
  
  IOREG_TMCRL_CH0 = 0x18;			/* PWM mode */
  IOREG_TMCRH_CH0 = 0x00;
  IOREG_TMCR2_CH0 = 0x01;			/* cks=0b1000 count clk 1/512 */
  IOREG_STC_CH0   = 0x00;
  IOREG_PCSR_CH0  = 0x61A;		/* Down count = 1562 */
  IOREG_PDUT_CH0  = 0x10;			/* Duty count = 16/1562=10% */
  
  IOREG_TMCRL_CH0 |= 0x03;			/* start base timer(softwere TRG) */
	
	IOREG_TMCRL_CH1 = 0x18;			/* PWM mode */
  IOREG_TMCRH_CH1 = 0x00;
  IOREG_TMCR2_CH1 = 0x01;			/* cks=0b1000 count clk 1/512 */
  IOREG_STC_CH1   = 0x00;
  IOREG_PCSR_CH1  = 0x61A;		/* Down count = 1562 */
  IOREG_PDUT_CH1  = 0x10;			/* Duty count = 16/1562=10% */
  
  IOREG_TMCRL_CH1 |= 0x03;			/* start base timer(softwere TRG) */
	
	IOREG_TMCRL_CH2 = 0x18;			/* PWM mode */
  IOREG_TMCRH_CH2 = 0x00;
  IOREG_TMCR2_CH2 = 0x01;			/* cks=0b1000 count clk 1/512 */
  IOREG_STC_CH2   = 0x00;
  IOREG_PCSR_CH2  = 0x61A;		/* Down count = 1562 */
  IOREG_PDUT_CH2  = 0x10;			/* Duty count = 16/1562=10% */
  
  IOREG_TMCRL_CH2 |= 0x03;			/* start base timer(softwere TRG) */
}

/*************************************************************************
 * Function Name: Update_PWM
 * Parameters: ValDuty
 * Description: update the duty of pwm.
 *************************************************************************/
void Update_PWM(unsigned short ValDuty)
{
		/**/
	IOREG_PDUT_CH0 = 0x10 + ValDuty;
  IOREG_PDUT_CH1 = 0x10 + ValDuty;
  IOREG_PDUT_CH2 = 0x10 + ValDuty;
} 