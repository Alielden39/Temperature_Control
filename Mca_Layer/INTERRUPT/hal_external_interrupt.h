/* 
 * File:   hal_external_interrupt.h
 * Author: Alielden
 *
 * Created on October 9, 2023, 6:29 PM
 */

#ifndef HAL_EXTERNAL_INTERRUPT_H
#define	HAL_EXTERNAL_INTERRUPT_H

/* Section :  Includes */
#include "hal_interrupt_config.h"

 /* Section : Macros */


/* Section : Macros Functions */

/*************** INT0 ***********************/
#define EXT_INT0_ENABLE()               (INTCONbits.INT0IE    = 1  )
#define EXT_INT0_DISABLE()              (INTCONbits.INT0IE    = 0  )
#define EXT_INT0_ClearInterruptFlag()   (INTCONbits.INT0IF    = 0  )
#define EXT_INT0_InterruptRisingEdge()  (INTCON2bits.INTEDG0  = 1  )
#define EXT_INT0_InterruptFallingEdge() (INTCON2bits.INTEDG0  = 0  )

/*************** INT1 ***********************/
#define EXT_INT1_ENABLE()               (INTCON3bits.INT1IE    = 1 )
#define EXT_INT1_DISABLE()              (INTCON3bits.INT1IE    = 0 )
#define EXT_INT1_ClearInterruptFlag()   (INTCON3bits.INT1IF    = 0 )
#define EXT_INT1_InterruptRisingEdge()  (INTCON2bits.INTEDG1   = 1 )
#define EXT_INT1_InterruptFallingEdge() (INTCON2bits.INTEDG1   = 0 )

/*************** INT2 ***********************/
#define EXT_INT2_ENABLE()               (INTCON3bits.INT2IE    = 1 )
#define EXT_INT2_DISABLE()              (INTCON3bits.INT2IE    = 0 )
#define EXT_INT2_ClearInterruptFlag()   (INTCON3bits.INT2IF    = 0 )
#define EXT_INT2_InterruptRisingEdge()  (INTCON2bits.INTEDG2   = 1 )
#define EXT_INT2_InterruptFallingEdge() (INTCON2bits.INTEDG2   = 0 )

/****************** Priority *************************************/
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EXT_INT1_HighPriority()         (INTCON3bits.INT1IP    = 1 )
#define EXT_INT1_LowPriority()         (INTCON3bits.INT1IP    = 0 )

#define EXT_INT2_HighPriority()        (INTCON3bits.INT2IP    = 1 )
#define EXT_INT2_LowPriority()         (INTCON3bits.INT2IP    = 0 )

#endif
///////////////////////////////////////////////////////////////////

/****************** OnChange *************************************/

#define EXT_OnChange_RB_ENABLE()             (INTCONbits.RBIE = 1 )
#define EXT_OnChange_RB_DISABLE()            (INTCONbits.RBIE = 0 )
#define EXT_OnChange_RB_ClearInterruptFlag() (INTCONbits.RBIF = 0 )

/*************** Priority ***************************************/
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EXT_OnChange_RB_HighPriority()  (INTCON2bits.RBIP = 1 )
#define EXT_OnChange_RB_LowPriority()   (INTCON2bits.RBIP = 0 )

#endif
///////////////////////////////////////////////////////////////////
/* Section : Data type Declaration */

typedef enum {
    EXTERNAL_INT0 = 0 ,
    EXTERNAL_INT1 ,
    EXTERNAL_INT2
}INTx_pin;

typedef enum 
{
    INTERRUPT_FALLING_EDGE = 0 ,
    INTERRUPT_RISING_EDGE        
}Interrupt_edge;

typedef enum
{
    LOW_PRIORITY = 0 ,
    HIGH_PRIORITY
}Interrupt_priority;

typedef struct 
{
    void (*interrupt_call_back)(void) ;
    pin_config_t       pin ;
    INTx_pin           int_number ;
    Interrupt_edge     edge ;
    Interrupt_priority priority ;
}interrupt_INTx_t;

typedef struct 
{
    void (*interrupt_call_back_High)(void) ;
    void (*interrupt_call_back_Low)(void) ;
    pin_config_t       pin ;
    Interrupt_priority priority ;
}interrupt_RB_t;

/* Section : Functions Declaration */

Std_ReturnType Interrupt_INTx_Intializing(interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_INTx_Deintializing(interrupt_INTx_t *int_obj);

Std_ReturnType Interrupt_RB_Intializing(interrupt_RB_t *int_obj);
Std_ReturnType Interrupt_RB_Deintializing(interrupt_RB_t *int_obj);

#endif	/* HAL_EXTERNAL_INTERRUPT_H */

