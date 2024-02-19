/* 
 * File:   ecu_dc_motor.h
 * Author: Alielden
 *
 * Created on September 21, 2023, 3:22 PM
 */

#ifndef ECU_DC_MOTOR_H

/* Section :  Includes */

#include "../../Mca_Layer/GPIO/hal_gpio.h"

/* Section : Macros */



/* Section : Macros Functions */


/* Section : Data type Declaration */

typedef enum 
{
    dc_motor_on = 0 ,
    dc_motor_off
}dc_motor_status_t;


typedef struct
{
    pin_config_t dc_motor[2] ;    // Because Dc motor driver need 2 pins from MCU to control direction . 
}dc_motor_t;

/* Section : Functions Declaration */

Std_ReturnType dc_motor_intialize(dc_motor_t *dc_motor);
Std_ReturnType dc_motor_move_forward(dc_motor_t *dc_motor);
Std_ReturnType dc_motor_move_backward(dc_motor_t *dc_motor);
Std_ReturnType dc_motor_stop(dc_motor_t *dc_motor);




#endif	/* ECU_DC_MOTOR_H */

