/* 
 * File:   hal_i2c.c
 * Author: Alielden
 *
 * Created on February 16, 2024, 1:34 PM
 */

#include "hal_i2c.h"

#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*I2C_INTERRUPTHANDLER)(void) = NULL ;   
static void (*I2C_COLLISION_ERROR_INTERRUPTHANDLER)(void) = NULL ;   
static void (*I2C_OVERFLOW_ERROR_INTERRUPTHANDLER)(void) = NULL ;   
#endif



static void I2C_General_Call_Configuration(const mssp_i2c_t *i2c);
static void I2C_Master_Submode_Configuration(const mssp_i2c_t *i2c);
static void I2C_Slave_Submode_Configuration(const mssp_i2c_t *i2c);
static void I2C_Interrupt_Configuration(const mssp_i2c_t *i2c);

/**
 * 
 * @param timer0
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType MSSP_I2C_init(const mssp_i2c_t *i2c)
{
    Std_ReturnType ret = STD_OK ;
    if(  NULL == i2c  )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* Disable I2C */
        MSSP_MODULE_DISABLE_FUNC() ;
        /* mode configuration*/
        if( i2c->mode == I2C_MASTER_MODE )
        {
            /* master sub mode configuration*/
            I2C_Master_Submode_Configuration(i2c)  ;    
        }
       else if( i2c->mode == I2C_SLAVE_MODE )
        {
           /* slave sub mode configuration*/
            I2C_Slave_Submode_Configuration(i2c);
            /* General call configuration */
            I2C_General_Call_Configuration(i2c);
            /* Clear collision bit */
            I2C_SLAVE_TRANSMIT_MODE_NO_COLLISION();
            /* Clear Overflow bit */
            I2C_SLAVE_RECEIEVE_MODE_NO_OVERFLOW();
            /* Release the clock */
            I2C_SLAVE_MODE_RELEASE_CLOCK();
            /* Assign the slave address */
            SSPADD = i2c->slave_address ;
        }
        /* GPIO initial */
            TRISCbits.TRISC3 = GPIO_INPUT   ;       /// SCL 
            TRISCbits.TRISC4 = GPIO_INPUT   ;       /// SDA
        /* Slew Rate Configuration */
        if( i2c->slew_rate == I2C_SLEW_RATE_DISABLE )
        {
            I2C_SLEW_RATE_DISABLE_FUNC();
        }
        else if( i2c->slew_rate == I2C_SLEW_RATE_ENABLE )    
        {
            I2C_SLEW_RATE_ENABLE_FUNC() ; 
        }
        /* SMBus Configuration */
        if( i2c->SMBus == I2C_SMBUS_DISABLE )
        {
            I2C_SMBUS_DISABLE_FUNC();
        }
        else if(  i2c->SMBus == I2C_SMBUS_ENABLE )    
        {
            I2C_SMBUS_ENABLE_FUNC() ; 
        }
        /* Enable Interrupt */     
        I2C_Interrupt_Configuration(i2c);
        /* Enable I2C */
        MSSP_MODULE_ENABLE_FUNC() ;
        
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
Std_ReturnType MSSP_I2C_Deinit(const mssp_i2c_t *i2c)
{
    Std_ReturnType ret = STD_OK ;
    if(  NULL == i2c  )
    {
        ret = STD_NOT_OK ;
    }
    else{
         /* Disable I2C */
        MSSP_MODULE_DISABLE_FUNC() ;
        /* Disable Interrupt */
#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE 
        I2C_INTERRUPT_DISABLE();
        I2C_BUS_COLLISION_INTERRUPT_DISABLE();    
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
Std_ReturnType MSSP_I2C_send_start(const mssp_i2c_t *i2c)
{
    Std_ReturnType ret = STD_OK ;
    if(  NULL == i2c  )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* Start condition Enable */
        SSPCON2bits.SEN = I2C_MASTER_MODE_START_CONDITION_ENABLE ;
        /* Wait Until Detect Start bit*/
        while( SSPCON2bits.SEN ) ;
        /* Clear IF */
        PIR1bits.SSPIF = 0 ;
        /* Check If Start bit detected */
        if( SSPSTATbits.S == I2C_START_BIT_DETECTED )
        {
            ret = STD_OK ;
        }
        else if( SSPSTATbits.S == I2C_START_BIT_NOT_DETECTED )
        {
            ret = STD_NOT_OK ;
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
Std_ReturnType MSSP_I2C_send_repeated_start(const mssp_i2c_t *i2c)
{
    Std_ReturnType ret = STD_OK ;
    if(  NULL == i2c  )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /*  RepeatedStart condition Enable */
        SSPCON2bits.RSEN = I2C_MASTER_MODE_REPEATED_START_CONDITION_ENABLE ;
        /* Wait Until Detect Start bit*/
        while( SSPCON2bits.RSEN ) ;
        /* Clear IF */
        PIR1bits.SSPIF = 0 ;
        
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
Std_ReturnType MSSP_I2C_send_stop(const mssp_i2c_t *i2c)
{
    Std_ReturnType ret = STD_OK ;
    if(  NULL == i2c  )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* Stop condition Enable */
        SSPCON2bits.PEN = I2C_MASTER_MODE_STOP_CONDITION_ENABLE ;
        /* Wait Until Detect Start bit*/
        while( SSPCON2bits.PEN ) ;
        /* Clear IF */
        PIR1bits.SSPIF = 0 ;
        /* Check If Start bit detected */
        if( SSPSTATbits.P == I2C_STOP_BIT_DETECTED )
        {
            ret = STD_OK ;
        }
        else if( SSPSTATbits.S == I2C_STOP_BIT_NOT_DETECTED )
        {
            ret = STD_NOT_OK ;
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
Std_ReturnType MSSP_I2C_Master_receive_read(const mssp_i2c_t *i2c , uint8 ack , uint8 *data)
{
    Std_ReturnType ret = STD_OK ;
    if(  (NULL == i2c)  ||   (NULL == data) )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* Enable Master Receive bit */
        I2C_MASTER_MODE_RECIEVE_ENABLE_FUNC()  ;
        /* Wait until complete transmission */
        while( SSPSTATbits.BF == I2C_BUFREG_IS_EMPTY );
        /* Clear IF */
        PIR1bits.SSPIF = 0 ;
        /* Read data */
        *data = SSPBUF ;
        /* send ack or nack */
        if( ack == I2C_ACKNOWLEDGE )
        {
            SSPCON2bits.ACKDT = I2C_ACKNOWLEDGE ;
            SSPCON2bits.ACKEN = I2C_MASTER_RECEIVE_MODE_ACK_ENABLE ;
        }
        else if( ack == I2C_NOT_ACKNOWLEDGE)
        {
            SSPCON2bits.ACKDT = I2C_NOT_ACKNOWLEDGE ;
            SSPCON2bits.ACKEN = I2C_MASTER_RECEIVE_MODE_ACK_ENABLE ;
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
Std_ReturnType MSSP_I2C_Master_Transmit_write(const mssp_i2c_t *i2c , uint8 *ack ,  uint8 data)
{
    Std_ReturnType ret = STD_OK ;
    if(  (NULL == i2c)  ||  (NULL == ack)  )
    {
        ret = STD_NOT_OK ;
    }
    else{
        /* Writing data on data register */
        SSPBUF = data ;
        /* Wait until complete transmission */
        while( !PIR1bits.SSPIF );
        /* Clear IF */
        PIR1bits.SSPIF = 0 ;
        /* check if ack is received*/
        if( SSPCON2bits.ACKSTAT == I2C_MASTER_TRANSMIT_MODE_ACK_IS_RECIEVED )
        {
            *ack = I2C_ACKNOWLEDGE ;
        }
        else if( SSPCON2bits.ACKSTAT == I2C_MASTER_TRANSMIT_MODE_ACK_IS_NOT_RECIEVED )
        {
            *ack = I2C_NOT_ACKNOWLEDGE ;
        }
        
        
    }
    return ret ;
}


Std_ReturnType MSSP_I2C_Slave_read_write(const mssp_i2c_t *i2c ,  uint8 *data)
{
    Std_ReturnType ret = STD_OK ;
    if(  (NULL == i2c)  ||   (NULL == data) )
    {
        ret = STD_NOT_OK ;
    }
    else{
            /* clock hold */
        I2C_SLAVE_MODE_STRETCH_CLOCK() ;
        /* read or write  data */
        if( (SSPSTATbits.R_nW == I2C_SLAVE_RECEIVE_MODE_WRITE)  &&  (SSPSTATbits.D_nA == I2C_LAST_BYTE_IS_ADDRESS) )
        {
            uint8 empty_buffer = SSPBUF ;                            // clear buffer register to read data 
            while( SSPSTATbits.BF == I2C_BUFREG_IS_EMPTY );          // Wait until complete transmission 
            *data = SSPBUF ;                                         // read data  
        }
        else if( SSPSTATbits.R_nW == I2C_SLAVE_TRANSMIT_MODE_READ )
        {
        
        }
        /* release clock */
        I2C_SLAVE_MODE_RELEASE_CLOCK();
    }
    return ret ;
}



static void I2C_Master_Submode_Configuration(const mssp_i2c_t *i2c)
{
    if (i2c->sub_mode == I2C_MASTER_MODE_DEFINED_CLOCK)
    {
        I2C_SUB_MODE_FUNC(i2c->sub_mode);
        /* clock configuration*/
        SSPADD = (uint8) ((((_XTAL_FREQ / 4.0) / i2c->i2c_clk) - 1));
    }
    
    else if (i2c->sub_mode == I2C_MASTER_MODE_FIRMWARE_CONTROLLED)
    {
        I2C_SUB_MODE_FUNC(i2c->sub_mode);
    } 
}

static void I2C_Slave_Submode_Configuration(const mssp_i2c_t *i2c)
{
    if (i2c->sub_mode == I2C_SLAVE_MODE_7BIT_ADDRESS)
    {
        I2C_SUB_MODE_FUNC(i2c->sub_mode);
    } 
    
    else if (i2c->sub_mode == I2C_SLAVE_MODE_10BIT_ADDRESS)
    {
        I2C_SUB_MODE_FUNC(i2c->sub_mode);
    }
    
    else if (i2c->sub_mode == I2C_SLAVE_MODE_7BIT_ADDRESS_START_STOP_INTERRUPT_ENABLE) 
    {
        I2C_SUB_MODE_FUNC(i2c->sub_mode);
    }
    
    else if (i2c->sub_mode == I2C_SLAVE_MODE_10BIT_ADDRESS_START_STOP_INTERRUPT_ENABLE)
    {
        I2C_SUB_MODE_FUNC(i2c->sub_mode);
    } 
}

static void I2C_General_Call_Configuration(const mssp_i2c_t *i2c)
{
    if( i2c->general_call == I2C_SLAVE_MODE_GENERAL_CALL_INTERRUPT_ENABLE )
    {
        I2C_SLAVE_MODE_GENERAL_CALL_INTERRUPT_ENABLE_FUNC();
    }
    else if( i2c->general_call == I2C_SLAVE_MODE_GENERAL_CALL_DISABLE )
    {
        I2C_SLAVE_MODE_GENERAL_CALL_DISABLE_FUNC() ;
    }
}



static void I2C_Interrupt_Configuration(const mssp_i2c_t *i2c)
{
#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        I2C_INTERRUPT_ENABLE();
        I2C_INTERRUPT_CLR_FLAG();
        
        I2C_BUS_COLLISION_INTERRUPT_ENABLE();
        I2C_BUS_COLLISION_INTERRUPT_CLR_FLAG();
        
        I2C_INTERRUPTHANDLER = i2c->i2c_DefaultInterruptHandler ;
        I2C_COLLISION_ERROR_INTERRUPTHANDLER = i2c->i2c_CollisionError ;
        I2C_OVERFLOW_ERROR_INTERRUPTHANDLER = i2c->i2c_OverflowError ;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE  
        INTERRUPT_InterruptPriorityEnable();
        if(i2c->i2c_priority == HIGH_PRIORITY )
        {
            INTERRUPT_GloblsInterruptHighEnable();
            I2C_INTERRUPT_HIGH_PRIORITY();
        }
        else if(i2c->i2c_priority == LOW_PRIORITY)
        {
            INTERRUPT_GloblsInterruptLowEnable();
            I2C_INTERRUPT_LOW_PRIORITY();
        }
        if(i2c->i2c_collision_priority == HIGH_PRIORITY )
        {
            INTERRUPT_GloblsInterruptHighEnable();
            I2C_BUS_COLLISION_INTERRUPT_HIGH_PRIORITY();
        }
        else if(i2c->i2c_collision_priority == LOW_PRIORITY)
        {
            INTERRUPT_GloblsInterruptLowEnable();
            I2C_BUS_COLLISION_INTERRUPT_LOW_PRIORITY();
        }
#else
    INTCONbits.PEIE = 1 ;
    INTERRUPT_GlobalInterruptEnable();
#endif     
#endif
    
}


void MSSP_I2C_ISR(void)
{
#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    
    I2C_INTERRUPT_CLR_FLAG() ;
    
    /* Code */
    
    if(I2C_INTERRUPTHANDLER)
    {
        I2C_INTERRUPTHANDLER();          /////////  should read in isr application 
    }
    
#endif  
}


void MSSP_I2C_BUS_Collision_ISR(void)
{
#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    
    I2C_BUS_COLLISION_INTERRUPT_CLR_FLAG() ;
    
    /* Code */
    
    if(I2C_COLLISION_ERROR_INTERRUPTHANDLER)
    {
        I2C_COLLISION_ERROR_INTERRUPTHANDLER();          /////////  should read in isr application 
    }
    
#endif  
}