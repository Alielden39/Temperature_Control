/* 
 * File:   hal_usart.c
 * Author: Alielden
 *
 * Created on December 27, 2023, 10:26 PM
 */

#include "hal_usart.h"

static void BaudRate_Calculation(usart_t *usart );
static void Usart_Asynchronous_Tx_Init(usart_t *usart);
static void Usart_Asynchronous_Rx_Init(usart_t *usart);

#ifdef USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*USART_TX_INTERRUPTHANDLER)(void) = NULL ;   
#endif

#ifdef USART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*USART_RX_INTERRUPTHANDLER)(void) = NULL ;   
static void (*USART_RX_FRAMING_ERROR_INTERRUPTHANDLER)(void) = NULL ;   
static void (*USART_RX_OVERRUN_ERROR_INTERRUPTHANDLER)(void) = NULL ;   
#endif


/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType Usart_Async_init(usart_t *usart )
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == usart  )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /********** DISABLE TX/RX PINS *****************/
        RCSTAbits.SPEN = SERIAL_PORT_TX_RX_DISABLE ;
        /*********** BAUDRATE INTIALIZE ****************/
        BaudRate_Calculation(usart);
        /********** ENABLE TX/RX PINS *****************/
        TRISCbits.RC6 = 1 ;
        TRISCbits.RC7 = 1 ;
        RCSTAbits.SPEN = SERIAL_PORT_TX_RX_ENABLE ;
        /********** TX/RX INIT ************************/
        Usart_Asynchronous_Tx_Init(usart);
        Usart_Asynchronous_Rx_Init(usart);
        
      
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
Std_ReturnType Usart_Async_Deinit(usart_t *usart )
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == usart  )
    {
        ret = STD_NOT_OK ;
    }
    else{
      RCSTAbits.SPEN = SERIAL_PORT_TX_RX_DISABLE ;
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
Std_ReturnType Usart_Async_WriteByte( uint8 data )
{
   Std_ReturnType ret = STD_OK ;
    
    while( TXSTAbits.TRMT == TSR_FULL ){}
#ifdef USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    USART_TX_INTERRUPT_ENABLE() ;
#endif
    TXREG = data ;
}

    
    

Std_ReturnType Usart_Async_WriteString( uint8 *data , uint8 length )
{
    Std_ReturnType ret = STD_OK ;
    uint8 count = 0 ;
    if(  NULL == data )
    {
        ret = STD_NOT_OK ;
    }
    else{
        for( count=0 ; count<length ; count++)
        {
           while( TXSTAbits.TRMT == TSR_FULL ){}
#ifdef USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
           USART_TX_INTERRUPT_ENABLE() ;
#endif
           TXREG =  data[count] ;
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
Std_ReturnType Usart_Async_ReadByte( uint8 *data )
{
    Std_ReturnType ret = STD_OK ;
    if(  NULL == data  )
    {
        ret = STD_NOT_OK ;
    }
    else{
        while( PIR1bits.RCIF == USART_RX_INTERRUPT_FLAG_DISABLE );
        *data = RCREG ;
      
    }
    return ret ;
    
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void BaudRate_Calculation(usart_t *usart)
{
    Std_ReturnType ret = STD_OK ;
    float BaudRate_Value = 0 ;
    switch(usart->baudrate_eqn){
        case ASYN_8BIT_LOW_SPEED :
            TXSTAbits.BRGH = USART_LOW_BAUDRATE_SPEED ;
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE ;
            BAUDCONbits.BRG16 = USART_8BIT_BAUDRATE ;  
            
            BaudRate_Value = ( ( _XTAL_FREQ  / (float)usart->baudrate ) / 64 ) - 1  ;
            break ;
        
        case ASYN_8BIT_HIGH_SPEED :
             TXSTAbits.BRGH = USART_HIGH_BAUDRATE_SPEED ;
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE ;
            BAUDCONbits.BRG16 =  USART_8BIT_BAUDRATE ;  
            
            BaudRate_Value = ( ( _XTAL_FREQ  / (float)usart->baudrate ) / 16 ) - 1  ;
            break ;
            
         case ASYN_16BIT_LOW_SPEED :
              TXSTAbits.BRGH = USART_LOW_BAUDRATE_SPEED ;
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE ;
            BAUDCONbits.BRG16 =  USART_16BIT_BAUDRATE ; 
            
            BaudRate_Value = ( ( _XTAL_FREQ  / (float)usart->baudrate ) / 16 ) - 1  ;
            break ;
        
        case ASYN_16BIT_HIGH_SPEED :
             TXSTAbits.BRGH = USART_HIGH_BAUDRATE_SPEED ;
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE ;
            BAUDCONbits.BRG16 = USART_16BIT_BAUDRATE ;
            
            BaudRate_Value = ( ( _XTAL_FREQ  / (float)usart->baudrate ) / 4 ) - 1  ;
            break ;
            
         case SYNC_8BIT : 
            TXSTAbits.SYNC = USART_SYNCHRONOUS_MODE ;
            BAUDCONbits.BRG16 =  USART_8BIT_BAUDRATE ;  
            
            BaudRate_Value = ( ( _XTAL_FREQ  / (float)usart->baudrate ) / 4 ) - 1  ;
            break ;
        
        case SYNC_16BIT : 
            TXSTAbits.SYNC = USART_SYNCHRONOUS_MODE ;
            BAUDCONbits.BRG16 =  USART_16BIT_BAUDRATE ; 
            
            BaudRate_Value = ( ( _XTAL_FREQ  / (float)usart->baudrate ) / 4 ) - 1  ;
            break ; 
           
        default :
            ret = STD_NOT_OK ;
    }
    SPBRG = (uint8)((uint32)BaudRate_Value) ;
    SPBRGH =  (uint8)( ( (uint32)BaudRate_Value ) >> 8 ) ;
    
} 


static void Usart_Asynchronous_Tx_Init(usart_t *usart)
{
    if( usart->tx_cfg.tx_enable == USART_TX_ENABLE )
    {
    /******************* INTERRUPT CONFIGURATION ************/
    PIE1bits.TXIE = usart->tx_cfg.tx_interrupt ;
#ifdef USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        USART_TX_INTERRUPT_ENABLE(); 
        USART_TX_INTERRUPTHANDLER = usart->USART_TX_CALLBACK ;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE  
        INTERRUPT_InterruptPriorityEnable();
        if(usart->Tx_priority == HIGH_PRIORITY )
        {
            INTERRUPT_GloblsInterruptHighEnable();
            USART_TX_INTERRUPT_HIGH_PRIORITY();
        }
        else if(usart->Tx_priority == LOW_PRIORITY)
        {
            INTERRUPT_GloblsInterruptLowEnable();
            USART_TX_INTERRUPT_LOW_PRIORITY();
        }
#else
    INTCONbits.PEIE = 1 ;
    INTERRUPT_GlobalInterruptEnable();
#endif     
#endif
    /******************* 9-BIT CONFIGURATION ***************/
    TXSTAbits.TX9 = usart->tx_cfg.tx_9bit ;
    /******************* ENABLE TRANSMISSION ***************/
    TXSTAbits.TXEN = USART_TX_ENABLE ;
    }
    else{ /* NOTHING */ }
}

static void Usart_Asynchronous_Rx_Init(usart_t *usart)
{
    if( usart->rx_cfg.rx_enable == USART_RX_ENABLE )
    {
    /******************* INTERRUPT CONFIGURATION ************/
    PIE1bits.RCIE = usart->rx_cfg.rx_interrupt ;
#ifdef USART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        USART_RX_INTERRUPT_ENABLE();
        USART_RX_INTERRUPTHANDLER = usart->USART_RX_CALLBACK ;
        USART_RX_FRAMING_ERROR_INTERRUPTHANDLER = usart->USART_RX_FRAMING_ERROR_CALLBACK ;   
        USART_RX_OVERRUN_ERROR_INTERRUPTHANDLER = usart->USART_RX_OVERRUN_ERROR_CALLBACK ;  
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE  
        INTERRUPT_InterruptPriorityEnable();
        if(usart->Rx_priority == HIGH_PRIORITY )
        {
            INTERRUPT_GloblsInterruptHighEnable();
            USART_RX_INTERRUPT_HIGH_PRIORITY();
        }
        else if(usart->Rx_priority == LOW_PRIORITY)
        {
            INTERRUPT_GloblsInterruptLowEnable();
            USART_RX_INTERRUPT_LOW_PRIORITY() ;
        }
#else
    INTCONbits.PEIE = 1 ;
    INTERRUPT_GlobalInterruptEnable();
#endif     
#endif
    /******************* 9-BIT CONFIGURATION ***************/
    RCSTAbits.RX9 = usart->rx_cfg.rx_9bit ;
    /******************* ENABLE TRANSMISSION ***************/
    RCSTAbits.CREN = USART_RX_ENABLE ;
    }
    else{ /* NOTHING */ }
}

void USART_TX_ISR(void) {
#ifdef USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    USART_TX_INTERRUPT_DISABLE() ;
    /* Code */
    
    
    if(USART_TX_INTERRUPTHANDLER)
    {
        USART_TX_INTERRUPTHANDLER();
    }
#endif
    
}
void USART_RX_ISR(void){
#ifdef USART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    PIE1bits.TXIE = 0 ;
    
    /* Code */
    
    
    if(USART_RX_INTERRUPTHANDLER)
    {
        USART_RX_INTERRUPTHANDLER();          /////////  should read in isr application 
    }
    
    if(USART_RX_FRAMING_ERROR_INTERRUPTHANDLER)
    {
        USART_RX_FRAMING_ERROR_INTERRUPTHANDLER();   /////////  should read in isr application 
    }
    
    if(USART_RX_OVERRUN_ERROR_INTERRUPTHANDLER)
    {
        /**************  RESTART RX *****************/
        RCSTA1bits.CREN = USART_RX_DISABLE ;
        RCSTA1bits.CREN = USART_RX_ENABLE ;
        /*******************************************/
        USART_RX_OVERRUN_ERROR_INTERRUPTHANDLER();       ////////////  should restart rx 
    }
#endif  
}