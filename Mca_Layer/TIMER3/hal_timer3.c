
/* 
 * File:   hal_timer3.c
 * Author: Alielden
 *
 * Created on February 2, 2024, 4:51 PM
 */

#include "hal_timer3.h"

#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TIMER3_InterruptHandler)(void) = NULL ;   
#endif

static uint8 Timer3_Preload = 0 ;

static Std_ReturnType Timer3_select_mode(timer3_t *timer3);



/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType Timer3_init(timer3_t *timer3)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == timer3 ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* Disable Timer */
        TIMER3_DISABLE() ;
        /* Pre scaler Configure  */
        TIMER3_PRESCALER_SELECT(timer3->prescaler_value);
        /* Mode Configure  */
        Timer3_select_mode(timer3) ;
        /* Pre load value */
        TMR3H = ( (timer3->Timer3_Preload_Value)>>8 ) ;
        TMR3L =   (uint8)(timer3->Timer3_Preload_Value) ;
        Timer3_Preload = timer3->Timer3_Preload_Value   ;
        /* Enable Interrupt */     
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_CLR_FLAG();
        TIMER3_InterruptHandler = timer3->timer3_call_back ;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE  
        INTERRUPT_InterruptPriorityEnable();
        if(timer3->priority == HIGH_PRIORITY )
        {
            INTERRUPT_GloblsInterruptHighEnable();
            TIMER3_INTERRUPT_HIGH_PRIORITY();
        }
        else if(timer3->priority == LOW_PRIORITY)
        {
            INTERRUPT_GloblsInterruptLowEnable();
            TIMER3_INTERRUPT_LOW_PRIORITY();
        }
#else
    INTCONbits.PEIE = 1 ;
    INTERRUPT_GlobalInterruptEnable();
#endif     
#endif
        /* Enable Timer */
        TIMER3_ENABLE();
    }
    return ret ;
    
}

/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType Timer3_Deinit(timer3_t *timer3)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == timer3 )
    {
        ret = STD_NOT_OK ;
    }
    else{
         TIMER3_DISABLE();
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
       TIMER3_INTERRUPT_DISABLE(); 
#endif
       
    }
    return ret ; 
}



/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType Timer3_Read_value(timer3_t *timer3 , uint16 *value)
{
     Std_ReturnType ret = STD_OK ;
    uint8 l_tmr3l = 0 , l_tmr3h = 0 ;
    if( (NULL == timer3)  ||  (NULL ==value) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        l_tmr3l = TMR3L ;
        l_tmr3h = TMR3H ;
        *value = (l_tmr3h<<8) + (l_tmr3l) ;
    }
    return ret ;
}


/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType Timer3_Write_value(timer3_t *timer3 , uint16 value)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == timer3 )
    {
        ret = STD_NOT_OK ;
    }
    else{
        TMR3H = ( value>>8 ) ;
        TMR3L =   (uint8)(value) ; 
    }
    return ret ;
}



void Timer3_ISR(void)
{
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    TIMER3_INTERRUPT_CLR_FLAG();
    
    /* Code */
    TMR3H = ( (Timer3_Preload)>>8 ) ;
    TMR3L =   (uint8)(Timer3_Preload) ;
    
    if(TIMER3_InterruptHandler)
    {
        TIMER3_InterruptHandler();
    }
#endif
}





static Std_ReturnType Timer3_select_mode(timer3_t *timer3)
{
       if( timer3->timer3_mode == TIMER3_TIMER )
        {
            TIMER3_TIMER_MODE();
        }
        else if( timer3->timer3_mode == TIMER3_COUNTER )
        {
            TIMER3_COUNTER_MODE();
            if( timer3->counter_mode == TIMER3_SYN_COUNTER_MODE )
            {
                TIMER3_SYNC_COUNTER_MODE();
            }
            else if( timer3->counter_mode == TIMER3_ASYN_COUNTER_MODE )
            {
                TIMER3_ASYNC_COUNTER_MODE();
            }
        }
}

