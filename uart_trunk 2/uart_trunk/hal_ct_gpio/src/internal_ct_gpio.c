/*******************************************************************************
Copyright (c) 2021 - Cientra All Rights Reserved.
This software is proprietary & confidential to Cientra
and its licensor.
********************************************************************************
* file name   : internal_ct_gpio.c
* description : Contains gpio driver related internal functions   
* version     : 1.0
* date        : 31-May-2021
* author      : Jaijith
*******************************************************************************/


#include "../../hal_ct_gpio/src/internal_ct_gpio.h"
#include "../../common/src/hal_ct_common.h"


/*******************************************************************************
* function name        : gpio_ip_config
* function description : Writes the gpio configuration to a particular register.
*******************************************************************************/
void gpio_ip_config(uint32_t *REG_ADDR, uint32_t config_data)
{
    *REG_ADDR = config_data;
}

/*******************************************************************************
* function name        : get_gpio_reg_addr
* function description : To get the gpio register address of a particular gpio instance.
*******************************************************************************/
uint32_t get_gpio_reg_addr(uint32_t base_address, uint8_t reg_index, uint8_t multiplication_factor)
{
    uint32_t REG_ADDR;
    REG_ADDR = (base_address + (multiplication_factor * reg_index));
    return REG_ADDR;
}

/*******************************************************************************
* function name        : ct_gpio_handle_valid
* function description : To check whether gpio address is valid or not
*******************************************************************************/
bool ct_gpio_handle_valid(HAL_CT_HANDLE devHandle,HAL_CT_DEVICE_INFO *device,uint32_t no_of_devices)
{
    uint8_t l_device_num = 0;
    bool l_retval = FALSE;
    for(l_device_num=0; l_device_num < no_of_devices; l_device_num++)
    {
        if(devHandle == device[l_device_num].baseaddress)
        {
            l_retval = TRUE;
        }
    }
    return l_retval;
}

/*******************************************************************************
* function name        : ct_gpio_get_device_index
* function description : To check whether gpio address is valid or not
*******************************************************************************/
uint32_t ct_gpio_get_device_index(HAL_CT_HANDLE devHandle,HAL_CT_DEVICE_INFO *device,uint32_t no_of_devices)
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
/*******************************************************************************
* function name        :    ct_gpio_init_with_default
* function description : To Initialize GPIO control register with default values
*******************************************************************************/
void ct_gpio_init_with_default(HAL_CT_HANDLE f_index,HAL_CT_DEVICE_INFO *device)
{

//	WriteRegister32(device[f_index].baseaddress + GPIO_0_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_1_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_2_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_3_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_4_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_5_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_6_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_7_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_8_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_9_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_10_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_11_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_12_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_13_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_14_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_15_CTRL,0x00000000);
//	WriteRegister32(device[f_index].baseaddress + GPIO_IRQ_CTRL,0x00000000);

}
