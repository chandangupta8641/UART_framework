/*******************************************************************************
Copyright (c) 2021 - Cientra All Rights Reserved.
This software is proprietary & confidential to Cientra
and its licensor.
********************************************************************************
* file name   : hal_ct_common.h
* description : Contains data required for the user reference
* version     : 1.0
* date        : 31-May-2021
* author      : Jaijith
*******************************************************************************/
#ifndef HAL_CT_COMMON_H_
#define HAL_CT_COMMON_H_

#define MUL_FACTOR_ADDR                         0x04

/**
  * @brief  ReadRegister8  Read the 8 bit data from register.
  * @param  addr  contain the address of specified register.              
  * @retval uint8_t
  */
uint8_t ReadRegister8(uint32_t addr);

/**
  * @brief  ReadRegister32  Read the 32 bit data from register.
  * @param  addr  contain the address of specified register.              
  * @retval uint32_t
  */
uint32_t ReadRegister32(uint32_t addr);



/**
  * @brief  WriteRegister32  Read the 32 bit data from register.
  * @param  data  contain data which we want to write into the perticular address of register.    
  *@param   addr  contain the address of specified register.           
  * @retval None
  */
void WriteRegister32(uint32_t addr,uint32_t data);

/**
  * @brief  WriteRegister8  Write the 8 bit data into specific register.
  * @param  data  contain data which we want to write into the perticular address of register.    
  *@param   addr  contain the address of specified register.           
  * @retval None
  */
//void WriteRegister64(uint32_t addr,uint64_t data);

void WriteRegister8(uint32_t addr,uint8_t data);


#endif /* HAL_CT_COMMON_H_ */
