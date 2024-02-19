/* 
 * File:   hal_ccp.c
 * Author: Alielden
 *
 * Created on February 4, 2024, 4:46 PM
 */

#include "hal_ccp.h"

#ifdef CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*CCP1_InterruptHandler)(void) = NULL ;   
#endif

#ifdef CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*CCP2_InterruptHandler)(void) = NULL ;   
#endif

static void CCP_Interrupt_Init(const ccp_t  *_ccp);
static void CCP_Mode_Init(const ccp_t  *_ccp);

/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType CCP_Init(const ccp_t  *_ccp)   
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == _ccp )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* DISABLE CCP MODULE */
         if( _ccp->ccp_inst == ccp1_inst )
         {
            CCP1_SET_MODE(DISABLE_CCP) ;
         }
                
         else if( _ccp->ccp_inst == ccp2_inst )
         {
            CCP2_SET_MODE(DISABLE_CCP) ;
         }
        /* SET MODE  */
         CCP_Mode_Init(_ccp) ;
        /* PIN CONFIGURATION */   
        ret = gpio_pin_intialize(&(_ccp->pin));
        /* ENABLE INTERRUPT  */  
        CCP_Interrupt_Init(_ccp) ;
    return ret ; 
}
}


/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType CCP_Deinit(const ccp_t  *_ccp) 
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == _ccp )
    {
        ret = STD_NOT_OK ;
    }
    else{
        
        if( _ccp->ccp_inst == ccp1_inst )
         {
            CCP1_SET_MODE(DISABLE_CCP);
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP1_INTERRUPT_DISABLE(); 
#endif
         }
                
         else if( _ccp->ccp_inst == ccp2_inst )
         {
            CCP2_SET_MODE(DISABLE_CCP);
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP2_INTERRUPT_DISABLE(); 
#endif
       
         }
       
    }
}



#if (CCP1_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED) 
/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType CCP_Is_Capture_Done(const ccp_t  *_ccp , uint8 *ccp_status)
{
    Std_ReturnType ret = STD_OK ;
    if( (NULL == _ccp)  ||  (NULL == ccp_status) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        
         if( _ccp->ccp_inst == ccp1_inst )
         {
            if( PIR1bits.CCP1IF == CAPTURE_OCURRED )
            {
                 *ccp_status = CAPTURE_OCURRED ;
                 CCP1_INTERRUPT_CLR_FLAG();   
            }
            else if ( PIR1bits.CCP1IF == CAPTURE_NOT_OCURRED )
            {
                *ccp_status = CAPTURE_NOT_OCURRED ;
            }
         }
                
         else if( _ccp->ccp_inst == ccp2_inst )
         {
            if( PIR2bits.CCP2IF == CAPTURE_OCURRED )
            {
                 *ccp_status = CAPTURE_OCURRED ;
                 CCP2_INTERRUPT_CLR_FLAG();   
            }
            else if ( PIR2bits.CCP2IF == CAPTURE_NOT_OCURRED )
            {
                *ccp_status = CAPTURE_NOT_OCURRED ;
            }
         }
        
       
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
Std_ReturnType CCP_Capture_Read_Value(const ccp_t  *_ccp , uint16 *capture_value)
{
    Std_ReturnType ret = STD_OK ;
    uint8 ccp1l = 0 , ccp1h = 0 , ccp2l = 0 , ccp2h = 0; 
    if( (NULL == _ccp)  ||  (NULL == capture_value) )
    {
        ret = STD_NOT_OK ;
    }
    else{
         if( _ccp->ccp_inst == ccp1_inst )
         {
            ccp1l = CCPR1L ;
            ccp1h = CCPR1H ; 
            *capture_value = (ccp1h << 8 ) + ccp1l ;
         }
                
         else if( _ccp->ccp_inst == ccp2_inst )
         {
            ccp2l = CCPR2L ;
            ccp2h = CCPR2H ; 
            *capture_value = (ccp2h << 8 ) + ccp2l ;
         }
        
    }
    return ret ; 
}
#endif 

#if (CCP1_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED) 
/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType CCP_Is_Compare_Done(const ccp_t  *_ccp , uint8 *ccp_status)
{
    Std_ReturnType ret = STD_OK ;
    if( (NULL == _ccp)  ||   (NULL == ccp_status) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        
         if( _ccp->ccp_inst == ccp1_inst )
         {
            if( PIR1bits.CCP1IF == COMPARE_OCURRED )
            {
                *ccp_status = COMPARE_OCURRED ;
                 CCP1_INTERRUPT_CLR_FLAG();   
            }
            else if ( PIR1bits.CCP1IF == COMPARE_NOT_OCURRED )
            {
                *ccp_status = COMPARE_NOT_OCURRED ;
            }
         }
                
         else if( _ccp->ccp_inst == ccp2_inst )
         {
             if( PIR2bits.CCP2IF == COMPARE_OCURRED )
            {
                *ccp_status = COMPARE_OCURRED ;
                 CCP2_INTERRUPT_CLR_FLAG();   
            }
            else if ( PIR2bits.CCP2IF == COMPARE_NOT_OCURRED )
            {
                *ccp_status = COMPARE_NOT_OCURRED ;
            }
         }
        
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
Std_ReturnType CCP_Compare_Write_Value(const ccp_t  *_ccp , uint16 compare_value)
{
    Std_ReturnType ret = STD_OK ; 
    if( NULL == _ccp )
    {
        ret = STD_NOT_OK ;
    }
    else{
        if( _ccp->ccp_inst == ccp1_inst )
         {
            CCPR1L = (uint8)compare_value ;
            CCPR1H = (uint8)(compare_value >> 8);
         }
                
         else if( _ccp->ccp_inst == ccp2_inst )
         {
            CCPR2L = (uint8)compare_value ;
            CCPR2H = (uint8)(compare_value >> 8);
         }
      
    }
    return ret ; 
}
#endif 


#if (CCP1_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)    
/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t  *_ccp , uint8 duty_cycle)
{
    Std_ReturnType ret = STD_OK ;
    uint16 temp_val = 0 ;
    if( NULL == _ccp )
    {
        ret = STD_NOT_OK ;
    }
    else{
        if( _ccp->ccp_inst == ccp1_inst )
        {
            temp_val = (uint8)( 4 * ( PR2 + 1 ) * ( (duty_cycle)  / 100.0 ) ) ;
            CCP1CONbits.DC1B = (uint8)(temp_val &  0x0003 ) ;
            CCPR1L = (uint8)(temp_val >> 2 ) ; 
        }
        else if ( _ccp->ccp_inst == ccp2_inst )
        {
            temp_val = (uint8)( 4 * ( PR2 + 1 ) * ( (duty_cycle)  / 100.0 ) ) ;
            CCP2CONbits.DC2B = (uint8)(temp_val &  0x0003 ) ;
            CCPR2L = (uint8)(temp_val >> 2 ) ; 
        }
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
Std_ReturnType CCP_PWM_Start(const ccp_t  *_ccp)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == _ccp )
    {
        ret = STD_NOT_OK ;
    }
    else{
        if( _ccp->ccp_inst == ccp1_inst )
        {
            CCP1_SET_MODE(CCP_PWM_MODE);
        }
        else if ( _ccp->ccp_inst == ccp2_inst )
        {
            CCP2_SET_MODE(CCP_PWM_MODE);
        }
      
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
Std_ReturnType CCP_PWM_Stop(const ccp_t  *_ccp)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == _ccp )
    {
        ret = STD_NOT_OK ;
    }
    else{
        if( _ccp->ccp_inst == ccp1_inst )
        {
            CCP1_SET_MODE(DISABLE_CCP);
        }
        else if ( _ccp->ccp_inst == ccp2_inst )
        {
            CCP2_SET_MODE(DISABLE_CCP);
        }
      
    }
    return ret ; 
} 

#endif    




void CCP1_ISR(void)
{
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP1_INTERRUPT_CLR_FLAG();
    
    /* Code */
    
    
    if(CCP1_InterruptHandler)
    {
        CCP1_InterruptHandler();
    }
#endif
}

void CCP2_ISR(void)
{
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP2_INTERRUPT_CLR_FLAG();
    
    /* Code */
    
    
    if(CCP2_InterruptHandler)
    {
        CCP2_InterruptHandler();
    }
#endif
}



static void CCP_Mode_Init(const ccp_t  *_ccp)
{
        Std_ReturnType ret = STD_OK ;
        if(_ccp->_mode == _CAPTURE_MODE)
        {
           
                if( _ccp->ccp_inst == ccp1_inst )
                {
                    switch(_ccp->Sub_Mode)
                     {
                        case CCP_CAPTURE_MODE_FALLING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_FALLING_EDGE) ; break ;
                        case CCP_CAPTURE_MODE_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_RISING_EDGE) ; break ;
                        case CCP_CAPTURE_MODE_4TH_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_4TH_RISING_EDGE) ; break ;
                        case CCP_CAPTURE_MODE_16TH_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_16TH_RISING_EDGE) ; break ;
                        default: ret = STD_NOT_OK ;    
                     }
                }
                else if( _ccp->ccp_inst == ccp2_inst )
                {
                    switch(_ccp->Sub_Mode)
                     {
                        case CCP_CAPTURE_MODE_FALLING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_FALLING_EDGE) ; break ;
                        case CCP_CAPTURE_MODE_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_RISING_EDGE) ; break ;
                        case CCP_CAPTURE_MODE_4TH_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_4TH_RISING_EDGE) ; break ;
                        case CCP_CAPTURE_MODE_16TH_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_16TH_RISING_EDGE) ; break ;
                        default: ret = STD_NOT_OK ;    
                     }
                }
            
        
            
#if (CCP1_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED) ||  (CCP2_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED)
            if( _ccp->Timer_Select == CCP1_TIMER1_CCP2_TIMER1 )
            {
                T3CONbits.T3CCP2 = 0 ;
                T3CONbits.T3CCP1 = 0 ;
            }
            else if( _ccp->Timer_Select == CCP1_TIMER1_CCP2_TIMER3 )
            {
                T3CONbits.T3CCP2 = 0 ;
                T3CONbits.T3CCP1 = 1 ;
            }
            else if( _ccp->Timer_Select == CCP1_TIMER3_CCP2_TIMER3 )
            {
                T3CONbits.T3CCP2 = 1 ;
                T3CONbits.T3CCP1 = 0 ;
            }
#endif
            
        }
        else if(_ccp->_mode == _COMPARE_MODE)
        {
            
                if( _ccp->ccp_inst == ccp1_inst )
                {
                    switch(_ccp->Sub_Mode)
                    {
                        case CCP_COMPARE_MODE_TOGGLE_OUTPUT : CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_OUTPUT) ; break ;
                        case CCP_COMPARE_MODE_CCP_PIN_LOW : CCP1_SET_MODE(CCP_COMPARE_MODE_CCP_PIN_LOW) ; break ;
                        case CCP_COMPARE_MODE_CCP_PIN_HIGH : CCP1_SET_MODE(CCP_COMPARE_MODE_CCP_PIN_HIGH) ; break ;
                        default: ret = STD_NOT_OK ;
                    }
                }
                else if( _ccp->ccp_inst == ccp2_inst )
                {
                    switch(_ccp->Sub_Mode)
                    {
                        case CCP_COMPARE_MODE_TOGGLE_OUTPUT : CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_OUTPUT) ; break ;
                        case CCP_COMPARE_MODE_CCP_PIN_LOW : CCP2_SET_MODE(CCP_COMPARE_MODE_CCP_PIN_LOW) ; break ;
                        case CCP_COMPARE_MODE_CCP_PIN_HIGH : CCP2_SET_MODE(CCP_COMPARE_MODE_CCP_PIN_HIGH) ; break ;
                        default: ret = STD_NOT_OK ;
                    }
                }
            
            
#if (CCP1_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)  ||  (CCP2_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)
            if( _ccp->Timer_Select == CCP1_TIMER1_CCP2_TIMER1 )
            {
                T3CONbits.T3CCP2 = 0 ;
                T3CONbits.T3CCP1 = 0 ;
            }
            else if( _ccp->Timer_Select == CCP1_TIMER1_CCP2_TIMER3 )
            {
                T3CONbits.T3CCP2 = 0 ;
                T3CONbits.T3CCP1 = 1 ;
            }
            else if( _ccp->Timer_Select == CCP1_TIMER3_CCP2_TIMER3 )
            {
                T3CONbits.T3CCP2 = 1 ;
                T3CONbits.T3CCP1 = 0 ;
            }
#endif
        }
        else if(_ccp->_mode == _PWM_MODE )
        {
            if( _ccp->Sub_Mode == CCP_PWM_MODE )
            {
                if( _ccp->ccp_inst == ccp1_inst )
                {
                CCP1_SET_MODE(CCP_PWM_MODE);
                }
                
                else if( _ccp->ccp_inst == ccp2_inst )
                {
                 CCP2_SET_MODE(CCP_PWM_MODE);
                }
#if (CCP1_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)  ||  (CCP2_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) 
                 /* PWM FREQ INTAILIZE */
                PR2 = (uint8)((_XTAL_FREQ   / (_ccp->PWM_Freq  * 4.0  *  _ccp->Timer2_postscaler_value  *  _ccp->Timer2_prescaler_value))
                        - 1 ) ;
#endif
            }
            else
            {
                ret = STD_NOT_OK ;
            }
        }
}



static void CCP_Interrupt_Init(const ccp_t  *_ccp)
{
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_ENABLE();
        CCP1_INTERRUPT_CLR_FLAG();
        CCP1_InterruptHandler = _ccp->ccp1_call_back ;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE  
        INTERRUPT_InterruptPriorityEnable();
        if(_ccp->ccp1_priority == HIGH_PRIORITY )
        {
            INTERRUPT_GloblsInterruptHighEnable();
            CCP1_INTERRUPT_HIGH_PRIORITY();
        }
        else if(_ccp->ccp1_priority == LOW_PRIORITY)
        {
            INTERRUPT_GloblsInterruptLowEnable();
            CCP1_INTERRUPT_LOW_PRIORITY();
        }
#else
    INTCONbits.PEIE = 1 ;
    INTERRUPT_GlobalInterruptEnable();
#endif     
#endif
    
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        CCP2_INTERRUPT_ENABLE();
        CCP2_INTERRUPT_CLR_FLAG();
        CCP2_InterruptHandler = _ccp->ccp2_call_back ;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE  
        INTERRUPT_InterruptPriorityEnable();
        if(_ccp->ccp2_priority == HIGH_PRIORITY )
        {
            INTERRUPT_GloblsInterruptHighEnable();
            CCP2_INTERRUPT_HIGH_PRIORITY();
        }
        else if(_ccp->ccp2_priority == LOW_PRIORITY)
        {
            INTERRUPT_GloblsInterruptLowEnable();
            CCP2_INTERRUPT_LOW_PRIORITY();
        }
#else
    INTCONbits.PEIE = 1 ;
    INTERRUPT_GlobalInterruptEnable();
#endif     
#endif  
    
}



