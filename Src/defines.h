/**
  * @file    defines.h
  * @author  
  * @version 
  * @date    2021
  * @brief   Here you can define functions, global variables and constants, 
  *          structures, classes e.t.c.
  * 		 and other necessary includes
  * @verbatim 
*/

#ifndef DEFINES_H
#define DEFINES_H

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include <rtx_os.h>

//	----------------------------  //
//  	Init/Config functions	  //
void Clocks_Init(void);
void CRC_Unit_Init(void);
void GPIO_Config(void);
void UART_Config(void);
void Main_Timer_Init(TIM_TypeDef* TIMx);


//	----------------------------  //
//  	Threads defining		  //
void Thread_One (void *argument);
void Thread_Two (void *argument);


#endif	// (DEFINES_H)

















