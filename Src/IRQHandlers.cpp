/**
  * @file    IRQHandlers.cpp
  * @author  
  * @version 
  * @date    2021
  * @brief   Contents the interrupts handlers 
  *          
  * 
  * @verbatim 
*/



#include "defines.h"

void USART2_IRQHandler()
{
	
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	// Resieve data by USART2
	{

		
		USART_ClearFlag(USART2, USART_IT_RXNE);		
		
	}	// End of (USART2 IT_RXNE) Handler
	
//	--------------------------------------------------------------------  //

	if (USART_GetITStatus(USART2, USART_IT_IDLE) != RESET) 
	// USART2 resiving is over and IDLE flag rised 
	{
	  
		
		USART_ClearFlag(USART2, USART_IT_IDLE);
	}	// End of (USART_IT_IDLE) Handler	
	
//	--------------------------------------------------------------------  //

	if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
	// Transive data from USART2 if TX is empty
	{
		
		USART_ClearFlag(USART2, USART_IT_TXE);
	}	// USART2_TXE
	
}	//End of (USART2_IRQHandler)	
	
//	--------------------------------------------------------------------  //


void TIM2_IRQHandler()
{	
	if ( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
	{
		
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	}	// TIM2 IT_Update End
	
	if ( TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET) 
	{	

		TIM_ClearFlag(TIM2, TIM_FLAG_CC1);
	}	// TIM2 IT_CC1 End
	
}	// TIM2_IRQHandler End

//	--------------------------------------------------------------------  //
	

void HardFault_Handler()
{
	
	NVIC_SystemReset();
}


//	--------------------------------------------------------------------  //







