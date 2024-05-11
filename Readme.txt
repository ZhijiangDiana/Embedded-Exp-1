==========================================================================
                 uC/OS-II Demo Project for MB9BF506 Series 
==========================================================================
                 (C) FUJITSU SEMICONDUCTOR (SHANGHAI) CO., LTD                 
                                                                        
 Software that is described herein is for illustrative purposes only
 which provides customers with programming information regarding the
 products. This software is supplied "AS IS" without any warranties.
 Fujitsu Semiconductor assumes no responsibility or liability for the
 use of the software, conveys no license or title under any patent,
 copyright, or mask work right to the product. Fujitsu Semiconductor
 reserves the right to make changes in the software without notification. 
 Fujitsu Semiconductor also makes no representation or warranty that 
 such application will be suitable for the specified use without further 
 testing or modification.                                                                                                                                                       
==========================================================================

History
Date          Ver    Author       Description
2011-03-15    0.1    Edison       original version
2012-11-13    0.2    Edison       Port on MB9BF506R

==========================================================================

This is a sample project to demonstrate how to tranplan and apply uC/OS-II on.
FM3 MCU. It is evaluated on FSSDC-9B506-EK EASY Kit.

It supplies two application examples with IAR Embedded Workbench V6.21 Kickstart 
and Keil uvision V4.21.

注：EVB ucos-II调试成功（AD、按键、LCD、uart）
增加按键功能
1、up、down按键翻页控制
2、left、right禁止操作显示：disable
3、增加UART，显示AD Value：xxx


