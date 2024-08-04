/*
 * LCD_interface.h
 *
 *  Created on: Sep 13, 2023
 *      Author: Ahmed Atef
 */

#ifndef LCD_LCD_INTERFACE_H_
#define LCD_LCD_INTERFACE_H_



#endif /* LCD_LCD_INTERFACE_H_ */

void H_LCD_voidInit(void);
void H_LCD_voidSendCommand(u8 copy_u8command);
void H_LCD_voidSendChar(u8 copy_u8data);
void H_LCD_voidSendString(c8*copy_str);
void H_LCD_voidSetPosition(u8 copy_u8row,u8 copy_u8col);
void H_LCD_SendNumber(s64 copy_u8num);
void H_LCD_voidClearDisplay(void);
void H_LCD_voidWriteHex(u8 num);
void H_LCD_voidSetCustomCharacter(char*ptr_pattern,
		u8 copy_u8position);
