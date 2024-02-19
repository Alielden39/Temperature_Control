/* 
 * File:   hal_eeprom.h
 * Author: Alielden
 *
 * Created on October 14, 2023, 5:51 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* Section :  Includes */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../INTERRUPT/hal_interrupt_config.h"

 /* Section : Macros */
#define Access_data_EEPROM_memory   0
#define Access_Flash_program_memory 1

#define Access_Flash_program_or_data_EEPROM_memory 0
#define Access_Configuration_registers             1

#define Allows_write_cycles_to_Flash_program_or_dataEEPROM   1
#define Disllows_write_cycles_to_Flash_program_or_dataEEPROM 0

#define Initiates_dataEEPROM_or_Flash_program_erase_or_write_cycle 1
#define cycle_EEPROM_complete 0

#define Initiates_dataEEPROM_or_Flash_program_read_cycle 1
#define cycle_EEPROM_complete 0


/* Section : Data type Declaration */


/* Section : Functions Declaration */

Std_ReturnType EEPROM_WriteData(uint16 bADD , uint8 bData);
Std_ReturnType EEPROM_ReadData(uint16 bADD , uint8 *bData);
#endif	/* HAL_EEPROM_H */

