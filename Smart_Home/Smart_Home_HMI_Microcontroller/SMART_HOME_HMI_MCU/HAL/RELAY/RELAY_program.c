/*
 * RELAY_program.c
 *
 *  Created on: Jan 13, 2024
 *      Author: ahmed
 */


/*--------------------------------- Includes ---------------------------------*/
#define  F_CPU  8000000
/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"

/*----------------------------------- MCAL -----------------------------------*/
#include "../../MCAL/DIO/DIO_interface.h"
/*----------------------------------- HAL ------------------------------------*/
#include "RELAY_private.h"
#include "RELAY_configuration.h"
#include "RELAY_interface.h"

void H_RELAY_voidInit(void)
{
	M_DIO_voidSetPinDirection(RELAY_PIN,OUTPUT);
}
void H_RELAY_voidTurnOn(void)
{
	M_DIO_voidSetPinValue(RELAY_PIN, HIGH);
}
void H_RELAY_voidTurnOff(void)
{
	M_DIO_voidSetPinValue(RELAY_PIN, LOW);
}

