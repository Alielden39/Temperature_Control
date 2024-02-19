/* 
 * File:   ecu_led.h
 * Author: Alielden
 *
 * Created on September 9, 2023, 6:58 PM
 */

#ifndef LED_H
#define	LED_H

/* Section :  Includes */

#include "../../Mca_Layer/GPIO/hal_gpio.h"


 /* Section : Macros */


/* Section : Macros Functions */


/* Section : Data type Declaration */

typedef enum{
    led_OFF = 0 ,
    led_ON        
}led_status;


typedef struct{
    uint8 port            : 3 ;
    uint8 pin             : 3 ;
    uint8 led_status : 1 ;
}led_t;

/* Section : Functions Declaration */

Std_ReturnType led_intialize (led_t *led );
Std_ReturnType led_turn_on (led_t *led );
Std_ReturnType led_turn_off (led_t *led );
Std_ReturnType led_turn_toggle (led_t *led );


#endif	/* LED_H */

