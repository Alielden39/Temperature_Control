/* 
 * File:   Application.h
 * Author: Alielden
 *
 * Created on September 9, 2023, 7:04 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section :  Includes */
#include "Mca_Layer/GPIO/hal_gpio.h"
#include "Ecua_Layer/LED/ecu_led.h"
#include "Ecua_Layer/BUTTON/ecu_button.h"
#include "Ecua_Layer/RELAY/ecu_relay.h"
#include "Ecua_Layer/DC_MOTOR/ecu_dc_motor.h"
#include "Ecua_Layer/7_SEGMENT/ecu_seven_seg.h"
#include "Ecua_Layer/KEYPAD/ecu_keypad.h"
#include "Ecua_Layer/LCD/ecu_lcd.h"
#include "Mca_Layer/INTERRUPT/hal_external_interrupt.h"
#include "Mca_Layer/INTERRUPT/hal_internal_interrupt.h"
#include "Mca_Layer/INTERRUPT/hal_interrupt_manager.h"
#include "Mca_Layer/INTERRUPT/hal_interrupt_config.h"
#include "Mca_Layer/EEPROM/hal_eeprom.h"
#include "Mca_Layer/ADC/hal_adc.h"
#include "Mca_Layer/TIMER0/hal_timer0.h"
#include "Mca_Layer/TIMER1/hal_timer_1.h"
#include "Mca_Layer/TIMER2/hal_timer2.h"
#include "Mca_Layer/TIMER3/hal_timer3.h"
#include "Mca_Layer/CCP1/hal_ccp.h"
#include "Mca_Layer/usart/hal_usart.h"
#include "Mca_Layer/I2C/hal_i2c.h"
#include <xc.h>


 /* Section : Macros */

#define SLAVE_1   0x60    // 0x30 + r/w(0)


#define CPU1    1
#define CPU2    2


#define CPU_CFG    (CPU1)

/* Section : Macros Functions */



/* Section : Data type Declaration */


/* Section : Functions Declaration */

void APPLICATION_INTIALIZE(void);

void green_led_turn_on(void);
void green_led_turn_off(void);
void red_led_turn_on(void);
void red_led_turn_off(void);
void blue_led_turn_on(void);
void blue_led_turn_off(void);




#endif	/* APPLICATION_H */

