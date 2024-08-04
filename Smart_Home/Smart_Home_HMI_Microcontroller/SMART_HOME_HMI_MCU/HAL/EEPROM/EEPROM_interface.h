/*
 * EEPROM_interface.h
 *
 *  Created on: Sep 29, 2023
 *      Author: ahmed
 */

#ifndef HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EEPROM_EEPROM_INTERFACE_H_

void H_EEPROM_voidInit(void);
u8   H_EEPROM_u8Write_Byte(u16 address,u8 data);
u8   H_EEPROM_u8Read_Byte(u16 address,u8*ptr_data);

#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */
