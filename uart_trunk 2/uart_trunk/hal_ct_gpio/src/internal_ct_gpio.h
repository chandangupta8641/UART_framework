/*******************************************************************************
Copyright (c) 2021 - Cientra All Rights Reserved.
This software is proprietary & confidential to Cientra
and its licensor.
********************************************************************************
* file name   : internal_ct_gpio.h
* description : Contains gpio driver related internal functions  
* version     : 1.0
* date        : 31-May-2021
* author      : Jaijith
*******************************************************************************/
#include "../../common/src/hal_ct_porting.h"

#ifndef INC_INTERNAL_CT_GPIO_H_
#define INC_INTERNAL_CT_GPIO_H_

/*Includes -------------------------------------------------------------------------*/
/*****************Bit definition for MODE********************/
#define GPIO_CTRL_MODE_SHIFT							(0U)
#define GPIO_CTRL_MODE_BITS								(4U)
#define GPIO_CTRL_MODE_MASK								(((1U << GPIO_CTRL_MODE_BITS)-1U) << GPIO_CTRL_MODE_SHIFT)
#define GPIO_CTRL_MODE_OUT_0							((((1U << GPIO_CTRL_MODE_BITS)-1U) & 0x00) << GPIO_CTRL_MODE_SHIFT)
#define GPIO_CTRL_MODE_OUT_1							((((1U << GPIO_CTRL_MODE_BITS)-1U) & 0x01) << GPIO_CTRL_MODE_SHIFT)
#define GPIO_CTRL_MODE_IN_REG							((((1U << GPIO_CTRL_MODE_BITS)-1U) & 0x02) << GPIO_CTRL_MODE_SHIFT)
#define GPIO_CTRL_MODE_IN_REG_BYPASS                    ((((1U << GPIO_CTRL_MODE_BITS)-1U) & 0x03) << GPIO_CTRL_MODE_SHIFT)
#define GPIO_CTRL_MODE_OUT_CORE							((((1U << GPIO_CTRL_MODE_BITS)-1U) & 0x04) << GPIO_CTRL_MODE_SHIFT)
#define GPIO_CTRL_MODE_OUT_CORE_OE						((((1U << GPIO_CTRL_MODE_BITS)-1U) & 0x05) << GPIO_CTRL_MODE_SHIFT)
#define GPIO_CTRL_MODE_IN_DEMUX_CORE					((((1U << GPIO_CTRL_MODE_BITS)-1U) & 0x06) << GPIO_CTRL_MODE_SHIFT)
#define GPIO_CTRL_MODE_CORE_IO							((((1U << GPIO_CTRL_MODE_BITS)-1U) & 0x08) << GPIO_CTRL_MODE_SHIFT)
#define GPIO_CTRL_MODE_BUF_IFF_0						((((1U << GPIO_CTRL_MODE_BITS)-1U) & 0x09) << GPIO_CTRL_MODE_SHIFT)
#define GPIO_CTRL_MODE_BUF_IFF_1						((((1U << GPIO_CTRL_MODE_BITS)-1U) & 0x0A) << GPIO_CTRL_MODE_SHIFT)





/***********************************bit definition for mux pin**************************************/
#define GPIO_CTRL_MUX_SHIFT                     	  (4U)//
#define GPIO_CTRL_MUX_BITS							  (4U)//how many bits sleceted for mux
#define GPIO_CTRL_MUX_MASK			                  (((1U << GPIO_CTRL_MUX_BITS)-1U) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_UART_TX          			      ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x0) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_UART_RX          			      ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x2) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_SPIM_MISO          			  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0xA) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_SPIM_MOSI         			  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x4) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_SPIM_SS         			      ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x6) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_SPIM_SCLK          			  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x5) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_SPIS_MISO         			  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x7) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_SPIS_MOSI         			  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x9) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_SPIS_SS         			 	  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x7) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_SPIS_SCLK          			  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x8) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_I2SM_WS          			      ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0xA) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_I2SM_SCLK          			  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x9) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_I2SM_SOUT          			  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x8) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_I2SM_SIN          			  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x6) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_I2SS_WS          			      ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x3) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_I2SS_SCLK          			  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x5) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_I2SS_SOUT          			  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0xB) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_I2SS_SIN          			  ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x4) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_PWM_OUT         			      ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0xC) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_EXT_STIMER_TRIG       	      ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x2) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_EXT_STIMER_EN           	      ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x1) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_EXT_WDT_HOLD          	      ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0x0) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_STS_WDT_BIT           	      ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0xE) << GPIO_CTRL_MUX_SHIFT)
//#define GPIO_CTRL_MUX_STS_WDT_BARK          	      ((((1U << GPIO_CTRL_MUX_BITS)-1U) & 0xD) << GPIO_CTRL_MUX_SHIFT)


void gpio_ip_config(uint32_t *REG_ADDR, uint32_t config_data); /*Writes the gpio configuration to a particular register.*/
uint32_t get_gpio_reg_addr(uint32_t base_address, uint8_t reg_index, uint8_t multiplication_factor); /*To get the gpio register address of a particular gpio instance.*/
uint32_t ct_gpio_get_device_index(HAL_CT_HANDLE devHandle,HAL_CT_DEVICE_INFO *device,uint32_t no_of_devices);
bool ct_gpio_handle_valid(HAL_CT_HANDLE ,HAL_CT_DEVICE_INFO *,uint32_t);        /* To check the device valid or not */
void ct_gpio_init_with_default(HAL_CT_HANDLE f_index,HAL_CT_DEVICE_INFO *device);  /* To set the RESET values */
#endif /* INC_INTERNAL_CT_GPIO_H_ */
