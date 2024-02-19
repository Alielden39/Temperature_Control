/* 
 * File:   hal_timer2.h
 * Author: Alielden
 *
 * Created on February 2, 2024, 4:48 PM
 */

#ifndef HAL_TIMER2_H

/* Section :  Includes */

#include "../INTERRUPT/hal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"

 /* Section : Macros */

#define TIMER2_PRESCALER_DIV_BY_1   0
#define TIMER2_PRESCALER_DIV_BY_4   1
#define TIMER2_PRESCALER_DIV_BY_16  2

/* Section : Macros Functions */

#define TIMER2_DISABLE()                         (T2CONbits.TMR2ON=0)
#define TIMER2_ENABLE()                          (T2CONbits.TMR2ON=1)

#define TIMER2_PRESCALER_SELECT(PRESCALER)     (T2CONbits.T2CKPS=PRESCALER)

#define TIMER2_PPOSTSCALER_SELECT(PPOSTSCALER)     (T2CONbits.TOUTPS=PPOSTSCALER)


/* Section : Data type Declaration */
typedef enum 
{
    timer2_postscaler_div_1 = 0 ,
    timer2_postscaler_div_2     ,
    timer2_postscaler_div_3     ,
    timer2_postscaler_div_4     ,
    timer2_postscaler_div_5     ,
    timer2_postscaler_div_6     ,
    timer2_postscaler_div_7     ,
    timer2_postscaler_div_8     ,
    timer2_postscaler_div_9     ,
    timer2_postscaler_div_10    ,
    timer2_postscaler_div_11    ,
    timer2_postscaler_div_12    ,
    timer2_postscaler_div_13    ,
    timer2_postscaler_div_14    ,
    timer2_postscaler_div_15    ,
    timer2_postscaler_div_16  
}timer0_postscaler_select;

typedef struct 
{
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*timer2_call_back)(void) ;
    uint8 priority ; 
#endif
   uint8 Timer2_Preload_Value ;
   uint8 prescaler_value ;
   uint8 postscaler_value ;
}timer2_t;


/* Section : Functions Declaration */

Std_ReturnType Timer2_init(timer2_t *timer2);
Std_ReturnType Timer2_Deinit(timer2_t *timer2);
Std_ReturnType Timer2_Read_value(timer2_t *timer2 , uint16 *value);
Std_ReturnType Timer2_Write_value(timer2_t *timer2 , uint16 value);



#endif	/* HAL_TIMER2_H */

