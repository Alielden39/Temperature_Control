/* 
 * File:   hal_usart.h
 * Author: Alielden
 *
 * Created on December 27, 2023, 10:26 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* Section :  Includes */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "../INTERRUPT/hal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "hal_usart_cfg.h"

 /* Section : Macros */
#define SERIAL_PORT_TX_RX_ENABLE  1
#define SERIAL_PORT_TX_RX_DISABLE 0

#define USART_ASYNCHRONOUS_MODE 0
#define USART_SYNCHRONOUS_MODE  1

#define USART_HIGH_BAUDRATE_SPEED   1
#define USART_LOW_BAUDRATE_SPEED    0

#define USART_16BIT_BAUDRATE   1
#define USART_8BIT_BAUDRATE    0

#define USART_TX_ENABLE   1
#define USART_TX_DISABLE  0

#define USART_TX_INTERRUPT_FLAG_ENABLE  1 
#define USART_TX_INTERRUPT_FLAG_DISABLE 0 


#define EUSART_TX_INTERRUPT_ENABLE   1
#define EUSART_TX_INTERRUPT_DISABLE  0

#define USART_TX_9BIT_DATA_ENABLE   1
#define USART_TX_9BIT_DATA_DISABLE  0

#define TSR_EMPTY 1
#define TSR_FULL 0 

#define USART_RX_ENABLE   1
#define USART_RX_DISABLE  0

#define EUSART_RX_INTERRUPT_ENABLE   1
#define EUSART_RX_INTERRUPT_DISABLE  0

#define USART_RX_9BIT_DATA_ENABLE   1
#define USART_RX_9BIT_DATA_DISABLE  0

#define USART_RX_INTERRUPT_FLAG_ENABLE  1 
#define USART_RX_INTERRUPT_FLAG_DISABLE 0 

#define USART_RX_FRAMEERROR_DETECTED  1
#define USART_RX_FRAMEERROR_CLEARED   0

#define USART_RX_OVERRUN_ERROR_DETECTED  1
#define USART_RX_OVERRUN_ERROR_CLEARED   0


/* Section : Macros Functions */



/* Section : Data type Declaration */
typedef enum {
    ASYN_8BIT_LOW_SPEED,
    ASYN_8BIT_HIGH_SPEED,
    ASYN_16BIT_LOW_SPEED,
    ASYN_16BIT_HIGH_SPEED, 
    SYNC_8BIT,
    SYNC_16BIT        
}baudrate_gen_eqn_t;

typedef struct{
    uint8 tx_enable:1  ;
    uint8 tx_9bit:1      ;
    uint8 tx_interrupt:1 ;
}usart_tx_cfg_t;

typedef struct{
    uint8 rx_enable:1  ;
    uint8 rx_9bit:1      ;
    uint8 rx_interrupt:1 ;
}usart_rx_cfg_t;

typedef union{
    struct{
        uint8 frame_error:1    ;
        uint8 overrun_error:1  ;
    };
    uint8 error ;
}usart_rx_error_t;


typedef struct{
    uint32  baudrate ;
    baudrate_gen_eqn_t  baudrate_eqn ;
    usart_tx_cfg_t   tx_cfg ;
    usart_rx_cfg_t   rx_cfg ;
    usart_rx_error_t error_status ;
#ifdef USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*USART_TX_CALLBACK)(void);
    Interrupt_priority Tx_priority ; 
#endif
#ifdef USART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*USART_RX_CALLBACK)(void);
    void (*USART_RX_FRAMING_ERROR_CALLBACK)(void);
    void (*USART_RX_OVERRUN_ERROR_CALLBACK)(void);
    Interrupt_priority Rx_priority ; 
#endif
}usart_t;



/* Section : Functions Declaration */
Std_ReturnType Usart_Async_init(usart_t *usart );
Std_ReturnType Usart_Async_Deinit(usart_t *usart );
Std_ReturnType Usart_Async_WriteByte( uint8 data );
Std_ReturnType Usart_Async_ReadByte( uint8 *data );
Std_ReturnType Usart_Async_WriteString( uint8 *data , uint8 length );
Std_ReturnType Usart_Async_ReadString( uint8 *data );


#endif	/* HAL_USART_H */

