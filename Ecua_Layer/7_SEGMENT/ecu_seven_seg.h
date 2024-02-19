/* 
 * File:   ecu_seven_seg.h
 * Author: Alielden
 *
 * Created on September 25, 2023, 5:59 PM
 */

#ifndef ECU_SEVEN_SEG_H

/* Section :  Includes */

#include "../../Mca_Layer/GPIO/hal_gpio.h"

/* Section : Macros */



/* Section : Macros Functions */


/* Section : Data type Declaration */

typedef enum 
{
    SEGMENT_COMMON_ANODE = 0 ,
    SEGMENT_COMMON_CATHODE
}segment_type_t;


typedef struct
{
    pin_config_t   segment_pins[4] ;
    segment_type_t segment_type ;
}segment_config_t;

/* Section : Functions Declaration */

Std_ReturnType seven_segment_intialize(segment_config_t *segment) ;
Std_ReturnType seven_segment_write_number(segment_config_t *segment , uint8 number) ;

#endif	/* ECU_SEVEN_SEG_H */

