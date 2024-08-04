/*
 * LED_interface.h
 *
 *  Created on: Sep 10, 2023
 *      Author: Mario Ezzat
 */

#ifndef INCLUDE_HAL_LED_LED_INTERFACE_H_
#define INCLUDE_HAL_LED_LED_INTERFACE_H_

/* -------------------------------------------------------------------------- */
/*                                    LEDs                                    */
/* -------------------------------------------------------------------------- */


typedef enum{
	LED_OFF,
	LED_ON
}Led_Status_t;


void H_LED_voidInit(u8 copy_u8led);

void H_LED_voidTurnOn(u8 copy_u8led);

void H_LED_voidTurnOff(u8 copy_u8led);

void H_LED_voidToggle(u8 copy_u8led);

Led_Status_t H_LED_u8GetStatus(u8 copy_u8led);

#endif /* INCLUDE_HAL_LED_LED_INTERFACE_H_ */
