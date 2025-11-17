/**
  ******************************************************************************
  * @file    internal_ct_uart.c
  * @author  Sunil
  * @brief   CT HAL UART INTERNAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (UART).
  *           
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
  */

/*******************************************************************************
Copyright (c) 2021 - Cientra All Rights Reserved.
This software is proprietary & confidential to Cientra
and its licensor.

*/

#include "../../common/src/hal_ct_porting.h"
#include "../../common/src/hal_ct_common.h"
#include "../../hal_ct_uart/src/internal_ct_uart.h"


#define FIFOSIZE	128
static uint8_t uartRxFifo [FIFOSIZE];
static int32_t uartRxFifoRdIndex = 0;
static int32_t uartRxFifoWrIndex = 0;
/**
  * @brief  ct_uart_tx_full To check whether tx fifo full or not.
  * @param  devHandle  the base address for the specified UART module.              
  * @retval uint8_t
  */

bool ct_uart_tx_full(HAL_CT_HANDLE devHandle)
{
    uint32_t reg_value = ReadRegister32(devHandle + UART_APB_STATUS);
	
    if(reg_value & UART_APB_STATUS_TXFIFO_FULL)
    	return true;
    else
    	return false;
}
#if 0
bool ct_uart_tx_overrun(HAL_CT_HANDLE devHandle)
{
	uint32_t reg_value = ReadRegister32(devHandle + UART_APB_STATUS);

	if(reg_value & UART_APB_STATUS_TXFIFO_OVERRUN)
		return true;
	else
		return false;
}

bool ct_uart_rx_underrun(HAL_CT_HANDLE devHandle)
{
	uint32_t reg_value = ReadRegister32(devHandle + UART_APB_STATUS);

	if(reg_value & UART_APB_STATUS_RXFIFO_UNDERRUN)
		return true;
	else
		return false;
}

bool ct_uart_rx_fifo_writeAccess(HAL_CT_HANDLE devHandle)
{
	uint32_t reg_value = ReadRegister32(devHandle + UART_APB_STATUS);

		if(reg_value & UART_APB_STATUS_RXFIFO_WRITEACCESS)
			return true;
		else
			return false;
}
#endif

/**
  * @brief  ct_read_reg_status,To check status of registers.
  * @retval None
  */
//void ct_read_reg_status(uint32_t devHandle)
//{
//
//	uint32_t apb_status_register = ReadRegister32(devHandle + UART_APB_STATUS);
//	uint32_t line_status_register = ReadRegister32(devHandle + UART_LINE_STATUS);
//	uint32_t uart_control_status_register = ReadRegister32(devHandle + UART_CONTROL);
//
//}

/**
  * @brief  ct_uart_rx_available,To check whether data is available on rx line.
  * @param  data  contain data which we want to write into the particular address of register.
  *@param   addr  contain the address of specified register.           
  * @retval None
  */
bool ct_uart_rx_available(uint32_t devHandle)
{
	bool l_retval = FALSE;

    uint32_t l_device_index = ct_uart_get_device_index(devHandle,g_uart_device,NO_OF_UART_DEVICES);
    uint32_t l_reg_value = ReadRegister32(devHandle + UART_APB_STATUS);
    if(g_uart_device[l_device_index].int_enabled == FALSE)
    {
    	if (uartRxFifoRdIndex == uartRxFifoWrIndex)
    	{
    	// Error no data
    		l_retval=FALSE;
    	}
    	else
    	{
    		l_retval=TRUE;
    	}
    }
    else
    {
        if(l_reg_value & UART_APB_STATUS_RXFIFO_EMPTY)    /* In APB checking 1 bit, RX FIFO empty or not */
        {
             	l_retval = FALSE;
        }
        else
        {
        	uint32_t l_reg_value1 = ReadRegister32(devHandle + UART_INT_CLR);  /*Read whole IRQ_CLEAR 32 Registers*/
        	WriteRegister32(devHandle + UART_INT_CLR,l_reg_value1 | UART_INTCLR_RXFIFO_NOTEMPTY_SET);
        	WriteRegister32(devHandle + UART_INT_CLR,l_reg_value1 & UART_INTCLR_RXFIFO_NOTEMPTY_RESET);  /*RXFIFO-EMPTY*/

        	l_retval = TRUE;

        }
    }

    return l_retval;
}


void ct_uart_read_rx_fifo(HAL_CT_HANDLE devHandle,uint8_t *byte)
{
	uint32_t l_device_index = ct_uart_get_device_index(devHandle,g_uart_device,NO_OF_UART_DEVICES);
	if(g_uart_device[l_device_index].int_enabled == FALSE)
	{
		*byte = uartRxFifo [uartRxFifoRdIndex];
		ct_fifo_increment_ind (&uartRxFifoRdIndex, FIFOSIZE);
	}
	else
	{
		*(byte) = ReadRegister8(devHandle + UART_RX_FIFO_1B);

	}
}

bool ct_uart_handle_valid(HAL_CT_HANDLE devHandle,HAL_CT_DEVICE_INFO *device,uint32_t no_of_devices)
{
	uint8_t l_device_num = 0;
	bool l_retval = FALSE;
    for(l_device_num=0; l_device_num < no_of_devices; l_device_num++)
    {
        if(devHandle == device[l_device_num].baseaddress)
        {
        	l_retval = TRUE;
        }
        else
        {
        	l_retval = FALSE;
        }
    }
    return l_retval;

}

uint32_t ct_uart_get_device_index(HAL_CT_HANDLE devHandle,HAL_CT_DEVICE_INFO *device,uint32_t no_of_devices)
{
	uint32_t l_device_num = 0;
	uint32_t l_retval = 0;
    for(l_device_num=0; l_device_num < no_of_devices; l_device_num++)
    {
        if(devHandle == device[l_device_num].baseaddress)
        {
        	l_retval = l_device_num;
        }
        else
        {
        	l_retval = 0;
        }
    }
    return l_retval;

}

void ct_uart_init_with_default(HAL_CT_HANDLE f_index,HAL_CT_DEVICE_INFO *device)
{

	WriteRegister32(device[f_index].baseaddress + UART_CONTROL,0x00000000);
	WriteRegister32(device[f_index].baseaddress + UART_INT_MASK,0x00000000);
	WriteRegister32(device[f_index].baseaddress + UART_INT_CLR,0x00000000);
	WriteRegister32(device[f_index].baseaddress + UART_APB_STATUS,0x00000000);
	WriteRegister32(device[f_index].baseaddress + UART_LINE_STATUS,0x00000001);

}


int32_t ct_fifo_freesize (int32_t rdInd, int32_t wrInd, int32_t fifosize)
{
	int32_t l_freesize;
	l_freesize = rdInd - wrInd + fifosize - 1;
	if (l_freesize >= fifosize)
	{
		l_freesize = l_freesize - fifosize;
	}
	else
	{
		/* Do nothing */
	}
	return l_freesize;
}

void ct_fifo_increment_ind (int32_t *index, int32_t fifosize)
{
	*index = *index + 1;

	if (*index == fifosize)
	{
		*index = 0;
	}
	else
	{
		/* Do nothing */
	}
}

void ct_uart_write_rx_fifo(uint32_t deviceNumber,uint8_t byte)
{

	int32_t l_freesize = ct_fifo_freesize (uartRxFifoRdIndex, uartRxFifoWrIndex, FIFOSIZE);

	if (l_freesize)
	{
		uartRxFifo [uartRxFifoWrIndex] = byte;
		ct_fifo_increment_ind (&uartRxFifoWrIndex, FIFOSIZE);
	}
	else
	{
	// Error Fifo Full
	}
}

void ct_uart_reset_rx_fifo (uint32_t deviceNumber)
{
	uartRxFifoWrIndex = 0;
	uartRxFifoRdIndex = 0;
}

