/* 
 * File:   hal_interrupt_manager.h
 * Author: Alielden
 *
 * Created on October 9, 2023, 6:28 PM
 */

#ifndef HAL_INTERRUPT_MANAGER_H
#define	HAL_INTERRUPT_MANAGER_H

/* Section :  Includes */
#include "hal_interrupt_config.h"

 /* Section : Macros */


/* Section : Macros Functions */


/* Section : Data type Declaration */


/* Section : Functions Declaration */

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR_High(void);
void RB4_ISR_Low(void);
void RB5_ISR_High(void);
void RB5_ISR_Low(void);
void RB6_ISR_High(void);
void RB6_ISR_Low(void);
void RB7_ISR_High(void);
void RB7_ISR_Low(void);

void ADC_ISR(void) ;

void Timer0_ISR(void) ;
void Timer1_ISR(void) ;
void Timer2_ISR(void) ;
void Timer3_ISR(void) ;

void CCP1_ISR(void) ;
void CCP2_ISR(void) ;

void USART_TX_ISR(void) ;
void USART_RX_ISR(void) ;

void MSSP_I2C_ISR(void);
void MSSP_I2C_BUS_Collision_ISR(void);

#endif	/* HAL_INTERRUPT_MANAGER_H */

