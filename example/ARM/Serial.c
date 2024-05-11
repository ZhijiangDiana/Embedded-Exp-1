/******************************************************************************/
/* Serial.c: Low Level Serial Routines                                        */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2010 Keil - An ARM Company. All rights reserved.             */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

//#include <MB9BF50x.h>                   /* MB9BF50x definitions              */
#include "mb9bf506r.h"
#include "ucos_ii.h"


/*----------------------------------------------------------------------------
  Initialize UART pins, Baudrate
 *----------------------------------------------------------------------------*/
void SER_init (void) {
  /* add code */
}


/*----------------------------------------------------------------------------
  Write character to Serial Port
 *----------------------------------------------------------------------------*/
int sendchar (int c) {
    OS_CPU_SR  cpu_sr = 0;
#ifdef __DBG_ITM
    OS_ENTER_CRITICAL();
    ITM_SendChar(c);
	OS_EXIT_CRITICAL();
#else
  /* add code */
#endif

  return (c);
}


/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
int getkey (void) {
  /* add code */

  return (-1);
}
