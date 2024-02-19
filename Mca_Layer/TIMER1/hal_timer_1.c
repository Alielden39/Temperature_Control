
/* 
 * File:   hal_timer1.c
 * Author: Alielden
 *
 * Created on February 1, 2024, 4:38 PM
 */
#include "hal_timer_1.h"

#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TIMER1_InterruptHandler)(void) = NULL ;   
#endif

static uint8 Timer1_Preload = 0 ;

static Std_ReturnType Timer1_select_mode(timer1_t *timer1);


/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType Timer1_init(timer1_t *timer1)
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == timer1 ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* Disable Timer */
        TIMER1_DISABLE() ;
        /* Pre scaler Configure  */
        TIMER1_PRESCALER_SELECT(timer1->prescaler_value);
        /* Mode Configure  */
        Timer1_select_mode(timer1) ;
        /* Pre load value */
        TMR1H = ( (timer1->Timer1_Preload_Value)>>8 ) ;
        TMR1L =   (uint8)(timer1->Timer1_Preload_Value) ;
        Timer1_Preload = timer1->Timer1_Preload_Value   ;
        /* Enable Interrupt */     
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_CLR_FLAG();
        TIMER1_InterruptHandler = timer1->timer1_call_back ;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE  
        INTERRUPT_InterruptPriorityEnable();
        if(timer1->priority == HIGH_PRIORITY )
        {
            INTERRUPT_GloblsInterruptHighEnable();
            TIMER1_INTERRUPT_HIGH_PRIORITY();
        }
        else if(timer1->priority == LOW_PRIORITY)
        {
            INTERRUPT_GloblsInterruptLowEnable();
            TIMER1_INTERRUPT_LOW_PRIORITY();
        }
#else
    INTCONbits.PEIE = 1 ;
    INTERRUPT_GlobalInterruptEnable();
#endif     
#endif
        /* Enable Timer */
        TIMER1_ENABLE();
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
Std_ReturnType Timer1_Deinit(timer1_t *timer1)
{
   Std_ReturnType ret = STD_OK ;
    if( NULL == timer1 )
    {
        ret = STD_NOT_OK ;
    }
    else{
         TIMER1_DISABLE();
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
       TIMER1_INTERRUPT_DISABLE(); 
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
Std_ReturnType Timer1_Read_value(timer1_t *timer1 , uint16 *value)
{
    Std_ReturnType ret = STD_OK ;
    uint8 l_tmr1l = 0 , l_tmr1h = 0 ;
    if( (NULL == timer1)  ||  (NULL ==value) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        l_tmr1l = TMR1L ;
        l_tmr1h = TMR1H ;
        *value = (l_tmr1h<<8) + (l_tmr1l) ;
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
Std_ReturnType Timer1_Write_value(timer1_t *timer1 , uint16 value)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == timer1 )
    {
        ret = STD_NOT_OK ;
    }
    else{
        TMR1H = ( value>>8 ) ;
        TMR1L =   (uint8)(value) ; 
    }
    return ret ;
}


void Timer1_ISR(void)
{
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    TIMER1_INTERRUPT_CLR_FLAG();
    
    /* Code */
    TMR1H = ( (Timer1_Preload)>>8 ) ;
    TMR1L =   (uint8)(Timer1_Preload) ;
    
    if(TIMER1_InterruptHandler)
    {
        TIMER1_InterruptHandler();
    }
#endif
}




static Std_ReturnType Timer1_select_mode(timer1_t *timer1)
{
       if( timer1->timer1_mode == TIMER1_TIMEr_MODE )
        {
            TIMER1_TIMER_MODE();
        }
        else if( timer1->timer1_mode == TIMER1_COUNTEr_MODE )
        {
            TIMER1_COUNTER_MODE();
            if( timer1->counter_mode == TIMER1_SYN_COUNTER_MODE )
            {
                TIMER1_SYNC_COUNTER_MODE();
            }
            else if( timer1->counter_mode == TIMER1_ASYN_COUNTER_MODE )
            {
                TIMER1_ASYNC_COUNTER_MODE();
            }
        }
}