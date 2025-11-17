	/**
  ******************************************************************************
  * @file    hal_ct_uart.h
  * @author  Sunil
  * @brief   Contains Registers bit definations,function declarations,structure definations,enum definations.
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
#ifndef HAL_CT_UART_H_
#define HAL_CT_UART_H_
/* Includes ------------------------------------------------------------------*/


/*======================== D E F I N E S =====================================*/


/******************************************************************************/
/*                         Peripheral Registers Bits Definition               */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*      Universal Asynchronous Receiver Transmitter (UART)     				  */
/*                                                                            */
/******************************************************************************/

/*======================== S T R U C T U R E S=====================================*/

/**
  * @brief UART CONFIGRATIION DETAILS Structure definition
  */
typedef struct
{
    uint32_t instance;
    uint8_t enable;
    uint8_t baud;
    uint8_t data_width;
    uint8_t parity;
    uint8_t stop_bits;
    uint8_t flow_ctrl;
   // uint8_t lsb_first;  //it should be bool
    uint8_t clk;
    uint8_t intr_enable;
   // uint8_t reserved[2];
}UART_CONFIG_INFO;
/**
  * @brief UART READ Structure definition
  */
typedef struct
{
    uint32_t bytesToRead;
    uint32_t bytesRead;
    uint8_t *data;
}UART_READ_INFO;
/**
  * @brief UART SEND Structure definition
  */
typedef struct
{
    uint32_t bytesToSend;
    uint32_t *data;
}UART_SEND_INFO;


/*========================== E N U M E R A T I O N S =========================*/
/**
  * @brief UART Instance enum definition
  */
typedef enum
{
    UART1 = 0,
    UART2
}UART_INSTANCE;


/**
  * @brief UART ENABLE definition
  */
typedef enum
{
	UART_ENB = 1,
	UART_DISAB
}UART_enable;


/**
  * @brief UART BAUD definition
  */
typedef enum
{
    UART_BAUD_2400 =1,
    UART_BAUD_9600,
    UART_BAUD_19200,
	UART_BAUD_115200

}UART_BAUD;
/**
  * @brief UART CLOCK enum definition
  */
typedef enum
{
    UART_DATA_5BITS =1,
    UART_DATA_6BITS,
    UART_DATA_7BITS,
	UART_DATA_8BITS
}UART_DATA_WIDTH;
/**
  * @brief UART CLOCK enum definition
  */
typedef enum
{
    UART_IOCLK_2X =1,
    UART_IOCLK_3X,
	UART_IOCLK_4X
}UART_CLK;

/**
  * @brief UART PARITY enum definition
  */
typedef enum
{
    UART_PARITY_EVEN =1,
    UART_PARITY_ODD,
    UART_PARITY_NONE
}UART_PARITY;
/**
  * @brief uart stop bits definition
  */
typedef enum
{
    UART_STOPBITS_ONE =1,
    UART_STOPBITS_TWO
}UART_STOPBITS;
/**
  * @brief UART_INTR_ENABLE enum definition
  */
typedef enum
{
	UART_INTRENABLE = 0,
	UART_INTRDISABLE
}UART_INTR_ENABLE;

typedef enum
{
	UART_FLOW_CTRL_DIS = 1,
	UART_FLOW_CTRL_ENA
}UART_FLOW_CTRL;


/*======================== F U N C T I O N   D E C L A R A T I O N=====================================*/

HAL_CT_STATUS HAL_CT_uart_init(uint32_t *num_of_devices);  					   /*Initializes the base addresses of all the UART devices*/
HAL_CT_STATUS HAL_CT_uart_deinit(void);		                				   /*DeInitializes the base addresses of all the UART devices*/
HAL_CT_STATUS HAL_CT_uart_open (uint32_t device_number, HAL_CT_HANDLE *devHandle);  /*Returns the base address of a particular UART instance*/
HAL_CT_STATUS HAL_CT_uart_close(HAL_CT_HANDLE devHandle);                     /*Returns the status of particular UART instance*/
HAL_CT_STATUS HAL_CT_uart_ioctl (HAL_CT_HANDLE, uint16_t, void*);		/*Performs the UART IO control based on the commands issued by the user*/

//void HAL_CT_axiintc_interrupthandler_6();
void HAL_CT_uart_interrupthandler(uint32_t deviceNumber);

#endif /* HAL_CT_UART_H_ */
