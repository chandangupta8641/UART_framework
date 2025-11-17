/* USER CODE BEGIN Header */
/**
   *******************************************************************************
   * @file		:app_ct_uart.c
   * @brief		:Contains uart initialization and application
	* @version	:1.0
	* @date		:25-june-2021
	* @author	:sunil
   *******************************************************************************
   *@attention
   *
	*<h2><center>&copy;Copyright (c) 2021 - Cientra All Rights Reserved.</center></h2>
	*This software is proprietary & confidential to Cientra
	*and its licensor.
	*									www.cientra.com
	*
	*******************************************************************************
	*/
/* USER CODE END Header */

/* Includes ----------------------------------------------------------------------*/

// #include <stdio.h>
#include "../../common/src/hal_ct_porting.h"
#include "../../hal_ct_rcc/src/hal_ct_rcc.h"
#include "../../hal_ct_gpio/src/hal_ct_gpio.h"
#include "../../hal_ct_uart/src/hal_ct_uart.h"
#include "../src/internal_ct_uart.h"
#ifdef ZED_MICROBLAZE_BAREMETAL
//#include "../../hal_ct_axi_intc/src/hal_ct_axi_intc.h"
#endif
/* Private function prototypes -----------------------------------------------*/
//void HAL_CT_axiintc_interrupthandler_6() __attribute__((fast_interrupt));

static uint16_t CallbackCalled = 0;
// uint32_t M_control;

/**
	* @brief callback function
	* @retval None
	*/

#if 0
void UART_0_CallBack (uint32_t source)
{
	// store the source and return
	if(source & UART1_SR_RXFIFO_UNDERUN)
	{
		printf("RX FIFO Under run error\n");
	}
	if(source & UART1_LSR_PARITY_ERROR)
	{
		printf("parity error\n");
	}
	if(source & UART1_LSR_FRAME_ERROR)
	{
		printf("framming error\n");
	}
	CallbackCalled++;
}
#endif


/**
 * @brief The application entry point.
 * @retval void
 *
*/

int main()
{
    /*    RCC Declaration details    */

    uint32_t rccDevices;
    HAL_CT_HANDLE rccHandle;
    RCC_CONFIG_INFO rcc_config;
    rcc_config.instance = RCC1;
	
	RCC_CLK_CONFIG_INFO l_rcc_clk_config;

    /*    GPIO Declaration details    */

    uint32_t gpioDevices;
    GPIO_CONFIG_DETAILS gpio_config;
    gpio_config.instance = GPIO1;
    HAL_CT_HANDLE gpioHandle;

    /*    UART Declaration details    */
    uint32_t uartDevices;
    HAL_CT_HANDLE uartHandle;
    UART_CONFIG_INFO uart_config;
    uart_config.instance = UART1;




#ifdef ZED_MICROBLAZE_BAREMETAL
    /* UART AXI_INTERRUPT Declaration details    */
    uint32_t axiIntcDevices;
    HAL_CT_HANDLE axiIntcHandle;
    //AXIINTC_CONFIG_INFO axiintc_config;
    //axiintc_config.instance = AXIINTC;
#endif

    uint32_t l_retcode = HAL_CT_SUCCESS;

    uint32_t reg_value =0;

    /*-------------INIT---------------------------------------------------------*/

    /*returns number of RCC devices*/

    l_retcode = HAL_CT_rcc_init(&rccDevices);
    if (HAL_CT_SUCCESS != l_retcode)
    {
    	printf("RCC Init Status = %d\n",l_retcode);
    }

    /*returns number of GPIO devices*/

    l_retcode = HAL_CT_gpio_init(&gpioDevices);
    if (HAL_CT_SUCCESS != l_retcode)
    {
    	printf("GPIO Init Status = %d\n",l_retcode);
    }

    /*returns number of UART devices*/
    l_retcode = HAL_CT_uart_init(&uartDevices);
    if (HAL_CT_SUCCESS != l_retcode)
    {
    	printf("UART Init Status = %d\n",l_retcode);
    }

#ifdef ZED_MICROBLAZE_BAREMETAL
    /*returns number of AXI devices*/
    l_retcode = HAL_CT_axiintc_init(&axiIntcDevices);
    if (HAL_CT_SUCCESS != l_retcode)
    {
    	printf("AXI INTC Init Status = %d\n",l_retcode);
    }
#endif


    /*-----------------OPEN---------------------------------------------------------*/
    /*returns base address of particular device*/
    l_retcode = HAL_CT_rcc_open(rcc_config.instance ,&rccHandle);
    if (HAL_CT_SUCCESS != l_retcode)
    {
    	printf("RCC OpenDevice Status = %d\n",l_retcode);
    }

    /*returns base address of particular device*/
    l_retcode = HAL_CT_gpio_open(gpio_config.instance,&gpioHandle);
    if (HAL_CT_SUCCESS != l_retcode)
    {
    	printf("GPIO OpenDevice Status = %d\n",l_retcode);
    }

    /*returns base address of particular device*/
    l_retcode = HAL_CT_uart_open(uart_config.instance,&uartHandle);
    if (HAL_CT_SUCCESS != l_retcode)
    {
    	printf("UART OpenDevice Status = %d\n",l_retcode);
    }

#ifdef ZED_MICROBLAZE_BAREMETAL
    /*returns base address of particular device*/
    l_retcode = HAL_CT_axiintc_open(axiintc_config.instance,&axiIntcHandle);
    if (HAL_CT_SUCCESS != l_retcode)
    {
    	printf("AXI INTC OpenDevice Status = %d\n",l_retcode);
    }
#endif


/****************** RCC clock  ************************/

    rcc_config.tcxo_prescaler_enable = FALSE;
	rcc_config.pll_prescaler_enable = FALSE;
	rcc_config.tcxo_prescaler_divider = 0;
	rcc_config.pll_prescaler_divider = 0;

    l_retcode = HAL_CT_rcc_ioctl(rccHandle, HAL_CT_RCC_CONFIG, (void*)&rcc_config);
    if(HAL_CT_SUCCESS != l_retcode)
    {
    	printf("HAL_CT_rcc_ioctl Failed with status =%d\n", l_retcode);
    }

    //  RCC_CLK = 5.5Mhz
     l_rcc_clk_config.clk_div = 0xC; // Clock divison value for 115200 and clock is 460.800Khz  -->tested
   // l_rcc_clk_config.clk_div = 0x18; // Clock divison value for 57600 and clock is 230.4Khz -->tested
  //  l_rcc_clk_config.clk_div = 0x24; // Clock divison value for 38400 and clock is 153.600Khz   --> tested
  //  l_rcc_clk_config.clk_div = 0x47; // Clock divison value for 19200 and clock is 76.800Khz     --> tested
  //  l_rcc_clk_config.clk_div = 0x8F;  // Clock divison value for 9600 and uart clock is 38.4Khz  -->tested
	l_rcc_clk_config.clk_index = HAL_CT_UART_CLK;
    l_retcode = HAL_CT_rcc_ioctl(rccHandle, HAL_CT_RCC_CLK_CONFIG, (void*)&l_rcc_clk_config);

    if(HAL_CT_SUCCESS != l_retcode)
    {
    	 printf("HAL_CT_rcc_ioctl Failed with status =%d\n", l_retcode);
    }


    /**********************  UART Tx*********************/
    gpio_config.instance = GPIO1;
    gpio_config.gpio_index = GPIO_0_CTRL;
    gpio_config.pin_type = GPIO_OUTPUT;
    gpio_config.mux_demux_pin = 0;  //mux

    l_retcode = HAL_CT_gpio_ioctl(gpioHandle, HAL_CT_GPIO_CONFIG, &gpio_config);
    if (HAL_CT_SUCCESS != l_retcode)
    {
          printf("GPIO Ioctl GPIO Default Read Status = %d\n",l_retcode);
    }


    /****************   UART  rx       ***************/
    gpio_config.instance = GPIO1;
    gpio_config.gpio_index = GPIO_3_CTRL;
    gpio_config.pin_type = GPIO_INPUT;
    gpio_config.mux_demux_pin = 3;     //macro to be declared for this value

    l_retcode = HAL_CT_gpio_ioctl(gpioHandle, HAL_CT_GPIO_CONFIG, &gpio_config);
    if (HAL_CT_SUCCESS != l_retcode)
    {
          printf("GPIO Ioctl GPIO Default Read Status = %d\n",l_retcode);
    }



#if 0
    /*******************************Hard_coded_configure values**********************************/
	uint32_t baud_rate;
	uint8_t enable;
	uint32_t data_width;
	uint32_t parity;
	uint32_t stopbits;
	uint32_t flow_ctrl;
	uint32_t clk;
	uint32_t setup;

	uart_config.enable = UART_ENB;
	uart_config.baud = UART_BAUD_115200;
	uart_config.data_width = UART_DATA_8BITS;
	uart_config.parity = UART_PARITY_NONE;
	uart_config.stop_bits = UART_STOPBITS_ONE;
	uart_config.flow_ctrl = UART_FLOW_CTRL_DIS;
	uart_config.clk = UART_IOCLK_4X;


	ct_uart_test_1(uart_config,uartHandle);


	ct_uart_test_2(uart_config, uartHandle);

    ct_uart_test_3(uart_config, uartHandle);  //Internal loopback

	ct_uart_test_4(uart_config, uartHandle);	//External loop back

#endif





#if 0
    #ifdef ZED_MICROBLAZE_BAREMETAL
    /*------------------------AXI INTC CONFIG----------------------------------------------------------*/
    axiintc_config.irq_number = UART1_AXIINTC_ENABLE;   /*IRQ number to be enable*/
    axiintc_config.int_handler = (void (*)(uint32_t))HAL_CT_uart_interrupthandler;
	l_retcode = HAL_CT_axiintc_ioctl(axiIntcHandle, HAL_CT_AXIINTC_INTENABLE,(void*) &axiintc_config);
    if (HAL_CT_SUCCESS != l_retcode)
    {
    	printf("AXI_INTC Ioctl INTC Config Status = %d\n",l_retcode);
    }

    /* TO enable the microblaze interrupts*/
    //enableInterrupts();
    #endif
#endif


#if 1
    //uint8_t c;
    do{
    	uint32_t baud_rate;
    	uint8_t enable;
    	uint32_t data_width;
    	uint32_t parity;
    	uint32_t stopbits;
    	uint32_t flow_ctrl;
    	uint32_t clk;
    	uint32_t setup;



    	///////////////////////////////////////////////////////////////////////////////////////////

    	printf("Select uart enable\n");
    	printf("1. Enable\n");
    	printf("2. Disable\n");
    	printf("Default is Disable\n>");

    	scanf("%d",&enable);
      	printf("uart_enable=%d\n",enable);
    	switch(enable)
    	{
    	case 1:
    	uart_config.enable = UART_ENB;
    	break;

    	case 2:
    	uart_config.enable= UART_DISAB;
    	break;

    	default:
    	uart_config.enable = UART_ENB;
    	break;
    	}


    	///
    	//xil_printf("Enter the Baud Rate for which you want to configure. Type 1 or 2 or 3\n");
    	printf("1. 2400\n");
    	printf("2. 9600\n");
    	printf("3. 19200\n");
    	printf("4. 115200\n");
	    printf("Default: 2400\nEnter baud : ");
    	scanf("%d",&baud_rate);
    	printf("configured_baudrate=%d\n",baud_rate);

				switch(baud_rate){
					case 1:
						uart_config.baud = UART_BAUD_2400;
						break;
					case 2:
						uart_config.baud = UART_BAUD_9600;
						break;
					case 3:
						uart_config.baud = UART_BAUD_19200;
						break;
					case 4:
						uart_config.baud = UART_BAUD_115200;
						break;
					default:
						printf("default baud rate = 115200\n");
					uart_config.baud = UART_BAUD_115200;


				}

    	 printf("Enter the data width\n");
         printf("1. 5 bits\n");
    	 printf("2. 6 bits\n");
    	 printf("3. 7 bits\n");
    	 printf("4. 8 bits\n");
    	 printf("Default: 8 bits\n>");
    	 scanf("%d",&data_width);
    	 printf("configured_datawidth=%d\n",data_width);

    	    	switch(data_width){
    	    		case 1:
    	    			uart_config.data_width = UART_DATA_5BITS;
    	    			break;
    	    		case 2:
    	    			uart_config.data_width= UART_DATA_6BITS;
    	    			break;
    	    		case 3:
    	    			uart_config.data_width = UART_DATA_7BITS;
    	    			break;
    				case 4:
    	    			uart_config.data_width = UART_DATA_8BITS;
    	    			break;
    	    		default:
    				    uart_config.data_width = UART_DATA_8BITS;
    	    			break;

    	    	}

    	printf("Enter the Parity for which you want to configure. Type 1 or 2 or 3\n");
    	printf("1. None\n");
    	printf("2. Even\n");
    	printf("3. Odd\n");
	    printf("Default. None\n>");
    	scanf("%d",&parity);
    	printf("configured_parity=%d\n",parity);
				switch(parity){
					case 1:
						uart_config.parity = UART_PARITY_NONE;
						break;
					case 2:
						uart_config.parity = UART_PARITY_EVEN;
						break;
					case 3:
						uart_config.parity = UART_PARITY_ODD;
						break;
					default:
						printf("default parity = none\n");
						uart_config.parity = UART_PARITY_NONE;
						break;

				 }
    	printf("Enter the Stopbits for which you want to configure. Type 1 or 2\n");
    	printf("1. One\n");
    	printf("2. Two\n");
	    printf("Default. one\n>");
    	scanf("%d",&stopbits);
    	printf("configured_stopbits=%d\n",stopbits);

				switch(stopbits){
				   case 1:
						uart_config.stop_bits = UART_STOPBITS_ONE;
						break;
				   case 2:
						uart_config.stop_bits = UART_STOPBITS_TWO;
						break;
				   default:
						//printf("default stop bit = one\n");
				uart_config.stop_bits = UART_STOPBITS_ONE;
						break;

				}

    	printf("Select flow control\n");
        printf("1. Disable\n");
        printf("2. Enable\n");
    	printf("Default is Disable\n>");
        scanf("%d",&flow_ctrl);
        printf("confi_flowcontrol=%d\n",flow_ctrl);

				switch(flow_ctrl){
				   case 1:
						uart_config.flow_ctrl = UART_FLOW_CTRL_DIS;
						break;
				   case 2:
						uart_config.flow_ctrl = UART_FLOW_CTRL_ENA;
						break;
				   default:
						uart_config.flow_ctrl = UART_FLOW_CTRL_DIS;
						break;

				}

        printf("Select IO CLK multiplier\n");
        printf("1. 2X\n");
        printf("2. 3X\n");
        printf("3. 4X\n");
        printf("Default is 2X\n>");
        scanf("%d",&clk);
        printf("configured_clk=%d\n",clk);

            	switch(clk){
            	    case 1:
            	        uart_config.clk = UART_IOCLK_2X;
            	        break;
            	    case 2:
            	    	uart_config.clk = UART_IOCLK_3X;
            	    	break;
        		    case 3:
            	    	uart_config.clk = UART_IOCLK_4X;
            	    	break;
            	    default:
        		        uart_config.clk = UART_IOCLK_4X;
            	        break;

            	}

  /*  	printf("Enter the LSB and the MSB for which you want to configure. Type 1 or 2\n");
    	printf("1. 0x1 - LSB\n");
    	printf("2. 0x0 - MSB\n");
	printf("Default. 0x1 - LSB\n>");
    	uint8_t lsb_msb;
    	scanf("%d",&lsb_msb);
    	switch(lsb_msb){
    	    case 1:
    	    	uart_config.lsb_first = 0x1;
    	    	break;
    	    case 2:
    	    	uart_config.lsb_first = 0x0;
    	    	break;
    	    default:
    	    	//printf("default = LSB\n");
		uart_config.lsb_first = 0x1;
    	    	break;

    	}
    	*/


        printf("Select the setup\n");
    	printf("1. Tranmit only\n");
		printf("2. Receive only\n");
    	printf("3. External loopback\n");
    	printf("Default. External loopback\n>");
    	scanf("%d",&setup);
    	printf("setupvalue=%d\n",setup);
				switch(setup){
					case 1:
						printf("Please ensure Tx is line is connected\n");
						ct_uart_test_1(uart_config,uartHandle);
						break;
					case 2:
						printf("Please ensure Rx is line is connected\n");
						  ct_uart_test_2(uart_config, uartHandle);
						break;
					case 3:
						printf("Please ensure internal loop back connection is made.\n");
						ct_uart_test_3(uart_config,uartHandle);
						break;
					case 4:
						printf("Please ensure external loop back connection is made.\n");
						ct_uart_test_4(uart_config,uartHandle);
						break;
					default:
						printf("Please ensure external loop back connection is made.\n");
						break;
				}
#if 0
    	//uart_config.clk = UART_BCLK;                           /*select the uart bclk clock*/
    	uart_config.intr_enable = UART_INTRDISABLE;            /*disable the uart interrupts*/

		switch(setup){
    	    case 1:
    	    		ct_uart_test_1(uart_config,uartHandle);
    	    		break;
    	    case 2:
    	    		ct_uart_test_2(uart_config, uartHandle);
    	    		break;
    	    case 3:
    	    		ct_uart_test_3(uart_config, uartHandle);
    	    		break;
    	    case 4:
    	    		ct_uart_test_3(uart_config, uartHandle);
    	    		break;
    	    default:
    	    		printf("Not supported setup\n");
    	    		break;
	}
#endif
	   printf("Do you want to continue. Press y or n\n>");
getchar();
  	}while('y'== getchar());

#endif



}




void ct_uart_test_1(UART_CONFIG_INFO uart_config,HAL_CT_HANDLE uartHandle)
{
	/*bool l_test_status = FAIL;*/
	uint32_t l_retcode;
	uint32_t i=0;

	uint8_t l_bufferTx[100]="ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";			//load this {'W'} data in to buffer when checking with interrupt
	UART_SEND_INFO l_uartSend;

		 //****** UART COnfigutation ****/

		 l_retcode = HAL_CT_uart_ioctl (uartHandle, HAL_CT_UART_CONFIG,(void*) &uart_config);

		   if (HAL_CT_SUCCESS != l_retcode)
		   {
		   	printf("HAL_CT_UART_CONFIG failed ... status = %d\n",l_retcode);
		   	return;
		   }

		 while(i<1)
		 {
			  l_uartSend.data = &l_bufferTx;
			  l_uartSend.bytesToSend =32;
			  l_retcode=HAL_CT_uart_ioctl (uartHandle, HAL_CT_UART_SEND,(void*) &l_uartSend);
              if (HAL_CT_SUCCESS != l_retcode)
			  {
					printf("HAL_CT_UART_SEND failed ... status = %x\n",l_retcode);
	          }
					printf("\n");
			  i++;
		  }

}


void ct_uart_test_2(UART_CONFIG_INFO uart_config,HAL_CT_HANDLE uartHandle)
{

	/*bool l_test_status = FAIL;*/
	uint8_t l_test_status = 0;
	uint32_t l_retcode=0;
	uint8_t i=0;
	UART_READ_INFO l_uartRead;
	UART_SEND_INFO l_uartSend;
	char baud[40], parity[40], stop[40], first_bit[40];
	uint32_t l_bufferRx[16]={0};
	 uint32_t l_bufferTx[8]={0x44434241, 0x48474645, 0x4c4b4a49, 0x504f4e4d, 0x54535251, 0x58575655, 0x31305a59, 0x35343332};

	l_retcode = HAL_CT_uart_ioctl (uartHandle, HAL_CT_UART_CONFIG,(void*) &uart_config);
    if (HAL_CT_SUCCESS != l_retcode)
    {
    	printf("HAL_CT_UART_CONFIG failed ... status = %d\n",l_retcode);
    }
	else
	{

		    /*Read data*/
            l_uartRead.bytesToRead = 8;
	    	l_uartRead.data = (uint8_t*)l_bufferRx;
		    l_retcode = HAL_CT_uart_ioctl (uartHandle, HAL_CT_UART_READ,(void*) &l_uartRead);
		    if (HAL_CT_SUCCESS != l_retcode)
		    {
		        printf("HAL_CT_UART_READ failed ... status = %d\n",l_retcode);
		    }
			else
			{
				if(l_uartRead.bytesRead != 8)
				{
					printf("HAL_CT_UART_READ partially passed, bytes read = %d\n",l_uartRead.bytesRead);
				}
    		    else
                {

					if (*l_bufferRx == *l_bufferTx)
					{

						l_test_status = 1;
					}
					else
					{
						/* Do nothing */
					}

                }
			}
		}
}

void ct_uart_test_3(UART_CONFIG_INFO uart_config,HAL_CT_HANDLE uartHandle)
{
	/*bool l_test_status = FAIL;*/
	uint8_t l_test_status = 0;
	uint32_t l_retcode=0;
	uint8_t i=0;
	UART_READ_INFO l_uartRead;
	UART_SEND_INFO l_uartSend;
	char baud[40], parity[40], stop[40], first_bit[40];
	uint32_t l_bufferRx[100]={0};

	l_retcode = HAL_CT_uart_ioctl (uartHandle, HAL_CT_UART_CONFIG,(void*) &uart_config);
    if (HAL_CT_SUCCESS != l_retcode)
    {
    	printf("HAL_CT_UART_CONFIG failed ... status = %d\n",l_retcode);
    }
	else
	{
      uint32_t l_bufferTx[8]={0x44434241, 0x48474645, 0x4c4b4a49, 0x504f4e4d, 0x54535251, 0x58575655, 0x31305a59, 0x35343332};

		    /*Read data*/
            l_uartRead.bytesToRead = 32;
	    	l_uartRead.data = (uint8_t *) l_bufferRx;
		    l_retcode = HAL_CT_uart_ioctl (uartHandle, HAL_CT_UART_READ,(void*) &l_uartRead);
		    if (HAL_CT_SUCCESS != l_retcode)
		    {
		        printf("HAL_CT_UART_READ failed ... status = %d\n",l_retcode);
		    }
			else
			{
				if(l_uartRead.bytesRead != 32)
				{
					printf("HAL_CT_UART_READ Partially passed, bytes read = %d\n",l_uartRead.bytesRead);
				}
    		    else
                {
					if (*l_bufferRx == *l_bufferTx)
					{

						l_test_status = 1;
					}
					else
					{
						/* Do nothing */
					}

                }
			}
		    l_uartSend.data = &l_bufferRx;
		  	l_uartSend.bytesToSend =l_uartRead.bytesRead-1; // Excluding Enter character
		  	usleep(100);
		  	l_retcode=HAL_CT_uart_ioctl(uartHandle, HAL_CT_UART_SEND,(void*) &l_uartSend);
		    if (HAL_CT_SUCCESS != l_retcode)
		  	{
		  		printf("HAL_CT_UART_SEND failed ... status = %x\n",l_retcode);
		  	 }
		  	printf("\n");
	}
}




    /*****************************************External loop back *************************************************/
    void ct_uart_test_4(UART_CONFIG_INFO uart_config,HAL_CT_HANDLE uartHandle)
    {
    	/*bool l_test_status = FAIL;*/
    	uint8_t l_test_status = 0;
    	uint32_t l_retcode=0;
    	uint8_t i=0;
    	UART_READ_INFO l_uartRead;
    	UART_SEND_INFO l_uartSend;
    	char baud[40], parity[40], stop[40], first_bit[40];
    	uint32_t l_bufferRx[100]={0};

    	uint8_t l_bufferTx[100]="123451234ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
    	 //****** UART COnfigutation ****/

    	 l_retcode = HAL_CT_uart_ioctl (uartHandle, HAL_CT_UART_CONFIG,(void*) &uart_config);

    	   if (HAL_CT_SUCCESS != l_retcode)
    	   {
    	   	printf("HAL_CT_UART_CONFIG failed ... status = %d\n",l_retcode);
    	   	return;
    	   }
    	   else
    	   {

    	 while(i<1)
    	 {
    		  l_uartSend.data = &l_bufferTx;
    		  l_uartSend.bytesToSend =31;
    		  l_retcode=HAL_CT_uart_ioctl (uartHandle, HAL_CT_UART_SEND,(void*) &l_uartSend);
             if (HAL_CT_SUCCESS != l_retcode)
    		  {
    				printf("HAL_CT_UART_SEND failed ... status = %x\n",l_retcode);
             }
    				printf("\n");
    		  i++;
    	  }


        //  uint32_t l_bufferTx[8]={0x44434241, 0x48474645, 0x4c4b4a49, 0x504f4e4d, 0x54535251, 0x58575655, 0x31305a59, 0x35343332};

    		    /*Read data*/
                l_uartRead.bytesToRead = 32;
    	    	l_uartRead.data = (uint8_t *)l_bufferRx;
    		    l_retcode = HAL_CT_uart_ioctl (uartHandle, HAL_CT_UART_READ,(void*) &l_uartRead);
    		    if (HAL_CT_SUCCESS != l_retcode)
    		    {
    		        printf("HAL_CT_UART_READ failed ... status = %d\n",l_retcode);
    		    }
    			else
    			{
    				if(l_uartRead.bytesRead != 32)
    				{
    					printf("HAL_CT_UART_READ Partially passed, bytes read = %d\n",l_uartRead.bytesRead);
    				}
        		    else
                    {
    					if (*l_bufferRx == *l_bufferTx)
    					{

    						l_test_status = 1;
    					}
    					else
    					{
    						/* Do nothing */
    					}

                    }
    			}

    		}
    }










