;/**************************************************************************//**
; * @file     startup_MB9BF50x.s
; * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Source File
; *           for the Fujitsu MB9BF50x Device Series
; * @version  V1.02
; * @date     21. December 2010
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; * @note
; * Copyright (C) 2010 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M 
; * processor based microcontrollers.  This file can be freely distributed 
; * within development tools that are supporting such ARM based processors. 
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                ;DCD     PendSV_Handler             ; PendSV Handler
				IMPORT  OS_CPU_PendSVHandler
				DCD		OS_CPU_PendSVHandler
                ;DCD     SysTick_Handler            ; SysTick Handler
				IMPORT	OS_CPU_SysTickHandler
				DCD		OS_CPU_SysTickHandler

                ; External Interrupts
                DCD     FCS_IRQHandler            ; 16+ 0: Anomalous Frequency Detection by Clock Supervisor (FCS)
                DCD     SWWDT_IRQHandler          ; 16+ 1: Software Watchdog Timer
                DCD     LVD_IRQHandler            ; 16+ 2: Low Voltage Detector (LVD)
                DCD     MFT_WFG_IRQHandler        ; 16+ 3: MFT unit0, unit1 Wave Form Generator / DTIF(Motor Emergency Stop)
                DCD     EXTI7_0_IRQHandler        ; 16+ 4: External INT_RQ ch.0 to ch.7
                DCD     EXTI15_8_IRQHandler       ; 16+ 5: External INT_RQ ch.8 to ch.15
               ; DCD     TIM_QPRC_IRQHandler       ; 16+ 6: Dual Timer / Quadrature Position/Resolution Counter (QPRC) ch.0, ch.1
                IMPORT  DT_QDU_IRQHandler
				DCD     DT_QDU_IRQHandler
				DCD     MFS0_R_IRQHandler         ; 16+ 7: Reception INT_RQ of MFS IF ch.0
                DCD     MFS0_TS_IRQHandler        ; 16+ 8: Transmission INT_RQ and Status INT_RQ of MFS IF ch.0
                DCD     MFS1_R_IRQHandler         ; 16+ 9: Reception INT_RQ of MFS IF ch.1
                DCD     MFS1_TS_IRQHandler        ; 16+10: Transmission INT_RQ and Status INT_RQ of MFS IF ch.1
                DCD     FMS2_R_IRQHandler         ; 16+11: Reception INT_RQ of MFA IF ch.2
                DCD     MFS2_TS_IRQHandler        ; 16+12: Transmission INT_RQ and Status INT_RQ of MFS IF ch.2
                DCD     MFS3_R_IRQHandler         ; 16+13: Reception INT_RQ of MFS IF ch.3
                DCD     MFS3_TS_IRQHandler        ; 16+14: Transmission INT_RQ and Status INT_RQ of MFS IF ch.3
                DCD     MFS4_R_IRQHandler         ; 16+15: Reception INT_RQ of MFS IF ch.4
                DCD     MFS4_TS_IRQHandler        ; 16+16: Transmission INT_RQ and Status INT_RQ of MFS IF ch.4
                DCD     MFS5_R_IRQHandler         ; 16+17: Reception INT_RQ of MFS IF ch.5
                DCD     MFS5_TS_IRQHandler        ; 16+18: Transmission INT_RQ and Status INT_RQ of MFS IF ch.5
                DCD     MFS6_R_IRQHandler         ; 16+19: Reception INT_RQ of MFS IF ch.6
                DCD     MFS6_TS_IRQHandler        ; 16+20: Transmission INT_RQ and Status INT_RQ of MFS IF ch.6
                DCD     MFS7_R_IRQHandler         ; 16+21: Reception INT_RQ of MFS IF ch.7
                DCD     MFS7_TS_IRQHandler        ; 16+22: Transmission INT_RQ and Status INT_RQ of MFS IF ch.7
                DCD     PPG_IRQHandler            ; 16+23: PPG ch.0/2/4/8/10/12
                DCD     OSC_PLL_WCNT_IRQHandler   ; 16+24: Ext. Main OSC / Ext. Sub OSC / Main PLL / PLL for USB / Watch CNT
                DCD     ADC0_IRQHandler           ; 16+25: A/D Converter unit0
                DCD     ADC1_IRQHandler           ; 16+26: A/D Converter unit1
                DCD     ADC2_IRQHandler           ; 16+27: A/D Converter unit2
                DCD     MFT_FRT_IRQHandler        ; 16+28: MFT unit0, unit1 Free-run Timer
                DCD     MFT_IC_IRQHandler         ; 16+29: MFT unit0, unit1 Input Capture
                DCD     MFT_OC_IRQHandler         ; 16+30: MFT unit0, unit1 Output Compare
                DCD     BTIM_IRQHandler           ; 16+31: Base Timer ch.0 to ch.7
                DCD     CAN0_IRQHandler           ; 16+32: CAN ch.0
                DCD     CAN1_IRQHandler           ; 16+33: CAN ch.1
                DCD     USB_EP1_EP5_IRQHandler    ; 16+34: USB Function (DRQ of End Point 1 to 5)
                DCD     USB_EP0_STA_IRQHandler    ; 16+35: USB Function (DRQI of End Point 0, DRQO) / USB HOST
                DCD     0                         ; 16+36: Reserved
                DCD     0                         ; 16+37: Reserved
                DCD     DMA0_IRQHandler           ; 16+38: DMA Controller (DMAC) ch.0
                DCD     DMA1_IRQHandler           ; 16+39: DMA Controller (DMAC) ch.1
                DCD     DMA2_IRQHandler           ; 16+40: DMA Controller (DMAC) ch.2
                DCD     DMA3_IRQHandler           ; 16+41: DMA Controller (DMAC) ch.3
                DCD     DMA4_IRQHandler           ; 16+42: DMA Controller (DMAC) ch.4
                DCD     DMA5_IRQHandler           ; 16+43: DMA Controller (DMAC) ch.5
                DCD     DMA6_IRQHandler           ; 16+44: DMA Controller (DMAC) ch.6
                DCD     DMA7_IRQHandler           ; 16+45: DMA Controller (DMAC) ch.7
                DCD     0                         ; 16+46: Reserved
                DCD     0                         ; 16+47: Reserved

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  FCS_IRQHandler            [WEAK]
                EXPORT  SWWDT_IRQHandler          [WEAK]
                EXPORT  LVD_IRQHandler            [WEAK]
                EXPORT  MFT_WFG_IRQHandler        [WEAK]
                EXPORT  EXTI7_0_IRQHandler        [WEAK]
                EXPORT  EXTI15_8_IRQHandler       [WEAK]
                EXPORT  TIM_QPRC_IRQHandler       [WEAK]
                EXPORT  MFS0_R_IRQHandler         [WEAK]
                EXPORT  MFS0_TS_IRQHandler        [WEAK]
                EXPORT  MFS1_R_IRQHandler         [WEAK]
                EXPORT  MFS1_TS_IRQHandler        [WEAK]
                EXPORT  FMS2_R_IRQHandler         [WEAK]
                EXPORT  MFS2_TS_IRQHandler        [WEAK]
                EXPORT  MFS3_R_IRQHandler         [WEAK]
                EXPORT  MFS3_TS_IRQHandler        [WEAK]
                EXPORT  MFS4_R_IRQHandler         [WEAK]
                EXPORT  MFS4_TS_IRQHandler        [WEAK]
                EXPORT  MFS5_R_IRQHandler         [WEAK]
                EXPORT  MFS5_TS_IRQHandler        [WEAK]
                EXPORT  MFS6_R_IRQHandler         [WEAK]
                EXPORT  MFS6_TS_IRQHandler        [WEAK]
                EXPORT  MFS7_R_IRQHandler         [WEAK]
                EXPORT  MFS7_TS_IRQHandler        [WEAK]
                EXPORT  PPG_IRQHandler            [WEAK]
                EXPORT  OSC_PLL_WCNT_IRQHandler   [WEAK]
                EXPORT  ADC0_IRQHandler           [WEAK]
                EXPORT  ADC1_IRQHandler           [WEAK]
                EXPORT  ADC2_IRQHandler           [WEAK]
                EXPORT  MFT_FRT_IRQHandler        [WEAK]
                EXPORT  MFT_IC_IRQHandler         [WEAK]
                EXPORT  MFT_OC_IRQHandler         [WEAK]
                EXPORT  BTIM_IRQHandler           [WEAK]
                EXPORT  CAN0_IRQHandler           [WEAK]
                EXPORT  CAN1_IRQHandler           [WEAK]
                EXPORT  USB_EP1_EP5_IRQHandler    [WEAK]
                EXPORT  USB_EP0_STA_IRQHandler    [WEAK]
                EXPORT  DMA0_IRQHandler           [WEAK]
                EXPORT  DMA1_IRQHandler           [WEAK]
                EXPORT  DMA2_IRQHandler           [WEAK]
                EXPORT  DMA3_IRQHandler           [WEAK]
                EXPORT  DMA4_IRQHandler           [WEAK]
                EXPORT  DMA5_IRQHandler           [WEAK]
                EXPORT  DMA6_IRQHandler           [WEAK]
                EXPORT  DMA7_IRQHandler           [WEAK]

FCS_IRQHandler     
SWWDT_IRQHandler   
LVD_IRQHandler     
MFT_WFG_IRQHandler 
EXTI7_0_IRQHandler 
EXTI15_8_IRQHandler
TIM_QPRC_IRQHandler
MFS0_R_IRQHandler  
MFS0_TS_IRQHandler 
MFS1_R_IRQHandler  
MFS1_TS_IRQHandler 
FMS2_R_IRQHandler  
MFS2_TS_IRQHandler 
MFS3_R_IRQHandler  
MFS3_TS_IRQHandler 
MFS4_R_IRQHandler  
MFS4_TS_IRQHandler 
MFS5_R_IRQHandler  
MFS5_TS_IRQHandler 
MFS6_R_IRQHandler  
MFS6_TS_IRQHandler 
MFS7_R_IRQHandler  
MFS7_TS_IRQHandler 
PPG_IRQHandler     
OSC_PLL_WCNT_IRQHandler  
ADC0_IRQHandler    
ADC1_IRQHandler    
ADC2_IRQHandler    
MFT_FRT_IRQHandler 
MFT_IC_IRQHandler  
MFT_OC_IRQHandler  
BTIM_IRQHandler    
CAN0_IRQHandler    
CAN1_IRQHandler    
USB_EP1_EP5_IRQHandler    
USB_EP0_STA_IRQHandler    
DMA0_IRQHandler    
DMA1_IRQHandler    
DMA2_IRQHandler    
DMA3_IRQHandler    
DMA4_IRQHandler    
DMA5_IRQHandler    
DMA6_IRQHandler    
DMA7_IRQHandler    

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
