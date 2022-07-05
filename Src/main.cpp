#include "defines.h"



int main(void)
{
  

	Clocks_Init();
	CRC_Unit_Init();
	SystemCoreClockUpdate();
	
	GPIO_Config();
	UART_Config();
	//Main_Timer_Init(TIM2);


	//Global Interrupt enable
	__enable_irq(); 

	//Nested Interrupt Vector Enable
	NVIC_EnableIRQ(USART2_IRQn);
	

	//Spetial Interrupt Enable
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);


	
	// Tread configuration
	typedef struct {
	   // you can use it as some kind of global variables
	} ThreadCfg;
	
	ThreadCfg Cfg_Thread1 = {};
		
	// RTOS Initialisation
	osKernelInitialize();

	// Threads creation
	osThreadId_t Thread_One_ID = osThreadNew (Thread_One, &Cfg_Thread1, NULL);
	
	osThreadId_t Thread_Two_ID = osThreadNew (Thread_Two, NULL, NULL);
	
	
	// Start RTOS
	osKernelStart();
	
	// osThreadYield() - switch treads
}



//}	// extern "C" ends

