/*******************************************************************************
Copyright (c) 2021 - Cientra All Rights Reserved.
This software is proprietary & confidential to Cientra
and its licensor.
********************************************************************************
* file name   : hal_ct_porting.h
* description : Contains data required for the user reference
* version     : 1.0
* date        : 31-May-2021
* author      : Jaijith
*******************************************************************************/

//#include <asm/io.h>
#include "../../common/src/hal_ct_porting.h"
#include "../../common/src/hal_ct_common.h"

#ifdef OS_BAREMETAL
/**
  * @brief  ReadRegister8  Read the 8 bit data from register.
  * @param  addr  contain the address of specified register.
  * @retval uint8_t
  */
uint8_t ReadRegister8(uint32_t addr)
{
    return (*(volatile uint8_t*) addr);
}
/**
  * @brief  ReadRegister32  Read the 32 bit data from register.
  * @param  addr  contain the address of specified register.
  * @retval uint32_t
  */
uint32_t ReadRegister32(uint32_t addr)
{
    return (*(volatile uint32_t*) addr);
}
/**
  * @brief  WriteRegister64  write 64 bits of data to register.
  * @param  data  contain data which we want to write into the perticular address of register.
  *@param   addr  contain the address of specified register.
  * @retval None
  */

/**
  * @brief  WriteRegister32  Read the 32 bit data from register.
  * @param  data  contain data which we want to write into the perticular address of register.
  *@param   addr  contain the address of specified register.
  * @retval None
  */
void WriteRegister32(uint32_t addr,uint32_t data)
{
    (*(volatile uint32_t*) addr) = data;
}
/**
  * @brief  WriteRegister8  Write the 8 bit data into specific register.
  * @param  data  contain data which we want to write into the perticular address of register.
  *@param   addr  contain the address of specified register.
  * @retval None
  */

void WriteRegister8(uint32_t addr,uint8_t data)
{
    (*(volatile uint8_t*) addr) = data;
}
#endif

#ifdef OS_LINUX

uint32_t ReadRegister32(uint32_t addr)
{
    // pr_err("PHYSICAl ADDR = %x\n", addr);
	uint32_t l_value;//l_value
	void *l_ptr;//l_ptr
	//pr_err("Before ioremap\n");
	l_ptr = ioremap(addr, 4);
	//pr_err("After ioremap\n");
	l_value = ioread32(l_ptr);
	//pr_err("After ioread32\n");
        iounmap(l_ptr);
	//pr_err("After iounmap\n");
	return l_value;
}

void WriteRegister32(uint32_t addr,uint32_t data)
{
	void *l_ptr;//l_ptr
    //pr_err("PHYSICAl ADDR = %x, DATA = %d\n", addr, data);
	l_ptr = ioremap(addr, 4);
	iowrite32(data,l_ptr);
	iounmap(l_ptr);
}



uint8_t ReadRegister8(uint32_t addr)
{
	uint8_t l_value;//l_value
	void *l_ptr;//l_ptr
	l_ptr = ioremap(addr, 4);
	l_value = ioread8(l_ptr);
	iounmap(l_ptr);
	//pr_err("RX DATA = %x\n",value);
	return l_value;
}
#endif



