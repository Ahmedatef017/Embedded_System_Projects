/*
 * MOTOR_program.c
 *
 *  Created on: Jan 14, 2024
 *      Author: ahmed
 */

/*--------------------------------- Includes ---------------------------------*/

/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
//#include "../../LIB/BitMath.h"
#include "util/delay.h"
/*----------------------------------- MCAL -----------------------------------*/
#include "../../MCAL/DIO/DIO_interface.h"
/*----------------------------------- HAL ------------------------------------*/
#include "MOTOR_private.h"
#include "MOTOR_configuration.h"
#include "MOTOR_interface.h"

/*---------------------------- Software Interfaces ---------------------------*/

u8 MotorPinsArray[MAX_MOTOR_NUM][2]= Motor_Pins_Config;

void H_MOTOR_voidInit(void)
{
 for(u8 i=0;i<MAX_MOTOR_NUM;i++)
 {
	 M_DIO_voidSetPinDirection(MotorPinsArray[i][IN1], OUTPUT);
	 M_DIO_voidSetPinDirection(MotorPinsArray[i][IN2], OUTPUT);
 }

}
void H_MOTOR_voidCW(MOTOR_type motor)
{
	M_DIO_voidSetPinValue(MotorPinsArray[motor][IN1],HIGH);
	M_DIO_voidSetPinValue(MotorPinsArray[motor][IN2],LOW);
}

void H_MOTOR_voidCCW(MOTOR_type motor)
{
	M_DIO_voidSetPinValue(MotorPinsArray[motor][IN1],LOW);
	M_DIO_voidSetPinValue(MotorPinsArray[motor][IN2],HIGH);

}
void H_MOTOR_voidStop(MOTOR_type motor)
{
	M_DIO_voidSetPinValue(MotorPinsArray[motor][IN1],HIGH);
	M_DIO_voidSetPinValue(MotorPinsArray[motor][IN2],HIGH);
}

