/*******************************************************************************
Copyright (c) 2021 - Cientra All Rights Reserved.
This software is proprietary & confidential to Cientra
and its licensor.
********************************************************************************
* file name   : hal_ct_gpio.h
* description : Contains gpio driver API's   
* version     : 1.0
* date        : 31-May-2021
* author      : Jaijith
*******************************************************************************/

#ifndef HAL_CT_GPIO_H_
#define HAL_CT_GPIO_H_

/*======================== S T R U C T U R E S=====================================*/

typedef enum
{
    GPIO_INPUT,
    GPIO_OUTPUT,
    GPIO_BIDIRECTIONAL
} GPIO_PIN_TYPE;




typedef struct
{
    uint32_t instance;
    GPIO_PIN_TYPE pin_type;
    uint8_t gpio_index;
    uint8_t mux_demux_pin;
}GPIO_CONFIG_DETAILS;

/*========================== E N U M E R A T I O N S =========================*/
/**
* @brief  GPIO instance enumeration
*/
typedef enum
{
    GPIO1 = 0,
    GPIO2,
    GPIO3,
    GPIO4,
    GPIO5,
    GPIO6,
    GPIO7
}GPIO_INSTANCE;

typedef enum
{
	GPIO_PIN0 = 0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7,
	GPIO_PIN8,
	GPIO_PIN9,
	GPIO_PIN10,
	GPIO_PIN11,
	GPIO_PIN12,
	GPIO_PIN13,
	GPIO_PIN14,
	GPIO_PIN15,
}GPIO_PINS;


typedef enum
{
	GPIO_0_CTRL = 0x00,
	GPIO_1_CTRL,
	GPIO_2_CTRL,
	GPIO_3_CTRL,
	GPIO_4_CTRL,
	GPIO_5_CTRL,
	GPIO_6_CTRL,
	GPIO_7_CTRL,
	GPIO_8_CTRL,
	GPIO_9_CTRL,
	GPIO_10_CTRL,
	GPIO_11_CTRL,
	GPIO_12_CTRL,
	GPIO_13_CTRL,
	GPIO_14_CTRL,
	GPIO_15_CTRL,
	GPIO_IRQ_CTRL,
	GPIO_0_STS,
	GPIO_1_STS,
}pad_index;






/*======================== F U N C T I O N   D E C L A R A T I O N=====================================*/
HAL_CT_STATUS HAL_CT_gpio_init(uint32_t *num_of_devices); /*Initializes the base addresses of all the GPIO devices.*/
HAL_CT_STATUS HAL_CT_gpio_deinit(void); /*DeInitializes the base addresses of all the GPIO devices.*/
HAL_CT_STATUS HAL_CT_gpio_open(uint32_t device_number, uint32_t *devHandle  ); /*Returns the base address of a particular gpio instance.*/
HAL_CT_STATUS HAL_CT_gpio_close(HAL_CT_HANDLE devHandle); /*Returns the status of particular gpio instance.*/
HAL_CT_STATUS HAL_CT_gpio_ioctl(uint32_t devHandle, uint16_t cmd, void *ptr ); /*Performs the IO control based on the commands issued by the user.*/


#endif /* INC_HAL_CT_GPIO_H_ */
