/*******************************************************************************
* File Name          : key.h
* Date First Issued  : 2010.8.20
* Version            : V0.1
* Description        : This file contains all the functions prototypes for the LCD
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEY_H
#define __KEY_H

/* Includes ------------------------------------------------------------------*/ 
#include "board.h"
#include "os_cpu.h"
/* Exported types ------------------------------------------------------------*/

#define  KeyboardNumbers   7//键盘个数
#define  KeyboardPushTimes 2//单击键盘次数
#define  KeyboardLongPushTimes 25//长压键盘2次间隔时间
#define  KeyboardRunTimes 5//长压键进入时间

//       键盘名         		管脚号      IO       	编码
#define GetValKey_1() 		(JOY_PDIR & JOY_DOWN)
#define GetValKey_2() 		(JOY_PDIR & JOY_LEFT)
#define GetValKey_3() 		(JOY_PDIR & JOY_RIGHT)
#define GetValKey_4() 		(JOY_PDIR & JOY_UP)
/* Exported variables --------------------------------------------------------*/
extern unsigned char key_flag;
extern unsigned char LcdFlag;
extern unsigned short FlagCounter;
extern unsigned char page_id,ad_update_flag, cpu_usage, cpu_usage_flag;
extern OS_STK Task_LED_STK[128];
extern void LedTask(void *pdata);

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*---------------------------------------------------------
键盘事件处理函数声明
---------------------------------------------------------*/
void Key00(void);//放键事件
void Key01(void);
void Key02(void);
void Key03(void);
void Key10(void);//短压键事件
void Key11(void);
void Key12(void);
void Key13(void);
void Key20(void);//双击键事件
void Key21(void);
void Key22(void);
void Key23(void);
void Key30(void);//长键事件
void Key31(void);
void Key32(void);
void Key33(void);

void Key0_1(void);//组合键事件
void Key1_2(void);
void Key2_3(void);
void Key3_0(void); 

//放键表
void Keyboard_Key01(void);
void Keyboard_Key02(void);
void Keyboard_Key03(void);
void Keyboard_Key04(void);
void Keyboard_Key05(void);
void Keyboard_Key06(void);
void Keyboard_Key07(void);
// 短压表
void Keyboard_Key11(void);
void Keyboard_Key12(void);
void Keyboard_Key13(void);
void Keyboard_Key14(void);
void Keyboard_Key15(void);
void Keyboard_Key16(void);
void Keyboard_Key17(void);
// 长压表
void Keyboard_Key21(void);
void Keyboard_Key22(void);
void Keyboard_Key23(void);
void Keyboard_Key24(void);
void Keyboard_Key25(void);
void Keyboard_Key26(void);
void Keyboard_Key27(void);

void Keyboard_Init(void);
void Keyboard_Exec(void);
unsigned char Keyboard_Scan(void);

#endif

/************************ END OF FILE ************************/

