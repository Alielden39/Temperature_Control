/* 
 * File:   hal_timer1.h
 * Author: Alielden
 *
 * Created on February 1, 2024, 4:38 PM
 */

#ifndef HAL_TIMER1_H

/* Section :  Includes */

#include "../INTERRUPT/hal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"

 /* Section : Macros */

#define TIMER1_TIMEr_MODE   0
#define TIMER1_COUNTEr_MODE 1

#define TIMER1_SYN_COUNTER_MODE   0
#define TIMER1_ASYN_COUNTER_MODE  1

#define TIMER1_OSc_DISABLE         0
#define TIMER1_OSc_ENABLE          1  

#define TIMER1_PRESCALER_DIV_BY_1  0
#define TIMER1_PRESCALER_DIV_BY_2  1
#define TIMER1_PRESCALER_DIV_BY_4  2
#define TIMER1_PRESCALER_DIV_BY_8  3

#define TIMER1_RW_8_BIT            0           // 8 bit here not mean 8 bit mode but mean TMRL register could have anothher value  
#define TIMER1_RW_16_BIT           1 


/* Section : Macros Functions */
#define TIMER1_DISABLE()                         (T1CONbits.TMR1ON=0)
#define TIMER1_ENABLE()                          (T1CONbits.TMR1ON=1)

#define TIMER1_TIMER_MODE()                      (T1CONbits.TMR1CS=0)
#define TIMER1_COUNTER_MODE()                    (T1CONbits.TMR1CS=1)

#define TIMER1_SYNC_COUNTER_MODE()               (T1CONbits.T1SYNC=0)
#define TIMER1_ASYNC_COUNTER_MODE()              (T1CONbits.T1SYNC=1)

#define TIMER1_OSC_DISABLE()                     (T1CONbits.T1OSCEN=0)
#define TIMER1_OSC_ENABLE()                      (T1CONbits.T1OSCEN=1)

#define TIMER1_PRESCALER_SELECT(PRESCALER)     (T1CONbits.T1CKPS=PRESCALER)

#define TIMER1_RW_8_BIT_MODE()                        (T1CONbits.RD16=0) 
#define TIMER1_RW_16_BIT_MODE()                       (T1CONbits.RD16=1) 

/* Section : Data type Declaration */

typedef struct 
{
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*timer1_call_back)(void) ;
    uint8 priority ; 
#endif
   uint8 timer1_mode       : 1 ;
   uint8 counter_mode      : 1 ;
   uint8 timer1_osc        : 1 ;
   uint8 timer1_rw         : 1 ;
   uint16 Timer1_Preload_Value ;
   uint8 prescaler_value ;
}timer1_t;



/* Section : Functions Declaration */
Std_ReturnType Timer1_init(timer1_t *timer1);
Std_ReturnType Timer1_Deinit(timer1_t *timer1);
Std_ReturnType Timer1_Read_value(timer1_t *timer1 , uint16 *value);
Std_ReturnType Timer1_Write_value(timer1_t *timer1 , uint16 value);


#endif	/* HAL_TIMER1_H */


