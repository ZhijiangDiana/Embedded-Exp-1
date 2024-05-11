/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2010 IAR Systems. All rights reserved.
 *
 * $Revision: 39069 $
 *
 **************************************************/

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:ROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)                 ; Top of Stack
        DCD     __iar_program_start         ; Reset Handler
        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
        DCD     MemManage_Handler           ; MPU Fault Handler
        DCD     BusFault_Handler            ; Bus Fault Handler
        DCD     UsageFault_Handler          ; Usage Fault Handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall Handler
        DCD     DebugMon_Handler            ; Debug Monitor Handler
        DCD     0                           ; Reserved
       ;DCD     PendSV_Handler             ; PendSV Handler
        IMPORT  OS_CPU_PendSVHandler
        DCD	OS_CPU_PendSVHandler
        ;DCD     SysTick_Handler            ; SysTick Handler
        IMPORT	OS_CPU_SysTickHandler
        DCD	OS_CPU_SysTickHandler
        DCD     FCS_IRQHandler              ; Anomalous Frequency Detection by Clock Supervisor (FCS)                    
        DCD     SWDT_IRQHandler             ; Software Watchdog Timer                                                    
        DCD     LVD_IRQHandler              ; Low Voltage Detector (LVD)                                                 
        DCD     WFG_IRQHandler              ; Wave Form Generator unit0, unit1                                           
        DCD     EXTI0_7_IRQHandler          ; External Interrupt Request ch.0 to ch.7                                    
        DCD     EXTI8_15_IRQHandler         ; External Interrupt Request ch.8 to ch.15                                   
        DCD     DT_QDU_IRQHandler           ; Dual Timer / Quadrature Decoder Unit unit0, unit1                          
        DCD     MFSI_RX0_IRQHandler         ; Reception Interrupt Request of MFSI0        
        DCD     MFSI_TX0_IRQHandler         ; Transmission Interrupt Request and Status Interrupt Request of MFSI0
        DCD     MFSI_RX1_IRQHandler         ; Reception Interrupt Request of of MFSI1        
        DCD     MFSI_TX1_IRQHandler         ; Transmission Interrupt Request and Status Interrupt Request of MFSI1
        DCD     MFSI_RX2_IRQHandler         ; Reception Interrupt Request of MFSI2        
        DCD     MFSI_TX2_IRQHandler         ; Transmission Interrupt Request and Status Interrupt Request of MFSI2
        DCD     MFSI_RX3_IRQHandler         ; Reception Interrupt Request of MFSI3        
        DCD     MFSI_TX3_IRQHandler         ; Transmission Interrupt Request and Status Interrupt Request of MFSI3
        DCD     MFSI_RX4_IRQHandler         ; Reception Interrupt Request of MFSI4        
        DCD     MFSI_TX4_IRQHandler         ; Transmission Interrupt Request and Status Interrupt Request of MFSI4
        DCD     MFSI_RX5_IRQHandler         ; Reception Interrupt Request of of MFSI5        
        DCD     MFSI_TX5_IRQHandler         ; Transmission Interrupt Request and Status Interrupt Request of MFSI5
        DCD     MFSI_RX6_IRQHandler         ; Reception Interrupt Request of MFSI6        
        DCD     MFSI_TX6_IRQHandler         ; Transmission Interrupt Request and Status Interrupt Request of MFSI6
        DCD     MFSI_RX7_IRQHandler         ; Reception Interrupt Request of MFSI7        
        DCD     MFSI_TX7_IRQHandler         ; Transmission Interrupt Request and Status Interrupt Request of MFSI7
        DCD     PPG_IRQHandler              ; PPG unit0, unit1                                                           
        DCD     CLK_IRQHandler              ; External Main OSC/External Sub OSC/Main PLL/PLL for USB/Watch Count
        DCD     ADC0_IRQHandler             ; ADC unit0                                                        
        DCD     ADC1_IRQHandler             ; ADC unit1                                                        
        DCD     ADC2_IRQHandler             ; ADC unit2                                                        
        DCD     FRTIM_IRQHandler            ; Free-run Timer unit0, unit1                                                
        DCD     CAP_IRQHandler              ; Input Capture unit0, unit1                                                 
        DCD     COM_IRQHandler              ; Output Compare unit0, unit1                                                
        DCD     BTIM_IRQHandler             ; Base Timer ch.0 to ch.7                                                    
        DCD     CAN0_IRQHandler             ; CAN ch.0                                                                   
        DCD     CAN1_IRQHandler             ; CAN ch.1                                                                   
        DCD     USB_1_IRQHandler            ; USB Function (DRQ of End Point 1 to 5)                                     
        DCD     USB_2_IRQHandler            ; USB Function (DRQI of End Point 0, DRQO and each status)/USB HOST
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     DMA_CH0_IRQHandler          ; DMA Controller (DMAC) ch.0 
        DCD     DMA_CH1_IRQHandler          ; DMA Controller (DMAC) ch.1 
        DCD     DMA_CH2_IRQHandler          ; DMA Controller (DMAC) ch.2 
        DCD     DMA_CH3_IRQHandler          ; DMA Controller (DMAC) ch.3 
        DCD     DMA_CH4_IRQHandler          ; DMA Controller (DMAC) ch.4 
        DCD     DMA_CH5_IRQHandler          ; DMA Controller (DMAC) ch.5 
        DCD     DMA_CH6_IRQHandler          ; DMA Controller (DMAC) ch.6 
        DCD     DMA_CH7_IRQHandler          ; DMA Controller (DMAC) ch.7 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;

      PUBWEAK NMI_Handler       
      PUBWEAK HardFault_Handler 
      PUBWEAK MemManage_Handler 
      PUBWEAK BusFault_Handler  
      PUBWEAK UsageFault_Handler
      PUBWEAK SVC_Handler       
      PUBWEAK DebugMon_Handler  
      PUBWEAK PendSV_Handler    
      PUBWEAK SysTick_Handler   
      PUBWEAK FCS_IRQHandler    
      PUBWEAK SWDT_IRQHandler   
      PUBWEAK LVD_IRQHandler   
      PUBWEAK WFG_IRQHandler   
      PUBWEAK EXTI0_7_IRQHandler 
      PUBWEAK EXTI8_15_IRQHandler
      PUBWEAK DT_QDU_IRQHandler  
      PUBWEAK MFSI_RX0_IRQHandler
      PUBWEAK MFSI_TX0_IRQHandler
      PUBWEAK MFSI_RX1_IRQHandler
      PUBWEAK MFSI_TX1_IRQHandler
      PUBWEAK MFSI_RX2_IRQHandler
      PUBWEAK MFSI_TX2_IRQHandler
      PUBWEAK MFSI_RX3_IRQHandler
      PUBWEAK MFSI_TX3_IRQHandler
      PUBWEAK MFSI_RX4_IRQHandler
      PUBWEAK MFSI_TX4_IRQHandler
      PUBWEAK MFSI_RX5_IRQHandler
      PUBWEAK MFSI_TX5_IRQHandler
      PUBWEAK MFSI_RX6_IRQHandler
      PUBWEAK MFSI_TX6_IRQHandler
      PUBWEAK MFSI_RX7_IRQHandler
      PUBWEAK MFSI_TX7_IRQHandler
      PUBWEAK PPG_IRQHandler    
      PUBWEAK CLK_IRQHandler    
      PUBWEAK ADC0_IRQHandler    
      PUBWEAK ADC1_IRQHandler  
      PUBWEAK ADC2_IRQHandler    
      PUBWEAK FRTIM_IRQHandler     
      PUBWEAK CAP_IRQHandler       
      PUBWEAK COM_IRQHandler    
      PUBWEAK BTIM_IRQHandler      
      PUBWEAK CAN0_IRQHandler  
      PUBWEAK CAN1_IRQHandler
      PUBWEAK USB_1_IRQHandler
      PUBWEAK USB_2_IRQHandler
      PUBWEAK DMA_CH0_IRQHandler
      PUBWEAK DMA_CH1_IRQHandler
      PUBWEAK DMA_CH2_IRQHandler
      PUBWEAK DMA_CH3_IRQHandler
      PUBWEAK DMA_CH4_IRQHandler
      PUBWEAK DMA_CH5_IRQHandler
      PUBWEAK DMA_CH6_IRQHandler
      PUBWEAK DMA_CH7_IRQHandler
      
      THUMB
      SECTION .text:CODE:REORDER:NOROOT(1)
        
NMI_Handler       
HardFault_Handler 
MemManage_Handler 
BusFault_Handler  
UsageFault_Handler
SVC_Handler       
DebugMon_Handler  
PendSV_Handler    
SysTick_Handler   
FCS_IRQHandler    
SWDT_IRQHandler   
LVD_IRQHandler   
WFG_IRQHandler   
EXTI0_7_IRQHandler   
EXTI8_15_IRQHandler  
DT_QDU_IRQHandler  
MFSI_RX0_IRQHandler  
MFSI_TX0_IRQHandler  
MFSI_RX1_IRQHandler   
MFSI_TX1_IRQHandler   
MFSI_RX2_IRQHandler   
MFSI_TX2_IRQHandler   
MFSI_RX3_IRQHandler    
MFSI_TX3_IRQHandler   
MFSI_RX4_IRQHandler   
MFSI_TX4_IRQHandler   
MFSI_RX5_IRQHandler    
MFSI_TX5_IRQHandler  
MFSI_RX6_IRQHandler  
MFSI_TX6_IRQHandler  
MFSI_RX7_IRQHandler  
MFSI_TX7_IRQHandler    
PPG_IRQHandler    
CLK_IRQHandler    
ADC0_IRQHandler    
ADC1_IRQHandler  
ADC2_IRQHandler    
FRTIM_IRQHandler         
CAP_IRQHandler              
COM_IRQHandler  
BTIM_IRQHandler               
CAN0_IRQHandler             
CAN1_IRQHandler
USB_1_IRQHandler
USB_2_IRQHandler
DMA_CH0_IRQHandler
DMA_CH1_IRQHandler
DMA_CH2_IRQHandler
DMA_CH3_IRQHandler
DMA_CH4_IRQHandler
DMA_CH5_IRQHandler
DMA_CH6_IRQHandler
DMA_CH7_IRQHandler
Default_Handler          
        B Default_Handler 
        END
