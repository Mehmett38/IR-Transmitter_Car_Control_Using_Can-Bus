/*
 * IRF.c
 *
 *  Created on: May 5, 2023
 *      Author: Mehmet Dincer
 */


#include "IRF.h"

Irf_STATE irfState;
uint32_t tempCode;
uint8_t bitIndex;
uint8_t cmd;
uint8_t cmdli;
uint32_t code;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  if(GPIO_Pin == IRF_IRQ_Pin)
  {
	  if (__HAL_TIM_GET_COUNTER(&htim1) > 8000)
	  {
		  tempCode = 0;
		  bitIndex = 0;
	  }
	  else if (__HAL_TIM_GET_COUNTER(&htim1) > 1700)
	  {
		  tempCode |= (1UL << (31-bitIndex));   // write 1
		  bitIndex++;
	  }
	  else if (__HAL_TIM_GET_COUNTER(&htim1) > 1000)
	  {
		  tempCode &= ~(1UL << (31-bitIndex));  // write 0
		  bitIndex++;
	  }
	  if(bitIndex == 32)
	  {
		  cmdli = ~tempCode; // Logical inverted last 8 bits
		  cmd = tempCode >> 8; // Second last 8 bits
		  if(cmdli == cmd) // Check for errors
		  {
			  code = tempCode; // If no bit errors
			  irfState.irfFlag = IRF_FLAG_ON;
			  irfState.code = tempCode;
			  // Do your main work HERE
		  }
		  bitIndex = 0;
	  }
	  __HAL_TIM_SET_COUNTER(&htim1, 0);
  }
}


void IRF_Init()
{
	HAL_TIM_Base_Start(&htim1);
}
