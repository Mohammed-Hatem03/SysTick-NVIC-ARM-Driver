#include "SysTick.h"

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

/* Global variable to hold the address of the callback function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/*********************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): a_TimeInMilliSeconds - Time interval in milliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the SysTick timer with the specified time interval
 **********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG    = 0;        /* Disable the SysTick Timer */
    if ((a_TimeInMilliSeconds * 16000) > 0xFFFFFF)
    {
        /* Handle overflow: Set reload value to maximum */
        SYSTICK_RELOAD_REG = 0xFFFFFF;
    }
    else
    {
        SYSTICK_RELOAD_REG = ((a_TimeInMilliSeconds * 16000) - 1); /* Set the reload value for the timer */
    }
    SYSTICK_CURRENT_REG = 0;       /* Clear the current register value */

    /* Configure the SysTick Control Register
     * ENABLE = 1 (Enable SysTick Timer)
     * INTEN = 1 (Enable SysTick Interrupt)
     * CLK_SRC = 1 (Select System Clock as the clock source)
    */
    SYSTICK_CTRL_REG   |= 0x07;
}

/*********************************************************************
 * Service Name: SysTick_StartBusyWait
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): a_TimeInMilliSeconds - Time interval in milliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Starts the SysTick timer and performs a busy-wait delay
 **********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG    = 0;         /* Disable the SysTick Timer */
    if ((a_TimeInMilliSeconds * 16000) > 0xFFFFFF)
    {
        /* Handle overflow: Set reload value to maximum */
        SYSTICK_RELOAD_REG = 0xFFFFFF;
    }
    else
    {
        SYSTICK_RELOAD_REG = ((a_TimeInMilliSeconds * 16000) - 1); /* Set the reload value for the timer */
    }
    SYSTICK_CURRENT_REG = 0;        /* Clear the current register value */

    /* Configure the SysTick Control Register
     * ENABLE = 1 (Enable SysTick Timer)
     * INTEN = 0 (Disable SysTick Interrupt)
     * CLK_SRC = 1 (Select System Clock as the clock source)
     * */
    SYSTICK_CTRL_REG   |= 0x05;

    /* Wait until the COUNT flag is set, indicating the timer has reached zero */
    while(!(SYSTICK_CTRL_REG & (1<<SYSTICK_FLAG_BIT)));
}

/*********************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Asynchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Interrupt handler for the SysTick timer
 **********************************************************************/
void SysTick_Handler(void)
{
    if(g_callBackPtr != NULL_PTR)
    {
        /* Call the registered callback function */
        (*g_callBackPtr)();
    }
}

/*********************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Ptr2Func - Pointer to the callback function
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Registers a callback function to be called by the SysTick handler
 **********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void))
{
    g_callBackPtr = Ptr2Func;
}

/*********************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Stops the SysTick timer
 **********************************************************************/
void SysTick_Stop(void)
{
    SYSTICK_CTRL_REG &= ~(1<<SYSTICK_ENABLE_BIT); /* Disable the SysTick Timer */
}

/*********************************************************************
 * Service Name: SysTick_Start
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Starts the SysTick timer
 **********************************************************************/
void SysTick_Start(void)
{
    SYSTICK_CTRL_REG |= (1<<SYSTICK_ENABLE_BIT); /* Enable the SysTick Timer */
}

/*********************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Deinitializes the SysTick timer and clears all registers
 **********************************************************************/
void SysTick_DeInit(void)
{
    SYSTICK_CTRL_REG    = 0; /* Disable the SysTick Timer */
    SYSTICK_RELOAD_REG  = 0; /* Clear the reload register */
    SYSTICK_CURRENT_REG = 0; /* Clear the current register */
}
