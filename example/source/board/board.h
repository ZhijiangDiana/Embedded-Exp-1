/***************************************************************************
 **
 **    This file defines the board FSSDC-9B506-EK specific definition
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 ***************************************************************************/
#include "mb9bf506r.h"

#ifndef __BOARD_H
#define __BOARD_H

#define CLKHC          (4000000L) //(4MHZ)
#define CLKLC           (100000L)//(100KHZ)


/*Clock Definitions*/
#define CLKMO          (4000000L)// (4MHZ)
#define CLKSO           (32768UL)
/*Bus Deviders*/
#define BSC_PSR_VAL     0
#define APB0_PSR_VAL    1
#define APB1_PSR_VAL    1 
#define APB2_PSR_VAL    1

/*LEDs*/
#define LED1        (1UL<<10)
#define LED2        (1UL<<11)
#define LED3        (1UL<<12)
#define LED_MASK    (LED1 | LED2 | LED3)
#define LED_PFR     PFR3
#define LED_DDR     DDR3
#define LED_PDOR    PDOR3

/********* LCD Hardward Interface *************
LCD_CS		PORT1.7
LCD_CD		PORT1.6
LCD_WR		PORT1.5
LCD_RD		PORT1.4
LCD_SCK		PORT1.3
LCD_MOSI	PORT1.2
LCD_C86		PORT1.1
LCD_PS		PORT1.0
LCD_DATA[0..7]		PORT5.[0..7]
***********************************************/
#define LCD_CS                    (1UL << 5)
#define LCD_CS_DDR                FM3_GPIO->DDR1
#define LCD_CS_PFR                FM3_GPIO->PFR1
#define LCD_CS_PDOR               FM3_GPIO->PDOR1

#define LCD_CD                    (1UL << 4)
#define LCD_CD_DDR                FM3_GPIO->DDR1
#define LCD_CD_PFR                FM3_GPIO->PFR1
#define LCD_CD_PDOR               FM3_GPIO->PDOR1


#define LCD_CLK                   (1UL << 3)
#define LCD_CLK_DDR               FM3_GPIO->DDR1
#define LCD_CLK_PFR               FM3_GPIO->PFR1
#define LCD_CLK_PDOR              FM3_GPIO->PDOR1


#define LCD_DATA                  (1UL << 2)
#define LCD_DATA_DDR              FM3_GPIO->DDR1
#define LCD_DATA_PFR              FM3_GPIO->PFR1
#define LCD_DATA_PDOR             FM3_GPIO->PDOR1

/*JOY Stick*/
#define JOY_DOWN      (1<<2)
#define JOY_LEFT      (1<<0)
#define JOY_RIGHT     (1<<3)
#define JOY_UP        (1<<1)

#define JOY_MASK    	(JOY_DOWN | JOY_LEFT | JOY_RIGHT | JOY_UP)
#define JOY_PFR    		FM3_GPIO->PFR4
#define JOY_PCR    		FM3_GPIO->PCR4
#define JOY_PDIR   		FM3_GPIO->PDIR4
#define JOY_DDR    		FM3_GPIO->DDR4

/* LED */
#define USER_LED1      (1UL<<0x9)
#define USER_LED2      (1UL<<0xa)
#define USER_LED3      (1UL<<0xb)

#define USER_LED_MASK    	(USER_LED1 | USER_LED2 | USER_LED3)
#define USER_LED_PFR    		FM3_GPIO->PFR1
#define USER_LED_PCR    		FM3_GPIO->PCR1
#define USER_LED_PDOR   		FM3_GPIO->PDOR1
#define USER_LED_DDR    		FM3_GPIO->DDR1
      

/*TRIMER VR2*/
#define VR2         (1<<13)

/*ADC channels*/
#define VR_CHANNEL      7




#endif /* __BOARD_H */
