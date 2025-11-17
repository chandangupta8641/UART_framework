
/**
  ******************************************************************************
  * @file    hal_ct_rcc.h
  * @author  Jaijith
  * @brief   Contains rcc driver bit definations,structures,enum definations,function declarations.
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
#ifndef HAL_CT_RCC_H_
#define HAL_CT_RCC_H_

/* Includes ------------------------------------------------------------------*/
/* Bit definition for RCC clock register */
#define RCC_CLK_CONTROL_CLK_DIV_DEF		                     (0x00000000)
#define RCC_CLK_CONTROL_CLK_DIV_BY_1                         (0x00000001)       /*!< Divide by 1 */
#define RCC_CLK_CONTROL_CLK_DIV_BY_2                         (0x00000002)       /*!< Divide by 2 */
#define RCC_CLK_CONTROL_CLK_DIV_BY_3                         (0x00000003)       /*!< Divide by 3 */
#define RCC_CLK_CONTROL_CLK_DIV_BY_4                         (0x00000004)       /*!< Divide by 4 */
#define RCC_CLK_CONTROL_CLK_DIV_BY_5                         (0x00000005)       /*!< Divide by 5 */
#define RCC_CLK_CONTROL_CLK_DIV_BY_6                         (0x00000006)       /*!< Divide by 6 */
#define RCC_CLK_CONTROL_CLK_DIV_BY_7                         (0x00000007)       /*!< Divide by 7 */
#define RCC_CLK_CONTROL_CLK_DIV_BY_8                         (0x00000008)       /*!< Divide by 8 */
#define RCC_CLK_CONTROL_CLK_DIV_BY_9                         (0x00000009)       /*!< Divide by 9 */
#define RCC_CLK_CONTROL_CLK_DIV_BY_192                       (0x00000300)       /*!< Divide by 192 */
#define RCC_CLK_CONTROL_CLK_DIV_BY_50                        (0x00000032)       /*!< Divide by 50 */
#define RCC_CLK_CONTROL_CLK_DIV_BY_217                       (0x000000D9)       /*!< Divide by 217 */ /*115200 BD */


//#define RCC_PLL_CLK_DIV_BY_1                                 (0x00000001)       /*!< Divide by 1 */
//#define RCC_PLL_CLK_DIV_BY_2                                 (0x00000002)       /*!< Divide by 2 */
//#define RCC_PLL_CLK_DIV_BY_3                                 (0x00000003)       /*!< Divide by 3 */
//#define RCC_PLL_CLK_DIV_BY_7                                 (0x00000007)       /*!< Divide by 7 */
//#define RCC_PLL_CLK_DIV_BY_10                                (0x0000000A)       /*!< Divide by 10 */
//#define RCC_PLL_CLK_DIV_BY_13                                (0x0000000D)       /*!< Divide by 13 */
//#define RCC_PLL_CLK_DIV_BY_25                                (0x00000019)       /*!< Divide by 25 */

//#define RCC_TIMER_CLK_CONTROL_CLK_MUL_BY_2                   (0x00000008)       /*!< Divide by 2 */
/*======================== D E F I N E S =====================================*/


/*========================== E N U M E R A T I O N S =========================*/
/**
  * @brief RCC Instance enum definition
  */
typedef enum
{
    RCC1 = 0,
    RCC2,
    RCC3,
    RCC4,
    RCC5,
    RCC6,
    RCC7
}RCC_INSTANCE;


typedef enum
{
    CLK_TYPE_TCXO = 0,
    CLK_TYPE_PLL
}RCC_CLK_TYPE;



/*======================== S T R U C T U R E S=====================================*/


/**
  * @brief RCC DEVICE INFORMATION Structure definition
  */
//typedef struct
//{
//    uint32_t baseaddress;
//} DEVICE_INFO;
//

/**
  * @brief RCC CONFIG DETAILS Structure definition
  */
typedef struct
{
    uint32_t instance;
	bool     tcxo_prescaler_enable;
	bool     pll_prescaler_enable;
	uint32_t tcxo_prescaler_divider;
	uint32_t pll_prescaler_divider;
	uint32_t pll_multiplier;
} RCC_CONFIG_INFO;

/**
  * @brief RCC CLK CONFIG DETAILS Structure definition
  */
typedef struct
{
	uint32_t clk_index;
    uint32_t clk_div;
    RCC_CLK_TYPE clk_type;
	bool     prescaler_enable;
} RCC_CLK_CONFIG_INFO;




/*======================== F U N C T I O N   D E C L A R A T I O N=====================================*/

HAL_CT_STATUS HAL_CT_rcc_init (uint32_t *num_of_devices);   /*Initializes the base addresses of all the RCC devices*/
HAL_CT_STATUS HAL_CT_rcc_deinit(void);  /*DeInitializes the base addresses of all the RCC devices*/
HAL_CT_STATUS HAL_CT_rcc_open (uint32_t device_number, HAL_CT_HANDLE *devHandle  );  /*Returns the base address of a particular rcc instance*/
HAL_CT_STATUS HAL_CT_rcc_close(HAL_CT_HANDLE devHandle);  /*Closes the RCC device*/
HAL_CT_STATUS HAL_CT_rcc_ioctl (HAL_CT_HANDLE devHandle, uint16_t cmd, void *ptr);    /*Performs the RCC IO control based on the commands issued by the user*/



#endif /* HAL_CT_RCC_H_ */
