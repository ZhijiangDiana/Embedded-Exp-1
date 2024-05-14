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
����ϵͳ����
---------------------------------------------------------*/
volatile signed int KeyPressCount[4];	//����ѹ��20mS����������
volatile signed int KeyDblCount[4];		//�����ֵ���������� 
volatile unsigned char PressCount[KeyboardNumbers], PressTimes[KeyboardNumbers];
unsigned char Count;
typedef void (*FunctionPtr)(void);//����ָ��
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
    },//�ż���
    {
        Keyboard_Key11,
        Keyboard_Key12,
        Keyboard_Key13,
        Keyboard_Key14,
        Keyboard_Key15,
        Keyboard_Key16,
        Keyboard_Key17
    },//��ѹ��
    {
        Keyboard_Key21,
        Keyboard_Key22,
        Keyboard_Key23,
        Keyboard_Key24,
        Keyboard_Key25,
        Keyboard_Key26,
        Keyboard_Key27
    } //��ѹ��
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
	KeyCount = PressCount[Count];//ȡѹ������
	if (Keyboard_Scan() == Count + 1)//�м�ѹ��
	{
		KeyCount++;//ѹ������	
		if (KeyCount >= KeyboardPushTimes)
		{
			if (KeyCount == KeyboardPushTimes)//��ѹ��
			{
				PressTimes[Count] = 0;
				KeyboardCommandTab[1][Count]();
			}
			if (KeyCount == KeyboardLongPushTimes)//��ѹ��
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
	else//�޼�ѹ��
	{
		if (KeyCount > 0)//��ǰ�м�ѹ��
		{			
			if (KeyCount > KeyboardPushTimes)	
			{
				KeyCount = KeyboardPushTimes;
			}		
			else
			{
				KeyCount--;//�ż�����
				if (KeyCount == 0)//���ͷ�
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

// key_1 �ż��¼�����
void Keyboard_Key01(void)
{
	// lcd show "down"
	//LCD_ClearSCR();
	//LCD_PutString(48, 48, "down");
	key_flag = 1;
	if (page_id!=0)	page_id--;
	FlagCounter = 0;
}

// key_2 �ż��¼�����
void Keyboard_Key02(void)
{
		// lcd show "left"
	LCD_ClearSCR();
	LCD_PutString(8, 28, "disable");
	LcdFlag = 1;
	page_id=1;
	FlagCounter = 0;
}

// key_3 �ż��¼�����
void Keyboard_Key03(void)
{
	// lcd show right
	LCD_ClearSCR();
	LCD_PutString(88, 28, "disable");
	LcdFlag = 1;
	page_id=1;
	FlagCounter = 0;
}

// key_4�ż��¼�����
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

// key_5 �ż��¼�����
void Keyboard_Key05(void)
{
	
}

// key_6 �ż��¼�����
void Keyboard_Key06(void)
{
	
}

// key_7 �ż��¼�����
void Keyboard_Key07(void)
{
}

//����KEY2ѹ���¼�����
void Keyboard_Key11(void)
{
}

//����KEY3ѹ���¼�����
void Keyboard_Key12(void)
{
}

//����KEY4_UPѹ���¼�����
void Keyboard_Key13(void)
{
}

//����KEY4_DOWNѹ���¼�����
void Keyboard_Key14(void)
{
}


//����KEY4_LEFTѹ���¼�����
void Keyboard_Key15(void)
{
}


//����KEY4_RIGHTѹ���¼�����
void Keyboard_Key16(void)
{
}


//����KEY4_SELѹ���¼�����
void Keyboard_Key17(void)
{
}

//����KEY2��ѹ���¼�����
void Keyboard_Key21(void)
{
}

//����KEY3��ѹ���¼�����
void Keyboard_Key22(void)
{
}

//����KEY4_UP��ѹ���¼�����
void Keyboard_Key23(void)
{
}

//����KEY4_DOWN��ѹ���¼�����
void Keyboard_Key24(void)
{
}

//����KeyStartStop��ѹ���¼�����
void Keyboard_Key25(void)
{
}
//���� KeyToggle��ѹ���¼�����
void Keyboard_Key26(void)
{
}

//����KEY4_SEL��ѹ���¼�����
void Keyboard_Key27(void)
{
}


