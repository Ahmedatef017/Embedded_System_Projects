/*----------------------------------------------------------------------------*/
/*-- @breief: SSD_program.c          -----------------------------------------*/
/*-- @Author: Ahmed Atef Abdelrahman -----------------------------------------*/
/*-- @date:    Sep 11, 2023          -----------------------------------------*/
/*----------------------------------------------------------------------------*/

/*--------------------------------- Includes ---------------------------------*/
#define  F_CPU  8000000
#include "util/delay.h"
/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"
/*----------------------------------- MCAL -----------------------------------*/
#include "../../MCAL/DIO/DIO_interface.h"
/*----------------------------------- HAL ------------------------------------*/
#include "SSD_private.h"
#include "SSD_config.h"
#include "SSD_interface.h"
/*---------------------------- Software Interfaces ---------------------------*/
/*
void SSD_voidInit(void) {
	DIO_voidSetPinDirection(SSD_COM1_PIN, OUTPUT);
	DIO_voidSetPinDirection(SSD_COM2_PIN, OUTPUT);
	DIO_voidSetPinDirection(SSD_COM3_PIN, OUTPUT);
	DIO_voidSetPinDirection(SSD_COM4_PIN, OUTPUT);

	DIO_voidSetPinDirection(SSD_PINA, OUTPUT);
	DIO_voidSetPinDirection(SSD_PINB, OUTPUT);
	DIO_voidSetPinDirection(SSD_PINC, OUTPUT);
	DIO_voidSetPinDirection(SSD_PIND, OUTPUT);

	DIO_voidSetPinValue(SSD_COM1_PIN, 1); //DISABLE COM1
	DIO_voidSetPinValue(SSD_COM1_PIN, 1); //DISABLE COM2
	DIO_voidSetPinValue(SSD_COM1_PIN, 1); //DISABLE COM3
	DIO_voidSetPinValue(SSD_COM1_PIN, 1); //DISABLE COM4
}
*/
/*
void SSD_voidDisplay(u16 number, u16 time) {
	u16 digit;   //number 1047

	for (int i = 0; i < time/8; i++) {
		digit = number % 10;   //7 0111

		DIO_voidSetPinValue(SSD_COM1_PIN, 0); //ENABLE  COM1


		DIO_voidSetPinValue(SSD_PINA, READ_BIT(digit, 0)); //A->1
		DIO_voidSetPinValue(SSD_PINB, READ_BIT(digit, 1)); //B->1
		DIO_voidSetPinValue(SSD_PINC, READ_BIT(digit, 2)); //C->1
		DIO_voidSetPinValue(SSD_PIND, READ_BIT(digit, 3)); //D->0
		_delay_ms(2);

		digit = number / 10;  //digit = 104
		digit = digit % 10;  //digit = 4

		DIO_voidSetPinValue(SSD_COM1_PIN, 1); //DISABLE  COM1
		DIO_voidSetPinValue(SSD_COM2_PIN, 0); //ENABLE COM2
		DIO_voidSetPinValue(SSD_COM3_PIN, 1); //DISABLE COM3
		DIO_voidSetPinValue(SSD_COM4_PIN, 1); //DISABLE COM4

		DIO_voidSetPinValue(SSD_PINA, READ_BIT(digit, 0)); //A->1
		DIO_voidSetPinValue(SSD_PINB, READ_BIT(digit, 1)); //B->1
		DIO_voidSetPinValue(SSD_PINC, READ_BIT(digit, 2)); //C->1
		DIO_voidSetPinValue(SSD_PIND, READ_BIT(digit, 3)); //D->0

		_delay_ms(2);

		digit = number / 100;  //digit = 10
		digit = digit % 10;  //digit = 0

		DIO_voidSetPinValue(SSD_COM1_PIN, 1); //DISABLE COM1
		DIO_voidSetPinValue(SSD_COM2_PIN, 1); //DISABLE  COM2
		DIO_voidSetPinValue(SSD_COM3_PIN, 0); //ENABLE COM3
		DIO_voidSetPinValue(SSD_COM4_PIN, 1); //DISABLE COM4

		DIO_voidSetPinValue(SSD_PINA, READ_BIT(digit, 0)); //A->1
		DIO_voidSetPinValue(SSD_PINB, READ_BIT(digit, 1)); //B->1
		DIO_voidSetPinValue(SSD_PINC, READ_BIT(digit, 2)); //C->1
		DIO_voidSetPinValue(SSD_PIND, READ_BIT(digit, 3)); //D->0

		_delay_ms(2);

		digit = number / 1000;  //digit = 1
		digit = digit % 10;  //digit = 1

		DIO_voidSetPinValue(SSD_COM1_PIN, 1); //DISABLE COM1
		DIO_voidSetPinValue(SSD_COM2_PIN, 1); //DISABLE COM2
		DIO_voidSetPinValue(SSD_COM3_PIN, 1); //DISABLE  COM3
		DIO_voidSetPinValue(SSD_COM4_PIN, 0); //ENABLE COM4

		DIO_voidSetPinValue(SSD_PINA, READ_BIT(digit, 0)); //A->1
		DIO_voidSetPinValue(SSD_PINB, READ_BIT(digit, 1)); //B->1
		DIO_voidSetPinValue(SSD_PINC, READ_BIT(digit, 2)); //C->1
		DIO_voidSetPinValue(SSD_PIND, READ_BIT(digit, 3)); //D->0

		_delay_ms(2);
	}

}
*/
void H_SSD_voidInit(void) {
	  M_DIO_voidSetPinDirection(SSD_COM2_PIN, OUTPUT);//seg right
	  M_DIO_voidSetPinDirection(SSD_COM1_PIN, OUTPUT);//seg left

	  //M_DIO_voidSetPortDirection(PORT_D, OUTPUT);

	  M_DIO_voidSetPinDirection(SSD_PINA, OUTPUT);
	  M_DIO_voidSetPinDirection(SSD_PINB, OUTPUT);
	  M_DIO_voidSetPinDirection(SSD_PINC, OUTPUT);
	  M_DIO_voidSetPinDirection(SSD_PIND, OUTPUT);

	  M_DIO_voidSetPinValue(SSD_COM2_PIN,LOW);
	  M_DIO_voidSetPinValue(SSD_COM1_PIN,LOW);
}

void H_SSD_voidDisplayNumForAtime(u8 number, u16 time) {

	u8 left = number/10;  //4  0100
	u8 right = number%10; //5  0101
	               //     3210
	for (u8 i = 0; i < time/8; i++) {

		M_DIO_voidSetPinValue(SSD_COM2_PIN,LOW); //enable seg right
		M_DIO_voidSetPinValue(SSD_COM1_PIN,HIGH); //Disable seg left

		//DIO_voidSetPortValue(PORT_D, right);
		M_DIO_voidSetPinValue(SSD_PINA, READ_BIT(right,0));
		M_DIO_voidSetPinValue(SSD_PINB, READ_BIT(right,1));
	    M_DIO_voidSetPinValue(SSD_PINC, READ_BIT(right,2));
		M_DIO_voidSetPinValue(SSD_PIND, READ_BIT(right,3));

		_delay_ms(4);

		M_DIO_voidSetPinValue(SSD_COM1_PIN,LOW); //enable seg left
		M_DIO_voidSetPinValue(SSD_COM2_PIN,HIGH); //Disable seg right

		//DIO_voidSetPortValue(PORT_D, left);
		M_DIO_voidSetPinValue(SSD_PINA, READ_BIT(left,0));
		M_DIO_voidSetPinValue(SSD_PINB, READ_BIT(left,1));
	    M_DIO_voidSetPinValue(SSD_PINC, READ_BIT(left,2));
		M_DIO_voidSetPinValue(SSD_PIND, READ_BIT(left,3));
		_delay_ms(4);
	}
	
	  M_DIO_voidSetPinValue(SSD_COM2_PIN,LOW);
	  M_DIO_voidSetPinValue(SSD_COM1_PIN,LOW);

}


void H_SSD_voidDisplay(u8 number)
{
	u8 left = number/10;  //4  0100
	u8 right = number%10; //5  0101

	M_DIO_voidSetPinValue(SSD_COM2_PIN,LOW); //enable seg right
	M_DIO_voidSetPinValue(SSD_COM1_PIN,HIGH); //Disable seg left

	//DIO_voidSetPortValue(PORT_D, right);
	M_DIO_voidSetPinValue(SSD_PINA, READ_BIT(right,0));
	M_DIO_voidSetPinValue(SSD_PINB, READ_BIT(right,1));
    M_DIO_voidSetPinValue(SSD_PINC, READ_BIT(right,2));
	M_DIO_voidSetPinValue(SSD_PIND, READ_BIT(right,3));

	_delay_ms(2);

	M_DIO_voidSetPinValue(SSD_COM1_PIN,LOW); //enable seg left
	M_DIO_voidSetPinValue(SSD_COM2_PIN,HIGH); //Disable seg right

	//DIO_voidSetPortValue(PORT_D, left);
	M_DIO_voidSetPinValue(SSD_PINA, READ_BIT(left,0));
	M_DIO_voidSetPinValue(SSD_PINB, READ_BIT(left,1));
	M_DIO_voidSetPinValue(SSD_PINC, READ_BIT(left,2));
	M_DIO_voidSetPinValue(SSD_PIND, READ_BIT(left,3));
	_delay_ms(2);
}
