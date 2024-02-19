/* 
 * File:   hal_timer3.h
 * Author: Alielden
 *
 * Created on February 2, 2024, 4:51 PM
 */

#ifndef HAL_TIMER3_H
/* Section :  Includes */

#include "../INTERRUPT/hal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"

 /* Section : Macros */

#define TIMER3_TIMER   0
#define TIMER3_COUNTER 1

#define TIMER3_SYN_COUNTER_MODE   0
#define TIMER3_ASYN_COUNTER_MODE  1 

#define TIMER3_PRESCALER_DIV_BY_1  0
#define TIMER3_PRESCALER_DIV_BY_2  1
#define TIMER3_PRESCALER_DIV_BY_4  2
#define TIMER3_PRESCALER_DIV_BY_8  3

#define TIMER3_RW_8_BIT            0           // 8 bit here not mean 8 bit mode but mean TMRL register could have anothher value  
#define TIMER3_RW_16_BIT           1 


/* Section : Macros Functions */

#define TIMER3_DISABLE()                         (T3CONbits.TMR3ON=0)
#define TIMER3_ENABLE()                          (T3CONbits.TMR3ON=1)

#define TIMER3_TIMER_MODE()                      (T3CONbits.TMR3CS=0)
#define TIMER3_COUNTER_MODE()                    (T3CONbits.TMR3CS=1)

#define TIMER3_SYNC_COUNTER_MODE()               (T3CONbits.T3SYNC=0)
#define TIMER3_ASYNC_COUNTER_MODE()              (T3CONbits.T3SYNC=1)

#define TIMER3_PRESCALER_SELECT(PRESCALER)     (T3CONbits.T3CKPS=PRESCALER)

#define TIMER3_RW_8_BIT_MODE()                        (T3CONbits.RD16=0) 
#define TIMER3_RW_16_BIT_MODE()                       (T3CONbits.RD16=1) 


/* Section : Data type Declaration */

typedef struct 
{
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*timer3_call_back)(void) ;
    uint8 priority ; 
#endif
   uint8 timer3_mode       : 1 ;
   uint8 counter_mode      : 1 ;
   uint8 timer3_rw         : 1 ;
   uint16 Timer3_Preload_Value ;
   uint8 prescaler_value ;
}timer3_t;


/* Section : Functions Declaration */
Std_ReturnType Timer3_init(timer3_t *timer3);
Std_ReturnType Timer3_Deinit(timer3_t *timer3);
Std_ReturnType Timer3_Read_value(timer3_t *timer3 , uint16 *value);
Std_ReturnType Timer3_Write_value(timer3_t *timer3 , uint16 value);

#endif	/* HAL_TIMER3_H */

