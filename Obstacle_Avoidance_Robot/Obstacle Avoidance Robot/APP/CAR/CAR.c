/*
 * CAR.C
 *
 *  Created on: Jan 31, 2024
 *      Author: ahmed
 */

#define F_CPU 8000000
#include <util/delay.h>

#include "../../LIB/StdTypes.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../HAL/DC_MOTOR/MOTOR_interface.h"
#include "../../MCAL/TIMER_0/TIMER0_interface.h"
#include "CAR.h"
static u8 speed_flag=0;
void CAR_voidInit(void)
{
	M_DIO_voidSetPinDirection(PINB3,OUTPUT);//oc0;
	M_Timer0_Init();
	M_Timer0_start();
	H_MOTOR_voidInit();
}
void CAR_vMoveForward(void)
{
	if(speed_flag==0)
	{
		H_MOTOR_voidForward(Motor_FL);
		H_MOTOR_voidForward(Motor_FR);
		H_MOTOR_voidForward(Motor_BL);
		H_MOTOR_voidForward(Motor_BR);
		CAR_Speed(HALF_SPEED);
		_delay_ms(300);
		CAR_Speed(HIGH_SPEED);
		_delay_ms(300);
		CAR_Speed(MAX_SPEED);
		speed_flag=1;	
	}


}
void CAR_vMoveBackward(void)
{
	H_MOTOR_voidBackward(Motor_FL);
	H_MOTOR_voidBackward(Motor_FR);
	H_MOTOR_voidBackward(Motor_BL);
	H_MOTOR_voidBackward(Motor_BR);
}
void CAR_vMoveLeft(void)
{
	H_MOTOR_voidBackward(Motor_FL);
	H_MOTOR_voidForward(Motor_FR);
	H_MOTOR_voidBackward(Motor_BL);
	H_MOTOR_voidForward(Motor_BR);
}
void CAR_vMoveRight(void)
{
	H_MOTOR_voidForward(Motor_FL);
	H_MOTOR_voidBackward(Motor_FR);
	H_MOTOR_voidForward(Motor_BL);
	H_MOTOR_voidBackward(Motor_BR);
}
void CAR_voidStop(void)
{
	if(speed_flag==1)
	{
		H_MOTOR_voidStop(Motor_FL);
		H_MOTOR_voidStop(Motor_FR);
		H_MOTOR_voidStop(Motor_BL);
		H_MOTOR_voidStop(Motor_BR);
		speed_flag =0;	
	}


}
void CAR_voidTurnRight90(void)
{
	CAR_vMoveRight();
	_delay_ms(1500);
	CAR_voidStop();
	
}
void CAR_voidTurnLeft90(void)
{
	
	CAR_vMoveLeft();
	_delay_ms(1500);
	CAR_voidStop();
	
	
}
void CAR_Reverse(void)
{
	
}

void CAR_Speed(Speed_t speed)
{
	M_Timer0_SetFastPWM(speed);
}