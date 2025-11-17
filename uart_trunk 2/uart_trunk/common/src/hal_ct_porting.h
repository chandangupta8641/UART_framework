/*******************************************************************************
Copyright (c) 2021 - Cientra All Rights Reserved.
This software is proprietary & confidential to Cientra
and its licensor.
********************************************************************************
* file name   : hal_ct_porting.h
* description : Contains data required for the user reference
* version     : 1.0
* date        : 31-May-2021
* author      : Jaijith
*******************************************************************************/
#ifndef HAL_CT_PORTING_H_
#define HAL_CT_PORTING_H_

#include <stdbool.h>

/* Board_Processor_OS */
#define EDGE_ZYNQ_BAREMETAL
//#define ZED_MICROBLAZE_BAREMETAL
//#define ZED_ZYNQ_LINUX
//#define SIM_MICROBLAZE_BAREMETAL


#ifdef EDGE_ZYNQ_BAREMETAL
    #define BOARD_EDGE
    #define PROCESSOR_ZYNQ
    #define OS_BAREMETAL
    #define HAL_CT_RCC
    #define HAL_CT_GPIO
    #define HAL_CT_UART
	#define HAL_CT_TIMER
    #define HAL_CT_I2CM
#endif

#ifdef ZED_MICROBLAZE_BAREMETAL
    #define BOARD_ZED
    #define PROCESSOR_MICROBLAZE
    #define OS_BAREMETAL
    #define HAL_CT_RCC
    #define HAL_CT_GPIO
   // #define HAL_CT_AXIINTC
    #define HAL_CT_UART
#endif

#ifdef ZED_ZYNQ_LINUX
    #define BOARD_ZED
    #define PROCESSOR_ZYNQ
    #define OS_LINUX
    #define HAL_CT_RCC                'A'  
    #define HAL_CT_GPIO               'B'
    #define HAL_CT_UART               'C'
    #define HAL_CT_SPIM				  'D'
    #define HAL_CT_SPIS				  'E'
    #define HAL_CT_I3CM               'F'
    #define HAL_CT_I3CS               'G'
   // #define HAL_CT_I2CM             'H'
    //#define HAL_CT_I2CS             'I'
    #define HAL_CT_GEMAC			  'J'
    
#endif

#ifdef SIM_MICROBLAZE_BAREMETAL
#define BOARD_SIM
#define PROCESSOR_MICROBLAZE
#define OS_BAREMETAL
#define HAL_CT_RCC
#define HAL_CT_GPIO
#define HAL_CT_AXIINTC
#define HAL_CT_UART
#endif

#if defined (BOARD_EDGE) && defined (OS_BAREMETAL)
	#include <xil_io.h>
	extern void enableInterrupts();   /* TO enable the interrupts*/
#endif

#if defined (BOARD_ZED) && defined (OS_BAREMETAL)
	#include <xil_io.h>
	extern void enableInterrupts();   /* TO enable the microblaze interrupts*/
#endif

#if defined (BOARD_SIM) && defined (OS_BAREMETAL)
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <stddef.h>
    #define FALSE false
    #define TRUE true
    typedef unsigned int uint32_t;
    typedef  int int32_t;
    extern void enableInterrupts();   /* TO enable the microblaze interrupts*/
#endif

#ifdef OS_LINUX
	#define FALSE false
    #define TRUE true
    #define NULL 0
	typedef int int32_t;
    typedef unsigned int uint32_t;
#endif

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

typedef uint32_t HAL_CT_HANDLE;

typedef struct
{
    uint32_t baseaddress;
    bool int_enabled;
    uint8_t reserved[3];
} HAL_CT_DEVICE_INFO;

#ifdef HAL_CT_TIMER
    typedef struct
    {
        uint32_t baseaddress;
        uint32_t ST_TIMER;
        uint32_t WDT_TIMER;
	    uint32_t PWM_TIMER;
    } HAL_CT_TIMER_INFO;
#endif

#ifdef HAL_CT_AXIINTC
    typedef struct
    {
        uint32_t baseaddress;
        void (*vector_table[32])(uint32_t);
    } HAL_CT_AXIINTC_INFO;
#endif




#ifdef EDGE_ZYNQ_BAREMETAL
#ifdef HAL_CT_RCC
    #define NO_OF_RCC_DEVICES                        1
    #define RCC0_BASE_ADDRESS						 (0x43C00000)
	#define MAX_NUMBER_OF_CLKS_PER_TYPE				 12
    extern uint32_t g_rcc_baseaddress[NO_OF_RCC_DEVICES];
    extern HAL_CT_DEVICE_INFO g_rcc_device[NO_OF_RCC_DEVICES];

#endif

#ifdef HAL_CT_GPIO
    #define NO_OF_GPIO_DEVICES                       1
    #define GPIO0_BASE_ADDRESS                       (0x43C01000)
    extern uint32_t g_gpio_baseaddress[NO_OF_GPIO_DEVICES];
    extern HAL_CT_DEVICE_INFO g_gpio_device[NO_OF_GPIO_DEVICES];
#endif

#ifdef HAL_CT_AXIINTC
    #define NO_OF_AXI_INTC_DEVICES					 1
    #define AXIINTC_BASE_ADDRESS					 (0x41200000)
    extern uint32_t g_axi_intc_baseaddress[NO_OF_AXI_INTC_DEVICES];
    extern HAL_CT_AXIINTC_INFO g_axi_intc_device[NO_OF_AXI_INTC_DEVICES];
#endif

#ifdef HAL_CT_UART
    #define NO_OF_UART_DEVICES                       1
    #define UART0_BASE_ADDRESS						 (0x43C02000)
    extern uint32_t g_uart_baseaddress[NO_OF_UART_DEVICES];
    extern HAL_CT_DEVICE_INFO g_uart_device[NO_OF_UART_DEVICES];
#endif


#ifdef HAL_CT_I2CM
    #define NO_OF_I2CM_DEVICES                       1
    #define I2CM0_BASE_ADDRESS						 (0x43C03000)
    extern uint32_t g_i2cm_baseaddress[NO_OF_I2CM_DEVICES];
    extern HAL_CT_DEVICE_INFO g_i2cm_device[NO_OF_I2CM_DEVICES];
#endif

#ifdef HAL_CT_GEMAC
    #define NO_OF_GEMAC_DEVICES                       1 
    #define GEMAC0_BASE_ADDRESS                       (0x44A06008)
    extern uint32_t g_gemac_baseaddress[NO_OF_GEMAC_DEVICES];
    extern HAL_CT_DEVICE_INFO g_gemac_device[NO_OF_GEMAC_DEVICES];
#endif

#ifdef  HAL_CT_TIMER
	#define TIMER0_BASE_ADDRESS						  (0x43c07000)
	#define NO_OF_TIMER_DEVICES				          1
	#define MAX_NUMBER_OF_ST_TIMERS                   4
	#define MAX_NUMBER_OF_WDT_TIMERS	   			  2
	#define MAX_NUMBER_OF_PWM_TIMERS         	      2
	#define SYSCLK					     			  0X4099800  //0X00546000						//0X4099800 					// 67.7376MHz SYSTEM CLOCK FREQUENCY
	#define APBCLK							 		  0X05F5E100 					//100MHz SYSTEM CLOCK FREQUENCY
	#define MAX_COUNT                     			  0XFFFFFFF
	#define TIME_PERIOD                               (1/SYSCLK)           //100MHZ TIME PERIOD
	#define  HAL_CT_TIMER_INT_ID     				  XPS_FPGA8_INT_ID
	extern HAL_CT_HANDLE g_timer_baseaddress[NO_OF_TIMER_DEVICES];
	extern HAL_CT_DEVICE_INFO g_timer_device[NO_OF_TIMER_DEVICES];
#endif

#endif


//#endif

#define DISABLE_ALL_INTR							  (0xffffffff)

#define DELAY_TWO_SEC								  (0x200)

typedef enum
{
  HAL_CT_SUCCESS = 0x0,
  HAL_CT_ERROR,
  HAL_CT_BUSY,
  HAL_OK,
  HAL_CT_DRIVER_NOT_INITIALIZED,
  HAL_CT_INVALID_HANDLE,
  HAL_CT_INVALID_GPIO_INDEX,
  HAL_CT_INVALID_DT_INSTANCE,    
  HAL_CT_INVALID_INIT_DEFAULT,
  HAL_CT_TIMEOUT,
  HAL_CT_INVALID_CLK_INDEX,
  HAL_CT_INVALID_DEVICE,
  HAL_CT_INVALID_IRQ,
  HAL_CT_NACK_RECEIVED
} HAL_CT_STATUS;

typedef enum
{
#ifdef HAL_CT_RCC
  HAL_CT_RCC_CONFIG  = 0x0000,
  HAL_CT_RCC_CLK_CONFIG = 0x0001,
#endif

#ifdef HAL_CT_GPIO
  HAL_CT_GPIO_CONFIG = 0x0100,
  HAL_CT_GPIO_ENABLE= 0X0200,
#endif

  HAL_CT_UART_CONFIG = 0x0200,
  HAL_CT_UART_CB,
  HAL_CT_UART_READ,
  HAL_CT_UART_SEND,
  HAL_CT_UART_EXTERNAL_LOOPBACK,
//  HAL_CT_AXIINTC_INTENABLE = 0x0300,
//  HAL_CT_AXIINTC_INTDISABLE,

#ifdef HAL_CT_TIMER
  HAL_CT_TIMER_GET_CAPABILITIES=0x0300,
  HAL_CT_RCC_TCLK_CONFIG,
  HAL_CT_RCC_PCLK_CONFIG,
  HAL_CT_RCC_GET_TCLK_CONFIG,
  HAL_CT_RCC_GET_PCLK_CONFIG,

//	STIMER
  HAL_CT_TIMER_ST_CONFIG,
  HAL_CT_TIMER_ST_OPERATION,
  HAL_CT_ST_TIMER_STATUS_CHECK,
  HAL_CT_TIMER_ST_TIMER_DISABLE,
//	PWM
  HAL_CT_TIMER_PWM_CONFIG,
  HAL_CT_TIMER_PWM_CONFIG_1,
  HAL_CT_TIMER_PWM_OPERATION,
  HAL_CT_PWM_STATUS_CHECK,
  HAL_CT_TIMER_PWM_DISABLE,
//	WDT
  HAL_CT_TIMER_WDOG_CONFIG,
  HAL_CT_TIMER_WDOG_ENABLE,
  HAL_CT_BARK_STATUS_CHECK,
  HAL_CT_BITE_STATUS_CHECK,
  HAL_CT_TIMER_WDOG_DISABLE,
#endif
  
  HAL_CT_TIMER_PWM_CH_CONFIG=0x0008,
  HAL_CT_READ_ALL_DEFAULT,
  /*Interrupt mask*/
  HAL_CT_TIMER_ST_TIMER_MASK,
  HAL_CT_TIMER_PWM_MASK,
  HAL_CT_TIMER_WDT_BARK_INT_MASK,
  HAL_CT_TIMER_WDT_BITE_INT_MASK,
 

  HAL_CT_SPIM_CONFIG = 0x0400,
  HAL_CT_SPIM_READ,
  HAL_CT_SPIM_SEND,
  HAL_CT_SPIM_REG_DEF_VAL,
  HAL_CT_SPIM_READ_REG,

  HAL_CT_SPIS_CONFIG = 0x0500,
  HAL_CT_SPIS_READ,
  HAL_CT_SPIS_SEND,
  HAL_CT_SPIS_REG_DEF_VAL,
  HAL_CT_SPIS_READ_REG,
  
  HAL_CT_GEMAC_CONFIG = 0x0600,
  HAL_CT_GEMAC_SEND,
  HAL_CT_GEMAC_READ,

#ifdef HAL_CT_I2CM
  HAL_CT_I2CM_CONFIG = 0x0700,
  HAL_CT_I2CM_READ,
  HAL_CT_I2CM_WRITE,
#endif

#ifdef HAL_CT_I2CS
  HAL_CT_I2CS_CONFIG = 0x0800,
  HAL_CT_I2CS_READ,
  HAL_CT_I2CS_SEND,
#endif

#ifdef HAL_CT_I3CM
  HAL_CT_I3CM_CONFIG = 0x0900,
  HAL_CT_I3CM_CCC,
  HAL_CT_I3CM_SLAVEADDR,
  HAL_CT_I3CM_INTR,
  HAL_CT_I3CM_SEND,
  HAL_CT_I3CM_READ,
#endif

#ifdef HAL_CT_I3CS
HAL_CT_I3CS_CONFIG = 0x0A00,
HAL_CT_I3CS_SEND,
HAL_CT_I3CS_READ
#endif
} HAL_CT_CMD;

typedef enum
{
	HAL_CT_UART_CLK = 0x2,
    HAL_CT_I2CM_CLK = 0x3,	
	HAL_CT_TIMER_CLK = 0x5
} HAL_CT_CLK_INDEX;

#endif /* INC_HAL_CT_PORTING_H_ */

