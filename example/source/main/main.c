/*************************************************************************
 *
 *    Used with ARMCC/IARCC
 *
 *    (c) Copyright FUJITSU SEMICONDUCTOR (SHANGHAI) CO., LTD
 *
 *    File name   :  main.c
 *    Description :  This example project shows how to transplant and apply uC/OS-II
 *                   with Keil uversion 4.13a/IAR EWARM V6101 on FSSDC-9B506-EK board.
 *                   This application creates 3 tasks to demonstrates parallel implementation of these tasks.
 *                   Task 1: Implement AD sample
 *                   Task 2: Detect key press status
 *                   Task 3: Monitor system information and display it at debug printf window
 *
 *                   $ Press Joystick to switch display on LCD among system information, task list and
                       stack usage of each task.
 *
 *    1. Date        : 22, Feb 2011
 *       Author      : Edison Zhang
 *       Description : Initial revistion
 *
 *
 *     $Revision: #2 $
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "lcd.h"
#include "key.h"
#include "adc.h"
#include "ucos_ii.h"
#include "mb9bf50x_lib.h"
#include "uart.h"
#include "..\driver\mfs\uart\uart_fm3.h"

#include "mb9bf506r.h"
#include "debug.h"
#include "os_cpu.h"

#define TIMER0_TICK_PER_SEC   40

/* Task priority */
#define  Task_Start_PRIO    2
#define  Task_AD_PRIO       13
#define  Task_KEY_PRIO      14
#define  Task_Monitor_PRIO  OS_LOWEST_PRIO-3
#define  Task_LED_PRIO      28

/* Task stack size */
#define  Task_Start_SS      128
#define  Task_AD_SS     128
#define  Task_KEY_SS         128
#define  Task_Monitor_SS    256

#define  Task_LED_SS    128



/* Task stack array */
OS_STK  Task_Start_STK[Task_Start_SS];
OS_STK  Task_AD_STK[Task_AD_SS];
OS_STK  Task_KEY_STK[Task_KEY_SS];
OS_STK  Task_Monitor_STK[Task_Monitor_SS];

OS_STK Task_LED_STK[Task_LED_SS];

/* task declaration */
void Task_Start(void *pdata);
void Task_AD(void *pdata);
void Task_Key(void *pdata);
void Task_Monitor(void *pdata);

void LedTask(void *pdata);

/*variable for clitical section entry control*/
INT32U CriticalSecCntr;
char disp[16] = {'\0'};
unsigned short AD_Data, AD_Data_temp = 0;
unsigned char LcdFlag;
unsigned short FlagCounter,VaulePwm;

extern unsigned char Count;

uint8_t status = 0;
uint32_t delayed_100_ms_cnt = 0;

char *lcd_dsp_buf[3][8] =
{
    {
        "uC/OS-II V2.86",
        "Fujitsu Cotex M3",
        "CPU Usage:",
        "CPU Speed: 80 MHz",
        "Second: ",
        "AD value:",
        "< Press key >",
    },
    {
        "Task name  Pri",
        "Idle       252",
        "stat       251",
        "key        14",
        "AD         13",
        "Monitor    249",
        "< Press key >",
    },
    {
        "Stk  Used Remain",
        "Idle",
        "stat",
        "key",
        "AD",
        "Mon",
        "< Press key >",
    },
};


unsigned char page_id,ad_update_flag, cpu_usage, cpu_usage_flag;
unsigned int g_sec, g_sec_temp, time_update_flag;
unsigned char key_flag;
unsigned int idle_stk_used,idle_stk_remain;
unsigned int stat_stk_used,stat_stk_remain;
unsigned int ad_stk_used,ad_stk_remain;
unsigned int key_stk_used,key_stk_remain;
unsigned int mon_stk_used,mon_stk_remain;
unsigned char stk_update_flag;
/*************************************************************************
 * Function Name: NVIC_IntEnable
 * Parameters: IntNumber - Interrup number
 * Return: void
 *
 * Description: Enable interrup at NVIC
 *
 *
 *************************************************************************/
void NVIC_IntEnable(INT32S IntNumber)
{
    volatile INT32U * pNVIC_SetEn = (INT32U*)0xE000E100;

    IntNumber -= CSV_IRQn;

    pNVIC_SetEn += IntNumber/32;
    *pNVIC_SetEn = (1UL<<(IntNumber%32));

}

/*************************************************************************
 * Function Name: NVIC_IntDisable
 * Parameters: IntNumber - Interrup number
 * Return: void
 *
 * Description: Disables interrup at NVIC
 *
 *
 *************************************************************************/
void NVIC_IntDisable(INT32S IntNumber)
{
    volatile INT32U * pNVIC_ClrEn = (INT32U*)0xE000E180;

    IntNumber -= CSV_IRQn;

    pNVIC_ClrEn += IntNumber/32;
    *pNVIC_ClrEn = (1UL<<(IntNumber%32));

}

/*************************************************************************
 * Function Name: NVIC_ClrPend
 * Parameters: IntNumber - Interrup number
 * Return: void
 *
 * Description:Clear pending interrupt at NVIC
 *
 *
 *************************************************************************/
void NVIC_ClrPend(INT32S IntNumber)
{
    volatile INT32U * pNVIC_ClrPend = (INT32U*)0xE000E280;

    IntNumber -= CSV_IRQn;

    pNVIC_ClrPend += IntNumber/32;
    *pNVIC_ClrPend = (1UL<<(IntNumber%32));

}

/*************************************************************************
 * Function Name: NVIC_ClrPend
 * Parameters: IntNumber - Interrup number, Interrupt Priority
 * Return: void
 *
 * Description:Sets Interrupt priority
 *
 *
 *************************************************************************/
void NVIC_IntPri(INT32S IntNumber, INT8U Priority)
{
    volatile INT8U * pNVIC_IntPri = (INT8U *)0xE000E400;

    IntNumber -= CSV_IRQn;
    pNVIC_IntPri += IntNumber;
    *pNVIC_IntPri = Priority;
}


int Tmr1Tick;

/*************************************************************************
 * Function Name: DT_QDU_IRQHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Timer 1 interrupt handler
 *
 *************************************************************************/
void DT_QDU_IRQHandler(void)
{
    Tmr1Tick = 1;
    VaulePwm++;
    if(2038 == VaulePwm)
        VaulePwm = 10;
    if(1024 > VaulePwm)
        Update_PWM(VaulePwm);
    else
        Update_PWM(2048-VaulePwm);
    FlagCounter++;
    FM3_DTIM->TIMER1INTCLR = 1;
}

/*************************************************************************
 * Function Name: GetBaseClock
 * Parameters: void
 * Return: Base Clock in HZ
 *
 * Description:
 *
 *************************************************************************/
INT32S GetBaseClock(void)
{
    INT32S clock = -1;
    INT32U n,k;

    switch((FM3_CRG->SCM_STR&0xe0)>>5)
    {
            /*Internal High Speed oscilator*/
        case 0:
            clock = (CLKHC)/(FM3_CRG->BSC_PSR +1);
            break;
            /*Main oscilator*/
        case 1:
            clock = (CLKMO)/(FM3_CRG->BSC_PSR +1);
            break;
            /*PLL*/
            case 2:
             n = ((FM3_CRG->PLL_CTL2)& 0x3F)+1;		 //PLLN
             k = (((FM3_CRG->PLL_CTL1>>4)& 0x0F)+1); //PLLK
             clock = ((CLKMO*n)/k)/(FM3_CRG->BSC_PSR +1);	//�õ�72MHz	(0x044AA200)
            break;
            /*Internal Low Speed Oscilator*/
        case 4:
            clock = (CLKLC)
                    /(FM3_CRG->BSC_PSR +1);
            break;
            /*Sub Oscilator*/
        case 5:
            clock = (CLKSO)
                    /(FM3_CRG->BSC_PSR +1);
            break;
        default:
            break;
    }
    return clock;
}

/*************************************************************************
 * Function Name: InitLEDs
 * Parameters: void
 * Return: void
 *
 * Description: Init LED pins as outputs.
 *
 *************************************************************************/
void InitLEDs(void)
{
   /*Select CPIO function*/
    USER_LED_PFR &= ~USER_LED_MASK;
    /* disable analog input */
    FM3_GPIO->ADE &= ~USER_LED_MASK;
    /*Set CPIO Pull-Up function*/
    USER_LED_PCR |= USER_LED_MASK;
    /*Make led pins outputs*/
    USER_LED_DDR |= USER_LED_MASK;
    USER_LED_PDOR |= USER_LED_MASK;
}
/*************************************************************************
 * Function Name: Init_LCD_IO
 * Parameters: void
 * Return: void
 *
 * Description: Init LCD Pins
 *
 *************************************************************************/
void Init_LCD_IO()
{
   /* Release the analog input function*/
	FM3_GPIO->ADE =0x03;
	/*Select CPIO function*/
  LCD_CS_PFR &= ~LCD_CS;
  /*Make pin output*/
  LCD_CS_DDR |= LCD_CS;
  /*Select CPIO function*/
  LCD_CD_PFR &= ~LCD_CD;
  /*Make pin output*/
  LCD_CD_DDR |= LCD_CD;
  /*Select CPIO function*/
  LCD_CLK_PFR &= ~LCD_CLK;
  /*Make pin output*/
  LCD_CLK_DDR |= LCD_CLK;
  /*Select CPIO function*/
  LCD_DATA_PFR &= ~LCD_DATA;
  /*Make pin output*/
  LCD_DATA_DDR |= LCD_DATA;
}
/*************************************************************************
 * Function Name: Init_Joy_IO
 * Parameters: void
 * Return: void
 *
 * Description: Init Button pins as inputs.
 *
 *************************************************************************/
void Init_Joy_IO(void)
{
    /*Select CPIO function*/
    JOY_PFR &= ~JOY_MASK;
    /*Set CPIO Pull-Up function*/
    JOY_PCR |= JOY_MASK;
    /*Make button pins inputs*/
    JOY_DDR &= ~JOY_MASK;
}


/*************************************************************************
 * Function Name: DelayResolution100us
 * Parameters: Int32U Dly
 * Return: void
 *
 * Description: Delay Dly * [100us]
 *
 *************************************************************************/
void DelayResolution100us(INT32U Dly)
{
    volatile INT32U  loop_100us;
    for(;Dly;Dly--)
    {
        for(loop_100us = 550; loop_100us; loop_100us--)
        {
        }
    }
}

/*************************************************************************
 * Function Name: main
 * Parameters: none
 *
 * Return: none
 *
 * Description: main
 *
 *************************************************************************/
int main(void)
{
INT8U i=0;
#if (OS_TASK_NAME_SIZE > 5)
    INT8U  err;
#endif
    /* system initialization */
    SystemInit();

    /* uC/OS-II initialization */
    OSInit();

    /* Create task */
    OSTaskCreateExt(Task_Start,
                   (void *)0,
                   &Task_Start_STK[Task_Start_SS-1],
                   Task_Start_PRIO,
                   Task_Start_PRIO,
                   &Task_Start_STK[0],
                   Task_Start_SS, (void *)0,
                   OS_TASK_OPT_STK_CHK + OS_TASK_OPT_STK_CLR);

#if (OS_TASK_NAME_SIZE > 5)
    OSTaskNameSet(Task_Start_PRIO, "Start", &err);
#endif

    /* uC/OS-II starts to schdule*/
    OSStart();

    /*Main Loop*/
    while(1) {}
}

void LedTask(void *pdata) {
    while (TRUE) {
        switch (status) {
            case 0:
                if (delayed_100_ms_cnt == 20 * 10) {
                    delayed_100_ms_cnt = 0;
                    status++;
                }
                USER_LED_PDOR |= USER_LED_MASK;
                USER_LED_PDOR &= ~USER_LED1;
                OSTimeDlyHMSM(0, 0, 0,100);
                break;
            case 1:
                if (delayed_100_ms_cnt == 5) {
                    delayed_100_ms_cnt = 0;
                    status++;
                }
                USER_LED_PDOR |= USER_LED_MASK;
                USER_LED_PDOR &= ~USER_LED2;
                OSTimeDlyHMSM(0, 0, 0,100);
                break;
            case 2:
                if (delayed_100_ms_cnt == 10 * 10) {
                    delayed_100_ms_cnt = 0;
                    status = 0;
                }
                USER_LED_PDOR |= USER_LED_MASK;
                USER_LED_PDOR &= ~USER_LED3;
                OSTimeDlyHMSM(0, 0, 0,100);
                break;
            default:
                status = 0;
        }
        delayed_100_ms_cnt++;
    }
}

/******************************************************************/
/* Task name:        Task_Start                                   */
/* Task Description: This task is used to initial system timer    */
/*                   and start system task, so this task is       */
/*                   set to highest priority, which should be     */
/*                   implemented first after OS starts. After     */
/*                   this process finishes, it is deleted by      */
/*                   itself.                                      */
/******************************************************************/
void Task_Start(void *pdata)
{
#if (OS_TASK_NAME_SIZE > 5)
    INT8U  err;
#endif
	int32_t len,i=0;
        char enter[]="\n";

    OS_CPU_SysTickInit();       /* initial systemtick timer */
    OSStatInit();               /* start stat task  */

     /* Init LCD Pins */
    Init_LCD_IO();
    /* Init LCD */
    LCD_Initialize();
    /* Delay */
    DelayResolution100us(10);
    /* Display welcome */
   // LCD_FillAll(Fujitsu_Welcome);
    /* Init LEDs*/
    InitLEDs();
    /* Init Joy-sticks */
    Init_Joy_IO();
    Keyboard_Init();
    /* Init ADC conversion */
    Init_ADC();
    /* Init PWM output */
    Init_PWM();
    VaulePwm = 10;

    /*Set Timer 1 Load Value*/
    FM3_DTIM->TIMER1LOAD =  GetBaseClock() /* Base Clock */
                /2             /* APB Devider */
                /256           /* Timer devider */
                /1000;         /* 1000 times per second */
    /*Set Timer 1 Mode*/
    FM3_DTIM->TIMER1CONTROL = (0<<0) |     /*wrapping mode*/
                  (1<<1) |     /*1 = 32-bit counter*/
                  (2<<2) |     /*8 stages of prescale, clock is divided by 256*/
                  (1<<5) |     /*Interrupt Enable*/
                  (1<<6) |     /*Timer is in periodic mode*/
                  (1<<7) ;     /*Timer enabled*/
    /*Enable Dual Timer Interrup*/

		// InitUart2();
        //pt=lcd_dsp_buf;
        //len=sizeof(pt[0]);

	//UART_WriteBuf(2,(char *)pt[0],len);
	for(i=0; i<7 ;i++)
      {
      		len=strlen(lcd_dsp_buf[0][i]);
         	// UART_WriteBuf(2,  lcd_dsp_buf[0][i],len);
					// UART_WriteBuf(2,  &enter[0],1);
      }



    NVIC_IntEnable(DTIM_QDU_IRQn);

    OSTaskCreate(LedTask, NULL, Task_LED_STK, Task_LED_PRIO);

//    OSTaskCreateExt(Task_AD, (void *)0,
//                &Task_AD_STK[Task_AD_SS-1],
//                Task_AD_PRIO,
//                Task_AD_PRIO,
//                &Task_AD_STK[0],
//                Task_AD_SS,
//                (void *)0,
//                OS_TASK_OPT_STK_CHK + OS_TASK_OPT_STK_CLR);

//#if (OS_TASK_NAME_SIZE > 5)
//    OSTaskNameSet(Task_AD_PRIO, "AD", &err);
//#endif

    OSTaskCreateExt(Task_Key, (void *)0,
                &Task_KEY_STK[Task_KEY_SS-1],
                Task_KEY_PRIO,
                Task_KEY_PRIO,
                &Task_KEY_STK[0],
                Task_KEY_SS,
                (void *)0,
                OS_TASK_OPT_STK_CHK + OS_TASK_OPT_STK_CLR);
#if (OS_TASK_NAME_SIZE > 5)
    OSTaskNameSet(Task_KEY_PRIO, "Key", &err);
#endif

//    OSTaskCreateExt(Task_Monitor, (void *)0,
//                &Task_Monitor_STK[Task_Monitor_SS-1],
//                Task_Monitor_PRIO,
//                Task_Monitor_PRIO,
//                &Task_Monitor_STK[0],
//                Task_Monitor_SS,
//                (void *)0,
//                OS_TASK_OPT_STK_CHK + OS_TASK_OPT_STK_CLR);
//#if (OS_TASK_NAME_SIZE > 5)
//    OSTaskNameSet(Task_Monitor_PRIO, "Monitor", &err);
//#endif

    key_flag = 1;
    OSTaskDel(OS_PRIO_SELF);    /* deteled by itself */
}


/******************************************************************/
/* Task name:        Task_AD                                    */
/* Task Description: This task is used to make LED2,4,6,8         */
/*                   twinkle at 1Hz frequency.                    */
/*                                                                */
/******************************************************************/
void Task_AD(void *pdata)
{
    //UartDev_IOB *uart;
    int32_t size;
     char const  tx_buf[] = "\n AD Value: ";
	 char AD_Data_ASCII[3],temp;

    while(1)
    {

        if(0x80 == (IOREG_ADCR_U0 & 0x80))
        {
            IOREG_ADCR_U0 &= ~0x80;
            AD_Data_temp = IOREG_SCFD_U0;
            AD_Data_temp = AD_Data_temp >> 4;

		temp=AD_Data_temp &0x0f;
                if( temp > 9)
			AD_Data_ASCII[2]=(AD_Data_temp &0x0f)+0x37;
		else
			AD_Data_ASCII[2]=(AD_Data_temp &0x0f) |0x30;

                temp = (AD_Data_temp &0xf0)>>4;

		if(temp>9)
			AD_Data_ASCII[1]=((AD_Data_temp &0xf0)>>4) +0x37;
		else
                        AD_Data_ASCII[1]=((AD_Data_temp &0xf0)>>4) |0x30;

                 temp = (AD_Data_temp>>8)&0x0f;

                 if(temp>9)
			AD_Data_ASCII[0]=((AD_Data_temp>>8) &0x0f) +0x37;
		 else
                        AD_Data_ASCII[0]=((AD_Data_temp>>8) &0x0f) |0x30;

            size=strlen(tx_buf);

            // UART_WriteBuf(2,  (char *) &tx_buf[0],size);


            // UART_WriteBuf(2, (char *) &AD_Data_ASCII,3);

            IOREG_SCCR_U0 |= 0x01;                  /* A/DC start */
        }
        if(abs(AD_Data_temp - AD_Data) > 20)
        {
            ad_update_flag = 1;
            AD_Data = AD_Data_temp;
            AD_Data_temp = 0;
            FlagCounter = 0;



        }
        OSTimeDlyHMSM(0, 0, 0,100);  /* Task delay 100ms */
    }
 }

/******************************************************************/
/* Task name:        Task_Key                                     */
/* Task Description: This task is used to detect key press        */
/*                   status.                                      */
/*                                                                */
/******************************************************************/
void Task_Key(void *pdata)
{
      while(1)
      {
         Keyboard_Exec();
         if(Count%KeyboardNumbers == 0)
            OSTimeDlyHMSM(0, 0, 0, 30);  /* Task delay 500ms */
      }
}

/******************************************************************/
/* Function name:        LCD_stk_update                           */
/* Description: update stack usage display                        */
/*                                                                */
/******************************************************************/
void LCD_stk_update(char *str ,unsigned char offset, unsigned int used, unsigned int remain)
{
    sprintf(str, "%d", used);
    LCD_PutString(0+30, (0+offset*9), str);
    sprintf(str, "");
    sprintf(str, "%d", remain);
    LCD_PutString(0+30+30, (0+offset*9), str);
    sprintf(str, "");
}

/******************************************************************/
/* Function name:        LCD_display                              */
/* Description: Display imformation on LCD                        */
/*                                                                */
/******************************************************************/

void LCD_display(void)
{
  unsigned char i, ad_str[2];
  char t_str[16]={0};
  unsigned char update = 0;
  unsigned short temp_ad;
  if(key_flag){
      key_flag = 0;
      LCD_ClearSCR();
      for(i=0; i<7 ;i++)
      {
          LCD_PutString(0, (0+i*9), lcd_dsp_buf[page_id][i]);
      }
      time_update_flag = 1;
      ad_update_flag = 1;
      cpu_usage_flag = 1;
      stk_update_flag = 1;
  }
  if(time_update_flag || ad_update_flag || cpu_usage_flag || stk_update_flag)
      update = 1;
  switch(page_id){
    case 0:
      if(time_update_flag)
        {
            time_update_flag = 0;
            sprintf(t_str, "%d", g_sec);
            LCD_PutString(0+45, (0+4*9), t_str);
            sprintf(t_str, "");
        }

        if(ad_update_flag)
        {
            ad_update_flag = 0;
            temp_ad = (AD_Data*100)/1024;
            ad_str [0] = temp_ad%10 + '0';
            ad_str [1] = temp_ad/10 + '0';
            sprintf(t_str, "%c%c%c", ad_str [1], ad_str [0] , '%');
            LCD_PutString(0+56, (0+5*9), t_str);
            sprintf(t_str, "");
        }

        if(cpu_usage_flag)
        {
            cpu_usage_flag = 0;
            ad_str [0] = cpu_usage%10 + '0';
            ad_str [1] = cpu_usage/10 + '0';
            sprintf(t_str, "%c%c%c", ad_str [1], ad_str [0] , '%');
            LCD_PutString(0+66, (0+2*9), t_str);
            sprintf(t_str, "");

        }
        if(update)
            OSTimeDlyHMSM(0, 0, 0, 250);  /* Task delay 250ms */
        else
            OSTimeDlyHMSM(0, 0, 0, 50);  /* Task delay 50ms */
        break;
    case 1:
        OSTimeDlyHMSM(0, 0, 0, 250);  /* Task delay 250ms */
        break;
    case 2:
        if(stk_update_flag)
        {
            stk_update_flag = 0;
            LCD_stk_update(t_str, 1, idle_stk_used, idle_stk_remain);
            LCD_stk_update(t_str, 2, stat_stk_used, stat_stk_remain);
            LCD_stk_update(t_str, 3, ad_stk_used, ad_stk_remain);
            LCD_stk_update(t_str, 4, key_stk_used, key_stk_remain);
            LCD_stk_update(t_str, 5, mon_stk_used, mon_stk_remain);
        }
        if(update)
            OSTimeDlyHMSM(0, 0, 0, 250);  /* Task delay 250ms */
        else
            OSTimeDlyHMSM(0, 0, 0, 50);  /* Task delay 50ms */
        break;
  }

}

/******************************************************************/
/* Function name:        Get_OSSTK_Status                         */
/* Description: Get stack usage data                              */
/*                                                                */
/******************************************************************/
unsigned char Get_OSSTK_Status(unsigned char prio, unsigned int *usage, unsigned int *remain)
{
    unsigned char ret=0;
    OS_STK_DATA     stk;
    OSTaskStkChk(prio, &stk);
    if(*usage != stk.OSUsed)
    {
        ret = 1;
    }
    *usage = stk.OSUsed;
    *remain = stk.OSFree;
    return ret;
}

/******************************************************************/
/* Task name:        Task_Monitor                                 */
/* Task Description: this task monitors system implementation     */
/*                   status and prints CPU usage, stack usage,    */
/*                   AD value, and key status on debug printf     */
/*                   window.                                      */
/******************************************************************/
void Task_Monitor(void *pdata)
{
    while(1)
    {
        /* get system time */
        g_sec = OSTimeGet() / OS_TICKS_PER_SEC;
        if(g_sec != g_sec_temp)
        {
            time_update_flag = 1;
        }
        g_sec_temp = g_sec;

        /* get CPU usage */
        if(cpu_usage != OSCPUUsage)
        {
            cpu_usage_flag = 1;
        }
        cpu_usage = OSCPUUsage;

        /* get task stack data */
        if(Get_OSSTK_Status(OS_LOWEST_PRIO, &idle_stk_used, &idle_stk_remain)
          || Get_OSSTK_Status(OS_LOWEST_PRIO-1, &stat_stk_used, &stat_stk_remain)
          || Get_OSSTK_Status(Task_AD_PRIO, &ad_stk_used, &ad_stk_remain)
          || Get_OSSTK_Status(Task_KEY_PRIO, &key_stk_used, &key_stk_remain)
          || Get_OSSTK_Status(Task_Monitor_PRIO, &mon_stk_used, &mon_stk_remain))
        {
            stk_update_flag = 1;
        }
        /* display information on LCD */
        LCD_display();

    }
}

