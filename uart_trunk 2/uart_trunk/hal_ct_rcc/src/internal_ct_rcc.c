
/**
  ******************************************************************************
  * @file    internal_ct_rcc.c
  * @author  Jaijith
  * @brief   Contains rcc driver related internal functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 Cientra.
  * All rights reserved.</center></h2>
  *
  *This software is proprietary & confidential to Cientra
  *and its licensor.
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "../../common/src/hal_ct_porting.h"
#include "../../common/src/hal_ct_common.h"
#include "../../hal_ct_rcc/src/internal_ct_rcc.h"

bool ct_rcc_handle_valid(HAL_CT_HANDLE devHandle,HAL_CT_DEVICE_INFO *device,uint32_t no_of_devices)
{
	uint8_t l_device_num = 0;
	bool l_retval = false;
    for(l_device_num=0; l_device_num < no_of_devices; l_device_num++)
    {
        if((uint32_t)devHandle == device[l_device_num].baseaddress)
        {
        	l_retval = true;
        }
        else
        {
        	l_retval = false;
        }
    }
    return l_retval;

}

uint32_t ct_rcc_get_device_index(HAL_CT_HANDLE devHandle,HAL_CT_DEVICE_INFO *device,uint32_t no_of_devices)
{
	uint32_t l_device_num = 0;
	uint32_t l_retval = 0;
    for(l_device_num=0; l_device_num < no_of_devices; l_device_num++)
    {
        if((uint32_t)devHandle == device[l_device_num].baseaddress)
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


void ct_rcc_init_with_default(HAL_CT_HANDLE f_index,HAL_CT_DEVICE_INFO *device)
{
#if 0
	WriteRegister32(device[f_index].baseaddress + UART_CONTROL,0x00000000);
	WriteRegister32(device[f_index].baseaddress + UART_INT_MASK,0x00000000);
	WriteRegister32(device[f_index].baseaddress + UART_INT_CLR,0x00000000);
	WriteRegister32(device[f_index].baseaddress + UART_APB_STATUS,0x00000000);
	WriteRegister32(device[f_index].baseaddress + UART_LINE_STATUS,0x00000001);
#endif
}



