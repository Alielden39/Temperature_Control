/* 
 * File:   hal_ccp.h
 * Author: Alielden
 *
 * Created on February 4, 2024, 4:46 PM
 */

#ifndef HAL_CCP1_H

/* Section :  Includes */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../INTERRUPT/hal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "hal_ccp_cfg.h"
 

/* Section : Macros */

#define DISABLE_CCP                        0
#define CCP_CAPTURE_MODE_FALLING_EDGE      4
#define CCP_CAPTURE_MODE_RISING_EDGE       5
#define CCP_CAPTURE_MODE_4TH_RISING_EDGE   6
#define CCP_CAPTURE_MODE_16TH_RISING_EDGE  7
#define CCP_COMPARE_MODE_TOGGLE_OUTPUT     2 
#define CCP_COMPARE_MODE_CCP_PIN_LOW       8
#define CCP_COMPARE_MODE_CCP_PIN_HIGH      9
#define CCP_PWM_MODE                       12


#define CAPTURE_NOT_OCURRED   0
#define CAPTURE_OCURRED       1

#define COMPARE_NOT_OCURRED   0
#define COMPARE_OCURRED       1


#define CCP_TIMER2_PRESCALER_DIV_BY_1   1
#define CCP_TIMER2_PRESCALER_DIV_BY_4   4
#define CCP_TIMER2_PRESCALER_DIV_BY_16  16


#define CCP_timer2_postscaler_div_1      1 
#define CCP_timer2_postscaler_div_2      2
#define CCP_timer2_postscaler_div_3      3
#define CCP_timer2_postscaler_div_4      4
#define CCP_timer2_postscaler_div_5      5
#define CCP_timer2_postscaler_div_6      6
#define CCP_timer2_postscaler_div_7      7
#define CCP_timer2_postscaler_div_8      8
#define CCP_timer2_postscaler_div_9      9
#define CCP_timer2_postscaler_div_10     10
#define CCP_timer2_postscaler_div_11     11
#define CCP_timer2_postscaler_div_12     12
#define CCP_timer2_postscaler_div_13     13
#define CCP_timer2_postscaler_div_14     14
#define CCP_timer2_postscaler_div_15     15
#define CCP_timer2_postscaler_div_16     16

/* Section : Macros Functions */

#define CCP1_SET_MODE(mode)     (CCP1CONbits.CCP1M = mode)
#define CCP2_SET_MODE(mode)     (CCP2CONbits.CCP2M = mode)

/* Section : Data type Declaration */
typedef enum 
{
    _CAPTURE_MODE = 0 ,
    _COMPARE_MODE ,
    _PWM_MODE        
}ccp_mode;

typedef enum 
{
   CCP1_TIMER1_CCP2_TIMER1 = 0 ,
   CCP1_TIMER1_CCP2_TIMER3 ,
   CCP1_TIMER3_CCP2_TIMER3        
}ccp_timer;

typedef enum
{
    ccp1_inst = 0 ,
    ccp2_inst        
}ccp_inst_t;

typedef struct 
{ 
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*ccp1_call_back)(void) ;
    uint8 ccp1_priority ; 
#endif  
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*ccp2_call_back)(void) ;
    uint8 ccp2_priority ; 
#endif  
    ccp_mode _mode  ;
    uint8 Sub_Mode   ;
    pin_config_t pin ;
    ccp_inst_t ccp_inst ; 
#if (CCP1_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED)  ||  (CCP2_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED) 
    uint8 Timer_Select ;
#endif
#if (CCP1_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)  ||  (CCP2_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED) 
    uint8 Timer_Select ;
#endif
#if (CCP1_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)  ||  (CCP2_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)    
    uint32 PWM_Freq ;
    uint8 Timer2_prescaler_value ;
    uint8 Timer2_postscaler_value ;
#endif
    
    
}ccp_t;

/* Section : Functions Declaration */

Std_ReturnType CCP_Init(const ccp_t  *_ccp)   ;
Std_ReturnType CCP_Deinit(const ccp_t  *_ccp) ;

#if (CCP1_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED)    
Std_ReturnType CCP_Is_Capture_Done(const ccp_t  *_ccp , uint8 *ccp_status); 
Std_ReturnType CCP_Capture_Read_Value(const ccp_t  *_ccp , uint16 *capture_value); 
#endif 

#if (CCP1_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)    
Std_ReturnType CCP_Is_Compare_Done(const ccp_t  *_ccp , uint8 *ccp_status); 
Std_ReturnType CCP_Compare_Write_Value(const ccp_t  *_ccp , uint16 compare_value); 
#endif 


#if (CCP1_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)    
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t  *_ccp , uint8 duty_cycle);
Std_ReturnType CCP_PWM_Start(const ccp_t  *_ccp);
Std_ReturnType CCP_PWM_Stop(const ccp_t  *_ccp);
#endif    



#endif	/* HAL_CCP1_H */

