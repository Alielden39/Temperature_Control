/* 
 * File:   Application.c
 * Author: Alielden
 *
 * Created on September 9, 2023, 6:23 PM
 */

#include "Application.h"


#if ( CPU_CFG == CPU1 )

Std_ReturnType ret = STD_OK ;
uint8 ack = 0 , flag = 0   ;
uint8 adc_res_txt[6] ;
volatile uint16 adc_val = 0 , temp = 0 ;
uint16 sensor_read = 0 , count = 0 ;


void ADC_CallBack(void);
void I2C_send_byte(uint8 address , uint8 data);

led_t green_led =
{
  .port =  GPIO_PORTD ,
  .pin =   GPIO_PIN1 ,
  .led_status = led_OFF
};

led_t red_led =
{
  .port =  GPIO_PORTD ,
  .pin =   GPIO_PIN0 ,
  .led_status = led_OFF
};

led_t blue_led =
{
  .port =  GPIO_PORTD ,
  .pin =   GPIO_PIN2 ,
  .led_status = led_OFF
};


lcd_8bit_t lcd = 
{
  .lcd_rs.port      = GPIO_PORTA ,
  .lcd_rs.pin       = GPIO_PIN6 ,
  .lcd_rs.logic     = GPIO_LOW ,
  .lcd_rs.direction = GPIO_OUTPUT ,
  
  .lcd_en.port      = GPIO_PORTA ,
  .lcd_en.pin       = GPIO_PIN5 ,
  .lcd_en.logic     = GPIO_LOW ,
  .lcd_en.direction = GPIO_OUTPUT ,
  
  .lcd_data[0].port      = GPIO_PORTB ,
  .lcd_data[0].pin       = GPIO_PIN0 ,
  .lcd_data[0].logic     = GPIO_LOW ,
  .lcd_data[0].direction = GPIO_OUTPUT ,
  
  .lcd_data[1].port      = GPIO_PORTB ,
  .lcd_data[1].pin       = GPIO_PIN1 ,
  .lcd_data[1].logic     = GPIO_LOW ,
  .lcd_data[1].direction = GPIO_OUTPUT ,
  
  .lcd_data[2].port      = GPIO_PORTB ,
  .lcd_data[2].pin       = GPIO_PIN2 ,
  .lcd_data[2].logic     = GPIO_LOW ,
  .lcd_data[2].direction = GPIO_OUTPUT ,
  
  .lcd_data[3].port      = GPIO_PORTB ,
  .lcd_data[3].pin       = GPIO_PIN3 ,
  .lcd_data[3].logic     = GPIO_LOW ,
  .lcd_data[3].direction = GPIO_OUTPUT ,
  
  .lcd_data[4].port      = GPIO_PORTB ,
  .lcd_data[4].pin       = GPIO_PIN4 ,
  .lcd_data[4].logic     = GPIO_LOW ,
  .lcd_data[4].direction = GPIO_OUTPUT ,
  
  .lcd_data[5].port      = GPIO_PORTB ,
  .lcd_data[5].pin       = GPIO_PIN5 ,
  .lcd_data[5].logic     = GPIO_LOW ,
  .lcd_data[5].direction = GPIO_OUTPUT ,
  
  .lcd_data[6].port      = GPIO_PORTB ,
  .lcd_data[6].pin       = GPIO_PIN6 ,
  .lcd_data[6].logic     = GPIO_LOW ,
  .lcd_data[6].direction = GPIO_OUTPUT ,
  
  .lcd_data[7].port      = GPIO_PORTB ,
  .lcd_data[7].pin       = GPIO_PIN7 ,
  .lcd_data[7].logic     = GPIO_LOW ,
  .lcd_data[7].direction = GPIO_OUTPUT ,
};

mssp_i2c_t i2c_obj =
{
   .mode = I2C_MASTER_MODE ,
   .sub_mode = I2C_MASTER_MODE_DEFINED_CLOCK ,
   .i2c_clk = 100000 ,
   .SMBus = I2C_SMBUS_DISABLE ,
   .slew_rate = I2C_SLEW_RATE_DISABLE ,
};


adc_t adc =
{
  .adc_call_back = ADC_CallBack ,
  .Format_Select = RIGHT_FORMAT ,
  .Taq = ADC_12_TAD ,
  .Voltage_Refrence = VSS_VDD ,
  .channel = ADC_CHANNEL_AN0 ,
  .clk = ADC_FOSC_DIVIDE_16
};


int main() {
    
    APPLICATION_INTIALIZE();
    
    ret = lcd_8bit_send_string_data_pos(&lcd , 1 , 1 , "Temp  : ") ;
    
    
    
    while(1)
    {
        /* Start Conversion */
        if( flag == 0 )
        {
            while( count != 1000 ) 
            {
                count++ ;
                ret = ADC_GetConversion_Interrupt(&adc , ADC_CHANNEL_AN0 );
            }
            ret = ADC_GetConversion_Interrupt(&adc , ADC_CHANNEL_AN0 );
            flag = 1 ;
        }
        
        /* take the read of sensor */
        else if( flag == 2 )
        {
            sensor_read = adc_val * 4.88f ;
            sensor_read /= 10 ;
            ret = convert_short_to_string(sensor_read , adc_res_txt ) ;         
            ret = lcd_8bit_send_string_data_pos(&lcd , 1 , 12 , adc_res_txt ) ;
            flag = 0 ;
        }
        if( temp != sensor_read )
        {
            temp = sensor_read ;
            I2C_send_byte(SLAVE_1 , sensor_read ) ;
        }
        
        /* led configuration */
        if( sensor_read >= 30 )
        {
            red_led_turn_on() ;
            green_led_turn_off();
            blue_led_turn_off();
        }
        else if( (sensor_read < 30 )  &&  ( sensor_read > 25 ) )
        {
            red_led_turn_off() ;
            green_led_turn_on();
            blue_led_turn_off();
        }
        else if( sensor_read < 25 )
        {
            red_led_turn_off() ;
            green_led_turn_off();
            blue_led_turn_on();
        }      
    }

    return (EXIT_SUCCESS);
}


void APPLICATION_INTIALIZE(void)
{
    ret = MSSP_I2C_init(&i2c_obj);
    ret = ADC_Init(&adc);
    ret = lcd_8bit_intialize(&lcd) ;
    ret = led_intialize(&green_led);
    ret = led_intialize(&red_led);
    ret = led_intialize(&blue_led);
}


void ADC_CallBack(void)
{
    ret = ADC_ConversionValue(&adc , &adc_val ) ;
    flag = 2 ; 
}

void I2C_send_byte(uint8 address , uint8 data)
{
    ret = MSSP_I2C_send_start(&i2c_obj) ;
    ret = MSSP_I2C_Master_Transmit_write(&i2c_obj  , &ack , address ) ;
    ret = MSSP_I2C_Master_Transmit_write(&i2c_obj  , &ack , data ) ;
    ret = MSSP_I2C_send_stop(&i2c_obj ) ;
}


void green_led_turn_on(void)
{
    ret = led_turn_on(&green_led);
}

void green_led_turn_off(void)
{
    ret = led_turn_off(&green_led);
}

void red_led_turn_on(void)
{
    ret = led_turn_on(&red_led);
}

void red_led_turn_off(void)
{
    ret = led_turn_off(&red_led);
}

void blue_led_turn_on(void)
{
    ret = led_turn_on(&blue_led);
}

void blue_led_turn_off(void)
{
    ret = led_turn_off(&blue_led);
}



#endif



#if ( CPU_CFG == CPU2 )

Std_ReturnType ret = STD_OK ;
uint8 duty_cycle = 0 ;
volatile uint8 slave1_data = 0 ;

void I2C_callback(void);


mssp_i2c_t i2c_obj =
{
   .mode = I2C_SLAVE_MODE ,
   .sub_mode = I2C_SLAVE_MODE_7BIT_ADDRESS ,
   .SMBus = I2C_SMBUS_DISABLE ,
   .slew_rate = I2C_SLEW_RATE_DISABLE ,
   .i2c_DefaultInterruptHandler = I2C_callback ,
   .i2c_CollisionError = NULL ,
   .i2c_OverflowError = NULL ,
   .i2c_priority = LOW_PRIORITY ,
   .i2c_collision_priority = LOW_PRIORITY ,
   .general_call = I2C_SLAVE_MODE_GENERAL_CALL_DISABLE ,
   .slave_address = SLAVE_1
   
};

timer2_t  tmr2 = 
{
  .prescaler_value = TIMER2_PRESCALER_DIV_BY_1 ,
  .postscaler_value = timer2_postscaler_div_1 ,
  .Timer2_Preload_Value = 0
};


 
ccp_t ccp_obj1 =
{
  .PWM_Freq = 15000 ,
  .Sub_Mode = CCP_PWM_MODE ,
  ._mode = _PWM_MODE ,
  .Timer2_postscaler_value = CCP_TIMER2_PRESCALER_DIV_BY_1 ,
  .Timer2_prescaler_value = CCP_timer2_postscaler_div_1 ,
  .pin.direction = GPIO_OUTPUT ,
  .pin.logic = GPIO_LOW ,
  .pin.port = GPIO_PORTC ,
  .pin.pin = GPIO_PIN2  , 
  .ccp_inst = ccp1_inst 
};

ccp_t ccp_obj2 =
{
  .PWM_Freq = 15000 ,
  .Sub_Mode = CCP_PWM_MODE ,
  ._mode = _PWM_MODE ,
  .Timer2_postscaler_value = CCP_TIMER2_PRESCALER_DIV_BY_1 ,
  .Timer2_prescaler_value = CCP_timer2_postscaler_div_1 ,
  .pin.direction = GPIO_OUTPUT ,
  .pin.logic = GPIO_LOW ,
  .pin.port = GPIO_PORTC ,
  .pin.pin = GPIO_PIN1  , 
  .ccp_inst = ccp2_inst 
};



void I2C_callback(void)
{
    ret = MSSP_I2C_Slave_read_write(&i2c_obj , &slave1_data) ;
}

int main() {
    PIE1bits.ADIE = 0 ;
    APPLICATION_INTIALIZE();
    
    ret = CCP_PWM_Set_Duty(&ccp_obj1 , 0 ) ;
    ret = CCP_PWM_Start(&ccp_obj1) ;
    
    ret = CCP_PWM_Set_Duty(&ccp_obj2 , 0 ) ;
    ret = CCP_PWM_Start(&ccp_obj2) ;
    
    while(1)
    {
        if(  slave1_data  >=  30    )
        {
            ret = CCP_PWM_Set_Duty(&ccp_obj1 , slave1_data * 2 ) ;
            ret = CCP_PWM_Start(&ccp_obj1) ;
            ret = CCP_PWM_Stop(&ccp_obj2) ;
        }
        else if( slave1_data  <=  25 )
        {
            ret = CCP_PWM_Set_Duty(&ccp_obj2 , 100 - (slave1_data*2) ) ;
            ret = CCP_PWM_Start(&ccp_obj2) ;
            ret = CCP_PWM_Stop(&ccp_obj1) ;
        }
        else if(  25 < slave1_data < 30 )
        {
            ret = CCP_PWM_Stop(&ccp_obj1) ;
            ret = CCP_PWM_Stop(&ccp_obj2) ;
        }
        
    }

    return (EXIT_SUCCESS);
}


void APPLICATION_INTIALIZE(void)
{
    ret = Timer2_init(&tmr2) ;
    ret = CCP_Init(&ccp_obj1) ;
    ret = CCP_Init(&ccp_obj2) ;
    ret = MSSP_I2C_init(&i2c_obj);
    
    
}

#endif



