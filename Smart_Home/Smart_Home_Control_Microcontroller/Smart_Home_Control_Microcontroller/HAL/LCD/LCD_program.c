
/*----------------------------------------------------------------------------*/
/*-- @breief: LCD_program.c          -----------------------------------------*/
/*-- @Author: Ahmed Atef Abdelrahman -----------------------------------------*/
/*-- @date:    Sep 12, 2023          -----------------------------------------*/
/*----------------------------------------------------------------------------*/


/*--------------------------------- Includes ---------------------------------*/
#include <stdlib.h>

#define F_CPU 8000000
#include <util/delay.h>
/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"
/*----------------------------------- MCAL -----------------------------------*/
#include "../../MCAL/DIO/DIO_interface.h"
/*----------------------------------- HAL ------------------------------------*/
#include "LCD_private.h"
#include "LCD_configuration.h"
#include "LCD_interface.h"
/*---------------------------- Software Interfaces ---------------------------*/

#if  LCD_MODE == LCD_4BIT
void H_LCD_voidSendCommand(u8 copy_u8command) {
	M_DIO_voidSetPinValue(RS_PIN, LOW); //RS=0
	M_DIO_voidSetPinValue(D4_PIN, READ_BIT(copy_u8command, 4));
	M_DIO_voidSetPinValue(D5_PIN, READ_BIT(copy_u8command, 5));
	M_DIO_voidSetPinValue(D6_PIN, READ_BIT(copy_u8command, 6));
	M_DIO_voidSetPinValue(D7_PIN, READ_BIT(copy_u8command, 7));

	M_DIO_voidSetPinValue(EN_PIN, HIGH);
	_delay_ms(1);
	M_DIO_voidSetPinValue(EN_PIN, LOW);

	M_DIO_voidSetPinValue(D4_PIN, READ_BIT(copy_u8command, 0));
	M_DIO_voidSetPinValue(D5_PIN, READ_BIT(copy_u8command, 1));
	M_DIO_voidSetPinValue(D6_PIN, READ_BIT(copy_u8command, 2));
	M_DIO_voidSetPinValue(D7_PIN, READ_BIT(copy_u8command, 3));

	M_DIO_voidSetPinValue(EN_PIN, HIGH);
	_delay_ms(1);
	M_DIO_voidSetPinValue(EN_PIN, LOW);
	_delay_ms(1);
}
void H_LCD_voidSendData(u8 copy_u8data) {
	M_DIO_voidSetPinValue(RS_PIN, HIGH); //RS=1
	M_DIO_voidSetPinValue(D4_PIN, READ_BIT(copy_u8data, 4));
	M_DIO_voidSetPinValue(D5_PIN, READ_BIT(copy_u8data, 5));
	M_DIO_voidSetPinValue(D6_PIN, READ_BIT(copy_u8data, 6));
	M_DIO_voidSetPinValue(D7_PIN, READ_BIT(copy_u8data, 7));

	M_DIO_voidSetPinValue(EN_PIN, HIGH);
	_delay_ms(1);
	M_DIO_voidSetPinValue(EN_PIN, LOW);

	M_DIO_voidSetPinValue(D4_PIN, READ_BIT(copy_u8data, 0));
	M_DIO_voidSetPinValue(D5_PIN, READ_BIT(copy_u8data, 1));
	M_DIO_voidSetPinValue(D6_PIN, READ_BIT(copy_u8data, 2));
	M_DIO_voidSetPinValue(D7_PIN, READ_BIT(copy_u8data, 3));

	M_DIO_voidSetPinValue(EN_PIN, HIGH);
	_delay_ms(1);
	M_DIO_voidSetPinValue(EN_PIN, LOW);
	_delay_ms(1);

}
void H_LCD_voidInit(void) {
	//intialize RS & EN as output
	M_DIO_voidSetPinDirection(RS_PIN, OUTPUT);
	M_DIO_voidSetPinDirection(EN_PIN, OUTPUT);

	//intialize D4 -> D7 as output
	M_DIO_voidSetPinDirection(D4_PIN, OUTPUT);
	M_DIO_voidSetPinDirection(D5_PIN, OUTPUT);
	M_DIO_voidSetPinDirection(D6_PIN, OUTPUT);
	M_DIO_voidSetPinDirection(D7_PIN, OUTPUT);
	_delay_ms(50);
	H_LCD_voidSendCommand(0x02); //set fun
	H_LCD_voidSendCommand(0x28);
	H_LCD_voidSendCommand(0x0c);
	H_LCD_voidSendCommand(0x01);
	_delay_ms(1);
	H_LCD_voidSendCommand(0x06); //no shift ddram++
}
#elif LCD_MODE == LCD_8BIT
u8 LCD_Data_Pins[LCD_SIZE]={D0_PIN,D1_PIN,D2_PIN,D3_PIN,D4_PIN,D5_PIN,D6_PIN,D7_PIN};
void H_LCD_voidSendCommand(u8 copy_u8command)
{
	M_DIO_voidSetPinValue(RS_PIN, LOW); //RS=0
	for(int i=0;i<LCD_SIZE;i++)
	{
		M_DIO_voidSetPinValue(LCD_Data_Pins[i], READ_BIT(copy_u8command, i));
	}

	M_DIO_voidSetPinValue(EN_PIN, HIGH);
	_delay_ms(1);
	M_DIO_voidSetPinValue(EN_PIN, LOW);
	_delay_ms(1);
}
 void H_LCD_voidSendData(u8 copy_u8data)
{
	 M_DIO_voidSetPinValue(RS_PIN, HIGH); //RS=1
	for(int i=0;i<LCD_SIZE;i++)
	{
		M_DIO_voidSetPinValue(LCD_Data_Pins[i], READ_BIT(copy_u8data, i));
	}
	M_DIO_voidSetPinValue(EN_PIN, HIGH);
	_delay_ms(1);
	M_DIO_voidSetPinValue(EN_PIN, LOW);
	_delay_ms(1);
}

void H_LCD_voidInit(void) {
	//intialize RS & EN as output
	M_DIO_voidSetPinDirection(RS_PIN, OUTPUT);
	M_DIO_voidSetPinDirection(EN_PIN, OUTPUT);

	//intialize D0 -> D7 as output
	for(int i=0;i<LCD_SIZE;i++)
	{
		M_DIO_voidSetPinDirection(LCD_Data_Pins[i], OUTPUT);
	}
	_delay_ms(50);
	H_LCD_voidSendCommand(0x38);
	H_LCD_voidSendCommand(0x0C);
	H_LCD_voidSendCommand(0x01);
	_delay_ms(1);
	H_LCD_voidSendCommand(0x06);
}
#endif

void H_LCD_voidSendChar(u8 copy_u8char) {
	H_LCD_voidSendData(copy_u8char);
}

void H_LCD_voidSendString(c8*copy_str) {
	u8 i = 0;
	if (copy_str == 0) {
		//do nothing
	} else {
		while (copy_str[i]) {
			H_LCD_voidSendChar(copy_str[i]);
			i++;
		}
	}
}
void H_LCD_voidSetPosition(u8 copy_u8row, u8 copy_u8col) {
	if (copy_u8row == 1) {
		H_LCD_voidSendCommand(0x80 + copy_u8col);
	} else if (copy_u8row == 2) {
		H_LCD_voidSendCommand(0x80 + 0x40 + copy_u8col);

	} else if (copy_u8row == 3) {
		H_LCD_voidSendCommand(0x80 + 0x14 + copy_u8col);
	} else if (copy_u8row == 4) {
		H_LCD_voidSendCommand(0x80 + 0x54 + copy_u8col);
	}

}
void H_LCD_SendNumber(s64 copy_u8num) {
	/*char lcoal_ArrStrig[10];
	itoa(copy_u8num, lcoal_ArrStrig, 10);
	H_LCD_voidSendString(lcoal_ArrStrig);*/
		u8 i=0;
		s8 j;
	char lcoal_ArrStrig[20];
	if(copy_u8num==0)
	{
		H_LCD_voidSendChar('0');
	}
    if (copy_u8num<0)
	{
		H_LCD_voidSendChar('-');
		copy_u8num = copy_u8num*-1;
	}
	while(copy_u8num>0)
	{
		lcoal_ArrStrig[i] = copy_u8num%10+'0';
		copy_u8num = copy_u8num/10;
		i++;
	}
	for(j=i-1;j>=0;j--)
	{
		H_LCD_voidSendChar(lcoal_ArrStrig[j]);
	}
}

void H_LCD_voidClearDisplay(void) {

	H_LCD_voidSendCommand(0x01);
	_delay_ms(1);
}

void H_LCD_voidSetCustomCharacter(c8*ptr_pattern,
		u8 copy_u8position)
{
	H_LCD_voidSendCommand(0x40+(8*copy_u8position));
	for(u8 i=0;i<8;i++)
	{
		H_LCD_voidSendChar(ptr_pattern[i]);
	}
	//H_LCD_voidSendCommand(0x80);   // set DDRAM ADDRESS
}

void H_LCD_voidWriteHex(u8 num)
{
	u8 Ln=num&0x0f;
	u8 Hn=num>>4;
	if(Hn<=9)
	{
		H_LCD_voidSendChar(Hn+'0');
	}
	else
	{
		H_LCD_voidSendChar(Hn-10+'A');
	}
	if(Ln<=9)
	{
		H_LCD_voidSendChar(Ln+'0');
	}
	else
	{
		H_LCD_voidSendChar(Ln-10+'A');
	}
}
