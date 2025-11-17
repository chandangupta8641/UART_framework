/**
  ******************************************************************************
  * @file    internal_ct_uart.h
  * @author  Sunil
  * @brief   Contains uart driver related internal functions
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
#ifndef INTERNAL_CT_UART_H_
#define INTERNAL_CT_UART_H_
/* Includes ------------------------------------------------------------------*/

#include "../../common/src/hal_ct_porting.h"



/***  Bit definition ***/

/* DATA_REVERSE */

#define UART_DATA_FIRST_BYTE              0x000000FF
#define UART_DATA_SECOND_BYTE             0x0000FF00
#define UART_DATA_THIRD_BYTE              0x00FF0000
#define UART_DATA_FOURTH_BYTE             0xFF000000

/* DATA_REVERSE_END */

/*UART_CONTROL*/

#define UART_BAUD_RATE_2400		      		0x00000A2C4 /* divisor value for baud of 2400 */
#define UART_BAUD_RATE_9600	           		0x0000028B0 /* divisor value for baud of 9600 */
#define UART_BAUD_RATE_19200		        0x000001458 /* divisor value for baud of 19200 */
#define UART_BAUD_RATE_115200		        0x000000364/* divisor value for baud of 19200 */

#define UART_ENABLE_SHFT 					(0U)
#define UART_ENABLE_BITS 					(1U)
#define UART_ENABLE_MASK 					(((1U << UART_ENABLE_BITS)-1U) << UART_ENABLE_SHFT)
#define UART_DISABLE 						((((1U << UART_ENABLE_BITS)-1U) & 0x00U) << UART_ENABLE_SHFT)
#define UART_ENABLE 						((((1U << UART_ENABLE_BITS)-1U) & 0x01U) << UART_ENABLE_SHFT)

#define UART_PARITY_ENABLE_SHFT    			(1U)
#define UART_PARITY_ENABLE_BITS    			(1U)
#define UART_PARITY_ENABLE_MASK    			(((1U << UART_PARITY_ENABLE_BITS)-1U) << UART_PARITY_ENABLE_SHFT)
#define UART_PARITY_DISABLE        			((((1U << UART_PARITY_ENABLE_BITS)-1U) & 0x00U) << UART_PARITY_ENABLE_SHFT)
#define UART_PARITY_ENABLE         			((((1U << UART_PARITY_ENABLE_BITS)-1U) & 0x01U) << UART_PARITY_ENABLE_SHFT)

#define UART_PARITY_SHFT 					(2U)
#define UART_PARITY_BITS 					(1U)
#define UART_PARITY_MASK 					(((1U << UART_PARITY_BITS)-1U) << UART_PARITY_SHFT)
#define UART_EVEN_PARITY 					((((1U << UART_PARITY_BITS)-1U) & 0x01U) << UART_PARITY_SHFT)
#define UART_ODD_PARITY 					((((1U << UART_PARITY_BITS)-1U) & 0x00U) << UART_PARITY_SHFT)

#define UART_STOP_BITS_SHFT 				(3U)
#define UART_STOP_BITS_BITS 				(1U)
#define UART_STOP_BITS_MASK 				(((1U << UART_STOP_BITS_BITS)-1U) << UART_STOP_BITS_SHFT)
#define UART_STOP_BITS_ONE 					((((1U << UART_STOP_BITS_BITS)-1U) & 0x00U) << UART_STOP_BITS_SHFT)
#define UART_STOP_BITS_TWO 					((((1U << UART_STOP_BITS_BITS)-1U) & 0x01U) << UART_STOP_BITS_SHFT)

#define UART_XFER_SIZE_SHFT 				(4U)
#define UART_XFER_SIZE_BITS 				(2U)
#define UART_XFER_SIZE_MASK 				(((1U << UART_XFER_SIZE_BITS)-1U) << UART_XFER_SIZE_SHFT)
#define UART_XFER_SIZE_5BITS				((((1U << UART_XFER_SIZE_BITS)-1U) & 0x00U) << UART_XFER_SIZE_SHFT)
#define UART_XFER_SIZE_6BITS				((((1U << UART_XFER_SIZE_BITS)-1U) & 0x01U) << UART_XFER_SIZE_SHFT)
#define UART_XFER_SIZE_7BITS				((((1U << UART_XFER_SIZE_BITS)-1U) & 0x02U) << UART_XFER_SIZE_SHFT)
#define UART_XFER_SIZE_8BITS				((((1U << UART_XFER_SIZE_BITS)-1U) & 0x03U) << UART_XFER_SIZE_SHFT)

#define UART_CLK_SHFT 						(6U)
#define UART_CLK_BITS 						(2U)
#define UART_CLK_MASK 						(((1U << UART_CLK_BITS)-1U) << UART_CLK_SHFT)
#define UART_CLK_IO_2X 						((((1U << UART_CLK_BITS)-1U) & 0x00U) << UART_CLK_SHFT)
#define UART_CLK_IO_3X						((((1U << UART_CLK_BITS)-1U) & 0x01U) << UART_CLK_SHFT)
#define UART_CLK_IO_4X						((((1U << UART_CLK_BITS)-1U) & 0x02U) << UART_CLK_SHFT)
#define UART_CLK_IO_NA						((((1U << UART_CLK_BITS)-1U) & 0x03U) << UART_CLK_SHFT)

#define UART_FLOW_ENABLE_SHFT 				(8U)
#define UART_FLOW_ENABLE_BITS 				(1U)
#define UART_FLOW_ENABLE_MASK 				(((1U << UART_FLOW_ENABLE_BITS)-1U) << UART_FLOW_ENABLE_SHFT)
#define UART_FLOW_CTRL_DISABLE 				((((1U << UART_FLOW_ENABLE_BITS)-1U) & 0x00U) << UART_FLOW_ENABLE_SHFT)
#define UART_FLOW_CTRL_ENABLE 				((((1U << UART_FLOW_ENABLE_BITS)-1U) & 0x01U) << UART_FLOW_ENABLE_SHFT)

#define UART_FLOW_MODE_SHFT 				(8U)
#define UART_FLOW_MODE_BITS 				(1U)
#define UART_FLOW_MODE_MASK 				(((1U << UART_FLOW_MODE_BITS)-1U) << UART_FLOW_MODE_SHFT)
#define UART_FLOW_MODE_MS   				((((1U << UART_FLOW_MODE_BITS)-1U) & 0x00U) << UART_FLOW_MODE_SHFT)
#define UART_FLOW_MODE_FD   				((((1U << UART_FLOW_MODE_BITS)-1U) & 0x01U) << UART_FLOW_MODE_SHFT)


#if 0

#define UART_RX_ENABLE_SHFT 				(19U)
#define UART_RX_ENABLE_BITS 				(1U)
#define UART_RX_ENABLE_MASK 				(((1U << UART_RX_ENABLE_BITS)-1U) << UART_RX_ENABLE_SHFT)
#define UART_RX_DISABLE 					((((1U << UART_RX_ENABLE_BITS)-1U) & 0x00U) << UART_RX_ENABLE_SHFT)
#define UART_RX_ENABLE 						((((1U << UART_RX_ENABLE_BITS)-1U) & 0x01U) << UART_RX_ENABLE_SHFT)

#define UART_CLK_SHFT 						(20U)
#define UART_CLK_BITS 						(1U)
#define UART_CLK_MASK 						(((1U << UART_CLK_BITS)-1U) << UART_CLK_SHFT)
#define UART_CLK_IO 						((((1U << UART_CLK_BITS)-1U) & 0x00U) << UART_CLK_SHFT)
#define UART_CLK_B 							((((1U << UART_CLK_BITS)-1U) & 0x01U) << UART_CLK_SHFT)

#define UART_TX_LSB_SHFT 					(22U)
#define UART_TX_LSB_BITS 					(1U)
#define UART_TX_LSB_MASK 					(((1U << UART_TX_LSB_BITS)-1U) << UART_TX_LSB_SHFT)
#define UART_TX_LSB_FIRST 					((((1U << UART_TX_LSB_BITS)-1U) & 0x00U) << UART_TX_LSB_SHFT)
#define UART_TX_MSB_FIRST 					((((1U << UART_TX_LSB_BITS)-1U) & 0x01U) << UART_TX_LSB_SHFT)

#define UART_RX_LSB_SHFT 					(23U)
#define UART_RX_LSB_BITS 					(1U)
#define UART_RX_LSB_MASK 					(((1U << UART_RX_LSB_BITS)-1U) << UART_RX_LSB_SHFT)
#define UART_RX_LSB_FIRST 					((((1U << UART_RX_LSB_BITS)-1U) & 0x00U) << UART_RX_LSB_SHFT)
#define UART_RX_MSB_FIRST 					((((1U << UART_RX_LSB_BITS)-1U) & 0x01U) << UART_RX_LSB_SHFT)

#endif
/*   UART_CONTROL_END */

/*  UART_INT_MASK  */

#define UART_INT_RXFIFO_FULL_SHFT 			(18U)
#define UART_INT_RXFIFO_FULL_BITS 			(1U)
#define UART_INT_RXFIFO_FULL_MASK 			(((1U << UART_INT_RXFIFO_FULL_BITS)-1U) << UART_INT_RXFIFO_FULL_SHFT)
#define UART_INT_RXFIFO_FULL 				((((1U << UART_INT_RXFIFO_FULL_BITS)-1U) & 0x01U) << UART_INT_RXFIFO_FULL_SHFT)

#define UART_INT_RXFIFO_NOTEMPTY_SHFT 		(3U)
#define UART_INT_RXFIFO_NOTEMPTY_BITS 		(1U)
#define UART_INT_RXFIFO_NOTEMPTY_MASK 		(((1U << UART_INT_RXFIFO_NOTEMPTY_BITS)-1U) << UART_INT_RXFIFO_NOTEMPTY_SHFT)
#define UART_INT_RXFIFO_NOTEMPTY 			((((1U << UART_INT_RXFIFO_NOTEMPTY_BITS)-1U) & 0x01U) << UART_INT_RXFIFO_NOTEMPTY_SHFT)

/* UART_INT_MASK_END  */

/* UART_INT_CLR */

#define UART_INTRCLR_SET					(0x003f01ff)
#define UART_INTRCLR_RESET					(0x00000000)

#define UART_INTCLR_RXFIFO_NOTEMPTY_SHFT 	(3U)
#define UART_INTCLR_RXFIFO_NOTEMPTY_BITS 	(1U)
#define UART_INTCLR_RXFIFO_NOTEMPTY_MASK 	(((1U << UART_INTCLR_RXFIFO_NOTEMPTY_BITS)-1U) << UART_INTCLR_RXFIFO_NOTEMPTY_SHFT)
#define UART_INTCLR_RXFIFO_NOTEMPTY_RESET 	((((1U << UART_INTCLR_RXFIFO_NOTEMPTY_BITS)-1U) & 0x00U) << UART_INTCLR_RXFIFO_NOTEMPTY_SHFT)
#define UART_INTCLR_RXFIFO_NOTEMPTY_SET 	((((1U << UART_INTCLR_RXFIFO_NOTEMPTY_BITS)-1U) & 0x01U) << UART_INTCLR_RXFIFO_NOTEMPTY_SHFT)

#define UART_INTCLR_RXFIFO_FULL_SHFT 		(18U)
#define UART_INTCLR_RXFIFO_FULL_BITS 		(1U)
#define UART_INTCLR_RXFIFO_FULL_MASK 		(((1U << UART_INTCLR_RXFIFO_FULL_BITS)-1U) << UART_INTCLR_RXFIFO_FULL_SHFT)
#define UART_INTCLR_RXFIFO_FULL_RESET 		((((1U << UART_INTCLR_RXFIFO_FULL_BITS)-1U) & 0x00U) << UART_INTCLR_RXFIFO_FULL_SHFT)
#define UART_INTCLR_RXFIFO_FULL_SET 		((((1U << UART_INTCLR_RXFIFO_FULL_BITS)-1U) & 0x01U) << UART_INTCLR_RXFIFO_FULL_SHFT)

/* UART_INT_CLR END */

/* UART_APB_STATUS */

#define UART_APB_STATUS_TXFIFO_FULL_SHFT 	(0U)
#define UART_APB_STATUS_TXFIFO_FULL_BITS 	(1U)
#define UART_APB_STATUS_TXFIFO_FULL_MASK 	(((1U << UART_APB_STATUS_TXFIFO_FULL_BITS)-1U) << UART_APB_STATUS_TXFIFO_FULL_SHFT)
#define UART_APB_STATUS_TXFIFO_FULL 		((((1U << UART_APB_STATUS_TXFIFO_FULL_BITS)-1U) & 0x01U) << UART_APB_STATUS_TXFIFO_FULL_SHFT)

#define UART_LINE_STATUS_TXFIFO_NOTEMPTY_SHFT	(0U)
#define UART_LINE_STATUS_TXFIFO_NOTEMPTY_BITS	(1U)
#define UART_LINE_STATUS_TXFIFO_NOTEMPTY_MASK	(((1U << UART_LINE_STATUS_TXFIFO_NOTEMPTY_BITS)-1U) << UART_LINE_STATUS_TXFIFO_NOTEMPTY_SHFT)
#define UART_LINE_STATUS_TXFIFO_EMPTY			(((1U << UART_LINE_STATUS_TXFIFO_NOTEMPTY_BITS)-1U) & 0x01U) << UART_LINE_STATUS_TXFIFO_NOTEMPTY_SHFT)

#define UART_APB_STATUS_RXFIFO_NOTEMPTY_SHFT 	(3U)
#define UART_APB_STATUS_RXFIFO_NOTEMPTY_BITS 	(1U)
#define UART_APB_STATUS_RXFIFO_NOTEMPTY_MASK 	(((1U << UART_APB_STATUS_RXFIFO_NOTEMPTY_BITS)-1U) << UART_APB_STATUS_RXFIFO_NOTEMPTY_SHFT)
#define UART_APB_STATUS_RXFIFO_NOTEMPTY 		((((1U << UART_APB_STATUS_RXFIFO_NOTEMPTY_BITS)-1U) & 0x00U) << UART_APB_STATUS_RXFIFO_NOTEMPTY_SHFT)
#define UART_APB_STATUS_RXFIFO_EMPTY 		    ((((1U << UART_APB_STATUS_RXFIFO_NOTEMPTY_BITS)-1U) & 0x01U) << UART_APB_STATUS_RXFIFO_NOTEMPTY_SHFT)

/* UART_APB_STATUS END */

/* UART_REGISTER_MAP */

#define UART_TX_FIFO_4B					0x00              /*offset address for TX FIFO 4 Byte*/
#define UART_TX_FIFO_1B 				0x04 		      /*offset address for TX FIFO 1 Byte*/
#define UART_TX_FIFO_2B					0x08			  /*offset address for TX FIFO 2 Byte*/
#define UART_TX_FIFO_3B					0x0c			  /*offset address for TX FIFO 3 Byte*/
#define UART_CONTROL		 			0x10			  /*offset address for UART_TX_CONTROL_0 */
#define UART_RX_FIFO_1B		 			0x80			  /*offset address for UART_RX_FIFO*/
#define UART_INT_MASK					0x14			  /*offset address for UART_INTR_MASK_REG*/
#define UART_INT_CLR			 		0x18			  /*offset address for UART_STS_CLEANR_REG*/
#define UART_APB_STATUS					0x84		      /*offset address for UART_PCLK_STATUS_0*/
#define UART_LINE_STATUS			 	0x88			  /*offset address for UART_IO_CLK_STATUS_0*/

/* UART_REGISTER_MAP END */

/*======================== F U N C T I O N   D E C L A R A T I O N=====================================*/
bool ct_uart_tx_empty(HAL_CT_HANDLE devHandle); /*@surya*/
bool ct_uart_rx_available(uint32_t devHandle);				    /*To check whether data is available or not*/
bool ct_uart_tx_full(HAL_CT_HANDLE devHandle);					/*To check whether tx fifo full*/
uint32_t ct_uart_get_device_index(HAL_CT_HANDLE devHandle,HAL_CT_DEVICE_INFO *device,uint32_t no_of_devices);
void ct_uart_init_with_default(uint32_t f_index,HAL_CT_DEVICE_INFO *);			/* To set the RESET values */
bool ct_uart_handle_valid(HAL_CT_HANDLE ,HAL_CT_DEVICE_INFO *,uint32_t);		/* To check the device valid or not */

void ct_uart_write_rx_fifo (uint32_t deviceNumber,uint8_t byte);
void ct_uart_read_rx_fifo(HAL_CT_HANDLE devHandle,uint8_t *byte);
void ct_fifo_increment_ind (int32_t *index, int32_t fifosize);
int32_t ct_fifo_freesize (int32_t rdInd, int32_t wrInd, int32_t fifosize);
void ct_uart_reset_rx_fifo (uint32_t deviceNumber);

#endif /* INTERNAL_CT_UART_H_ */
