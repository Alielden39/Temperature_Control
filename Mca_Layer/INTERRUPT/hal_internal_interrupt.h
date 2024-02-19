/* 
 * File:   hal_internal_interrupt.h
 * Author: Alielden
 *
 * Created on October 9, 2023, 6:29 PM
 */

#ifndef HAL_INTERNAL_INTERRUPT_H
#define	HAL_INTERNAL_INTERRUPT_H

/* Section :  Includes */

#include "hal_interrupt_config.h"
#include "hal_external_interrupt.h"
#include "hal_interrupt_gen_config.h"

 /* Section : Macros */


/* Section : Macros Functions */

/********************** ADC ********************/
#ifdef ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_ENABLE()      (PIE1bits.ADIE = 1 )
#define ADC_INTERRUPT_DISABLE()     (PIE1bits.ADIE = 0 )
#define ADC_INTERRUPT_CLR_FLAG()    (PIR1bits.ADIF = 0 )

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_HIGH_PRIORITY()  (IPR1bits.ADIP = 1)
#define ADC_INTERRUPT_LOW_PRIORITY()   (IPR1bits.ADIP = 0)
#endif              
#endif

/********************** TIMER0 ********************/
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_ENABLE()     ( INTCONbits.TMR0IE = 1 )
#define TIMER0_INTERRUPT_DISABLE()    ( INTCONbits.TMR0IE = 0 )
#define TIMER0_INTERRUPT_CLR_FLAG()   ( INTCONbits.TMR0IF = 0 ) 

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_HIGH_PRIORITY()  (INTCON2bits.TMR0IP = 1)
#define TIMER0_INTERRUPT_LOW_PRIORITY()   (INTCON2bits.TMR0IP = 0)
#endif              
#endif



/********************** TIMER1 ********************/
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_ENABLE()     ( PIE1bits.TMR1IE = 1 )
#define TIMER1_INTERRUPT_DISABLE()    ( PIE1bits.TMR1IE = 0 )
#define TIMER1_INTERRUPT_CLR_FLAG()   ( PIR1bits.TMR1IF = 0 ) 

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_HIGH_PRIORITY()  (IPR1bits.TMR1IP = 1)
#define TIMER1_INTERRUPT_LOW_PRIORITY()   (IPR1bits.TMR1IP = 0)
#endif              
#endif


/********************** TIMER2 ********************/
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_ENABLE()     ( PIE1bits.TMR2IE = 1 )
#define TIMER2_INTERRUPT_DISABLE()    ( PIE1bits.TMR2IE = 0 )
#define TIMER2_INTERRUPT_CLR_FLAG()   ( PIR1bits.TMR2IF = 0 ) 

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_HIGH_PRIORITY()  (IPR1bits.TMR2IP = 1)
#define TIMER2_INTERRUPT_LOW_PRIORITY()   (IPR1bits.TMR2IP = 0)
#endif              
#endif

/********************** TIMER3 ********************/
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_ENABLE()     ( PIE2bits.TMR3IE = 1 )
#define TIMER3_INTERRUPT_DISABLE()    ( PIE2bits.TMR3IE = 0 )
#define TIMER3_INTERRUPT_CLR_FLAG()   ( PIR2bits.TMR3IF = 0 ) 

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_HIGH_PRIORITY()  (IPR2bits.TMR3IP = 1)
#define TIMER3_INTERRUPT_LOW_PRIORITY()   (IPR2bits.TMR3IP = 0)
#endif              
#endif

/********************** CCP1 ********************/
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define CCP1_INTERRUPT_ENABLE()     ( PIE1bits.CCP1IE = 1 )
#define CCP1_INTERRUPT_DISABLE()    ( PIE1bits.CCP1IE = 0 )
#define CCP1_INTERRUPT_CLR_FLAG()   ( PIR1bits.CCP1IF = 0 ) 

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define CCP1_INTERRUPT_HIGH_PRIORITY()  (IPR1bits.CCP1IP = 1)
#define CCP1_INTERRUPT_LOW_PRIORITY()   (IPR1bits.CCP1IP = 0)
#endif              
#endif

/********************** CCP2 ********************/
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_ENABLE()     ( PIE2bits.CCP2IE = 1 )
#define CCP2_INTERRUPT_DISABLE()    ( PIE2bits.CCP2IE = 0 )
#define CCP2_INTERRUPT_CLR_FLAG()   ( PIR2bits.CCP2IF = 0 ) 

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_HIGH_PRIORITY()  (IPR2bits.CCP2IP = 1)
#define CCP2_INTERRUPT_LOW_PRIORITY()   (IPR2bits.CCP2IP = 0)
#endif              
#endif
/********************** USART_TX ********************/
#ifdef USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define USART_TX_INTERRUPT_ENABLE()     ( PIE1bits.TXIE = 1 )
#define USART_TX_INTERRUPT_DISABLE()    ( PIE1bits.TXIE = 0 )

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define USART_TX_INTERRUPT_HIGH_PRIORITY()  ( IPR1bits.TXIP = 1)
#define USART_TX_INTERRUPT_LOW_PRIORITY()   ( IPR1bits.TXIP = 0)
#endif              
#endif


/********************** USART_RX ********************/
#ifdef USART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define USART_RX_INTERRUPT_ENABLE()     ( PIE1bits.RCIE = 1 )
#define USART_RX_INTERRUPT_DISABLE()    ( PIE1bits.RCIE = 0 )
  
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define USART_RX_INTERRUPT_HIGH_PRIORITY()  ( IPR1bits.RCIP = 1)
#define USART_RX_INTERRUPT_LOW_PRIORITY()   ( IPR1bits.RCIP = 0)
#endif              
#endif

/********************** I2C ********************/
#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define I2C_INTERRUPT_ENABLE()                   ( PIE1bits.SSPIE = 1 )
#define I2C_INTERRUPT_DISABLE()                  ( PIE1bits.SSPIE = 0 )
#define I2C_INTERRUPT_CLR_FLAG()                 ( PIR1bits.SSPIF = 0 ) 

#define I2C_BUS_COLLISION_INTERRUPT_ENABLE()     ( PIE2bits.BCLIE = 1 )
#define I2C_BUS_COLLISION_INTERRUPT_DISABLE()    ( PIE2bits.BCLIE = 0 )
#define I2C_BUS_COLLISION_INTERRUPT_CLR_FLAG()   ( PIR2bits.BCLIF = 0 )
  
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define I2C_INTERRUPT_HIGH_PRIORITY()  ( IPR1bits.SSPIP = 1)
#define I2C_INTERRUPT_LOW_PRIORITY()   ( IPR1bits.SSPIP = 0)

#define I2C_BUS_COLLISION_INTERRUPT_HIGH_PRIORITY()  ( IPR2bits.BCLIP = 1)
#define I2C_BUS_COLLISION_INTERRUPT_LOW_PRIORITY()   ( IPR2bits.BCLIP = 0)
#endif              
#endif



/* Section : Data type Declaration */


/* Section : Functions Declaration */

#endif	/* HAL_INTERNAL_INTERRUPT_H */

