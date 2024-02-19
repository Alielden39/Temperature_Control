/* 
 * File:   ecu_relay.h
 * Author: Alielden
 *
 * Created on September 21, 2023, 1:34 PM
 */

#ifndef ECU_RELAY_H

/* Section :  Includes */

#include "../../Mca_Layer/GPIO/hal_gpio.h"

 /* Section : Macros */



/* Section : Macros Functions */


/* Section : Data type Declaration */

typedef enum 
{
    relay_off = 0 ,
    relay_on       
}relay_status_t;

typedef struct{
    uint8 port         : 3 ;
    uint8 pin          : 3 ;
    uint8 relay_sts    : 1 ;
}relay_t;

/* Section : Functions Declaration */

Std_ReturnType relay_intialize(relay_t *relay);
Std_ReturnType relay_ON(relay_t *relay) ;
Std_ReturnType relay_OFF(relay_t *relay) ;

#endif	/* ECU_RELAY_H */

