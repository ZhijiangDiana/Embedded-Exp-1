/*******************************************************************************
* File Name          : lcd.c
* Version            : V1.1.0
* Date               : 11/13/2010
* Description        : Manley zymG12864C3
*******************************************************************************/
#include "lcd.h"
#include "font.h"

static unsigned char gui_disp_buf[GUI_LCM_YMAX/8][GUI_LCM_XMAX];
const unsigned char BIT_MASK[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
/* simple font: ' ', '0'~'9','a'~'z','A'~'Z' */
extern const unsigned char  FONTTYPE8_8[][8];
/*******************************************************************************
* Function Name  : LCD_Init
* Description    : initialize lcd
* Input          : None.
* Return         : None.
*******************************************************************************/
void LCD_Initialize(void)
//void LCD_Initialize(void)
{ 
	Power_Delay();
  LCD_WriteCmd(Display_Off);
  Reset_Delay();
  // Resetting circuit
  LCD_WriteCmd(Reset_LCD);
  Reset_Delay();
  // LCD bias setting
  LCD_WriteCmd(Set_LCD_Bias_9);
  Reset_Delay();
  // ADC selection: display from left to right
  LCD_WriteCmd(Set_ADC_Normal);		
  Reset_Delay();
  // Common output state selection: display from up to down
  LCD_WriteCmd(COM_Scan_Dir_Reverse);
  Reset_Delay();
	
  LCD_WriteCmd(Power_Booster_On);
  Power_Delay(); // 50ms requried
  LCD_WriteCmd(Power_Regulator_On);
  Power_Delay(); // 50ms
  LCD_WriteCmd(Power_Follower_On);
  Power_Delay(); // 50ms
	
  // Setting the built-in resistance radio for regulation of the V0 voltage
  // Electronic volume control
  // Power control setting
  LCD_WriteCmd(Set_ElecVol_Reg|0x05);
  Delay();
  LCD_WriteCmd(Set_ElecVol_Mode);
  Delay();
  LCD_WriteCmd(Set_ElecVol_Reg);
  Delay();
  //  LCD_Clear();
  Delay();
  LCD_WriteCmd(Set_Page_Addr_0);
  Delay();
  LCD_WriteCmd(Set_ColH_Addr_0);
  Delay();
  LCD_WriteCmd(Set_ColL_Addr_0);
  Delay();
  LCD_WriteCmd(Display_On);
  Delay();
	
  LCD_WriteCmd(Display_All_On);
  Delay();
  LCD_WriteCmd(Display_Off);
  Delay();
  LCD_WriteCmd(Display_On);
  Delay();
  LCD_WriteCmd(Display_All_Normal);
  Delay();
  
  LCD_ClearSCR();
}


/*******************************************************************************
* Function Name  : LCD_PowerOn
* Description    : Power on the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Power_On(void)
{
  LCD_WriteCmd(Display_On);
  Delay();
  LCD_WriteCmd(Power_Booster_On);
  Delay();
  LCD_WriteCmd(Power_Regulator_On);
  Delay();
  LCD_WriteCmd(Power_Follower_On);
  Delay();
}

/*******************************************************************************
* Function Name  : LCD_PowerOff
* Description    : Power off the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Power_Off(void)
{	
  LCD_WriteCmd(Display_Off);		// Power saver
  Delay();
  LCD_WriteCmd(Display_All_On);	        // commands(compound)
  Delay();
}

/*******************************************************************************
* Function Name  : LCD_Sleep_Enter
* Description    : Enter the sleep mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Sleep_Enter(void)
{
  // Sleep Mode Setting (Sleep Mode)
  LCD_WriteCmd(Sleep_Mode_Enable);	// preceding Command
  Delay();
  LCD_WriteCmd(Sleep_Mode_Deliver);	// pollowing Command
  Delay();
  LCD_WriteCmd(Display_Off);				// power saver
  Delay();
}

/*******************************************************************************
* Function Name  : LCD_Sleep_Exit
* Description    : Exit the sleep mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Sleep_Exit(void)
{
  LCD_WriteCmd(Display_All_Normal);		// display all points OFF
  Delay();
  // Sleep Mode Setting (Normal Mode)
  LCD_WriteCmd(Sleep_Mode_Disable);		// preceding Command
  Delay();
  LCD_WriteCmd(Sleep_Mode_Deliver);		// pollowing Command
  Delay();
  LCD_WriteCmd(Display_On);
  Delay();
}

/*******************************************************************************
* Function Name  : LCD_DisplayOn
* Description    : Enables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOn(void)
{
  LCD_WriteCmd(Display_On);	
}

/*******************************************************************************
* Function Name  : LCD_DisplayOff
* Description    : Disables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOff(void)
{
  LCD_WriteCmd(Display_Off);	
}

/*******************************************************************************
* Function Name  : Delay
* Description    : Delay some time.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Delay(void)
{
  unsigned char i=0x8,dummy;
  while(i--)
    dummy = 0;
}

/*******************************************************************************
* Function Name  : Reset_Delay
* Description    : Delay some time
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Reset_Delay(void)
{
  unsigned short i=0xff,dummy;
  while(i--)
    dummy = 0;
}

/*******************************************************************************
* Function Name  : Power_Delay
* Description    : Delay some time for power up.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Power_Delay(void)
{
  unsigned long i=0x4ffff,dummy;
  while(i--)
    dummy = 0;
}

/*******************************************************************************
* Function Name  : LCD_ClearSCR
* Description    : clean screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_ClearSCR(void)
{
  unsigned char i,j;
  for(i=0; i<GUI_LCM_PAGE; i++)
  { 
    for(j = 0; j < GUI_LCM_XMAX; j++) 
      gui_disp_buf[i][j] = 0;
  }
  LCD_FillAll((unsigned char*)gui_disp_buf);
}
/*******************************************************************************
* Function Name  : LCD_FillAll
* Description    : Fill the whole LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_FillAll(unsigned char*	buffer)
{
  unsigned char i,j = GUI_LCM_XMAX;
  unsigned char* p = buffer;  
	
  for (i=0; i<GUI_LCM_PAGE; i++)
  { 
    LCD_WriteCmd(Set_Page_Addr_0|i);	
    LCD_WriteCmd(Set_ColH_Addr_0);		
    LCD_WriteCmd(Set_ColL_Addr_0);
    j = GUI_LCM_XMAX;
    while (j--)
    {
      LCD_WriteData(*p++);
      Delay();
    }
  }
}

/****************************************************************************
* Function Name  : LCD_UpdatePoint
* Description    : refresh the point in screen 
* Input          : x      X-coordinate
                   y      Y-coordinate
* Output         : None
* Return         : None
****************************************************************************/

void  LCD_UpdatePoint(unsigned int x, unsigned int y)
{
  unsigned char coll, colh, page;
  page = y / 8;
  coll = x & 0x0f;
  colh = x >> 4;
	
  LCD_WriteCmd(Set_Page_Addr_0 | page);	        // page no.
  LCD_WriteCmd(Set_ColH_Addr_0 | colh);		// fixed col first addr
  LCD_WriteCmd(Set_ColL_Addr_0 | coll);
  LCD_WriteData(gui_disp_buf[page][x]);
}

/****************************************************************************
* Function Name  : LCD_PutChar
* Description    : output a char to screen 
                  (the char only can be ' ','0'~'9','A'~'Z','a'~'z')
* Input          : x      X-coordinate
                   y      Y-coordinate
                   ch     character
* Output         : None
* Return         : 1    Success
                   0    Fail
****************************************************************************/
unsigned char  LCD_PutChar(unsigned long x, unsigned long y, unsigned char ch)
{  
   unsigned char data;
   unsigned char i,j;
   if( x >=(GUI_LCM_XMAX-8) ) return(0);
   if( y >=(GUI_LCM_YMAX-8) ) return(0);
   
   if(ch == 0x20)
     ch -= 0x20;
     else if((ch >= 0x30)&&(ch <= 0x39))
       ch -= 0x2f;
       else if((ch >= 0x41)&&(ch <= 0x5a))
         ch -= 0x36;
         else if((ch >= 0x61)&&(ch <= 0x7a))
          ch -= 0x3C;
         else if(ch == 0x3A) /* : */
                ch = 63;
         else if(ch == 0x25) /* % */
                ch = 64;
         else if(ch == 0x2e) /* . */
                ch = 65;
         else if(ch == 0x2f) /* / */
                ch = 66;
         else if(ch == 0x3c) /* < */
                ch = 67;
         else if(ch == 0x3e) /* > */
                ch = 68;
         else if(ch == 0x2d) /* - */
                ch = 69;
          else
            return(0);
    
   for(i = 0; i < 8; i++)
   {  
      data = FONTTYPE8_8[ch][i];
      
      for(j = 0; j < 8; j++)
      {  
         if( (data&BIT_MASK[j]) == 0)
           gui_disp_buf[y / 8][x] &= (~(0x01 << ( y % 8)));
         else  
           gui_disp_buf[y / 8][x] |= (0x01 <<( y % 8));
         LCD_UpdatePoint(x, y);
         x ++;
      }
      x -= 8;								
      y++;									
   }
   
   return(1);
}

/****************************************************************************
* Function Name  : LCD_PutString
* Description    : output string to screen 
* Input          : x      X-coordinate
                   y      Y-coordinate
                  str     pointer to string
* Output         : None
* Return         : None
****************************************************************************/
void  LCD_PutString(unsigned long x, unsigned long y, char *str)
{  
  while(1)
  {  
    if( (*str)=='\0' ) break;
    if( LCD_PutChar(x, y, *str++) == 0 ) break;
    x += 6;								
  }
}

/*******************************************************************************
* Function Name  : LCD_Write
* Description    : write data or command to lcd sdram 
* Input          : command
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteCmd(unsigned char command)
{

	unsigned char i;
	LCD_CS_LOW();
	LCD_CD_LOW();
	for(i=0; i<8; i++)
        {
            if(command & (0x80 >> i))
                    LCD_DATA_HIGH();
            else
                    LCD_DATA_LOW();
            
            LCD_CLK_LOW();
            Delay();
            LCD_CLK_HIGH();
            Delay();
        }
	LCD_CS_HIGH();

}
/*******************************************************************************
* Function Name  : LCD_Write
* Description    : write data or command to lcd sdram 
* Input          : data: data or command 
									 attribute: data or command
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteData(unsigned char data)
{
    unsigned char i;
    LCD_CS_LOW();
    LCD_CD_HIGH();
    for(i=0; i<8; i++)
    {
            if(data & (0x80 >> i))
                    LCD_DATA_HIGH();
            else
                    LCD_DATA_LOW();
            
            LCD_CLK_LOW();
            Delay();
            LCD_CLK_HIGH();
            Delay();
    }
    LCD_CS_HIGH();

}


/******************* (C) COPYRIGHT 2009 Manley electronics *****END OF FILE****/


