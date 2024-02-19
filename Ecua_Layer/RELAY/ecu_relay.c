/* 
 * File:   ecu_relay.h
 * Author: Alielden
 *
 * Created on September 21, 2023, 1:34 PM
 */

#include "ecu_relay.h"

/**
 * 
 * @param relay
* @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType relay_intialize(relay_t *relay)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == relay ){
         ret = STD_NOT_OK ;
    }
    else{
        pin_config_t pin_obj = {
          .port      = relay->port  ,
          .pin       = relay->pin   ,
          .direction = GPIO_OUTPUT ,
          .logic     = relay->relay_sts
        };
        gpio_pin_intialize(&pin_obj);
    }
    return ret ;
}

/**
 * 
 * @param relay
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType relay_ON(relay_t *relay) 
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == relay ){
         ret = STD_NOT_OK ;
    }
    else{
        pin_config_t pin_obj = {
          .port      = relay->port  ,
          .pin       = relay->pin   ,
          .direction = GPIO_OUTPUT ,
          .logic     = relay->relay_sts
        };
        gpio_pin_write_logic(&pin_obj , relay_on) ;
    }
    return ret ;
}


/**
 * 
 * @param relay
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType relay_OFF(relay_t *relay) 
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == relay ){
         ret = STD_NOT_OK ;
    }
    else{
         pin_config_t pin_obj = {
          .port      = relay->port  ,
          .pin       = relay->pin   ,
          .direction = GPIO_OUTPUT ,
          .logic     = relay->relay_sts
        };
        gpio_pin_write_logic(&pin_obj , relay_off) ;
    }
    return ret ;
}


