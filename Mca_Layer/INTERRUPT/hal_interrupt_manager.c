/* 
 * File:   hal_interrupt_manager.c
 * Author: Alielden
 *
 * Created on October 9, 2023, 6:28 PM
 */

#include "hal_interrupt_manager.h"
#include "hal_external_interrupt.h"

static volatile uint8  RB4_Flag = 1,RB5_Flag = 1,RB6_Flag = 1,RB7_Flag = 1 ;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptManagerHigh(void)
{
        if( (INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
        {
            INT0_ISR();
        }
        else{/*  NOTHING  */};
        
        if( (INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
        {
            INT2_ISR();
        }
        else{/*  NOTHING  */};
       
}

void __interrupt(low_priority)InterruptManagerLow(void)
{
        if( (INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
        {
            INT1_ISR();
        }
        else{/*  NOTHING  */};
}

#else
void __interrupt() InterruptManager(void)
{
    if( (INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else{/*  NOTHING  */};
    
    if( (INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else{/*  NOTHING  */}; 
    
    if( (INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else{/*  NOTHING  */};
    ////////////////////RB4///////////////////////////////////////////
    if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&  (PORTBbits.RB4 == GPIO_HIGH) && (RB4_Flag==1))
    {
        RB4_Flag = 0 ;
        RB4_ISR_High();
    }
    else{/*  NOTHING  */};
    
    if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)  &&  (PORTBbits.RB4 == GPIO_LOW) && (RB4_Flag==0) )
    {
        RB4_Flag = 1 ;
        RB4_ISR_Low();
    }
    else{/*  NOTHING  */};
    ///////////////////////////RB5////////////////////////////////////////////
    if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&&  (PORTBbits.RB5 == GPIO_HIGH) && (RB5_Flag==1))
    {
        RB5_Flag = 0 ;
        RB5_ISR_High();
    }
    else{/*  NOTHING  */};
    
    if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&&  (PORTBbits.RB5 == GPIO_LOW) && (RB5_Flag==0))
    {
        RB5_Flag = 1 ;
        RB5_ISR_Low();
    }
    else{/*  NOTHING  */};
    ////////////////////////////////////////////RB6//////////////////////////////////
    if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&&  (PORTBbits.RB6 == GPIO_HIGH) && (RB6_Flag==1))
    {
        RB6_Flag = 0 ;
        RB6_ISR_High();
    }
    else{/*  NOTHING  */};
    
    if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&&  (PORTBbits.RB6 == GPIO_LOW) && (RB6_Flag==0))
    {
        RB6_Flag = 1 ;
        RB6_ISR_Low();
    }
    else{/*  NOTHING  */};
    ///////////////////////////////////////RB7//////////////////////////////////////////
    if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&&  (PORTBbits.RB7 == GPIO_HIGH) && (RB7_Flag==1))
    {
        RB7_Flag = 0 ;
        RB7_ISR_High();
    }
    else{/*  NOTHING  */};
    
    if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&&  (PORTBbits.RB7 == GPIO_LOW) && (RB7_Flag==0))
    {
        RB7_Flag = 1 ;
        RB7_ISR_Low();
    }
    else{/*  NOTHING  */};
    /////////////////////////////////////// ADC //////////////////////////////////////////////////////
    if( (INTERRUPT_ENABLE == PIE1bits.ADIE ) && (INTERRUPT_OCCUR == PIR1bits.ADIF) )
    {
        ADC_ISR();
    }
    else{/*  NOTHING  */};
    /////////////////////////////////////// TIMER0 //////////////////////////////////////////////////////
    if( (INTERRUPT_ENABLE == INTCONbits.TMR0IE ) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF ) )
    {
        Timer0_ISR();
    }
    else{/*  NOTHING  */};
    /////////////////////////////////////// TIMER1 //////////////////////////////////////////////////////
    if( (INTERRUPT_ENABLE == PIE1bits.TMR1IE ) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF ) )
    {
        Timer1_ISR();
    }
    else{/*  NOTHING  */};
    /////////////////////////////////////// TIMER2 //////////////////////////////////////////////////////
    if( (INTERRUPT_ENABLE == PIE1bits.TMR2IE ) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF ) )
    {
        Timer2_ISR();
    }
    else{/*  NOTHING  */};
     /////////////////////////////////////// TIMER3 //////////////////////////////////////////////////////
    if( (INTERRUPT_ENABLE == PIE2bits.TMR3IE ) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF ) )
    {
        Timer3_ISR();
    }
    else{/*  NOTHING  */};
    /////////////////////////////////////// CCP1 //////////////////////////////////////////////////////
    if( (INTERRUPT_ENABLE == PIE1bits.CCP1IE  ) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF  ) )
    {
        CCP1_ISR();
    }
    else{/*  NOTHING  */};
    /////////////////////////////////////// CCP2 //////////////////////////////////////////////////////
    if( (INTERRUPT_ENABLE == PIE2bits.CCP2IE  ) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF  ) )
    {
        CCP2_ISR();
    }
    else{/*  NOTHING  */};
     /////////////////////////////////////// USART_TX //////////////////////////////////////////////////////
    if( (INTERRUPT_ENABLE == PIE1bits.TXIE ) && (INTERRUPT_OCCUR == PIR1bits.TXIF ) )
    {
        USART_TX_ISR();
    }
    else{/*  NOTHING  */};
     /////////////////////////////////////// USART_RX //////////////////////////////////////////////////////
    if( (INTERRUPT_ENABLE == PIE1bits.RCIE ) && (INTERRUPT_OCCUR == PIR1bits.RCIF ) )
    {
        USART_RX_ISR();
    }
    else{/*  NOTHING  */};
     /////////////////////////////////////// I2C //////////////////////////////////////////////////////
    if( (INTERRUPT_ENABLE == PIE1bits.SSPIE ) && (INTERRUPT_OCCUR == PIR1bits.SSPIF ) )
    {
        MSSP_I2C_ISR();
    }
    else{/*  NOTHING  */};
     /////////////////////////////////////// I2C_COLLISION_ERROR ///////////////////////////////////////////////
    if( (INTERRUPT_ENABLE == PIE2bits.BCLIE ) && (INTERRUPT_OCCUR == PIR2bits.BCLIF ) )
    {
        MSSP_I2C_BUS_Collision_ISR();
    }
    else{/*  NOTHING  */};
    
    
}

#endif