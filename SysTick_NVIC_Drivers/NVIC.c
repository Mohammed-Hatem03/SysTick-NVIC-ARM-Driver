#include "NVIC.h"

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/


/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ to enable from the interrupt vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Enables the interrupt request for a specific IRQ number
 **********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    if((IRQ_Num <= 31))
    {
        NVIC_EN0_REG |= (1<<IRQ_Num);
    }
    else if(IRQ_Num <= 63)
    {
        NVIC_EN1_REG |= (1<<(IRQ_Num-32));
    }
    else if(IRQ_Num <= 95)
    {
        NVIC_EN2_REG |= (1<<(IRQ_Num-64));
    }
    else if(IRQ_Num <= 127)
    {
        NVIC_EN3_REG |= (1<<(IRQ_Num-96));
    }
    else if(IRQ_Num <= 138)
    {
        NVIC_EN4_REG |= (1<<(IRQ_Num-128));
    }
}

/*********************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ to disable from the interrupt vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Disables the interrupt request for a specific IRQ number
 **********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    if((IRQ_Num <= 31))
    {
        NVIC_DIS0_REG |= (1<<IRQ_Num);
    }
    else if(IRQ_Num <= 63)
    {
        NVIC_DIS1_REG |= (1<<(IRQ_Num-32));
    }
    else if(IRQ_Num <= 95)
    {
        NVIC_DIS2_REG |= (1<<(IRQ_Num-64));
    }
    else if(IRQ_Num <= 127)
    {
        NVIC_DIS3_REG |= (1<<(IRQ_Num-96));
    }
    else if(IRQ_Num <= 138)
    {
        NVIC_DIS4_REG |= (1<<(IRQ_Num-128));
    }
}

/*********************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): IRQ_Num - IRQ number to set priority for
 *                  IRQ_Priority - Priority value for the IRQ
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the priority for a specific IRQ number
 **********************************************************************/
void NVIC_SetPriorityIRQ(
        NVIC_IRQType IRQ_Num,
        NVIC_IRQPriorityType IRQ_Priority
)
{
    uint32 i = 0;
    uint32 NVIC_IRQ_Address = NVIC_PRI0_ADDRESS;
    uint32 *NVIC_IRQ_Priority_Address = NULL_PTR;
    uint32 count = 0;

    for (i=0 ; i<IRQ_Num ; i++ )
    {
        count++;
        if (count == 4 )
        {
            NVIC_IRQ_Address = NVIC_IRQ_Address + 4;
            count = 0;
        }
    }
    NVIC_IRQ_Priority_Address =  ((( uint32 *) NVIC_IRQ_Address));

    if (IRQ_Num % 4 == 0)
    {
        *NVIC_IRQ_Priority_Address = (*NVIC_IRQ_Priority_Address & INTA_PRIORITY_MASK) | (IRQ_Priority << INTA_PRIORITY_BITS_POS);
    }
    else if (IRQ_Num % 4 == 1)
    {
        *NVIC_IRQ_Priority_Address = (*NVIC_IRQ_Priority_Address & INTB_PRIORITY_MASK) | (IRQ_Priority << INTB_PRIORITY_BITS_POS);
    }
    else if (IRQ_Num % 4 == 2)
    {
        *NVIC_IRQ_Priority_Address = (*NVIC_IRQ_Priority_Address & INTC_PRIORITY_MASK) | (IRQ_Priority << INTC_PRIORITY_BITS_POS);
    }
    else if(IRQ_Num % 4 == 3)
    {
        *NVIC_IRQ_Priority_Address = (*NVIC_IRQ_Priority_Address & INTD_PRIORITY_MASK) | (IRQ_Priority << INTD_PRIORITY_BITS_POS);
    }

}

/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Exception_Num - Number of the exception to enable
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Enables a specific exception
 **********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    switch (Exception_Num)
    {

    case EXCEPTION_MEM_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL |= (1 << MEM_FAULT_ENABLE_BIT);
        break;

    case EXCEPTION_BUS_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL |= (1 << BUS_FAULT_ENABLE_BIT);
        break;

    case EXCEPTION_USAGE_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL |= (1 << USAGE_FAULT_ENABLE_BIT);
        break;
    }
}
/*********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Exception_Num - Number of the exception to disable
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Disables a specific exception
 **********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    switch (Exception_Num)
    {
    case EXCEPTION_MEM_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL &= ~(1 << MEM_FAULT_ENABLE_BIT);
        break;

    case EXCEPTION_BUS_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL &= ~(1 << BUS_FAULT_ENABLE_BIT);
        break;

    case EXCEPTION_USAGE_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL &= ~(1 << USAGE_FAULT_ENABLE_BIT);
        break;
    }
}

/*********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Exception_Num - Exception number to set priority for
 *                  Exception_Priority - Priority value for the exception
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the priority for a specific exception
 **********************************************************************/
void NVIC_SetPriorityException(
        NVIC_ExceptionType Exception_Num,
        NVIC_ExceptionPriorityType Exception_Priority)
{
    switch (Exception_Num)
    {
    case EXCEPTION_MEM_FAULT_TYPE:
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & MEM_FAULT_PRIORITY_MASK ) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
        break;

    case EXCEPTION_BUS_FAULT_TYPE:
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & BUS_FAULT_PRIORITY_MASK) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
        break;

    case EXCEPTION_USAGE_FAULT_TYPE:
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & USAGE_FAULT_PRIORITY_MASK) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
        break;

    case EXCEPTION_SVC_TYPE:
        NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & SVC_PRIORITY_MASK) | (Exception_Priority << SVC_PRIORITY_BITS_POS);
        break;

    case EXCEPTION_DEBUG_MONITOR_TYPE:
        NVIC_SYSTEM_PRI3_REG =(NVIC_SYSTEM_PRI3_REG & DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority<< DEBUG_MONITOR_PRIORITY_BITS_POS);
        break;

    case EXCEPTION_PEND_SV_TYPE:
        NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & PENDSV_PRIORITY_MASK) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
        break;

    case EXCEPTION_SYSTICK_TYPE:
        NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
        break;
    }
}
