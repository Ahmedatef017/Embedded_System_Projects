
#ifndef LCD_H_
#define LCD_H_

#include "StdTypes.h"
/******************private***************/
#define  LCD_4BIT  1
#define  LCD_8BIT  0
/*****************LCD_Cfg***************/
/*CHOOSE LCD_4BIT  OR  LCD_8BIT */
#define LCD_MODE   LCD_4BIT
#define D7    PINA1     //
#define D6    PINA2      // NOT USED WITH 8 BIT MODE
#define D5    PINA3     //
#define D4    PINA4     //

#define LCD_PORT  PA     // NOT USED WITH 4 BIT MODE
#define RS        PINB0     
#define EN        PINB1
/***************************************/
void LCD_Init(void);
void LCD_Clear(void);
void LCD_WriteChar(u8 ch);
void LCD_WriteNumber(s64 num);
void LCD_WriteString(c8*str);
void LCD_WriteBinary(u8 num);
void LCD_WriteBinary_8D(u8 num);
void LCD_WriteHex(u8 num);
void LCD_WriteNumber_4D(u16 num);
void LCD_SetCurser(u8 line,u8 cell);
void LCD_ClearLocation(u8 line,u8 cell);
void LCD_ClearLocations(u8 line,u8 cell,u8 count);
void LCD_Create_Character(u8 *Pattern,u8 Location);
void lCD_GoToWriteSring(u8 line,u8 cell,c8*str);

#endif /* LCD_H_ */
