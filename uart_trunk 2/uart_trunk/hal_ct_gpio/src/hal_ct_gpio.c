/**
  ******************************************************************************
  * @file    hal_ct_gpio.c
  * @author  Jaijith
  * @brief   Contains gpio driver API's.
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
#include "../../hal_ct_gpio/src/hal_ct_gpio.h"
#include "../../hal_ct_gpio/src/internal_ct_gpio.h"


static bool g_gpio_driver_inited = FALSE;

//typedef uint32_t HAL_CT_HANDLE;
//HAL_CT_DEVICE_INFO gpioDevices [NO_OF_GPIO_DEVICES];
/**
  * @brief  HAL_CT_gpio_init,Initializes the base addresses of all the GPIO devices. 
  * @param  num_of_devices  contain the count related to how many devices base address initialized.         
  * @retval HAL_CT_STATUS
  */
HAL_CT_STATUS HAL_CT_gpio_init(uint32_t *num_of_devices)
{
	uint32_t i = 0u;
	
	for (i=0u ; i<NO_OF_GPIO_DEVICES ; i++)
	{
		g_gpio_device[i].baseaddress = g_gpio_baseaddress[i];
		g_gpio_device[i].int_enabled = FALSE;
	}

	*num_of_devices = NO_OF_GPIO_DEVICES;
    g_gpio_driver_inited = TRUE;
    return HAL_CT_SUCCESS;
}
/**
  * @brief  HAL_CT_gpio_deinit,DeInitializes the base addresses of all the GPIO devices.         
  * @retval HAL_CT_STATUS
  */
HAL_CT_STATUS HAL_CT_gpio_deinit(void)
{
    uint32_t i=0u;

    // close all open devices
    for (i=0u ; i< NO_OF_GPIO_DEVICES ; i++)
    {
    	g_gpio_device[i].baseaddress = (uint32_t)NULL;
    }

	g_gpio_driver_inited = FALSE;

    return HAL_CT_SUCCESS;
}

/*******************************************************************************
* function name        : HAL_CT_gpio_open
* function description : Returns the base address of a particular gpio instance.
*******************************************************************************/
HAL_CT_STATUS HAL_CT_gpio_open(uint32_t device_number, HAL_CT_HANDLE *devHandle)
{
	HAL_CT_STATUS l_retval = HAL_CT_ERROR;
    
	if (FALSE == g_gpio_driver_inited)
	{
	    l_retval = 	HAL_CT_DRIVER_NOT_INITIALIZED;
	}
	else
	{
		// verify device number HAL_CT_INVALID_DEVICE
		//if((device_number >= 0) && (device_number <= NO_OF_UART_DEVICES))
        if(device_number <= NO_OF_GPIO_DEVICES)
		{
			*devHandle = (HAL_CT_HANDLE)g_gpio_device[device_number].baseaddress;
			l_retval = 	HAL_CT_SUCCESS;
		}
		else
		{
			l_retval = 	HAL_CT_INVALID_DEVICE;
		}
	}

    return l_retval;
}
/**
  * @brief  HAL_CT_gpio_close,Returns the status of particular gpio instance.      
  * @retval HAL_CT_STATUS
  */
HAL_CT_STATUS HAL_CT_gpio_close(HAL_CT_HANDLE devHandle)
{
		HAL_CT_STATUS l_retval = HAL_CT_ERROR;
	    uint32_t l_device_index = 0u;

	    // Check whether the device handle is valid
	    if (FALSE == ct_gpio_handle_valid(devHandle,g_gpio_device,NO_OF_GPIO_DEVICES))
	    {
	        l_retval = HAL_CT_INVALID_HANDLE;
	    }
	    else
	    {
	        // Configure the device with default values or reset the device
	        l_device_index = ct_gpio_get_device_index(devHandle,g_gpio_device,NO_OF_GPIO_DEVICES);

	        ct_gpio_init_with_default(l_device_index,g_gpio_device);

	        g_gpio_device[l_device_index].baseaddress = (uint32_t)NULL;

	        l_retval = HAL_CT_SUCCESS;
	    }
	    return l_retval;
}

/*******************************************************************************
* function name        : HAL_CT_gpio_ioctl
* function description : Performs the GPIO IO control based on the commands issued by the user.
*******************************************************************************/
HAL_CT_STATUS HAL_CT_gpio_ioctl(HAL_CT_HANDLE devHandle, uint16_t cmd, void *ptr )
{
	uint16_t l_reg_val = 0;
    HAL_CT_STATUS l_retval = HAL_CT_SUCCESS;

    GPIO_CONFIG_DETAILS *gpio_config = (GPIO_CONFIG_DETAILS *) ptr;

    /* Check whether the device handle is valid */
    if (ct_gpio_handle_valid(devHandle,g_gpio_device,NO_OF_GPIO_DEVICES)==FALSE)
    {
    	l_retval = HAL_CT_INVALID_HANDLE;
    }
    else
    {
        /*process commmand*/
        switch (cmd)
		{
        case HAL_CT_GPIO_CONFIG:
		    {
		    	uint32_t l_gpio_sel_ip_reg = 0;
			
                if (gpio_config->gpio_index >= 16)
		    	{
			        // error 
			    	l_retval = HAL_CT_INVALID_GPIO_INDEX;
		    	}
			    else
		    	{ 
			        switch (gpio_config->pin_type)
			    	{
			    	case GPIO_INPUT:
				        l_reg_val = (gpio_config->mux_demux_pin << GPIO_CTRL_MUX_SHIFT) | GPIO_CTRL_MODE_IN_DEMUX_CORE;
    		        	WriteRegister8(devHandle + MUL_FACTOR_ADDR * gpio_config->gpio_index, l_reg_val);
				        break;
			    	case GPIO_OUTPUT:
				    	l_reg_val = (gpio_config->mux_demux_pin << GPIO_CTRL_MUX_SHIFT ) | GPIO_CTRL_MODE_OUT_CORE_OE;
    		        	WriteRegister8(devHandle + MUL_FACTOR_ADDR * gpio_config->gpio_index,l_reg_val);
				        break;
			    	case GPIO_BIDIRECTIONAL:
			    		l_reg_val = (gpio_config->mux_demux_pin << GPIO_CTRL_MUX_SHIFT ) | GPIO_CTRL_MODE_CORE_IO;
			    	    WriteRegister8(devHandle + MUL_FACTOR_ADDR * gpio_config->gpio_index,l_reg_val);

				        break;
			    	default:
				        break;
				    }
		    	}
		    }
			break;
		default:
		    break;
		}
	}
	return l_retval;
}
