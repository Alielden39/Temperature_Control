/* 
 * File:   ecu_button.h
 * Author: Alielden
 *
 * Created on September 14, 2023, 11:32 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section :  Includes */

#include "../../Mca_Layer/GPIO/hal_gpio.h"

 /* Section : Macros */


/* Section : Macros Functions */


/* Section : Data type Declaration */

typedef enum{
    button_released = 0 ,
    button_pressed
            
}button_state_t;


typedef enum{
    
    active_low = 0 ,
    active_high
            
}button_active_t;



typedef struct{
    pin_config_t     pin ;
    button_state_t   button_status ;
    button_active_t  button_connection ;
}button_t;


/* Section : Functions Declaration */
Std_ReturnType  button_intailze(button_t *button);
Std_ReturnType  button_read_status(button_t *button ,button_state_t *button_status );


#endif	/* ECU_BUTTON_H */

