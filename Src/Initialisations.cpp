/**
  * @file    Initialisations.cpp
  * @author  
  * @version 
  * @date    2021
  * @brief   Initialisations and configurations of MC periphery
  *          
  * 
  * @verbatim 
*/



#include "defines.h"


void Clocks_Init(void)	// timing to flash
{
	FLASH->ACR = 0x00000704;// Latency = 4, enable PRFTEN, ICEN, DCEN
	RCC_DeInit();
	
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div4);
	RCC_PCLK2Config(RCC_HCLK_Div2);
	RCC_AdjustHSICalibrationValue(16);
	RCC_HSICmd(ENABLE);
	RCC_PLLConfig(RCC_PLLSource_HSI, 8, 168, 2, 4);	// Max Freq
	RCC_PLLCmd(ENABLE);
	while((RCC->CR & RCC_CR_PLLRDY) == 0){}
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource() != 0x08){}

}

void CRC_Unit_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	
}
//	--------------------------------------------------------------------  //

void GPIO_Config(void)
{
	
}

//	--------------------------------------------------------------------  //


void UART_Config(void)
{
	RCC_APB1PeriphClockCmd( 0						// synch UARTx with bus APB1
							| RCC_APB1Periph_USART2
//							| RCC_APB1Periph_USART3
//							| RCC_APB1Periph_UART4
//							| RCC_APB1Periph_UART5
//							| RCC_APB1Periph_UART7
//							| RCC_APB1Periph_UART8
							, ENABLE);

	/* configuration for GPIO pin to work as UARTx 
	   (in this example USART2 connects to Pin2 and Pin3 of port A, PA2 and PA3)
	   - alternative function of PA2 as TX of USART2
	   - alternative function of PA3 as RX of USART2
	   - clear init structure
	   - write PA2 and PA3 to init structure
	   - Mode = alternative function as USART
	   - apply settings
	*/
	
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	// Alternative function for PA2, PA3 (aka UART2)
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//	------------------------------------------------  //
	
	/* USARTx configured as follows:
	   - BaudRate = 9600 baud  
	   - Word Length = 8 Bits
	   - One Stop Bit
	   - No parity
	   - Hardware flow control disabled (RTS and CTS signals)
	   - Receive and transmit enabled
	*/
	
	USART_InitTypeDef	USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure);		
	USART_Cmd(USART2, ENABLE);

}

//	--------------------------------------------------------------------  //

void Main_Timer_Init(TIM_TypeDef* TIMx)
{
	if(TIMx == TIM2)	// 32 bit, 84 MHz
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	if(TIMx == TIM3)	// 16 bit, 84 MHz
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	if(TIMx == TIM4)	// 16 bit, 84 MHz
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	if(TIMx == TIM5)	// 32 bit, 84 MHz
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	if(TIMx == TIM12)	// 16 bit, 84 MHz
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
	if(TIMx == TIM13)	// 16 bit, 84 MHz
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	if(TIMx == TIM14)	// 16 bit, 84 MHz
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

	if(TIMx == TIM1)	// 16 bit, 168 MHz, PWM
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	if(TIMx == TIM8)	// 16 bit, 168 MHz, PWM
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	if(TIMx == TIM9)	// 16 bit, 168 MHz
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	if(TIMx == TIM10)	// 16 bit, 168 MHz
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
	if(TIMx == TIM11)	// 16 bit, 168 MHz
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);

	
	TIM_TimeBaseInitTypeDef 	TIM_InitStructure;
	
	TIM_TimeBaseStructInit(&TIM_InitStructure);
	TIM_InitStructure.TIM_Prescaler = 84-1;					// f(cnt) = 1 MHz
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 0xFFFFFFFF;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIMx, &TIM_InitStructure);	
	
	//uncomment, if you wont to start countiing right now
	//TIMx->CR1 |= TIM_CR1_CEN; 	

	
}

//	--------------------------------------------------------------------  //



//	--------------------------------------------------------------------  //



