/*
 * BUZZER_program.c
 *
 *  Created on: Jan 13, 2024
 *      Author: ahmed
 */

/*--------------------------------- Includes ---------------------------------*/

/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
//#include "../../LIB/BitMath.h"
/*----------------------------------- MCAL -----------------------------------*/
#include "../../MCAL/DIO/DIO_interface.h"
/*----------------------------------------------------------------------------*/

#include "BUZZER_private.h"
#include "BUZZER_configuration.h"
#include "BUZZER_interface.h"

void H_BUZZER_voidInit(void)
{
	M_DIO_voidSetPinDirection(BUZZER_PIN, OUTPUT);
}
void H_BUZZER_voidTurnOn(void)
{
	M_DIO_voidSetPinValue(BUZZER_PIN, HIGH);
}
void H_BUZZER_voidTurnOff(void)
{
	M_DIO_voidSetPinValue(BUZZER_PIN, LOW);
}
