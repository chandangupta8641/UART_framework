/*******************************************************************************
Copyright (c) 2021 - Cientra All Rights Reserved.
This software is proprietary & confidential to Cientra
and its licensor.
********************************************************************************
* file name   : hal_ct_porting.c
* description : Contains data required for the user reference
* version     : 1.0
* date        : 31-May-2021
* author      : Jaijith
*******************************************************************************/

#include "../../common/src/hal_ct_porting.h"




#ifdef EDGE_ZYNQ_BAREMETAL
#ifdef HAL_CT_RCC
    uint32_t g_rcc_baseaddress[NO_OF_RCC_DEVICES]={RCC0_BASE_ADDRESS};
    HAL_CT_DEVICE_INFO g_rcc_device[NO_OF_RCC_DEVICES];
#endif

#ifdef HAL_CT_GPIO
    uint32_t g_gpio_baseaddress[NO_OF_GPIO_DEVICES]={GPIO0_BASE_ADDRESS};
    HAL_CT_DEVICE_INFO g_gpio_device[NO_OF_GPIO_DEVICES];
#endif

#ifdef HAL_CT_UART
    uint32_t g_uart_baseaddress[NO_OF_UART_DEVICES]={UART0_BASE_ADDRESS};
    HAL_CT_DEVICE_INFO g_uart_device[NO_OF_UART_DEVICES];
#endif

#ifdef HAL_CT_AXIINTC
    uint32_t g_axi_intc_baseaddress[NO_OF_AXI_INTC_DEVICES]={AXIINTC_BASE_ADDRESS};
    HAL_CT_AXIINTC_INFO g_axi_intc_device[NO_OF_AXI_INTC_DEVICES];
#endif

#ifdef HAL_CT_SPIM
    uint32_t g_spim_baseaddress[NO_OF_SPIM_DEVICES]={SPIM0_BASE_ADDRESS};
    HAL_CT_DEVICE_INFO g_spim_device[NO_OF_SPIM_DEVICES];
#endif

#ifdef HAL_CT_SPIS
    uint32_t g_spis_baseaddress[NO_OF_SPIS_DEVICES]={SPIS0_BASE_ADDRESS};
    HAL_CT_DEVICE_INFO g_spis_device[NO_OF_SPIS_DEVICES];
#endif

#ifdef HAL_CT_TIMER
    HAL_CT_HANDLE g_timer_baseaddress[NO_OF_TIMER_DEVICES]={TIMER0_BASE_ADDRESS};
    HAL_CT_DEVICE_INFO g_timer_device[NO_OF_TIMER_DEVICES];
#endif 

#ifdef HAL_CT_GEMAC
    uint32_t g_gemac_baseaddress[NO_OF_GEMAC_DEVICES]={GEMAC0_BASE_ADDRESS};
    HAL_CT_DEVICE_INFO g_gemac_device[NO_OF_GEMAC_DEVICES];
#endif

#ifdef HAL_CT_I2CM
    uint32_t g_i2cm_baseaddress[NO_OF_I2CM_DEVICES]={I2CM0_BASE_ADDRESS};
    HAL_CT_DEVICE_INFO g_i2cm_device[NO_OF_I2CM_DEVICES];
#endif

#ifdef HAL_CT_I2CS
    uint32_t g_i2cs_baseaddress[NO_OF_I2CS_DEVICES]={I2CS0_BASE_ADDRESS};
    HAL_CT_DEVICE_INFO g_i2cs_device[NO_OF_I2CS_DEVICES];
#endif

#ifdef HAL_CT_I3CM
    uint32_t g_i3cm_baseaddress[NO_OF_I3CM_DEVICES]={I3CM0_BASE_ADDRESS};
    HAL_CT_DEVICE_INFO g_i3cm_device[NO_OF_I3CM_DEVICES];
#endif

#ifdef HAL_CT_I3CS
    uint32_t g_i3cs_baseaddress[NO_OF_I3CS_DEVICES]={I3CS0_BASE_ADDRESS};
    HAL_CT_DEVICE_INFO g_i3cs_device[NO_OF_I3CS_DEVICES];
#endif

static g_InterruptSetupDone = FALSE;
static XScuGic g_IntcInstance;
 
int ScuGicInterruptSetup(XScuGic *IntcInstancePtr, u16 DeviceId)
{
	int Status;
	static XScuGic_Config *GicConfig;
	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	GicConfig = XScuGic_LookupConfig(DeviceId);
	if (NULL == GicConfig)
	{
		return XST_FAILURE;
	}
	Status = XScuGic_CfgInitialize(IntcInstancePtr, GicConfig,GicConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS)
	{
			return XST_FAILURE;
	}
	/*
	 * Initialize the exception table.
	 */
	Xil_ExceptionInit();
	/*
	 * Connect the interrupt controller interrupt handler to the hardware
	 * interrupt handling logic in the processor.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
				(Xil_ExceptionHandler)XScuGic_InterruptHandler,
				IntcInstancePtr);
	/*
	 * Enable exceptions.
	 */
	Xil_ExceptionEnable();
	return XST_SUCCESS;
}
 
HAL_CT_STATUS HAL_CT_InstallInterruptHandler (int interruptID, void (*interruptHandler)(void *), HAL_CT_HANDLE drvHandle)
{
	int              l_Status;
	HAL_CT_STATUS    l_reval = HAL_CT_SUCCESS;
    if (FALSE == g_InterruptSetupDone)
	{
	    l_Status=ScuGicInterruptSetup(&g_IntcInstance, INTC_DEVICE_ID);
        if (l_Status != XST_SUCCESS)
        {
            xil_printf("Interrupt controller setup failed\n");
			l_reval = HAL_CT_ERROR;
        }
		else
		{
		    g_InterruptSetupDone = TRUE;
		}
	}
	if (HAL_CT_SUCCESS == l_reval)
        {	
        l_Status = XScuGic_Connect(&g_IntcInstance, interruptID, (Xil_ExceptionHandler)interruptHandler, drvHandle);
        if (l_Status != XST_SUCCESS)
        {
            xil_printf("Failed to connect interrupt handler\n");
		    l_reval = HAL_CT_ERROR;
        }
		else
		{
            XScuGic_Enable(&g_IntcInstance, interruptID);
	    }
	return l_reval;
}

#endif //EDGE_ZYNQ_BAREMETAL



