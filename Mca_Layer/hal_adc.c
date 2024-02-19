 /* 
 * File:   hal_adc.c
 * Author: Alielden
 *
 * Created on October 18, 2023, 11:16 PM
 */

#include "ADC/hal_adc.h"

#ifdef ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*ADC_InterruptHandler)(void) = NULL ;   
#endif


static void ADC_PinIntialize(adc_channel_select_t channel);


/**
 * 
 * @param adc
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType ADC_Init(adc_t *adc)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == adc ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* Disable ADC */
        ADC_DISABLE();
        /* Configure The Acquisition Time */
        ADCON2bits.ACQT = adc->Taq ;
        /* Configure Clock */
        ADCON2bits.ADCS = adc->clk ;
        /* Channel Select */
        ADCON0bits.CHS = adc->channel ;
        ADC_PinIntialize(adc->channel);
        /* Configure Interrupt*/
        
        /* Select Format */
        if( adc->Format_Select == RIGHT_FORMAT )
        {
            ADC_RIGHT_JUSTIFIED() ;
        }
        else if(adc->Format_Select == LEFT_FORMAT)
        {
            ADC_LEFT_JUSTIFIED() ;
        }
        /*  Select Voltage Reference */
        if( adc->Voltage_Refrence == VREF )
        {
            ADCON1bits.VCFG1=1 ;
            ADCON1bits.VCFG0=1 ;
        }
        else if(adc->Voltage_Refrence == VSS_VDD)
        {
            ADCON1bits.VCFG1=0 ;
            ADCON1bits.VCFG0=0 ;
        }
        /* Configure Interrupt */
#ifdef ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PeripheralInterruptEnable() ;
        INTERRUPT_GlobalInterruptEnable();
        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_CLR_FLAG();
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE        
        if(adc->priority == HIGH_PRIORITY )
        {
            ADC_INTERRUPT_HIGH_PRIORITY();
        }
        else if(adc->priority == LOW_PRIORITY)
        {
            ADC_INTERRUPT_LOW_PRIORITY();
        }
#endif
        ADC_InterruptHandler = adc->adc_call_back ;
       
#endif
        /* Enable ADC */
        ADC_ENABLE();
    }
    return ret ;

}

/**
 * 
 * @param adc
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType ADC_DeInit(adc_t *adc)
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == adc ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        ADC_DISABLE();
#ifdef ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DISABLE(); 
#endif
    }
    return ret ;
}



/**
 * 
 * @param adc
 * @param channel
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType ADC_SelectChannel(adc_t *adc , adc_channel_select_t channel)
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == adc ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* Channel Select */
        ADCON0bits.CHS = channel ;
        ADC_PinIntialize(channel);
    }
    return ret ;
}

/**
 * 
 * @param adc
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType ADC_StartConversion(adc_t *adc )
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == adc ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* Set Go/Done Bit */
        ADC_START_CONVERSION();
    }
    return ret ;
}

/**
 * 
 * @param adc
 * @param status
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType ADC_IsDone(adc_t *adc , uint8 *status)
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == adc ) ||  (NULL == status) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        *status = ADC_CONVERSION_STATUS ;
    }
    return ret ;
}

/**
 * 
 * @param adc
 * @param value
* @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType ADC_ConversionValue(adc_t *adc , uint16  *value)
{
     Std_ReturnType ret = STD_OK ;
    if( ( NULL == adc ) ||  (NULL==value) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        if( adc->Format_Select == RIGHT_FORMAT)
        {
            *value = (uint16)( ( ADRESH << 8 ) + (ADRESL) ) ;
        }
        else if(adc->Format_Select == LEFT_FORMAT)
        {
            *value = (uint16)( ( ( ADRESH << 8 ) + (ADRESL) ) >> 6 ) ;
        }
    }
    return ret ;
}

/**
 * 
 * @param adc
 * @param channel
 * @param value
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType ADC_GetConversion(adc_t *adc , adc_channel_select_t channel ,uint16  *value )
{
     Std_ReturnType ret = STD_OK , conversion_status = 0  ;
    if( ( NULL == adc ) ||  (NULL==value) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        ret  = ADC_SelectChannel(adc , channel) ;
        ret = ADC_StartConversion(adc) ;
        
        while(ADC_CONVERSION_STATUS)
        {
            ret = ADC_IsDone(adc , &conversion_status) ;
            if( conversion_status== ADC_IDLE )
            {
               ret = ADC_ConversionValue(adc , value) ;
            }
            else
            {
                ret = STD_NOT_OK ;
            }
        }
        
    }
    return ret ;
}

/**
 * 
 * @param adc
 * @param channel
 * @param value
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType ADC_GetConversion_Interrupt(adc_t *adc , adc_channel_select_t channel  )
{
    
     Std_ReturnType ret = STD_OK  ;
    if( ( NULL == adc )  )
    {
        ret = STD_NOT_OK ;
    }
    else{
        ret  = ADC_SelectChannel(adc , channel) ;
        ret = ADC_StartConversion(adc) ;   
    }
    return ret ;
}

static void ADC_PinIntialize(adc_channel_select_t channel)
{
    switch(channel)
    {
        case ADC_CHANNEL_AN0 :
            SET_BIT(TRISA , _TRISA_RA0_POSITION) ;
            break ;
            
        case ADC_CHANNEL_AN1 :
            SET_BIT(TRISA , _TRISA_RA1_POSITION) ;
            break ;
            
        case ADC_CHANNEL_AN2 :
            SET_BIT(TRISA , _TRISA_RA2_POSITION) ;
            break ;
            
        case ADC_CHANNEL_AN3 :
            SET_BIT(TRISA , _TRISA_RA3_POSITION) ;
            break ;
            
        case ADC_CHANNEL_AN4 :
            SET_BIT(TRISA , _TRISA_RA5_POSITION) ;
            break ;
            
        case ADC_CHANNEL_AN5 :
            SET_BIT(TRISE , _TRISE_RE0_POSITION ) ;
            break ;
            
        case ADC_CHANNEL_AN6 :
            SET_BIT(TRISE , _TRISE_RE1_POSITION ) ;
            break ;
            
        case ADC_CHANNEL_AN7 :
            SET_BIT(TRISE , _TRISE_RE2_POSITION ) ;
            break ;
            
        case ADC_CHANNEL_AN8 :
            SET_BIT(TRISB , _TRISB_RB2_POSITION) ;
            break ;
        case ADC_CHANNEL_AN9 :
            SET_BIT(TRISB , _TRISB_RB3_POSITION) ;
            break ;
        case ADC_CHANNEL_AN10 :
            SET_BIT(TRISB , _TRISB_RB1_POSITION) ;
            break ;
        case ADC_CHANNEL_AN11 :
            SET_BIT(TRISB , _TRISB_RB4_POSITION) ;
            break ;
        case ADC_CHANNEL_AN12 :
           SET_BIT(TRISB , _TRISB_RB0_POSITION) ;
            break ;
            
    }
}


void ADC_ISR(void)
{
#ifdef ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    ADC_INTERRUPT_CLR_FLAG();
    
    /* Code */
    
    if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
#endif
}