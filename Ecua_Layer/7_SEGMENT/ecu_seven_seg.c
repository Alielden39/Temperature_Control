/* 
 * File:   ecu_seven_seg.?
 * Author: Alielden
 *
 * Created on September 25, 2023, 5:59 PM
 */

#include "ecu_seven_seg.h"

/**
 * 
 * @param segment
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType seven_segment_intialize(segment_config_t *segment) 
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == segment ){
         ret = STD_NOT_OK ;
    }
    else{
        gpio_pin_intialize(& (segment->segment_pins[0]) ) ;
        gpio_pin_intialize(& (segment->segment_pins[1]) ) ;
        gpio_pin_intialize(& (segment->segment_pins[2]) ) ;
        gpio_pin_intialize(& (segment->segment_pins[3]) ) ;
        
    }
    
    return ret ;
}


/**
 * 
 * @param segment
 * @param number
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType seven_segment_write_number(segment_config_t *segment , uint8 number) 
{
    Std_ReturnType ret = STD_OK ;
    if( (NULL == segment)  ||   ( number > 9 ) ){
         ret = STD_NOT_OK ;
    }
    else{
        gpio_pin_write_logic(& (segment->segment_pins[0]) , (number>>0) & 0x01 ) ;
        gpio_pin_write_logic(& (segment->segment_pins[1]) , (number>>1) & 0x01 ) ;
        gpio_pin_write_logic(& (segment->segment_pins[2]) , (number>>2) & 0x01 ) ;
        gpio_pin_write_logic(& (segment->segment_pins[3]) , (number>>3) & 0x01 ) ;
        
    }
    
    return ret ;
}