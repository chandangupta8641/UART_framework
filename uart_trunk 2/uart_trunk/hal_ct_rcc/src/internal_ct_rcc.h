/**
  ******************************************************************************
  * @file    internal_ct_rcc.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INTERNAL_CT_RCC_H_
#define INTERNAL_CT_RCC_H_
/* Includes ------------------------------------------------------------------*/


/* RCC_REGISTER_MAP */

#define RCC_CONTROL  						0x000              /*offset address for Global RCC control */
#define RCC_INT_MASK						0x004			  /*offset address for RCC_INTR_MASK_REG*/
#define RCC_INT_CLR			    			0x008			  /*offset address for RCC_STS_CLEAR_REG*/
#define RCC_TCXO_CONTROL_0 					0x010 		      /*offset address for TCXO_CONTROL_REG_0 */
#define RCC_PLL_CONTROL_0 					0x040 		      /*offset address for PLL_CONTROL_REG_0 */
#define RCC_APB_STATUS						0xA00		      /*offset address for RCC_APB_STATUS */
#define RCC_LINE_STATUS			    		0x900			  /*offset address for RCC_LINE_STATUS */

/*======================== D E F I N E S =====================================*/

/*****************************************RCC_CONTROL_REGISTER******************************************/
#define RCC_CLK_CONTROL_GLOBAL_RESET_SHIFT  (0U)
#define RCC_CLK_CONTROL_GLOBAL_RESET_BITS   (1U)
#define RCC_CLK_CONTROL_GLOBAL_RESET_MASK   (((1U << RCC_CLK_CONTROL_GLOBAL_RESET_BITS)-1U) << RCC_CLK_CONTROL_GLOBAL_RESET_SHIFT)
#define RCC_CLK_CONTROL_GLOBAL_RESET_RESET  ((((1U << RCC_CLK_CONTROL_GLOBAL_RESET_BITS)-1U) & 0x00U) << RCC_CLK_CONTROL_GLOBAL_RESET_SHIFT)
#define RCC_CLK_CONTROL_GLOBAL_RESET_SET    ((((1U << RCC_CLK_CONTROL_GLOBAL_RESET_BITS)-1U) & 0x01U) << RCC_CLK_CONTROL_GLOBAL_RESET_SHIFT)

#define RCC_TCXO_PRESCALAR_SHIFT			(1U)
#define RCC_TCXO_PRESCALAR_BITS				(1U)
#define RCC_TCXO_PRESCALER_MASK				(((1U << RCC_TCXO_PRESCALAR_BITS)-1U) << RCC_TCXO_PRESCALAR_SHIFT)
#define RCC_TCXO_PRESCALER_ENABLE			((((1U << RCC_TCXO_PRESCALAR_BITS)-1U) & 0x01U) << RCC_TCXO_PRESCALAR_SHIFT)
#define RCC_TCXO_PRESCALER_DISABLE			((((1U << RCC_TCXO_PRESCALAR_BITS)-1U) & 0x00U) << RCC_TCXO_PRESCALAR_SHIFT)

#define RCC_PLL_PRESCALER_SHIFT				(2U)
#define RCC_PLL_PRESCALER_BITS				(1U)
#define RCC_PLL_PRESCALER_MASK				(((1U << RCC_PLL_PRESCALER_BITS)-1U) << RCC_PLL_PRESCALER_SHIFT)
#define RCC_PLL_PRESCALER_ENABLE			((((1U << RCC_PLL_PRESCALER_BITS)-1U) & 0x01U) << RCC_PLL_PRESCALER_SHIFT)
#define RCC_PLL_PRESCALER_DISABLE			((((1U << RCC_PLL_PRESCALER_BITS)-1U) & 0x00U) << RCC_PLL_PRESCALER_SHIFT)

#define RCC_TCXO_PRESCALER_DIVIDER_SHIFT	(4U)
#define RCC_TCXO_PRESCALER_DIVIDER_BITS		(4U)
#define RCC_TCXO_PRESCALER_DIVIDER_MASK		(((1U << RCC_TCXO_PRESCALER_DIVIDER_BITS)-1U) << RCC_TCXO_PRESCALER_DIVIDER_SHIFT)

#define RCC_PLL_PRESCALER_DIVIDER_SHIFT		(8U)
#define RCC_PLL_PRESCALER_DIVIDER_BITS		(4U)
#define RCC_PLL_PRESCALER_DIVIDER_MASK		(((1U << RCC_PLL_PRESCALER_DIVIDER_BITS)-1U) << RCC_PLL_PRESCALER_DIVIDER_SHIFT)


#define RCC_PLL_MULTIPLIER_SHIFT			(16U)
#define RCC_PLL_MULTIPLIER_BITS				(8U)
#define RCC_PLL_MULTIPLIER_MASK				(((1U << RCC_PLL_MULTIPLIER_BITS)-1U) << RCC_PLL_MULTIPLIER_SHIFT)

/*********************************RCC_CLOCK_CONFIG************************************/
#define RCC_CLK_SOFTRESET_SHIFT				(0U)
#define RCC_CLK_SOFTRESET_BITS				(1U)
#define RCC_CLK_SOFTRESET_MASK				(((1U << RCC_CLK_SOFTRESET_BITS)-1U) << RCC_CLK_SOFTRESET_SHIFT)
#define RCC_CLK_SOFTRESET_SET				((((1U << RCC_CLK_SOFTRESET_BITS)-1U) & 0x01U) << RCC_CLK_SOFTRESET_SHIFT)
#define RCC_CLK_SOFTRESET_RESET				((((1U << RCC_CLK_SOFTRESET_BITS)-1U) & 0x00U) << RCC_CLK_SOFTRESET_SHIFT)



#define RCC_CLK_ENABLE_SHIFT				(1U)
#define RCC_CLK_ENABLE_BITS					(1U)
#define RCC_CLK_ENABLE_MASK					(((1U << RCC_CLK_ENABLE_BITS)-1U) << RCC_CLK_ENABLE_SHIFT)
#define RCC_CLK_ENABLE						((((1U << RCC_CLK_ENABLE_BITS)-1U) & 0x01U) << RCC_CLK_ENABLE_SHIFT)
#define RCC_CLK_DISABLE						((((1U << RCC_CLK_ENABLE_BITS)-1U) & 0x00U) << RCC_CLK_ENABLE_SHIFT)



#define RCC_CLK_PRESCALER_DIVIDER_SHIFT		(2U)
#define RCC_CLK_PRESCALER_DIVIDER_BITS		(8U)
#define RCC_CLK_PRESCALER_DIVIDER_MASK		(((1U << RCC_CLK_PRESCALER_DIVIDER_BITS)-1U) << RCC_CLK_PRESCALER_DIVIDER_SHIFT)

#define RCC_CLK_PRESCALER_SHIFT				(10U)
#define RCC_CLK_PRESCALER_BITS				(1U)
#define RCC_CLK_PRESCALER_MASK				(((1U << RCC_CLK_PRESCALER_BITS)-1U) << RCC_CLK_PRESCALER_SHIFT)
#define RCC_CLK_PRESCALER_ENABLE			((((1U << RCC_CLK_PRESCALER_BITS)-1U) & 0x01U) << RCC_CLK_PRESCALER_SHIFT)
#define RCC_CLK_PRESCALER_DISABLE			((((1U << RCC_CLK_PRESCALER_BITS)-1U) & 0x00U) << RCC_CLK_PRESCALER_SHIFT)

/* RCC_REGISTER_MAP END */

bool ct_rcc_handle_valid(HAL_CT_HANDLE devHandle,HAL_CT_DEVICE_INFO *device,uint32_t no_of_devices); 
uint32_t ct_rcc_get_device_index(HAL_CT_HANDLE devHandle,HAL_CT_DEVICE_INFO *device,uint32_t no_of_devices);
void ct_rcc_init_with_default(HAL_CT_HANDLE f_index,HAL_CT_DEVICE_INFO *device);

#endif /* INTERNAL_CT_RCC_H_ */
