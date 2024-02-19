/* 
 * File:   hal_timer2.c
 * Author: Alielden
 *
 * Created on February 2, 2024, 4:48 PM
 */

#include "hal_timer2.h"
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TIMER2_InterruptHandler)(void) = NULL ;   
#endif

static uint8 Timer2_Preload = 0 ;


/**
 * 
 * @param timer2
 * @return 
 */
Std_ReturnType Timer2_init(timer2_t *timer2)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == timer2 ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* Disable Timer */
        TIMER2_DISABLE() ;
        /* Pre scaler Configure  */
        TIMER2_PRESCALER_SELECT(timer2->prescaler_value);
        /* Post scaler Configure  */
        TIMER2_PPOSTSCALER_SELECT(timer2->postscaler_value);
        /* Pre load value */
        TMR2 = timer2->Timer2_Preload_Value ;
        Timer2_Preload = timer2->Timer2_Preload_Value   ;
        /* Enable Interrupt */     
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_INTERRUPT_CLR_FLAG();
        TIMER2_InterruptHandler = timer2->timer2_call_back ;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE  
        INTERRUPT_InterruptPriorityEnable();
        if(timer2->priority == HIGH_PRIORITY )
        {
            INTERRUPT_GloblsInterruptHighEnable();
            TIMER2_INTERRUPT_HIGH_PRIORITY();
        }
        else if(timer2->priority == LOW_PRIORITY)
        {
            INTERRUPT_GloblsInterruptLowEnable();
            TIMER2_INTERRUPT_LOW_PRIORITY();
        }
#else
    INTCONbits.PEIE = 1 ;
    INTERRUPT_GlobalInterruptEnable();
#endif     
#endif
        /* Enable Timer */
        TIMER2_ENABLE();
    }
    return ret ;
   
    
}


/**
 * 
 * @param timer2
 * @return 
 */
Std_ReturnType Timer2_Deinit(timer2_t *timer2)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == timer2 )
    {
        ret = STD_NOT_OK ;
    }
    else{
         TIMER2_DISABLE();
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
       TIMER2_INTERRUPT_DISABLE(); 
#endif       
    }
    return ret ; 
}


/**
 * 
 * @param timer2
 * @param value
 * @return 
 */
Std_ReturnType Timer2_Read_value(timer2_t *timer2 , uint16 *value)
{
    Std_ReturnType ret = STD_OK ;
    if( (NULL == timer2)  ||  (NULL ==value) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        *value = TMR2 ;
    }
    return ret ;
}


/**
 * 
 * @param timer2
 * @param value
 * @return 
 */
Std_ReturnType Timer2_Write_value(timer2_t *timer2 , uint16 value)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == timer2 )
    {
        ret = STD_NOT_OK ;
    }
    else{
        TMR2 = value ;
    }
    return ret ;
}



void Timer2_ISR(void)
{
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    TIMER2_INTERRUPT_CLR_FLAG();
    
    /* Code */
    TMR2 = Timer2_Preload ;
    
    if(TIMER2_InterruptHandler)
    {
        TIMER2_InterruptHandler();
    }
#endif
}