/* 
 * File:   hal_i2c.h
 * Author: Alielden
 *
 * Created on February 16, 2024, 1:34 PM
 */

#ifndef HAL_I2C_H

/* Section :  Includes */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../INTERRUPT/hal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"


 /* Section : Macros */

#define I2C_SLAVE_MODE   0
#define I2C_MASTER_MODE  1

#define I2C_ACKNOWLEDGE     0
#define I2C_NOT_ACKNOWLEDGE 1

#define I2C_SLEW_RATE_DISABLE  1
#define I2C_SLEW_RATE_ENABLE   0

#define I2C_SMBUS_DISABLE  0
#define I2C_SMBUS_ENABLE   1

#define I2C_SLAVE_MODE_7BIT_ADDRESS                               6
#define I2C_SLAVE_MODE_10BIT_ADDRESS                              7
#define I2C_SLAVE_MODE_7BIT_ADDRESS_START_STOP_INTERRUPT_ENABLE   14
#define I2C_SLAVE_MODE_10BIT_ADDRESS_START_STOP_INTERRUPT_ENABLE  15
#define I2C_MASTER_MODE_DEFINED_CLOCK                             8
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLED                       11

#define I2C_START_BIT_DETECTED     1
#define I2C_START_BIT_NOT_DETECTED 0

#define I2C_STOP_BIT_DETECTED     1
#define I2C_STOP_BIT_NOT_DETECTED 0

#define I2C_LAST_BYTE_IS_ADDRESS  0
#define I2C_LAST_BYTE_IS_DATA     1

#define I2C_SLAVE_TRANSMIT_MODE_READ   1
#define I2C_SLAVE_RECEIVE_MODE_WRITE  0

#define I2C_MASTER_MODE_TRANSMIT_INPROGRESS      1
#define I2C_MASTER_MODE_TRANSMIT_NOT_INPROGRESS  0

#define I2C_BUFREG_IS_FULL  1
#define I2C_BUFREG_IS_EMPTY 0

#define I2C_SLAVE_MODE_GENERAL_CALL_INTERRUPT_ENABLE   1
#define I2C_SLAVE_MODE_GENERAL_CALL_DISABLE            0  

#define I2C_MASTER_MODE_RECIEVE_ENABLE    1
#define I2C_MASTER_MODE_RECIEVE_DISABLE   0

#define I2C_MASTER_MODE_START_CONDITION_ENABLE    1
#define I2C_MASTER_MODE_START_CONDITION_DISABLE   0

#define I2C_MASTER_MODE_REPEATED_START_CONDITION_ENABLE    1
#define I2C_MASTER_MODE_REPEATED_START_CONDITION_DISABLE   0

#define I2C_MASTER_MODE_STOP_CONDITION_ENABLE    1
#define I2C_MASTER_MODE_STOP_CONDITION_DISABLE   0

#define I2C_MASTER_TRANSMIT_MODE_ACK_IS_RECIEVED      0
#define I2C_MASTER_TRANSMIT_MODE_ACK_IS_NOT_RECIEVED  1

#define I2C_MASTER_RECEIVE_MODE_ACK_ENABLE    1
#define I2C_MASTER_RECEIVE_MODE_ACK_DISABLE   0

/* Section : Macros Functions */

#define MSSP_MODULE_ENABLE_FUNC()                             (SSPCON1bits.SSPEN = 1 )
#define MSSP_MODULE_DISABLE_FUNC()                            (SSPCON1bits.SSPEN = 0 )

#define I2C_SLEW_RATE_DISABLE_FUNC()                          (SSPSTATbits.SMP = 1 )
#define I2C_SLEW_RATE_ENABLE_FUNC()                           (SSPSTATbits.SMP = 0 )

#define I2C_SMBUS_DISABLE_FUNC()                              (SSPSTATbits.CKE = 0 )
#define I2C_SMBUS_ENABLE_FUNC()                               (SSPSTATbits.CKE = 1 )
  
#define I2C_MASTER_MODE_RECIEVE_ENABLE_FUNC()                 (SSPCON2bits.RCEN = 1)
#define I2C_MASTER_MODE_RECIEVE_DISABLE_FUNC()                (SSPCON2bits.RCEN = 0)

#define I2C_SLAVE_MODE_GENERAL_CALL_INTERRUPT_ENABLE_FUNC()   (SSPCON2bits.GCEN = 1)  
#define I2C_SLAVE_MODE_GENERAL_CALL_DISABLE_FUNC()            (SSPCON2bits.GCEN = 0)

#define I2C_SLAVE_TRANSMIT_MODE_COLLISION()                   (SSPCON1bits.WCOL = 1)
#define I2C_SLAVE_TRANSMIT_MODE_NO_COLLISION()                (SSPCON1bits.WCOL = 0)

#define I2C_SLAVE_RECEIVE_MODE_OVERFLOW()                     (SSPCON1bits.SSPOV = 1)
#define I2C_SLAVE_RECEIEVE_MODE_NO_OVERFLOW()                 (SSPCON1bits.SSPOV = 0)

#define I2C_SLAVE_MODE_RELEASE_CLOCK()                        (SSPCON1bits.CKP = 1)
#define I2C_SLAVE_MODE_STRETCH_CLOCK()                        (SSPCON1bits.CKP = 0)

#define I2C_SUB_MODE_FUNC(sub_mode)                           (SSPCON1bits.SSPM = sub_mode)


/* Section : Data type Declaration */

typedef struct
{
    uint8 i2c_clk ;
    uint8 slave_address ;
    uint8 slew_rate ;
    uint8 SMBus ;
    uint8 mode ;
    uint8 sub_mode ;
    uint8 general_call ;
    uint8 master_recieve ;
#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE    
    void(*i2c_DefaultInterruptHandler)(void);
    void(*i2c_CollisionError)(void);
    uint8 i2c_priority ;
    uint8 i2c_collision_priority ;
#endif
    void(*i2c_OverflowError)(void);
}mssp_i2c_t;

/* Section : Functions Declaration */

Std_ReturnType MSSP_I2C_init(const mssp_i2c_t *i2c);
Std_ReturnType MSSP_I2C_Deinit(const mssp_i2c_t *i2c);
Std_ReturnType MSSP_I2C_send_start(const mssp_i2c_t *i2c);
Std_ReturnType MSSP_I2C_send_repeated_start(const mssp_i2c_t *i2c);
Std_ReturnType MSSP_I2C_send_stop(const mssp_i2c_t *i2c);
Std_ReturnType MSSP_I2C_Master_receive_read(const mssp_i2c_t *i2c , uint8 ack ,uint8 *data);
Std_ReturnType MSSP_I2C_Master_Transmit_write(const mssp_i2c_t *i2c , uint8 *ack ,  uint8 data);
Std_ReturnType MSSP_I2C_Slave_read_write(const mssp_i2c_t *i2c ,  uint8 *data);

#endif	/* HAL_I2C_H */

