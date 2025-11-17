
/**
  ******************************************************************************
  * @file    hal_ct_rcc.c
  * @author  Jaijith
  * @brief   Contains rcc driver API's.
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

//#include <stdio.h>
//#include <stdlib.h>

//#include "xil_printf.h"
#include "../../common/src/hal_ct_porting.h"
#include "../../common/src/hal_ct_common.h"
#include "../../hal_ct_rcc/src/hal_ct_rcc.h"
#include "../../hal_ct_rcc/src/internal_ct_rcc.h"
//#include "../../hal_ct_uart/src/internal_ct_uart.h"

static bool g_rcc_driver_inited = false;

/**
  * @brief  HAL_CT_rcc_init,Initializes the base addresses of all the RCC devices. 
  * @param  num_of_devices  contain the count related to how many devices base address initialized.         
  * @retval HAL_CT_STATUS
  */

HAL_CT_STATUS HAL_CT_rcc_init(uint32_t *num_of_devices)
{
	uint32_t i = 0u;
	
	for (i=0u ; i<NO_OF_RCC_DEVICES ; i++)
	{
		g_rcc_device[i].baseaddress = g_rcc_baseaddress[i];
	}

    *num_of_devices = NO_OF_RCC_DEVICES;
    g_rcc_driver_inited = true;
    return HAL_CT_SUCCESS;
}
/**
  * @brief  HAL_CT_rcc_deinit,DeInitializes the base addresses of all the RCC devices.         
  * @retval HAL_CT_STATUS
  */

HAL_CT_STATUS HAL_CT_rcc_deinit(void)
{
    uint32_t i = 0u;

    // close all open devices
    for (i=0u ; i< NO_OF_RCC_DEVICES ; i++)
    {
    	g_rcc_device[i].baseaddress = NULL;
    }

    g_rcc_driver_inited = false;
    return HAL_CT_SUCCESS;
}
/**
  * @brief  HAL_CT_rcc_open,Returns the base address of a particular rcc instance.         
  * @retval HAL_CT_STATUS
  */
HAL_CT_STATUS HAL_CT_rcc_open (uint32_t device_number, HAL_CT_HANDLE *devHandle  )
{
	HAL_CT_STATUS l_retval = HAL_CT_ERROR;
    
	if (false == g_rcc_driver_inited)
	{
	    l_retval = 	HAL_CT_DRIVER_NOT_INITIALIZED;
	}
	else
	{
		// verify device number HAL_CT_INVALID_DEVICE
		//if((device_number >= 0) && (device_number <= NO_OF_RCC_DEVICES))
        if(device_number <= NO_OF_RCC_DEVICES)
		{
			*devHandle = (HAL_CT_HANDLE)g_rcc_device[device_number].baseaddress;
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
  * @brief  HAL_CT_rcc_close,Returns the status of particular rcc instance.        
  * @retval HAL_CT_STATUS
  */
HAL_CT_STATUS HAL_CT_rcc_close(HAL_CT_HANDLE devHandle)
{
    HAL_CT_STATUS l_retval = HAL_CT_ERROR;
    uint32_t l_device_index = 0u;
    
    // Check whether the device handle is valid
    if (false == ct_rcc_handle_valid(devHandle,g_rcc_device,NO_OF_RCC_DEVICES))
    {
    	l_retval = HAL_CT_INVALID_HANDLE;
	}
	else
	{
		// Configure the device with default values or reset the device
		
		l_device_index = ct_rcc_get_device_index(devHandle,g_rcc_device,NO_OF_RCC_DEVICES);
		ct_rcc_init_with_default(l_device_index,g_rcc_device);

		g_rcc_device[l_device_index].baseaddress = NULL;
		l_retval = HAL_CT_SUCCESS;
	}
    return l_retval;
}
/**
  * @brief  HAL_CT_rcc_ioctl,Performs the RCC IO control based on the commands issued by the user.
  * @param  devHandle  Pointer to a HAL_CT_HANDLE that contains
  *                the base address information for the specified Register.  
  * @param cmd  contain command information.   
  * @param rcc_config  variable of RCC_CONFIG_DETAILS structure that contain all rcc configration related member. 
  * @retval HAL_CT_STATUS
  */

HAL_CT_STATUS HAL_CT_rcc_ioctl (HAL_CT_HANDLE devHandle, uint16_t cmd, void* ptr)
{		
	HAL_CT_STATUS l_retval = HAL_CT_ERROR;
	uint32_t l_control_reg = 0;
    
	// Check whether the device handle is valid
    if (ct_rcc_handle_valid(devHandle,g_rcc_device,NO_OF_RCC_DEVICES)==FALSE)
    {
    	l_retval = HAL_CT_INVALID_HANDLE;
    }
    else
    {
        /*process commmand*/
        switch (cmd)
        {



        case HAL_CT_RCC_CONFIG:
        {
        	RCC_CONFIG_INFO *l_rcc_config = (RCC_CONFIG_INFO *) ptr;
            if (TRUE == l_rcc_config->tcxo_prescaler_enable)
			{
            	l_control_reg = ((l_control_reg) & ~(RCC_TCXO_PRESCALER_MASK)|RCC_TCXO_PRESCALER_ENABLE);
				l_control_reg = (l_control_reg & ~(RCC_TCXO_PRESCALER_DIVIDER_MASK)) | (l_rcc_config->tcxo_prescaler_divider << RCC_TCXO_PRESCALER_DIVIDER_SHIFT);
			}
            else
			{
			    l_control_reg = ((l_control_reg & ~RCC_TCXO_PRESCALER_MASK) | RCC_TCXO_PRESCALER_DISABLE);
            }
			
			if (TRUE == l_rcc_config->pll_prescaler_enable)
			{
			    l_control_reg = (l_control_reg & ~RCC_PLL_PRESCALER_MASK) | RCC_PLL_PRESCALER_ENABLE;
				l_control_reg = (l_control_reg & ~RCC_PLL_PRESCALER_DIVIDER_MASK) | (l_rcc_config->pll_prescaler_divider << RCC_PLL_PRESCALER_DIVIDER_SHIFT);
				l_control_reg = (l_control_reg & ~RCC_PLL_MULTIPLIER_MASK) | (l_rcc_config->pll_multiplier << RCC_PLL_MULTIPLIER_SHIFT);
            }
			else
			{
                l_control_reg = (l_control_reg & ~RCC_PLL_PRESCALER_MASK) | RCC_PLL_PRESCALER_DISABLE;
            }
					
			l_control_reg = (l_control_reg & ~RCC_CLK_CONTROL_GLOBAL_RESET_MASK) | RCC_CLK_CONTROL_GLOBAL_RESET_SET;
			
        	WriteRegister32(devHandle,l_control_reg);

        }
        	break;
        case HAL_CT_RCC_CLK_CONFIG:
        {
        	RCC_CLK_CONFIG_INFO *l_rcc_clk_config = (RCC_CLK_CONFIG_INFO *) ptr;
			if (l_rcc_clk_config->clk_index >= MAX_NUMBER_OF_CLKS_PER_TYPE)
			{
			    l_retval = HAL_CT_INVALID_CLK_INDEX;
			}
            else
			{	
            	l_control_reg = (l_control_reg & ~RCC_CLK_SOFTRESET_MASK) | RCC_CLK_SOFTRESET_SET;
            	l_control_reg = (l_control_reg & ~RCC_CLK_ENABLE_MASK) | RCC_CLK_ENABLE;

                if (TRUE == l_rcc_clk_config->prescaler_enable)
		    	{
			        l_control_reg = (l_control_reg & ~RCC_CLK_PRESCALER_MASK) | RCC_CLK_PRESCALER_ENABLE;
                }
		    	else
		    	{
                    l_control_reg = (l_control_reg & ~RCC_CLK_PRESCALER_MASK) | RCC_CLK_PRESCALER_DISABLE;
                }
				
                l_control_reg = (l_control_reg & ~RCC_CLK_PRESCALER_DIVIDER_MASK) | (l_rcc_clk_config->clk_div << RCC_CLK_PRESCALER_DIVIDER_SHIFT);
			
		    	if (CLK_TYPE_TCXO == l_rcc_clk_config->clk_type)
			    {
                    WriteRegister32(devHandle + RCC_TCXO_CONTROL_0 + MUL_FACTOR_ADDR * l_rcc_clk_config->clk_index, l_control_reg);
		    	}
		    	else
		    	{
                    WriteRegister32(devHandle + RCC_PLL_CONTROL_0 + MUL_FACTOR_ADDR * l_rcc_clk_config->clk_index, l_control_reg);
			    }
			}
        }
            break;
			
        //case HAL_CT_RCC_SOFT_RESET:
//        WriteRegister32(devHandle + TCXO_CLOCK_CONTROLL, RCC_CLK_CONTROL_GLOBAL_RESET_RESET | (rcc_config->clk_div)<<2); //CLock division for RCC
//        	WriteRegister32(devHandle + TCXO_CLOCK_CONTROLL,RCC_TCXO_ENABLE_MASK | (rcc_config->clk_div)<<2);  //Enabling RCC Clock
//        WriteRegister32(devHandle + TCXO_CLOCK_CONTROLL,RCC_TCXO_ENABLE |( rcc_config->clk_div)<<2);  // CLock Reset enabling
        //	break;


#if 0
        case HAL_CT_READ_ALL_REGISTERS:
		    
		    rcc_registers->offset = RCC_CONTROL_REG;
			rcc_registers->val = ReadRegister32 (devHandle + RCC_CONTROL_REG);
		    break;
			
		case HAL_CT_WRITE_ALL_REGISTERS:
		    break;
		
        case HAL_CT_READ_ALL_DEFAULT:
        {
            uint32_t* readALL[8];
            readALL[0] = (uint32_t*)RCC_CONTROL_PLL_REG;
            readALL[1] = (uint32_t*)RCC_CONTROL_INTR_EN_REG0;
            readALL[2] = (uint32_t*)RCC_CONTROL_INTR_EN_REG1;
            readALL[3] = (uint32_t*)RCC_CONTROL_STS_CLR_REG0;
            readALL[4] = (uint32_t*)RCC_CONTROL_STS_CLR_REG1;
            readALL[5] = (uint32_t*)RCC_CONTROL_APB_STS_REG;
            readALL[6] = (uint32_t*)RCC_CONTROL_LINE_STS_REG;
            readALL[7] = (uint32_t*)RCC_CONTROL_RCC_CONTROL_REG;
            for(int i=0; i<8; i++)
            {
                printf("%x\n",*readALL[i]);
            }
        }
        break;
#endif 
        
        default :
           break;
        }
        l_retval = HAL_CT_SUCCESS;
    }
return l_retval;

}


