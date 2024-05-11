/*******************************************************************************
* File Name          : adc.h
* Version            : V1.0.0
* Date               : 11/13/2010
* Description        : This file contains all the functions prototypes for the
*                      ADC and PWM driver.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H
#define __ADC_H

/* Includes ------------------------------------------------------------------*/
//#include "board.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define BASEADD_ADC_U0	 0x40027000
#define	BASEADD_GPIO		 0x40033000
#define BASE_B_TIMER_CH0 0x40025000
#define BASE_B_TIMER_CH1 0x40025040
#define BASE_B_TIMER_CH2 0x40025080
#define BASE_B_TIMER_CH3 0x400250C0
#define BASE_B_TIMER_CH4 0x40025200
#define BASE_B_TIMER_CH5 0x40025240
#define BASE_B_TIMER_CH6 0x40025280
#define BASE_B_TIMER_CH7 0x400252C0

#define	IOREG_PFR1	*(volatile unsigned short*)(BASEADD_GPIO + 0x0004)
#define	IOREG_PCR1	*(volatile unsigned short*)(BASEADD_GPIO + 0x0104)
#define	IOREG_DDR1	*(volatile unsigned short*)(BASEADD_GPIO + 0x0204)
#define	IOREG_PDIR1	*(volatile unsigned short*)(BASEADD_GPIO + 0x0304)
#define	IOREG_PDOR1	*(volatile unsigned short*)(BASEADD_GPIO + 0x0404)
#define	IOREG_EPFR1	*(volatile unsigned long*)(BASEADD_GPIO + 0x0604)

#define	IOREG_ADE	*(volatile unsigned long*)(BASEADD_GPIO + 0x0500)

/* A/DC unit0 */
#define	IOREG_ADSR_U0		*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x000)
#define	IOREG_ADCR_U0		*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x001)
#define	IOREG_SFNS_U0		*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x008)
#define	IOREG_SCCR_U0		*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x009)
#define	IOREG_SCFD_U0		*(volatile unsigned short*)(BASEADD_ADC_U0 + 0x00C + 2)
#define	IOREG_SCIS2_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x010)
#define	IOREG_SCIS3_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x011)
#define	IOREG_SCIS0_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x014)
#define	IOREG_SCIS1_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x015)
#define	IOREG_PFNS_U0		*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x018)
#define	IOREG_PCCR_U0		*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x019)
#define	IOREG_PCFD_U0		*(volatile unsigned short*)(BASEADD_ADC_U0 + 0x01C)
#define	IOREG_PCIS_U0		*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x020)
#define	IOREG_CMPCR_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x024)
#define	IOREG_CMPD_U0		*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x025)
#define	IOREG_ADSS2_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x028)
#define	IOREG_ADSS3_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x029)
#define	IOREG_ADSS0_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x02C)
#define	IOREG_ADSS1_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x02D)
#define	IOREG_ADST1_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x030)
#define	IOREG_ADST0_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x031)
#define	IOREG_ADCT_U0		*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x034)
#define	IOREG_PRTSL_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x038)
#define	IOREG_SCTSL_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x039)
#define	IOREG_ADCEN_U0	*(volatile unsigned char*)(BASEADD_ADC_U0 + 0x03C)

/* GPIO */
#define	IOREG_PFR3	*(volatile unsigned short*)(BASEADD_GPIO + 0x000C)
#define	IOREG_PCR3	*(volatile unsigned short*)(BASEADD_GPIO + 0x010C)
#define	IOREG_DDR3	*(volatile unsigned short*)(BASEADD_GPIO + 0x020C)
#define	IOREG_PDIR3	*(volatile unsigned short*)(BASEADD_GPIO + 0x030C)
#define	IOREG_PDOR3	*(volatile unsigned short*)(BASEADD_GPIO + 0x040C)
#define	IOREG_EPFR3	*(volatile unsigned long*)(BASEADD_GPIO + 0x060C)
#define	IOREG_PFR4	*(volatile unsigned short*)(BASEADD_GPIO + 0x0010)
#define	IOREG_PCR4	*(volatile unsigned short*)(BASEADD_GPIO + 0x0110)
#define	IOREG_DDR4	*(volatile unsigned short*)(BASEADD_GPIO + 0x0210)
#define	IOREG_PDIR4	*(volatile unsigned short*)(BASEADD_GPIO + 0x0310)
#define	IOREG_PDOR4	*(volatile unsigned short*)(BASEADD_GPIO + 0x0410)
#define	IOREG_EPFR4	*(volatile unsigned long*)(BASEADD_GPIO + 0x0610)

/* Base Timer */
#define	IOREG_BTSEL0123	*(volatile unsigned char*)(0x40025100)
#define	IOREG_BTSEL4567	*(volatile unsigned char*)(0x40025300)
#define	IOREG_BTSSRSR	*(volatile unsigned short*)(0x400253FC)
  /* CH0. */
#define	IOREG_PCSR_CH0	*(volatile unsigned short*)(BASE_B_TIMER_CH0 + 0x0000)
#define	IOREG_PDUT_CH0	*(volatile unsigned short*)(BASE_B_TIMER_CH0 + 0x0004)
#define	IOREG_TMR_CH0		*(volatile unsigned short*)(BASE_B_TIMER_CH0 + 0x0008)
#define	IOREG_TMCRL_CH0	*(volatile unsigned char*)(BASE_B_TIMER_CH0 + 0x000C)
#define	IOREG_TMCRH_CH0	*(volatile unsigned char*)(BASE_B_TIMER_CH0 + 0x000D)
#define	IOREG_TMCR2_CH0	*(volatile unsigned char*)(BASE_B_TIMER_CH0 + 0x0011)
#define	IOREG_STC_CH0		*(volatile unsigned char*)(BASE_B_TIMER_CH0 + 0x0010)
  /* CH1. */
#define	IOREG_PCSR_CH1	*(volatile unsigned short*)(BASE_B_TIMER_CH1 + 0x0000)
#define	IOREG_PDUT_CH1	*(volatile unsigned short*)(BASE_B_TIMER_CH1 + 0x0004)
#define	IOREG_TMR_CH1		*(volatile unsigned short*)(BASE_B_TIMER_CH1 + 0x0008)
#define	IOREG_TMCRL_CH1	*(volatile unsigned char*)(BASE_B_TIMER_CH1 + 0x000C)
#define	IOREG_TMCRH_CH1	*(volatile unsigned char*)(BASE_B_TIMER_CH1 + 0x000D)
#define	IOREG_TMCR2_CH1	*(volatile unsigned char*)(BASE_B_TIMER_CH1 + 0x0011)
#define	IOREG_STC_CH1		*(volatile unsigned char*)(BASE_B_TIMER_CH1 + 0x0010)
  /* CH2. */
#define	IOREG_PCSR_CH2	*(volatile unsigned short*)(BASE_B_TIMER_CH2 + 0x0000)
#define	IOREG_PDUT_CH2	*(volatile unsigned short*)(BASE_B_TIMER_CH2 + 0x0004)
#define	IOREG_TMR_CH2		*(volatile unsigned short*)(BASE_B_TIMER_CH2 + 0x0008)
#define	IOREG_TMCRL_CH2	*(volatile unsigned char*)(BASE_B_TIMER_CH2 + 0x000C)
#define	IOREG_TMCRH_CH2	*(volatile unsigned char*)(BASE_B_TIMER_CH2 + 0x000D)
#define	IOREG_TMCR2_CH2	*(volatile unsigned char*)(BASE_B_TIMER_CH2 + 0x0011)
#define	IOREG_STC_CH2		*(volatile unsigned char*)(BASE_B_TIMER_CH2 + 0x0010)

/* Exported functions ------------------------------------------------------- */
void Init_ADC(void);
void Init_PWM(void);
void Update_PWM(unsigned short ValDuty);
#endif /* __ADC_H */

/******************* (C) COPYRIGHT 2010 Manley electronics *****END OF FILE****/

