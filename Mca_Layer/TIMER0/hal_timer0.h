/* 
 * File:   hal_timer0.h
 * Author: Alielden
 *
 * Created on November 5, 2023, 1:15 AM
 */

#ifndef HAL_TIMER0_H
/* Section :  Includes */

#include "../INTERRUPT/hal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_timer0_cfg.h"

 /* Section : Macros */

#define PRESCALER_ENABLE  0
#define PRESCALER_DISABLE 1

#define RISING_EDGE   0
#define FALLING_EDGE  1

#define TIMER_MODE   0
#define COUNTER_MODE 1

#define SELECT_16_BIT_CONFIG  0
#define SELECT_8_BIT_CONFIG   1

/* Section : Macros Functions */

#define TIMER0_DISABLE()             (T0CONbits.TMR0ON=0)
#define TIMER0_ENABLE()              (T0CONbits.TMR0ON=1)

#define TIMER0_PRESCALER_ENABLE()    (T0CONbits.PSA=0)
#define TIMER0_PRESCALER_DISABLE()   (T0CONbits.PSA=1)

#define TIMER0_RISING_EDGE()         (T0CONbits.T0SE=0)
#define TIMER0_FALLING_EDGE()        (T0CONbits.T0SE=1)

#define TIMER0_TIMER_MODE()          (T0CONbits.T0CS=0)
#define TIMER0_COUNTER_MODE()        (T0CONbits.T0CS=1)

#define TIMER0_16BIT_CFG()           (T0CONbits.T08BIT=0)
#define TIMER0_8BIT_CFG()            (T0CONbits.T08BIT=1)

/* Section : Data type Declaration */

typedef enum 
{
    timer0_prescale_div_2 = 0 ,
    timer0_prescale_div_4     ,
    timer0_prescale_div_8     ,
    timer0_prescale_div_16    ,
    timer0_prescale_div_32    ,
    timer0_prescale_div_64    ,
    timer0_prescale_div_128   ,
    timer0_prescale_div_256   ,
}timer0_prescaler_select;

typedef struct 
{
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*timer0_call_back)(void) ;
    uint8 priority ; 
#endif
   uint8 prescaler_enable : 1  ;
   uint8 source_edge : 1 ;
   uint8 clk_source : 1 ;
   uint8 bit_select : 1 ;
   uint16 Timer0_Preload_Value ;
   timer0_prescaler_select prescaler_value ;
}timer0_t;


/* Section : Functions Declaration */

Std_ReturnType Timer0_init(timer0_t *timer0);
Std_ReturnType Timer0_Deinit(timer0_t *timer0);
Std_ReturnType Timer0_Read_value(timer0_t *timer0 , uint16 *value);
Std_ReturnType Timer0_Write_value(timer0_t *timer0 , uint16 value);

#endif	/* HAL_TIMER0_H */

