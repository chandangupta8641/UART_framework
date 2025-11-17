/**
  ******************************************************************************
  * @file    hal_ct_uart.c
  * @author  Sunil
  * @brief   HAL CT UART module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (UART).
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
**/

/* Includes ------------------------------------------------------------------*/
#include "../../common/src/hal_ct_porting.h"
#include "../../common/src/hal_ct_common.h"
#include "../../hal_ct_uart/src/hal_ct_uart.h"
#include "../../hal_ct_uart/src/internal_ct_uart.h"



static bool g_uart_driver_inited = FALSE;
/**
  * @brief  HAL_CT_uart_interrupthandler ISR handler for uart
  * @param  deviceNumber the device number indicate the particular instance of the uart.
  * @retval None
  */
#ifdef OS_BAREMETAL
void HAL_CT_uart_interrupthandler(uint32_t deviceNumber)
{
	//decide whether it is uart1 or uart2 base on the vector no
    volatile uint32_t l_reg_value = 0u;
    uint32_t l_val;
    //uint32_t l_statusToBeReported=0u;

    l_reg_value = ReadRegister32(g_uart_device[deviceNumber].baseaddress + UART_APB_STATUS);  /*Read the pclk status*/

    while((l_reg_value & UART_APB_STATUS_RXFIFO_NOTEMPTY)>0)
    {
		l_val = (uint8_t)ReadRegister32(g_uart_device[deviceNumber].baseaddress + UART_RX_FIFO_1B);  /*Read the data from rx fifo*/
		//l_val1 = (l_val << 24);
		//WriteRegister32(g_uart_device[deviceNumber].baseaddress + UART_TX_FIFO_1B,l_val1);            /*Write data into tx fifo*/
		ct_uart_write_rx_fifo(deviceNumber,(uint8_t )l_val);
		l_reg_value = ReadRegister32(g_uart_device[deviceNumber].baseaddress + UART_APB_STATUS);
    }

    /*status cleaner reg*/
    l_reg_value = UART_APB_STATUS_RXFIFO_NOTEMPTY;											/* flag clear*/
    WriteRegister32(g_uart_device[deviceNumber].baseaddress + UART_INT_CLR,l_reg_value); /*write 1 into status cleaner register write 1*/
    l_reg_value = ~l_reg_value;
    WriteRegister32(g_uart_device[deviceNumber].baseaddress + UART_INT_CLR,l_reg_value); /*write 0 into status cleaner register write 0*/

}

#endif
/**
  * @brief  HAL_CT_uart_init, returns the number of UART devices
  * @param  uint32_t *, number of UART devices filled by this functon 
  * @retval HAL_CT_STATUS
**/
HAL_CT_STATUS HAL_CT_uart_init(uint32_t *num_of_devices)
{
	uint32_t i = 0u;
	
	for (i=0u ; i<NO_OF_UART_DEVICES ; i++)
	{
		g_uart_device[i].baseaddress = g_uart_baseaddress[i];
		g_uart_device[i].int_enabled = FALSE;
	}

    *num_of_devices = NO_OF_UART_DEVICES;
    g_uart_driver_inited = TRUE;
    return HAL_CT_SUCCESS;
}

/**
  * @brief  HAL_CT_uart_deinit,DeInitializes the base addresses of all the UART devices.
  * @retval HAL_CT_STATUS
  */
HAL_CT_STATUS HAL_CT_uart_deinit(void)
{
    uint32_t i=0u;

    // close all open devices
    for (i=0u ; i< NO_OF_UART_DEVICES ; i++)
    {
    	g_uart_device[i].baseaddress = (uint32_t)NULL;
    }

    g_uart_driver_inited = FALSE;
    return HAL_CT_SUCCESS;
}
/**
  * @brief  HAL_CT_uart_open, Returns the device handle for the given UART instance
  * @param  uint32_t, device number
  * @param  HAL_CT_HANDLE *, device handle filled by this functon
  * @retval HAL_CT_STATUS
**/
HAL_CT_STATUS HAL_CT_uart_open (uint32_t device_number, HAL_CT_HANDLE *devHandle  )
{
	HAL_CT_STATUS l_retval = HAL_CT_ERROR;
    
	if (FALSE == g_uart_driver_inited)
	{
	    l_retval = 	HAL_CT_DRIVER_NOT_INITIALIZED;
	}
	else
	{
		// verify device number HAL_CT_INVALID_DEVICE
		//if((device_number >= 0) && (device_number <= NO_OF_UART_DEVICES))
        if((device_number+1) <= NO_OF_UART_DEVICES)
		{
			*devHandle = (HAL_CT_HANDLE)g_uart_device[device_number].baseaddress;
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
  * @brief  HAL_CT_uart_close, Returns the status of particular UART instance.
  * @retval HAL_CT_STATUS
  */
HAL_CT_STATUS HAL_CT_uart_close(HAL_CT_HANDLE devHandle)
{
    HAL_CT_STATUS l_retval = HAL_CT_ERROR;
    uint32_t l_device_index = 0u;
    
    // Check whether the device handle is valid
    if (FALSE == ct_uart_handle_valid(devHandle,g_uart_device,NO_OF_UART_DEVICES))
    {
    	l_retval = HAL_CT_INVALID_HANDLE;
	}
	else
	{
		// Configure the device with default values or reset the device		
		l_device_index = ct_uart_get_device_index(devHandle,g_uart_device,NO_OF_UART_DEVICES);
		ct_uart_init_with_default(l_device_index,g_uart_device);

		g_uart_device[l_device_index].baseaddress = (uint32_t)NULL;
		l_retval = HAL_CT_SUCCESS;
	}
    return l_retval;
}
/**
  * @param  devHandle  Pointer to a HAL_CT_HANDLE structure that contains
  * @retval HAL_CT_STATUS
**/

HAL_CT_STATUS HAL_CT_uart_ioctl (HAL_CT_HANDLE devHandle, uint16_t cmd, void* ptr)
{
     HAL_CT_STATUS l_retval = HAL_CT_ERROR;
  
    // Check whether the device handle is valid
    if (ct_uart_handle_valid(devHandle,g_uart_device,NO_OF_UART_DEVICES)==FALSE)
    {
    	l_retval = HAL_CT_INVALID_HANDLE;
    }
    else
    {
        // process commmand
        switch (cmd)
        {
            case HAL_CT_UART_CONFIG:
            {
                uint32_t l_config_reg = 0u;
                uint32_t l_mask_reg = 0u;
        	    UART_CONFIG_INFO *l_uart_config = (UART_CONFIG_INFO *) ptr;
        	    uint32_t l_device_index = ct_uart_get_device_index(devHandle,g_uart_device,NO_OF_UART_DEVICES);
  				ct_uart_reset_rx_fifo(l_device_index);
			    switch(l_uart_config->parity)
			    {
			    	case UART_PARITY_EVEN:
				    	l_config_reg = (l_config_reg & ~UART_PARITY_MASK) | UART_EVEN_PARITY;
				    	l_config_reg = (l_config_reg & ~UART_PARITY_ENABLE_MASK) | UART_PARITY_ENABLE;
				    	break;
				    case UART_PARITY_ODD:
				    	l_config_reg = (l_config_reg & ~UART_PARITY_MASK) | UART_ODD_PARITY;
				    	l_config_reg = (l_config_reg & ~UART_PARITY_ENABLE_MASK) | UART_PARITY_ENABLE;
				    	break;
				    case UART_PARITY_NONE:
				    	l_config_reg = (l_config_reg & ~UART_PARITY_ENABLE_MASK) | UART_PARITY_DISABLE;
				    	break;
				    default:
				    	// return error statement
				    	l_config_reg = (l_config_reg & ~UART_PARITY_ENABLE_MASK) | UART_PARITY_DISABLE;
					    break;
			    }

			    switch(l_uart_config->stop_bits)
			    {
				    case UART_STOPBITS_ONE:
				    	l_config_reg = (l_config_reg & ~UART_STOP_BITS_MASK) | UART_STOP_BITS_ONE;
				    	break;
				    case UART_STOPBITS_TWO:
				    	l_config_reg = (l_config_reg & ~UART_STOP_BITS_MASK) | UART_STOP_BITS_TWO;
			    	    break;
			    	default:
				    	l_config_reg = (l_config_reg & ~UART_STOP_BITS_MASK) | UART_STOP_BITS_TWO;
				    	break;
		    	}

			    switch(l_uart_config->data_width)
			    {
			    case UART_DATA_5BITS:
			    	l_config_reg = (l_config_reg & ~UART_XFER_SIZE_MASK) | UART_XFER_SIZE_5BITS;
			    	break;
			    case UART_DATA_6BITS:
			    	l_config_reg = (l_config_reg & ~UART_XFER_SIZE_MASK) | UART_XFER_SIZE_6BITS;
			    	break;
			    case UART_DATA_7BITS:
			    	l_config_reg = (l_config_reg & ~UART_XFER_SIZE_MASK) | UART_XFER_SIZE_7BITS;
			    	break;
			    case UART_DATA_8BITS:
			    	l_config_reg = (l_config_reg & ~UART_XFER_SIZE_MASK) | UART_XFER_SIZE_8BITS;
			    	break;
			    default:
			    	l_config_reg = (l_config_reg) | UART_XFER_SIZE_8BITS;
			    	break;
			    }

			    switch(l_uart_config->clk)
			    {
				case UART_IOCLK_2X:
					l_config_reg = (l_config_reg & ~UART_CLK_MASK) | UART_CLK_IO_2X;
					break;
				case UART_IOCLK_3X:
					l_config_reg = (l_config_reg & ~UART_CLK_MASK) | UART_CLK_IO_3X;
					break;
				case UART_IOCLK_4X:
					l_config_reg = (l_config_reg & ~UART_CLK_MASK) | UART_CLK_IO_4X;
					break;
				default:
					l_config_reg = (l_config_reg & ~UART_CLK_MASK) | UART_CLK_IO_2X;
					break;
				}


			    switch(l_uart_config->flow_ctrl)
			    {
			    case UART_FLOW_CTRL_DIS:
			    	l_config_reg = (l_config_reg & ~UART_FLOW_ENABLE_MASK) | UART_FLOW_CTRL_DISABLE;
			    	break;
			    case UART_FLOW_CTRL_ENA:
			    	l_config_reg = (l_config_reg & ~UART_FLOW_ENABLE_MASK) | UART_FLOW_CTRL_ENABLE;
			    	break;
			    default:
			    	l_config_reg = (l_config_reg & ~UART_FLOW_ENABLE_MASK) | UART_FLOW_CTRL_DISABLE;
			    	break;

			    }

				switch(l_uart_config->intr_enable)
				{
				case UART_INTRENABLE:
					l_mask_reg = (l_mask_reg & ~UART_INT_RXFIFO_FULL_MASK) | UART_INT_RXFIFO_FULL;
					l_mask_reg = (l_mask_reg & ~UART_INT_RXFIFO_NOTEMPTY_MASK) | UART_INT_RXFIFO_NOTEMPTY;
					g_uart_device[l_device_index].int_enabled = TRUE;
					break;
				case UART_INTRDISABLE:
					l_mask_reg = (l_mask_reg & ~DISABLE_ALL_INTR);
					g_uart_device[l_device_index].int_enabled = FALSE;
				    break;
				default:
					l_mask_reg = (l_mask_reg & ~DISABLE_ALL_INTR);
					g_uart_device[l_device_index].int_enabled = FALSE;
					break;
				}

			    l_config_reg = (l_config_reg) | UART_ENABLE;
			    WriteRegister32(devHandle + UART_CONTROL,l_config_reg);
			    WriteRegister32(devHandle + UART_INT_MASK,l_mask_reg);
				l_retval = HAL_CT_SUCCESS;
			    }
			    break;

			    case HAL_CT_UART_READ:
			              {
			   		    	uint32_t l_delay_cnt = 0;
			   			    UART_READ_INFO *l_uart_read = (UART_READ_INFO *)ptr;
			   			    l_uart_read->bytesRead = 0;

			   		    	if(l_uart_read->bytesToRead == 0)
			   			    {
			   				    l_retval = HAL_CT_SUCCESS;
			   			    }
			   			    else
			   			    {
			                    l_retval = HAL_CT_SUCCESS;
			   				    while(l_uart_read->bytesToRead > 0)
			   				    {
			   					    if(l_delay_cnt > DELAY_TWO_SEC)
			   					    {
			   						    break;
			   					    }
			   					    if(ct_uart_rx_available(devHandle) == TRUE)
			   					    {
			   						    l_delay_cnt = 0;
			   						    ct_uart_read_rx_fifo(devHandle,l_uart_read->data);
		   						        l_uart_read->data++;
			   						    l_uart_read->bytesRead += 1;
			   						    l_uart_read->bytesToRead -= 1;
                                    } else
								    {

									    l_delay_cnt++;

								    }
							    }
			   				    if(l_uart_read->bytesRead == 0)
			   				    {
			   				    	l_retval = HAL_CT_TIMEOUT;
			   				    }
			   				    else
			   				    {

			   				    }
			   			    }

						    }

			            break;


			   case HAL_CT_UART_SEND:
			     {
			              	uint32_t l_data;
			  			    UART_SEND_INFO *l_uart_send = (UART_SEND_INFO *) ptr;
			                l_retval = HAL_CT_SUCCESS;

			           while(l_uart_send->bytesToSend > 0u)
			            {
			                if(l_uart_send->bytesToSend >= 4u)	//uint8_t l_bufferTx[40]="ABCDEFGHIJKLMNOPQRSTUVWXYZ012345";
			  			    {
			  			         while (true == ct_uart_tx_full(devHandle))
			  			        	 {
			  			        	 }     //checking the TxFIFO register
			  			         // l_data=(((*(l_uart_send->data)) & UART_DATA_FIRST_BYTE) << 24) | (((*(l_uart_send->data)) & UART_DATA_SECOND_BYTE) << 8) | (((*(l_uart_send->data)) & UART_DATA_THIRD_BYTE) >> 8) | (((*(l_uart_send->data)) & UART_DATA_FOURTH_BYTE) >> 24);
			  					 l_data = (*(l_uart_send->data));
			  					 WriteRegister32(devHandle + UART_TX_FIFO_4B,(l_data));

			  					 l_uart_send->bytesToSend = l_uart_send->bytesToSend-4;
			                     l_uart_send->data++;

			  			    }
	     			        else if (l_uart_send->bytesToSend == 3u)
		  				    {
			  				    	while (true == ct_uart_tx_full(devHandle));
			  				    //	l_data=(((*(l_uart_send->data)) & UART_DATA_FIRST_BYTE) << 16) | ((*(l_uart_send->data)) & UART_DATA_SECOND_BYTE) | (((*(l_uart_send->data)) & UART_DATA_THIRD_BYTE) >> 16);
			  				    	l_data = (*(l_uart_send->data));
			  				    	WriteRegister32(devHandle + UART_TX_FIFO_3B,(l_data));

			  					    l_uart_send->bytesToSend = l_uart_send->bytesToSend-3;
		  				    }
		  			    	else if (l_uart_send->bytesToSend == 2u)
		  				    {
			  					   while (true == ct_uart_tx_full(devHandle));
//			  					   l_data=(((*(l_uart_send->data)) & UART_DATA_FIRST_BYTE) << 8) | (((*(l_uart_send->data)) & UART_DATA_SECOND_BYTE) >> 8);
			  					   l_data = (*(l_uart_send->data));
			  					   WriteRegister32(devHandle + UART_TX_FIFO_2B,(l_data));

			  					   l_uart_send->bytesToSend = l_uart_send->bytesToSend-2;
		  				   }
     					   else if (l_uart_send->bytesToSend == 1u)
			  			   {
			  					   while (true == ct_uart_tx_full(devHandle));
			  					   l_data = (*(l_uart_send->data));
			  					   WriteRegister32(devHandle + UART_TX_FIFO_1B,(l_data));

			  					   l_uart_send->bytesToSend = l_uart_send->bytesToSend-1;

			  			  }
			  		   }
//			                ct_read_reg_status(devHandle);  //Read the APB,LINE & UART Control register status

			  			break;


			    default :
			    break;
			  	}

			 }
	   return l_retval;
    }
}


#if 0
    switch(l_uart_config->intr_enable)
			    			    {
			    				    case UART_INTRENABLE:
			    					    l_mask_reg = (l_mask_reg & ~UART_INT_RXFIFO_FULL_MASK) | UART_INT_RXFIFO_FULL;
			    					    l_mask_reg = (l_mask_reg & ~UART_INT_RXFIFO_NOTEMPTY_MASK) | UART_INT_RXFIFO_NOTEMPTY;
			    					    g_uart_device[l_device_index].int_enabled = TRUE;
			    					    break;
			    				    case UART_INTRDISABLE:
			    					    l_mask_reg = (l_mask_reg & ~DISABLE_ALL_INTR);
			    					    g_uart_device[l_device_index].int_enabled = FALSE;
			    					    break;
			    			    	default:
			    				    	l_mask_reg = (l_mask_reg & ~DISABLE_ALL_INTR);
			    					    g_uart_device[l_device_index].int_enabled = FALSE;
			    					    break;
			    			    }

			    	           l_config_reg = (l_config_reg & ~UART_RX_ENABLE_MASK) | UART_RX_ENABLE;
			    	           l_config_reg = (l_config_reg & ~UART_ENABLE_MASK) | UART_ENABLE;

			                   WriteRegister32(devHandle + UART_CONTROL,l_config_reg);
			                   WriteRegister32(devHandle + UART_INT_MASK,l_mask_reg);  /*enable the interrupts*/
			    	           l_retval = HAL_CT_SUCCESS;
			               }
			               break;

    	
		    	switch(l_uart_config->intr_enable)
			    {
				    case UART_INTRENABLE:
					    l_mask_reg = (l_mask_reg & ~UART_INT_RXFIFO_FULL_MASK) | UART_INT_RXFIFO_FULL;
					    l_mask_reg = (l_mask_reg & ~UART_INT_RXFIFO_NOTEMPTY_MASK) | UART_INT_RXFIFO_NOTEMPTY;
					    g_uart_device[l_device_index].int_enabled = FALSE;
					    break;
				    case UART_INTRDISABLE:
					    l_mask_reg = (l_mask_reg & ~DISABLE_ALL_INTR);
					    g_uart_device[l_device_index].int_enabled = TRUE;
					    break;
			    	default:
				    	l_mask_reg = (l_mask_reg & ~DISABLE_ALL_INTR);
					    g_uart_device[l_device_index].int_enabled = TRUE;
					    break;
			    }

	           l_config_reg = (l_config_reg & ~UART_RX_ENABLE_MASK) | UART_RX_ENABLE;
	           l_config_reg = (l_config_reg & ~UART_ENABLE_MASK) | UART_ENABLE;

               WriteRegister32(devHandle + UART_CONTROL,l_config_reg);
               WriteRegister32(devHandle + UART_INT_MASK,l_mask_reg);  /*enable the interrupts*/
	           l_retval = HAL_CT_SUCCESS;
           }
           break;

           case HAL_CT_UART_READ:
           {
		    	uint32_t l_delay_cnt = 0;
			    UART_READ_INFO *l_uart_read = (UART_READ_INFO *)ptr;
			    l_uart_read->bytesRead = 0;

		    	if(l_uart_read->bytesToRead == 0)
			    {
				    l_retval = HAL_CT_SUCCESS;
			    }
			    else
			    {
                    l_retval = HAL_CT_SUCCESS;
				    while(l_uart_read->bytesToRead > 0)
				    {
					    if(l_delay_cnt > DELAY_TWO_SEC)
					    {
						    l_retval = HAL_CT_TIMEOUT;
						    break;
					    }
					    if(ct_uart_rx_available(devHandle) == TRUE)
					    {
						    l_delay_cnt = 0;
						    ct_uart_read_rx_fifo(devHandle,l_uart_read->data);
						    l_uart_read->data++;
						    l_uart_read->bytesRead += 1;
						    l_uart_read->bytesToRead -= 1;
					    }
					    else
					    {
						    l_delay_cnt++;
					    }
				    }

			    }
            }
            break;
            case HAL_CT_UART_SEND:
            {
            	UART_SEND_INFO *l_uart_send = (UART_SEND_INFO *) ptr;
            	uint32_t l_data=0;
                l_retval = HAL_CT_SUCCESS;
			    if(l_uart_send->bytesToSend!= 0u)
			    {
			        while(l_uart_send->bytesToSend >=4u)
				    {
					    while (true == ct_uart_tx_full(devHandle));
					    l_data=(((*(l_uart_send->data)) & UART_DATA_FIRST_BYTE) << 24) | (((*(l_uart_send->data)) & UART_DATA_SECOND_BYTE) << 8) | (((*(l_uart_send->data)) & UART_DATA_THIRD_BYTE) >> 8) | (((*(l_uart_send->data)) & UART_DATA_FOURTH_BYTE) >> 24);
					    WriteRegister32(devHandle + UART_TX_FIFO_4B,(l_data));
					    l_uart_send->bytesToSend = l_uart_send->bytesToSend-4;
                        l_uart_send->data++;
				    }

				    if (l_uart_send->bytesToSend == 3u)
				    {
				    	while (true == ct_uart_tx_full(devHandle));
				    	l_data=(((*(l_uart_send->data)) & UART_DATA_FIRST_BYTE) << 16) | ((*(l_uart_send->data)) & UART_DATA_SECOND_BYTE) | (((*(l_uart_send->data)) & UART_DATA_THIRD_BYTE) >> 16);
				    	WriteRegister32(devHandle + UART_TX_FIFO_3B,(l_data <<8));
					    l_uart_send->bytesToSend = l_uart_send->bytesToSend-3;
				    }

			    	else if (l_uart_send->bytesToSend == 2u)
				    {
					    while (true == ct_uart_tx_full(devHandle));
					    l_data=(((*(l_uart_send->data)) & UART_DATA_FIRST_BYTE) << 8) | (((*(l_uart_send->data)) & UART_DATA_SECOND_BYTE) >> 8);
					    WriteRegister32(devHandle + UART_TX_FIFO_2B,(l_data <<16));
					    l_uart_send->bytesToSend = l_uart_send->bytesToSend-2;
				    }

				    else if (l_uart_send->bytesToSend == 1u)
				    {
					    while (true == ct_uart_tx_full(devHandle));
					    WriteRegister32(devHandle + UART_TX_FIFO_1B,(*(l_uart_send->data)<<24));
					    l_uart_send->bytesToSend = l_uart_send->bytesToSend-1;
				    }
			       	else
				    {
					    /* Do Nothing */
				    }
                }
            }
            break;

            default :
            break;
        }
    }
    return l_retval;
}
#endif
/**Copyright (c) 2021 - Cientra All Rights Reserved.
This software is proprietary & confidential to Cientra
and its licensor. *****END OF FILE****/
