
/*----------------------------------------------------------------------------*/
/*-- @breief: LED_program.c          -----------------------------------------*/
/*-- @Author: Ahmed Atef Abdelrahman -----------------------------------------*/
/*-- @date:    Sep 10, 2023          -----------------------------------------*/
/*----------------------------------------------------------------------------*/
/*--------------------------------- Includes ---------------------------------*/
#define  F_CPU  8000000
/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"

/*----------------------------------- MCAL -----------------------------------*/
#include "../../MCAL/DIO/DIO_interface.h"
/*----------------------------------- HAL ------------------------------------*/
#include "LED_private.h"
#include "LED_configuration.h"
#include "LED_interface.h"
/*---------------------------- Software Interfaces ---------------------------*/

void H_LED_voidInit(u8 copy_u8led)
{
	M_DIO_voidSetPinDirection(copy_u8led,OUTPUT);
}

void H_LED_voidTurnOn(u8 copy_u8led)
{
	M_DIO_voidSetPinValue(copy_u8led,HIGH);
}

void H_LED_voidTurnOff(u8 copy_u8led)
{
	M_DIO_voidSetPinValue(copy_u8led,LOW);
}

void H_LED_voidToggle(u8 copy_u8led)
{
	M_DIO_voidTogglePinValue(copy_u8led);
}

Led_Status_t H_LED_u8GetStatus(u8 copy_u8led)
{
	Led_Status_t Led_Status = LED_OFF;
	if(M_DIO_u8GetPinValue(copy_u8led)==LOW)
	{
		Led_Status = LED_OFF;
	}
	else
	{
		Led_Status = LED_ON;
	}
	return Led_Status;
}
