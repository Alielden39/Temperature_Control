/* 
 * File:   hal_external_interrupt.c
 * Author: Alielden
 *
 * Created on October 9, 2023, 6:29 PM
 */

#include "hal_external_interrupt.h"
static void (*Int0_InterruptHandler)(void) = NULL ;
static void (*Int1_InterruptHandler)(void) = NULL ;
static void (*Int2_InterruptHandler)(void) = NULL ;

static void (*RB4_InterruptHandler_High)(void) = NULL ;
static void (*RB4_InterruptHandler_Low)(void) = NULL ;
static void (*RB5_InterruptHandler_High)(void) = NULL ;
static void (*RB5_InterruptHandler_Low)(void) = NULL ;
static void (*RB6_InterruptHandler_High)(void) = NULL ;
static void (*RB6_InterruptHandler_Low)(void) = NULL ;
static void (*RB7_InterruptHandler_High)(void) = NULL ;
static void (*RB7_InterruptHandler_Low)(void) = NULL ;

static Std_ReturnType Interrupt_INTx_Enable(interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_init(interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(interrupt_INTx_t *int_obj);

static Std_ReturnType INTx_SetInterruptHandler(interrupt_INTx_t *int_obj);
static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void));

static Std_ReturnType Interrupt_RBx_Enable(interrupt_RB_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(interrupt_RB_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_init(interrupt_RB_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(interrupt_RB_t *int_obj);

static Std_ReturnType RBx_SetInterruptHandler(interrupt_RB_t *int_obj);
static Std_ReturnType RB4_SetInterruptHandler_High(void(*InterruptHandler)(void));
static Std_ReturnType RB4_SetInterruptHandler_Low(void(*InterruptHandler)(void));
static Std_ReturnType RB5_SetInterruptHandler_High(void(*InterruptHandler)(void));
static Std_ReturnType RB5_SetInterruptHandler_Low(void(*InterruptHandler)(void));
static Std_ReturnType RB6_SetInterruptHandler_High(void(*InterruptHandler)(void));
static Std_ReturnType RB6_SetInterruptHandler_Low(void(*InterruptHandler)(void));
static Std_ReturnType RB7_SetInterruptHandler_High(void(*InterruptHandler)(void));
static Std_ReturnType RB7_SetInterruptHandler_Low(void(*InterruptHandler)(void));

static Std_ReturnType Clear_IF_INTx(interrupt_INTx_t *int_obj);
static Std_ReturnType Clear_IF_RBx(interrupt_RB_t *int_obj);



/**
 * 
 * @param int_obj
* @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType Interrupt_INTx_Intializing(interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        ret = Interrupt_INTx_Disable(int_obj);          // interrupt disable
        ret = Clear_IF_INTx(int_obj);          
        #ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        ret = Interrupt_INTx_Priority_init(int_obj); 
        #endif // interrupt configure
        ret = Interrupt_INTx_Edge_Init(int_obj) ;
        ret = Interrupt_INTx_Pin_Init(int_obj) ;
        ret = INTx_SetInterruptHandler(int_obj);           // interrupt call back set
        ret = Interrupt_INTx_Enable(int_obj) ;              // interrupt enable
    }
        
    return ret ;
}

void INT0_ISR(void)
{
    /************ clear interrupt flag ********/
    EXT_INT0_ClearInterruptFlag() ; 
    
    /*******code**********/
    
    /************** CALL BACK ************/
    if(Int0_InterruptHandler)
    {
        Int0_InterruptHandler() ;
    }
}
void INT1_ISR(void)
{
    /************ clear interrupt flag ********/
    EXT_INT1_ClearInterruptFlag() ; 
    
    /*******code**********/
    
    /************** CALL BACK ************/
    if(Int1_InterruptHandler)
    {
        Int1_InterruptHandler() ;
    }
}
void INT2_ISR(void)
{
    /************ clear interrupt flag ********/
    EXT_INT2_ClearInterruptFlag() ; 
    
    /*******code**********/
    
    /************** CALL BACK ************/
    if(Int2_InterruptHandler)
    {
        Int2_InterruptHandler() ;
    }
}


/**
 * 
 * @param int_obj
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType Interrupt_INTx_Deintializing(interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        ret = Interrupt_INTx_Disable(int_obj);
    }
        
    return ret ;
}

/**
 * '
 * @param int_obj
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType Interrupt_RB_Intializing(interrupt_RB_t *int_obj)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        ret = Interrupt_RBx_Disable(int_obj);          // interrupt enable
        ret = Clear_IF_RBx(int_obj);          
        #ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_InterruptPriorityEnable();
        if( (int_obj->priority == LOW_PRIORITY) )
        {
            INTERRUPT_GloblsInterruptLowEnable();
            EXT_OnChange_RB_LowPriority();
        }
        else if((int_obj->priority ==HIGH_PRIORITY))
        {
            INTERRUPT_GloblsInterruptHighEnable();
            EXT_OnChange_RB_HighPriority();
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif // interrupt configure
        ret = Interrupt_RBx_Pin_Init(int_obj) ;
        ret = RBx_SetInterruptHandler(int_obj) ;          // interrupt call back set
        ret = Interrupt_RBx_Enable(int_obj) ;              // interrupt enable
    }
        
    return ret ;
}


/**
 * 
 * @param int_obj
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */


void RB4_ISR_High(void)
{
    /************ clear interrupt flag ********/
    EXT_OnChange_RB_ClearInterruptFlag() ; 
    
    /*******code**********/
    
    /************** CALL BACK ************/
    if(RB4_InterruptHandler_High)
    {
        RB4_InterruptHandler_High() ;
    }
}
void RB4_ISR_Low(void)
{
    /************ clear interrupt flag ********/
    EXT_OnChange_RB_ClearInterruptFlag() ; 
    
    /*******code**********/
    
    /************** CALL BACK ************/
    if(RB4_InterruptHandler_Low)
    {
        RB4_InterruptHandler_Low() ;
    }
}

void RB5_ISR_High(void)
{
    /************ clear interrupt flag ********/
    EXT_OnChange_RB_ClearInterruptFlag() ; 
    
    /*******code**********/
    
    /************** CALL BACK ************/
    if(RB5_InterruptHandler_High)
    {
        RB5_InterruptHandler_High() ;
    }
}

void RB5_ISR_Low(void)
{
    /************ clear interrupt flag ********/
    EXT_OnChange_RB_ClearInterruptFlag() ; 
    
    /*******code**********/
    
    /************** CALL BACK ************/
    if(RB5_InterruptHandler_Low)
    {
        RB5_InterruptHandler_Low() ;
    }
}

void RB6_ISR_High(void)
{
    /************ clear interrupt flag ********/
    EXT_OnChange_RB_ClearInterruptFlag() ; 
    
    /*******code**********/
    
    /************** CALL BACK ************/
    if(RB6_InterruptHandler_High)
    {
        RB6_InterruptHandler_High() ;
    }
}

void RB6_ISR_Low(void)
{
    /************ clear interrupt flag ********/
    EXT_OnChange_RB_ClearInterruptFlag() ; 
    
    /*******code**********/
    
    /************** CALL BACK ************/
    if(RB6_InterruptHandler_Low)
    {
        RB6_InterruptHandler_Low() ;
    }
}
void RB7_ISR_High(void)
{
    /************ clear interrupt flag ********/
    EXT_OnChange_RB_ClearInterruptFlag() ; 
    
    /*******code**********/
    
    /************** CALL BACK ************/
    if(RB7_InterruptHandler_High)
    {
        RB7_InterruptHandler_High() ;
    }
}

void RB7_ISR_Low(void)
{
    /************ clear interrupt flag ********/
    EXT_OnChange_RB_ClearInterruptFlag() ; 
    
    /*******code**********/
    
    /************** CALL BACK ************/
    if(RB7_InterruptHandler_Low)
    {
        RB7_InterruptHandler_Low() ;
    }
}


Std_ReturnType Interrupt_RB_Deintializing(interrupt_RB_t *int_obj)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        ret = Interrupt_RBx_Disable(int_obj);
    }
        
    return ret ;
}

/////////////////////////////////////////////////////////////////////////////////
static Std_ReturnType Interrupt_INTx_Enable(interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        switch(int_obj->int_number)
        {
            case EXTERNAL_INT0 :
                EXT_INT0_ENABLE() ;
                #ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_InterruptPriorityEnable();
                INTERRUPT_GloblsInterruptHighEnable();
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                break ;
            
            case EXTERNAL_INT1 :
                EXT_INT1_ENABLE() ;
                #ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_InterruptPriorityEnable();
                if( int_obj->priority == LOW_PRIORITY )
                {
                    INTERRUPT_GloblsInterruptLowEnable();
                }
                else if( int_obj->priority == HIGH_PRIORITY)
                {
                    INTERRUPT_GloblsInterruptHighEnable();
                }
                else{/* NOTHING */};
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                break ;
                
            case EXTERNAL_INT2 :
                EXT_INT2_ENABLE() ;
                #ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_InterruptPriorityEnable();
                if( int_obj->priority == LOW_PRIORITY )
                {
                    INTERRUPT_GloblsInterruptLowEnable();
                }
                else if( int_obj->priority == HIGH_PRIORITY)
                {
                    INTERRUPT_GloblsInterruptHighEnable();
                }
                else{/* NOTHING */};
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                break ;
            
            default :
                ret = STD_NOT_OK ;
        }
        
    }
        
    return ret ;
}

static Std_ReturnType Interrupt_INTx_Disable(interrupt_INTx_t *int_obj)
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        switch(int_obj->int_number)
        {
            case EXTERNAL_INT0 :
                EXT_INT0_DISABLE() ;
                break ;
            
            case EXTERNAL_INT1 :
                EXT_INT1_DISABLE() ;
                break ;
                
            case EXTERNAL_INT2 :
                EXT_INT2_DISABLE() ;
                break ;
            
            default :
                ret = STD_NOT_OK ;
        }
        
    }
        
    return ret ;
}

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_init(interrupt_INTx_t *int_obj)
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        switch(int_obj->int_number)
        {
            case EXTERNAL_INT1 :
                if( int_obj->priority == LOW_PRIORITY )
                {
                    EXT_INT1_LowPriority();
                }
                else if( int_obj->priority == HIGH_PRIORITY)
                {
                    EXT_INT1_HighPriority();
                }
                else{/* NOTHING */};
                break ;
                
            case EXTERNAL_INT2 :
                if( int_obj->priority == LOW_PRIORITY )
                {
                    EXT_INT2_LowPriority() ;
                }
                else if( int_obj->priority == HIGH_PRIORITY)
                {
                    EXT_INT2_HighPriority();
                }
                else{/* NOTHING */};
                break ;
            
            default :
                ret = STD_NOT_OK ;
        }
    }
        
    return ret ;
}
#endif

static Std_ReturnType Interrupt_INTx_Edge_Init(interrupt_INTx_t *int_obj)
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        switch(int_obj->int_number)
        {
            case EXTERNAL_INT0 :
                if( int_obj->edge == INTERRUPT_FALLING_EDGE )
                {
                    EXT_INT0_InterruptFallingEdge();
                }
                else if( int_obj->edge == INTERRUPT_RISING_EDGE)
                {
                    EXT_INT0_InterruptRisingEdge();
                }
                else{/* NOTHING */};
                break ;
            
            case EXTERNAL_INT1 :
                if( int_obj->edge == INTERRUPT_FALLING_EDGE )
                {
                    EXT_INT1_InterruptFallingEdge();
                }
                else if( int_obj->edge == INTERRUPT_RISING_EDGE)
                {
                    EXT_INT1_InterruptRisingEdge();
                }
                else{/* NOTHING */};
                break ;
                
            case EXTERNAL_INT2 :
                if( int_obj->edge == INTERRUPT_FALLING_EDGE )
                {
                    EXT_INT2_InterruptFallingEdge();
                }
                else if( int_obj->edge == INTERRUPT_RISING_EDGE)
                {
                    EXT_INT2_InterruptRisingEdge();
                }
                else{/* NOTHING */};
                break ;
            
            default :
                ret = STD_NOT_OK ;
        }
    }
        
    return ret ;
}
static Std_ReturnType Interrupt_INTx_Pin_Init(interrupt_INTx_t *int_obj)
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        ret = gpio_pin_intialize(&(int_obj->pin));
    }
        
    return ret ;
}


static Std_ReturnType INTx_SetInterruptHandler(interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        switch(int_obj->int_number)
        {
            case EXTERNAL_INT0 :
                ret = INT0_SetInterruptHandler(int_obj->interrupt_call_back)  ;
                break ;
            
            case EXTERNAL_INT1 :
                ret = INT1_SetInterruptHandler(int_obj->interrupt_call_back)  ;
                break ;
                
            case EXTERNAL_INT2 :
                ret = INT2_SetInterruptHandler(int_obj->interrupt_call_back)  ;
                break ;
            
            default :
                ret = STD_NOT_OK ;
        }
        
    }
        
    return ret ;
}
static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void))
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == InterruptHandler ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        Int0_InterruptHandler=InterruptHandler ;  
    }
    return ret ;
}
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void))
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == InterruptHandler ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        Int1_InterruptHandler=InterruptHandler ;
    }
    return ret ;
}
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void))
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == InterruptHandler ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        Int2_InterruptHandler=InterruptHandler ;
    }
    return ret ;
}

//////////////////////////////////////////////////////////////////////////////////

static Std_ReturnType Interrupt_RBx_Enable(interrupt_RB_t *int_obj)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        EXT_OnChange_RB_ENABLE() ;
    }
        
    return ret ;
}
static Std_ReturnType Interrupt_RBx_Disable(interrupt_RB_t *int_obj)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        EXT_OnChange_RB_DISABLE();
    }
        
    return ret ;
}

static Std_ReturnType Interrupt_RBx_Pin_Init(interrupt_RB_t *int_obj)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        ret = gpio_pin_intialize(&(int_obj->pin));
    }
        
    return ret ;
}


static Std_ReturnType RBx_SetInterruptHandler(interrupt_RB_t *int_obj)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        switch(int_obj->pin.pin)
        {
            case GPIO_PIN4 :
                RB4_SetInterruptHandler_High(int_obj->interrupt_call_back_High);
                RB4_SetInterruptHandler_Low(int_obj->interrupt_call_back_Low);
                break;
                
            case GPIO_PIN5 :
                RB5_SetInterruptHandler_High(int_obj->interrupt_call_back_High);
                RB5_SetInterruptHandler_Low(int_obj->interrupt_call_back_Low);
                break;
                
            case GPIO_PIN6 :
                RB6_SetInterruptHandler_High(int_obj->interrupt_call_back_High);
                RB6_SetInterruptHandler_Low(int_obj->interrupt_call_back_Low);
                break;
                
            case GPIO_PIN7 :
                RB7_SetInterruptHandler_High(int_obj->interrupt_call_back_High);
                RB7_SetInterruptHandler_Low(int_obj->interrupt_call_back_Low);
                break;
                
            default :
                ret = STD_NOT_OK ;
        }
        
        
    }
        
    return ret ;
}
static Std_ReturnType RB4_SetInterruptHandler_High(void(*InterruptHandler)(void))
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == InterruptHandler ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        RB4_InterruptHandler_High = InterruptHandler ;
    }
}

static Std_ReturnType RB4_SetInterruptHandler_Low(void(*InterruptHandler)(void))
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == InterruptHandler ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        RB4_InterruptHandler_Low = InterruptHandler ;
    }
}
static Std_ReturnType RB5_SetInterruptHandler_High(void(*InterruptHandler)(void))
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == InterruptHandler ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        RB5_InterruptHandler_High = InterruptHandler ;   
    }
}

static Std_ReturnType RB5_SetInterruptHandler_Low(void(*InterruptHandler)(void))
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == InterruptHandler ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        RB5_InterruptHandler_Low = InterruptHandler ;   
    }
}
static Std_ReturnType RB6_SetInterruptHandler_High(void(*InterruptHandler)(void))
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == InterruptHandler ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        RB6_InterruptHandler_High = InterruptHandler ;
    }
}

static Std_ReturnType RB6_SetInterruptHandler_Low(void(*InterruptHandler)(void))
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == InterruptHandler ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        RB6_InterruptHandler_Low = InterruptHandler ;
    }
}
static Std_ReturnType RB7_SetInterruptHandler_High(void(*InterruptHandler)(void))
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == InterruptHandler ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        RB7_InterruptHandler_High = InterruptHandler ;
    }
}

static Std_ReturnType RB7_SetInterruptHandler_Low(void(*InterruptHandler)(void))
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == InterruptHandler ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        RB7_InterruptHandler_Low = InterruptHandler ;
    }
}

///////////////////////////////////////////////////////////////////////////////

static Std_ReturnType Clear_IF_INTx(interrupt_INTx_t *int_obj)
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        switch(int_obj->int_number)
        {
            case EXTERNAL_INT0 :
                EXT_INT0_ClearInterruptFlag() ;
                break ;
            
            case EXTERNAL_INT1 :
                EXT_INT1_ClearInterruptFlag() ;
                break ;
                
            case EXTERNAL_INT2 :
                EXT_INT2_ClearInterruptFlag() ;
                break ;
            
            default :
                ret = STD_NOT_OK ;
        }
    }
        
    return ret ;
}


static Std_ReturnType Clear_IF_RBx(interrupt_RB_t *int_obj)
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == int_obj ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        EXT_OnChange_RB_ClearInterruptFlag();
    }
        
    return ret ;
}

