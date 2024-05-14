/*******************************************************************************
* File Name          : key.c
* Date First Issued  : 2010.8.20
* Version            : V0.1
* Description        : RTC basic functions
*
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "key.h"
#include "lcd.h"
#include "ucos_ii.h"
/* Local includes ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private variables--------------------------------------------------------- */
/*---------------------------------------------------------
申请系统变量
---------------------------------------------------------*/
volatile signed int KeyPressCount[4];	//申请压键20mS计数器数组
volatile signed int KeyDblCount[4];		//申请键值计数器数组 
volatile unsigned char PressCount[KeyboardNumbers], PressTimes[KeyboardNumbers];
unsigned char Count;
typedef void (*FunctionPtr)(void);//函数指针
	static const FunctionPtr KeyboardCommandTab[3][KeyboardNumbers] =
	{
    {
        Keyboard_Key01,
        Keyboard_Key02,
        Keyboard_Key03,
        Keyboard_Key04,
        Keyboard_Key05,
        Keyboard_Key06,
        Keyboard_Key07
    },//放键表
    {
        Keyboard_Key11,
        Keyboard_Key12,
        Keyboard_Key13,
        Keyboard_Key14,
        Keyboard_Key15,
        Keyboard_Key16,
        Keyboard_Key17
    },//短压表
    {
        Keyboard_Key21,
        Keyboard_Key22,
        Keyboard_Key23,
        Keyboard_Key24,
        Keyboard_Key25,
        Keyboard_Key26,
        Keyboard_Key27
    } //长压表
	};
	
	
///////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
///////////////////////////////////////////////////////////////////////////////
void Keyboard_Init(void)
{
	int i = 0;
    for (i = 0; i < sizeof(PressCount); i ++)
    {
        PressCount[i] = 0;
        PressTimes[i] = 0;
    }
    Count = 0;
}

void Keyboard_Exec(void)
{	
	unsigned char KeyCount;
	Count %= KeyboardNumbers;
	KeyCount = PressCount[Count];//取压键次数
	if (Keyboard_Scan() == Count + 1)//有键压下
	{
		KeyCount++;//压键计数	
		if (KeyCount >= KeyboardPushTimes)
		{
			if (KeyCount == KeyboardPushTimes)//短压键
			{
				PressTimes[Count] = 0;
				KeyboardCommandTab[1][Count]();
			}
			if (KeyCount == KeyboardLongPushTimes)//长压键
			{
				if (PressTimes[Count] < 250)
				{
					PressTimes[Count]++;
				}
				if (PressTimes[Count] >= KeyboardRunTimes)
				{
					KeyboardCommandTab[2][Count]();
					PressTimes[Count] = 0;
				}
				KeyCount = KeyboardPushTimes;	
			}
		}
	}
	else//无键压下
	{
		if (KeyCount > 0)//以前有键压下
		{			
			if (KeyCount > KeyboardPushTimes)	
			{
				KeyCount = KeyboardPushTimes;
			}		
			else
			{
				KeyCount--;//放键计数
				if (KeyCount == 0)//键释放
				{
					KeyboardCommandTab[0][Count]();
				}
			}
		}
		else
		{
			KeyCount = 0;
		}
	}
	PressCount[Count] = KeyCount;
	Count++;
	Count %= KeyboardNumbers;
}


unsigned char Keyboard_Scan(void)
{
	unsigned char KeyVal = 0;
	Count %= KeyboardNumbers;
	switch (Count)
	{
	case 0:
		if (!GetValKey_1())
		{
			KeyVal = Count + 1;
		}
		break;
	case 1:
		if (!GetValKey_2())
		{
			KeyVal = Count + 1;
		}
		break;
	case 2:
		if (!GetValKey_3())
		{
			KeyVal = Count + 1;
		}
		break;
	case 3:
		if (!GetValKey_4())
		{
			KeyVal = Count + 1;
		}
		break;
/*                
	case 4:
		if (!GetValKey_5())
		{
			KeyVal = Count + 1;
		}
		break; */
//	case 5:
//		if (!Value_Key_6)
//		{
//			KeyVal = Count + 1;
//		}
//		break;
//	case 6:
//		if (!GPIO_ReadInputDataBit(KEY_PORT_BASE, KEY_POWER))
//		{
//			KeyVal = Count + 1;
//		}
//		break;
	}
	return KeyVal;
}

// key_1 放键事件处理
void Keyboard_Key01(void)
{
	// lcd show "down"
	//LCD_ClearSCR();
	//LCD_PutString(48, 48, "down");
	key_flag = 1;
	if (page_id!=0)	page_id--;
	FlagCounter = 0;
}

// key_2 放键事件处理
void Keyboard_Key02(void)
{
		// lcd show "left"
	LCD_ClearSCR();
	LCD_PutString(8, 28, "disable");
	LcdFlag = 1;
	page_id=1;
	FlagCounter = 0;
}

// key_3 放键事件处理
void Keyboard_Key03(void)
{
	// lcd show right
	LCD_ClearSCR();
	LCD_PutString(88, 28, "disable");
	LcdFlag = 1;
	page_id=1;
	FlagCounter = 0;
}

// key_4放键事件处理
void Keyboard_Key04(void)
{
	// lcd show up
	//LCD_ClearSCR();
	//LCD_PutString(56, 8, "up");
	key_flag = 1;
	if (page_id!=2)	page_id++;
	FlagCounter = 0;

    status = 0;
    delayed_100_ms_cnt = 0;
}

// key_5 放键事件处理
void Keyboard_Key05(void)
{
	
}

// key_6 放键事件处理
void Keyboard_Key06(void)
{
	
}

// key_7 放键事件处理
void Keyboard_Key07(void)
{
}

//板上KEY2压键事件处理
void Keyboard_Key11(void)
{
}

//板上KEY3压键事件处理
void Keyboard_Key12(void)
{
}

//板上KEY4_UP压键事件处理
void Keyboard_Key13(void)
{
}

//板上KEY4_DOWN压键事件处理
void Keyboard_Key14(void)
{
}


//板上KEY4_LEFT压键事件处理
void Keyboard_Key15(void)
{
}


//板上KEY4_RIGHT压键事件处理
void Keyboard_Key16(void)
{
}


//板上KEY4_SEL压键事件处理
void Keyboard_Key17(void)
{
}

//板上KEY2长压键事件处理
void Keyboard_Key21(void)
{
}

//板上KEY3长压键事件处理
void Keyboard_Key22(void)
{
}

//板上KEY4_UP长压键事件处理
void Keyboard_Key23(void)
{
}

//板上KEY4_DOWN长压键事件处理
void Keyboard_Key24(void)
{
}

//板上KeyStartStop长压键事件处理
void Keyboard_Key25(void)
{
}
//板上 KeyToggle长压键事件处理
void Keyboard_Key26(void)
{
}

//板上KEY4_SEL长压键事件处理
void Keyboard_Key27(void)
{
}


