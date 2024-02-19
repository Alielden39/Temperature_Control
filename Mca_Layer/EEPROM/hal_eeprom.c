/* 
 * File:   hal_eeprom.c
 * Author: Alielden
 *
 * Created on October 14, 2023, 5:51 PM
 */
#include "hal_eeprom.h"


/**
 * 
 * @param bADD
 * @param bData
* @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType EEPROM_WriteData(uint16 bADD , uint8 bData)
{
    Std_ReturnType ret = STD_OK ;
   /* Read status of interrupt */
    uint8 Interrupt_Status = INTCONbits.GIE ;
    /* Update Address Register*/
    EEADRH = (uint8)( ( bADD >> 8 ) & 0x03 ) ;
    EEADR  = (uint8)( bADD & 0xFF ) ;
    /* Update the Data register*/
    EEDATA = bData ;
    /* Select access to eeprom*/
    EECON1bits.EEPGD =  Access_data_EEPROM_memory ;
    /* Select access to flash memory or eeprom*/
    EECON1bits.CFGS = Access_Flash_program_or_data_EEPROM_memory ;
    /* Allow write cycle */
    EECON1bits.WREN = Allows_write_cycles_to_Flash_program_or_dataEEPROM ;
    /* Disable all interrupts */
    INTERRUPT_GlobalInterruptDisable();
    /* Sequence */
    EECON2 = 0x55 ;
    EECON2 = 0xAA ;
    /* Initiates a data EEPROM erase/write cycle*/
    EECON1bits.WR = Initiates_dataEEPROM_or_Flash_program_erase_or_write_cycle ;
    /* Wait write to complete */
    while( EECON1bits.WR != cycle_EEPROM_complete )
    {}
    /* Return interrupt to first status*/
    INTCONbits.GIE = Interrupt_Status ;
    /* Disable write cycle */
    EECON1bits.WREN = Disllows_write_cycles_to_Flash_program_or_dataEEPROM ;
    
      
    return ret ;
}

/**
 * 
 * @param bADD
 * @param bData
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType EEPROM_ReadData(uint16 bADD , uint8 *bData)
{
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == bData ) )
    {
        ret = STD_NOT_OK ;
    }
    else{
    /* Update Address Register*/
    EEADRH = (uint8)( ( bADD >> 8 ) & 0x03 ) ;
    EEADR  = (uint8)( bADD & 0xFF ) ;
    /* Select access to eeprom*/
    EECON1bits.EEPGD =  Access_data_EEPROM_memory ;
    /* Select access to flash memory or eeprom*/
    EECON1bits.CFGS = Access_Flash_program_or_data_EEPROM_memory ;
    /* Initiates a data EEPROM read cycle*/
    EECON1bits.RD = Initiates_dataEEPROM_or_Flash_program_read_cycle ;
    NOP();
    NOP();
    /* Read Data */
    *bData = EEDATA ;
    }

    return ret ;
}