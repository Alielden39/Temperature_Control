/* 
 * File:   hal_interrupt_config.h
 * Author: Alielden
 *
 * Created on October 9, 2023, 6:38 PM
 */

#ifndef HAL_INTERRUPT_CONFIG_H
#define	HAL_INTERRUPT_CONFIG_H

/* Section :  Includes */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_interrupt_gen_config.h"
#include "../GPIO/hal_gpio.h"
#include "../ADC/hal_adc_cfg.h"

 /* Section : Macros */

#define INTERRUPT_DISABLE 0
#define INTERRUPT_ENABLE  1

#define INTERRUPT_NOT_OCCUR 0
#define INTERRUPT_OCCUR     1

#define INTERRUPT_PRIORITY_DISABLE 0
#define INTERRUPT_PRIORITY_ENABLE  1

/* Section : Macros Functions */
#define INTERRUPT_InterruptPriorityEnable()      (RCONbits.IPEN = 1 )
#define INTERRUPT_InterruptPriorityDisable()     (RCONbits.IPEN = 0 )

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

#define INTERRUPT_GloblsInterruptHighEnable()    (INTCONbits.GIEH = 1)
#define INTERRUPT_GloblsInterruptHighDisable()  (INTCONbits.GIEH = 0)

#define INTERRUPT_GloblsInterruptLowEnable()     (INTCONbits.GIEL = 1)
#define INTERRUPT_GloblsInterruptLowDisable()    (INTCONbits.GIEL = 0)

#else

#define INTERRUPT_PeripheralInterruptEnable()    (INTCONbits.PEIE = 1)
#define INTERRUPT_PeripheralInterruptDisable()   (INTCONbits.PEIE = 0)

#define INTERRUPT_GlobalInterruptEnable()        (INTCONbits.GIE = 1 )
#define INTERRUPT_GlobalInterruptDisable()       (INTCONbits.GIE = 0 )

#endif

/* Section : Data type Declaration */


/* Section : Functions Declaration */

#endif	/* HAL_INTERRUPT_CONFIG_H */

