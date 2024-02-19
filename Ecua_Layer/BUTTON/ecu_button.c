/* 
 * File:   ecu_button.c
 * Author: Alielden
 *
 * Created on September 14, 2023, 11:32 PM
 */

#include "ecu_button.h"


/**
 * 
 * @param button
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType  button_intailze(button_t *button){
    Std_ReturnType ret = STD_OK ;
    if( NULL == button ){
         ret = STD_NOT_OK ;
    }
    else{
        gpio_pin_direction_intialize(&(button->pin)) ;
    }
    return ret ;
}


/**
 * 
 * @param button
 * @param button_status
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType  button_read_status(button_t *button ,button_state_t *button_status ){
    Std_ReturnType ret = STD_OK ;
    logic_t logic = 0 ;
    if( (NULL == button)  ||   (NULL == button_status) ){
         ret = STD_NOT_OK ;
    }
    else{
        switch(button->button_connection){
            case active_high :
                ret = gpio_pin_read_logic( &(button->pin) , &logic ) ;
                if(GPIO_HIGH == logic){
                    *button_status = button_pressed ;
                }
                else{
                    *button_status = button_released ;
                }
                break;
                
            case active_low :
                ret = gpio_pin_read_logic( &(button->pin) , &logic ) ;
                if( GPIO_LOW == logic ){
                    *button_status = button_pressed ;
                }
                else{
                    *button_status = button_released ;
                }
                break;
                
            default :
                ret = STD_NOT_OK ;
        }
    }
    return ret ;
    
}
