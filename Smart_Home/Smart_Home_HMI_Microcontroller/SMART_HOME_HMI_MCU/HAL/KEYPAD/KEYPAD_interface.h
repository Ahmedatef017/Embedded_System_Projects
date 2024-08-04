/*
 * KEYPAD_interface.h
 *
 *  Created on: Sep 11, 2023
 *      Author: ahmed
 */

#ifndef KEYPAD_KEYPAD_INTERFACE_H_
#define KEYPAD_KEYPAD_INTERFACE_H_

#define NO_PRESSED_KEY  0xff

void H_KEYPAD_voidInit(void);
u8   H_KEYPAD_u8_getPressedKey(void);

#endif /* KEYPAD_KEYPAD_INTERFACE_H_ */
