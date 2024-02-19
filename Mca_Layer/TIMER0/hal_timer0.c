/* 
 * File:   hal_timer0.?
 * Author: Alielden
 *
 * Created on November 5, 2023, 1:15 AM
 */

#include "hal_timer0.h"

#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TIMER0_InterruptHandler)(void) = NULL ;   
#endif

static uint8 Timer0_Preload = 0 ;

static Std_ReturnType Timer0_prescaler_cfg(timer0_t *timer0);
static Std_ReturnType Timer0_select_mode(timer0_t *timer0);
static Std_ReturnType Timer0_bit_select(timer0_t *timer0);

/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType Timer0_init(timer0_t *timer0)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == timer0 ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* Disable Timer */
        TIMER0_DISABLE() ;
        /* Pre scaler Configure  */
        Timer0_prescaler_cfg(timer0);
        /* Mode Configure  */
        Timer0_select_mode(timer0);
        /* Bit size select */
        Timer0_bit_select(timer0);
        /* Pre load value */
        TMR0H = ( (timer0->Timer0_Preload_Value)>>8 ) ;
        TMR0L =   (uint8)(timer0->Timer0_Preload_Value) ;
        Timer0_Preload = timer0->Timer0_Preload_Value ;
        /* Enable Interrupt */     
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_CLR_FLAG();
        TIMER0_InterruptHandler = timer0->timer0_call_back ;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE  
        INTERRUPT_InterruptPriorityEnable();
        if(timer0->priority == HIGH_PRIORITY )
        {
            INTERRUPT_GloblsInterruptHighEnable();
            TIMER0_INTERRUPT_HIGH_PRIORITY();
        }
        else if(timer0->priority == LOW_PRIORITY)
        {
            INTERRUPT_GloblsInterruptLowEnable();
            TIMER0_INTERRUPT_LOW_PRIORITY();
        }
#else
    INTCONbits.PEIE = 1 ;
    INTERRUPT_GlobalInterruptEnable();
#endif     
#endif
        /* Enable Timer */
        TIMER0_ENABLE();
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
Std_ReturnType Timer0_Deinit(timer0_t *timer0)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == timer0 ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
       TIMER0_DISABLE();
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
       TIMER0_INTERRUPT_DISABLE(); 
#endif
    }
    return ret ;
}

/**
 * 
 * @param timer0
 * @param value
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType Timer0_Read_value(timer0_t *timer0 , uint16 *value)
{
    Std_ReturnType ret = STD_OK ;
    uint8 l_tmr0l = 0 , l_tmr0h = 0 ;
    if( ( NULL == timer0 ) ||  ( NULL == value ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        l_tmr0l = TMR0L ;
        l_tmr0h = TMR0H ;
        *value = (l_tmr0h<<8) + (l_tmr0l) ;
    }
    return ret ;
}

/**
 * 
 * @param timer0
 * @param value
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType Timer0_Write_value(timer0_t *timer0 , uint16 value)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == timer0 ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        TMR0H = ( value>>8 ) ;
        TMR0L =   (uint8)(value) ; 
    }
    return ret ;
}

void Timer0_ISR(void)
{
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    TIMER0_INTERRUPT_CLR_FLAG();
    
    /* Code */
    TMR0H = ( (Timer0_Preload)>>8 ) ;
    TMR0L =   (uint8)(Timer0_Preload) ;
    
    if(TIMER0_InterruptHandler)
    {
        TIMER0_InterruptHandler();
    }
#endif
}

static Std_ReturnType Timer0_prescaler_cfg(timer0_t *timer0)
{
    if( timer0->prescaler_enable == PRESCALER_ENABLE )
        {
            TIMER0_PRESCALER_ENABLE();
            T0CONbits.T0PS = timer0->prescaler_value ;
        }
        else if(  timer0->prescaler_enable == PRESCALER_DISABLE )
        {
            TIMER0_PRESCALER_DISABLE();
        } 
}


static Std_ReturnType Timer0_select_mode(timer0_t *timer0)
{
        if( timer0->clk_source == TIMER_MODE )
        {
            TIMER0_TIMER_MODE() ;
        }
        else if(  timer0->clk_source == COUNTER_MODE )
        {
            TIMER0_COUNTER_MODE();
            if( timer0->source_edge == RISING_EDGE )
            {
                TIMER0_RISING_EDGE();
            }
            else if(  timer0->source_edge == FALLING_EDGE )
            {
                TIMER0_FALLING_EDGE();
            }
        }
}

static Std_ReturnType Timer0_bit_select(timer0_t *timer0)
{
    if( timer0->bit_select == SELECT_8_BIT_CONFIG )
    {
        TIMER0_8BIT_CFG();
    }
    else if( timer0->bit_select == SELECT_16_BIT_CONFIG )
    {
        TIMER0_16BIT_CFG() ;
    }
}

