#ifndef SYSTICK_H_
#define SYSTICK_H_

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "tm4c123gh6pm_registers.h"
#include "std_types.h"

/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/
#define SYSTICK_FLAG_BIT 16
#define SYSTICK_ENABLE_BIT 0

/*******************************************************************************
 *                           Function Declaration                              *
 *******************************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds);
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);
void SysTick_Handler(void);
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));
void SysTick_Stop(void);
void SysTick_Start(void);
void SysTick_DeInit(void);

#endif /* SYSTICK_H_ */
