/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC.h
 *
 * Description: Header file for the ARM Cortex M4 NVIC driver
 *
 * Author: Mohamed Tarek (Edges For Training)
 *
 *******************************************************************************/

#ifndef NVIC_H_
#define NVIC_H_

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "std_types.h"

#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/
#define MAX_BIT_ENABLE_1    32
#define MAX_BIT_ENABLE_2    64
#define MAX_BIT_ENABLE_3    96
#define MAX_BIT_ENABLE_4    128

#define NVIC_PRI0_ADDRESS   0xE000E400

#define INTA_PRIORITY_MASK              0xFFFFFF1F
#define INTA_PRIORITY_BITS_POS          5

#define INTB_PRIORITY_MASK              0xFFFF1FFF
#define INTB_PRIORITY_BITS_POS          13

#define INTC_PRIORITY_MASK              0xFF1FFFFF
#define INTC_PRIORITY_BITS_POS          21

#define INTD_PRIORITY_MASK              0x1FFFFFFF
#define INTD_PRIORITY_BITS_POS          29

#define MEM_FAULT_PRIORITY_MASK              0x000000E0
#define MEM_FAULT_PRIORITY_BITS_POS          5
#define MEM_FAULT_ENABLE_BIT                 16


#define BUS_FAULT_PRIORITY_MASK              0x0000E000
#define BUS_FAULT_PRIORITY_BITS_POS          13
#define BUS_FAULT_ENABLE_BIT                 17

#define USAGE_FAULT_PRIORITY_MASK            0x00E00000
#define USAGE_FAULT_PRIORITY_BITS_POS        21
#define USAGE_FAULT_ENABLE_BIT               18


#define SVC_PRIORITY_MASK                    0xE0000000
#define SVC_PRIORITY_BITS_POS                29

#define DEBUG_MONITOR_PRIORITY_MASK          0x000000E0
#define DEBUG_MONITOR_PRIORITY_BITS_POS      5

#define PENDSV_PRIORITY_MASK                 0x00E00000
#define PENDSV_PRIORITY_BITS_POS             21

#define SYSTICK_PRIORITY_MASK                0xE0000000
#define SYSTICK_PRIORITY_BITS_POS            29

#define MEM_FAULT_ENABLE_MASK                0x00010000
#define BUS_FAULT_ENABLE_MASK                0x00020000
#define USAGE_FAULT_ENABLE_MASK              0x00040000

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")

/*******************************************************************************
 *                           Data Types Declarations                           *
 *******************************************************************************/
typedef uint8 NVIC_IRQType;

typedef uint8 NVIC_IRQPriorityType;

typedef enum
{
    EXCEPTION_RESET_TYPE,
    EXCEPTION_NMI_TYPE,
    EXCEPTION_HARD_FAULT_TYPE,
    EXCEPTION_MEM_FAULT_TYPE,
    EXCEPTION_BUS_FAULT_TYPE,
    EXCEPTION_USAGE_FAULT_TYPE,
    EXCEPTION_SVC_TYPE,
    EXCEPTION_DEBUG_MONITOR_TYPE,
    EXCEPTION_PEND_SV_TYPE,
    EXCEPTION_SYSTICK_TYPE
}NVIC_ExceptionType;

typedef uint8 NVIC_ExceptionPriorityType;

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num);

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num);

void NVIC_SetPriorityIRQ(
        NVIC_IRQType IRQ_Num,
        NVIC_IRQPriorityType IRQ_Priority
);

void NVIC_EnableException(NVIC_ExceptionType Exception_Num);

void NVIC_DisableException(NVIC_ExceptionType Exception_Num);

void NVIC_SetPriorityException(
        NVIC_ExceptionType Exception_Num,
        NVIC_ExceptionPriorityType Exception_Priority
);



/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/

#endif /* NVIC_H_ */
