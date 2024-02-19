/* 
 * File:   ecu_dc_motor.c
 * Author: Alielden
 *
 * Created on September 21, 2023, 3:22 PM
 */

#include "ecu_dc_motor.h"


/**
 * 
 * @param dc_motor
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType dc_motor_intialize(dc_motor_t *dc_motor)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == dc_motor ){
         ret = STD_NOT_OK ;
    }
    else{
    
        
        gpio_pin_intialize(&(dc_motor->dc_motor[0]));
        gpio_pin_intialize(&(dc_motor->dc_motor[1]) );
    }
    return ret ;
}

/**
 * 
 * @param dc_motor
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType dc_motor_move_forward(dc_motor_t *dc_motor)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == dc_motor ){
         ret = STD_NOT_OK ;
    }
    else{
       
        
        gpio_pin_write_logic(&(dc_motor->dc_motor[0]) , dc_motor_on );
        gpio_pin_write_logic(&(dc_motor->dc_motor[1]) , dc_motor_off );
    }
    return ret ;
}

/**
 * 
 * @param dc_motor
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType dc_motor_move_backward(dc_motor_t *dc_motor)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == dc_motor ){
         ret = STD_NOT_OK ;
    }
    else{
      
        
        gpio_pin_write_logic(&(dc_motor->dc_motor[0]) , dc_motor_off );
        gpio_pin_write_logic(&(dc_motor->dc_motor[1]) , dc_motor_on );
    }
    
    return ret ;
}


/**
 * 
 * @param dc_motor
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType dc_motor_stop(dc_motor_t *dc_motor)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == dc_motor ){
         ret = STD_NOT_OK ;
    }
    else{
    
        
        gpio_pin_write_logic(&(dc_motor->dc_motor[0]) , dc_motor_off );
        gpio_pin_write_logic(&(dc_motor->dc_motor[1]) , dc_motor_off );
    }
    
    return ret ;
}
      