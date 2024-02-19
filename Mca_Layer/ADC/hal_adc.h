/* 
 * File:   hal_adc.h
 * Author: Alielden
 *
 * Created on October 18, 2023, 11:16 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* Section :  Includes */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "../INTERRUPT/hal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "hal_adc_cfg.h"


 /* Section : Macros */
#define ADC_CONVERSION_STATUS   ADCON0bits.GO_nDONE         //  In Progress , Idle

#define ADC_IN_PROGRESS 1
#define ADC_IDLE        0


#define RIGHT_FORMAT 1
#define LEFT_FORMAT  0

#define VREF    1
#define VSS_VDD 0


/* Section : Macros Functions */
#define ADC_ENABLE()     (ADCON0bits.ADON = 1)
#define ADC_DISABLE()    (ADCON0bits.ADON = 0)


/* Start Conversion */
#define ADC_START_CONVERSION() (ADCON0bits.GODONE = 1)

/* VREF OR VDD,VSS */
#define ADC_VOLTAGE_REFRENCE_ENABLE()  ( ADCON1bits.VCFG1=1 ;\
                                          ADCON1bits.VCFG0=1 ;\)

#define ADC_VOLTAGE_REFRENCE_DISABLE()  ( ADCON1bits.VCFG1=0 ;\
                                          ADCON1bits.VCFG0=0 ;\)
                                           
/* ADC ANALOG DIGITAL CONFIGURATION BITS */
#define ADC_AN0_ANALOG()      ( ADCON1bits.PCFG = 0x0E )
#define ADC_AN1_ANALOG()      ( ADCON1bits.PCFG = 0x0D )
#define ADC_AN2_ANALOG()      ( ADCON1bits.PCFG = 0x0C )
#define ADC_AN3_ANALOG()      ( ADCON1bits.PCFG = 0x0B )
#define ADC_AN4_ANALOG()      ( ADCON1bits.PCFG = 0x0A )
#define ADC_AN5_ANALOG()      ( ADCON1bits.PCFG = 0x09 )
#define ADC_AN6_ANALOG()      ( ADCON1bits.PCFG = 0x08 )
#define ADC_AN7_ANALOG()      ( ADCON1bits.PCFG = 0x07 )
#define ADC_AN8_ANALOG()      ( ADCON1bits.PCFG = 0x06 )
#define ADC_AN9_ANALOG()      ( ADCON1bits.PCFG = 0x05 )
#define ADC_AN10_ANALOG()     ( ADCON1bits.PCFG = 0x04 )
#define ADC_AN12_ANALOG()     ( ADCON1bits.PCFG = 0x03 )
#define ADC_ALL_ANALOG()      ( ADCON1bits.PCFG = 0x00 )
#define ADC_ALL_DIGITAL()     ( ADCON1bits.PCFG = 0x0F )

/* ADC FORMAT SELECT : RIGHT OR LEFT */
#define ADC_RIGHT_JUSTIFIED()   (ADCON2bits.ADFM = 1)
#define ADC_LEFT_JUSTIFIED()    (ADCON2bits.ADFM = 0)

                                        
        

/* Section : Data type Declaration */
typedef enum 
{
    ADC_CHANNEL_AN0 = 0 ,
    ADC_CHANNEL_AN1  ,
    ADC_CHANNEL_AN2  ,
    ADC_CHANNEL_AN3  ,
    ADC_CHANNEL_AN4  ,
    ADC_CHANNEL_AN5  ,
    ADC_CHANNEL_AN6  ,
    ADC_CHANNEL_AN7  ,
    ADC_CHANNEL_AN8  ,
    ADC_CHANNEL_AN9  ,
    ADC_CHANNEL_AN10 ,
    ADC_CHANNEL_AN11 ,
    ADC_CHANNEL_AN12 
}adc_channel_select_t;

typedef enum 
{
    ADC_0_TAD = 0 ,
    ADC_2_TAD     ,
    ADC_4_TAD     ,
    ADC_6_TAD     ,
    ADC_8_TAD     ,
    ADC_12_TAD    ,
    ADC_16_TAD    ,
    ADC_20_TAD    ,
}adc_acquisition_time_t;

typedef enum 
{
    ADC_FOSC_DIVIDE_2 = 0  ,
    ADC_FOSC_DIVIDE_8      ,
    ADC_FOSC_DIVIDE_32     ,
    ADC_FRC                ,
    ADC_FOSC_DIVIDE_4      ,
    ADC_FOSC_DIVIDE_16     ,
    ADC_FOSC_DIVIDE_64     ,
}adc_clock_select_t;


typedef struct
{
#ifdef ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*adc_call_back)(void) ;
    uint8 priority ; 
#endif
    adc_channel_select_t channel ;
    adc_acquisition_time_t Taq ;
    adc_clock_select_t  clk; 
    uint8  Format_Select ;
    uint8  Voltage_Refrence ;
}adc_t;

/* Section : Functions Declaration */

Std_ReturnType ADC_Init(adc_t *adc);
Std_ReturnType ADC_DeInit(adc_t *adc);
Std_ReturnType ADC_SelectChannel(adc_t *adc , adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion(adc_t *adc );
Std_ReturnType ADC_IsDone(adc_t *adc , uint8 *status);
Std_ReturnType ADC_ConversionValue(adc_t *adc , uint16  *value);
Std_ReturnType ADC_GetConversion(adc_t *adc , adc_channel_select_t channel ,uint16  *value );
Std_ReturnType ADC_GetConversion_Interrupt(adc_t *adc , adc_channel_select_t channel );

#endif	/* HAL_ADC_H */

