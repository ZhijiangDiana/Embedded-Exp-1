/*******************************************************************************
* File Name          : lcd.h
* Version            : V1.1.0
* Date               : 11/13/2010
* Description        : This file contains all the functions prototypes for the
*                      lcd firmware driver.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

/* Includes ------------------------------------------------------------------*/
#include "board.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* LCD is Manley's ZYMG12864 and driver IC is ST7565R */
//#define LCD_FSMC_Interface
//#define LCD_Parallel_Interface


// Driver the LCD with Parallel or serial interface and the command/data control pin is gpio
#define LCD_CS_HIGH()             LCD_CS_PDOR  |=  LCD_CS
#define LCD_CS_LOW()              LCD_CS_PDOR  &= ~LCD_CS

#define LCD_CD_HIGH()             LCD_CD_PDOR |=  LCD_CD
#define LCD_CD_LOW()              LCD_CD_PDOR &= ~LCD_CD

#define LCD_CLK_HIGH()            LCD_CLK_PDOR |=  LCD_CLK
#define LCD_CLK_LOW()             LCD_CLK_PDOR &= ~LCD_CLK

#define LCD_DATA_HIGH()           LCD_DATA_PDOR |=  LCD_DATA
#define LCD_DATA_LOW()            LCD_DATA_PDOR &= ~LCD_DATA


// define the arrtibute of ZYMG12864(LCM)
#define GUI_LCM_XMAX 					128		// defined the lcd's line-number is 128 
#define GUI_LCM_YMAX 					64		// defined the lcd's column-number is 64
#define GUI_LCM_PAGE					8		// defined the lcd's page-number is 8(GUI_LCM_YMAX/8)

/* set LCD command */
#define Display_On					0xAF	// A0,RD,WR:010
#define Display_Off					0xAE	// A0,RD,WR:010

#define Set_Start_Line_0		0x40	// A0,RD,WR:010; line0~line63
#define Set_Page_Addr_0			0xB0	// A0,RD,WR:010; addr0~addr8
#define Set_ColH_Addr_0			0x10	// A0,RD,WR:010; 
#define Set_ColL_Addr_0			0x00	// A0,RD,WR:010; addr0~addr131

#define Read_Status				    0x-0	// A0,RD,WR:001; BUSY | ADC | ON/OFF |  RESET | 0 0 0 0
#define Status_Busy						0x80
#define Status_ADC_Reverse		0x40	// column address 131-n : SEG n, else column address n : SEG n
#define Status_Display_Off		0x20
#define Status_Reset					0x80

#define Write_Data				0x--	// A0,RD,WR:110
#define Read_Date					0x--	// A0,RD,WR:101; spi mode is unavailable


#define Set_ADC_Normal				0xA0	// A0,RD,WR:010
#define Set_ADC_Reverse				0xA1	// A0,RD,WR:010
#define Display_Normal				0xA6	// A0,RD,WR:010
#define Display_Reverse				0xA7	// A0,RD,WR:010; reverse color
#define Display_All_On				0xA5	// A0,RD,WR:010
#define Display_All_Normal		0xA4	// A0,RD,WR:010

/*************************************************************
*	bias:	1/65duty | 1/49duty | 1/33duty | 1/55duty | 1/53duty *
*	---------------|----------|----------|----------|--------- *
*	A2: 	1/9 bias | 1/8 bias | 1/6 bias | 1/8 bias | 1/8 bias *
*	A3:		1/7 bias | 1/6 bias | 1/5 bias | 1/6 bias | 1/6 bias *
**************************************************************/

#define Set_LCD_Bias_7    		0xA3	// A0,RD,WR:010
#define Set_LCD_Bias_9    		0xA2	// A0,RD,WR:010

#define RMW_Mode_Enable   		0xE0	// A0,RD,WR:010; the column address locked when read command operating
#define RMW_Mode_End		  		0xEE	// A0,RD,WR:010; returns to the column address when RMW was entered.
#define Reset_LCD         		0xE2	// A0,RD,WR:010


/**************************************************************************************
*	Com Scan Dir:	|	1/65duty 		| 1/49duty 		| 1/33duty 		| 1/55duty 		| 1/53duty		*
*	--------------|-------------|-------------|-------------|------------------------ 	*
*	C0: 	Normal	|	COM0:COM63	|	COM0:COM47	|	COM0:COM31	|	COM0:COM53	|	COM0:COM51	*
*	C8:		Reverse	|	COM63:COM0	|	COM47:COM0	|	COM31:COM0	|	COM53:COM0	|	COM51:COM0	*
***************************************************************************************/

#define COM_Scan_Dir_Normal 	   0xC0	// A0,RD,WR:010
#define COM_Scan_Dir_Reverse     0xC8	// A0,RD,WR:010

// 0 0 1 0 1 | Booster On | Regulator On | Follower On
#define Power_Booster_On			0x2C	// A0,RD,WR:010
#define Power_Regulator_On		0x2E	// A0,RD,WR:010
#define Power_Follower_On			0x2F	// A0,RD,WR:010

#define Set_Resistor_Ratio		0x20	// A0,RD,WR:010; 20~27:small~large

#define Set_ElecVol_Mode		0x81	// A0,RD,WR:010; double byte command
#define Set_ElecVol_Reg			0x20	// A0,RD,WR:010; the electronic volume(64 voltage levels:00~3F) function is not used.

#define Sleep_Mode_Enable			0xAC	// A0,RD,WR:010; double byte command, preceding command
#define Sleep_Mode_Disable		0xAD	// A0,RD,WR:010; preceding command
#define Sleep_Mode_Deliver		0x00	// A0,RD,WR:010; following command

#define Boost_Ratio_Set			0xF8	// A0,RD,WR:010; double byte command, preceding command
#define Boost_Ratio_234			0x00	// A0,RD,WR:010; following command
#define Boost_Ratio_5				0x01	// A0,RD,WR:010; following command
#define Boost_Ratio_6				0x03	// A0,RD,WR:010; following command

#define Command_Nop					0xE3	// A0,RD,WR:010
#define Command_IC_Test			0xFC	// A0,RD,WR:010; don't use

/* Exported functions ------------------------------------------------------- */
void LCD_Initialize(void);
void LCD_ClearSCR(void);
void LCD_UpdatePoint(unsigned int x, unsigned int y);
void LCD_FillAll(unsigned char* data);
unsigned char  LCD_PutChar(unsigned long x, unsigned long y, unsigned char ch);
void  LCD_PutString(unsigned long x, unsigned long y, char *str);
void LCD_Power_On(void);
void LCD_Power_Off(void);
void LCD_Sleep_Enter(void);
void LCD_Sleep_Exit(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_WriteCmd(unsigned char command);
void LCD_WriteData(unsigned char data);

void Delay(void);
void Reset_Delay(void);
void Power_Delay(void);

#endif /* __LCD_H */

/******************* (C) COPYRIGHT 2009 Manley electronics *****END OF FILE****/
