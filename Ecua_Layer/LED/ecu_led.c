/* 
 * File:   ecu_led.c
 * Author: Alielden
 *
 * Created on September 9, 2023, 6:58 PM
 */

#include "ecu_led.h"

/**
 * 
 * @param led
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType led_intialize (led_t *led ){
    Std_ReturnType ret = STD_OK ;
    if( NULL == led ){
         ret = STD_NOT_OK ;
    }
    else{
        pin_config_t pin_led = {
            .port      = led->port ,
            .pin       = led->pin ,
            .direction = GPIO_OUTPUT ,
            .logic     = led->led_status
        };
        gpio_pin_intialize(&pin_led) ;
    }
    return ret ; 
}


/**
 * 
 * @param led
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType led_turn_on (led_t *led ){
    Std_ReturnType ret = STD_OK ;
    if( NULL == led ){
         ret = STD_NOT_OK ;
    }
    else{
        pin_config_t pin_led = {
            .port      = led->port ,
            .pin       = led->pin ,
            .direction = GPIO_OUTPUT ,
            .logic     = led->led_status
        };
        gpio_pin_write_logic(&pin_led , led_ON ) ;
    }
    return ret ; 
}


/**
 * 
 * @param led
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType led_turn_off (led_t *led ){
    Std_ReturnType ret = STD_OK ;
    if( NULL == led ){
         ret = STD_NOT_OK ;
    }
    else{
        pin_config_t pin_led = {
            .port      = led->port ,
            .pin       = led->pin ,
            .direction = GPIO_OUTPUT ,
            .logic     = led->led_status
        };
        gpio_pin_write_logic(&pin_led , led_OFF ) ;
    }
    return ret ; 
    
}


/**
 * 
 * @param led
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType led_turn_toggle (led_t *led ){
    Std_ReturnType ret = STD_OK ;
    if( NULL == led ){
         ret = STD_NOT_OK ;
    }
    else{
        pin_config_t pin_led = {
            .port      = led->port ,
            .pin       = led->pin ,
            .direction = GPIO_OUTPUT ,
            .logic     = led->led_status
        };
        gpio_pin_toggle_logic(&pin_led ) ;
    }
    return ret ; 
}