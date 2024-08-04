/*
 * main.c
 *
 *  Created on: Jan 31, 2024
 *      Author: ahmed
 */

#include "../LIB/StdTypes.h"
#define F_CPU 8000000
#include <util/delay.h>
/*--------------------------------- Includes ---------------------------------*/
/*----------------------------------- MCAL -----------------------------------*/
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/TIMER_1/TIMER1_interface.h"
/*------------------------------------ HAL -----------------------------------*/
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/SERVO_MOTOR/SERVO_interface.h"
#include "../HAL/ULTRASONIC/ULTRASONIC_interface.h"
#include "../HAL/DC_MOTOR/MOTOR_interface.h"
/*------------------------------------ APP -----------------------------------*/
#include "../APP/CAR/CAR.h"
/*------------------------------------ main ----------------------------------*/
#define DEGREES_SYMBOL		   (u8)0xDF
#define TURN_RIGHT_ANGLE  0
#define TURN_LEFT_ANGLE  180
#define DEFAULT_ANGLE   90
#define STOP_DISTANCE   30

int main(void)
{
	u8 distance=0;
	u8 right_distance=0;
	u8 left_distance =0;
	H_LCD_voidInit();
	H_Ultrasonic_voidInit();
	H_Servo_voidInit();
    H_Servo_voidSetAngle(DEFAULT_ANGLE);
    CAR_voidInit();
	while(1)
	{
		distance = H_Ultrasonic_voidGetDistance();
		
		H_LCD_voidSetPosition(1,1);
		H_LCD_voidSendString("Distance = ");
		H_LCD_SendNumber(distance);
		H_LCD_voidSendString(" ");
		H_LCD_voidSetPosition(1,15);
		H_LCD_voidSendString("cm");
		H_LCD_voidSetPosition(2,1);

		if(distance < STOP_DISTANCE)
		{
			H_LCD_voidClearDisplay();
			/*print car stop*/
			H_LCD_voidSendString("     Stop!");
			/*stop car*/
            CAR_voidStop();
            _delay_ms(2000);
            H_LCD_voidClearDisplay();


            /*print turn right*/
            H_LCD_voidSendString("Turn Servo Right->>");
			/*turn right*/
            H_Servo_voidSetAngle(TURN_RIGHT_ANGLE);
			H_LCD_voidSetPosition(2,1);
			H_LCD_voidSendString("Servo Angle = ");
			H_LCD_SendNumber(TURN_RIGHT_ANGLE);
			H_LCD_voidSendChar(DEGREES_SYMBOL);
			H_LCD_voidSendString(" ");
			H_LCD_voidSetPosition(1,18);
			_delay_ms(2000);
            H_LCD_voidClearDisplay();


			/*print get right distance*/
            H_LCD_voidSendString("Get Right Distance");
			/*get right distance*/
            right_distance = H_Ultrasonic_voidGetDistance();
			H_LCD_voidSetPosition(2,1);
			H_LCD_voidSendString("Right_Distance=");
			H_LCD_SendNumber(right_distance);
			H_LCD_voidSendString(" ");
			H_LCD_voidSetPosition(2,18);
			H_LCD_voidSendString("cm");
			_delay_ms(2000);
            H_LCD_voidClearDisplay();


			/*print turn left*/
            H_LCD_voidSendString("<<-Turn Left");
			/*get left distance*/
			H_Servo_voidSetAngle(TURN_LEFT_ANGLE);
			H_LCD_voidSetPosition(2,1);
			H_LCD_voidSendString("Servo Angle = ");
			H_LCD_SendNumber(TURN_LEFT_ANGLE);
			H_LCD_voidSendChar(DEGREES_SYMBOL);
			H_LCD_voidSendString(" ");
			H_LCD_voidSetPosition(1,18);
			_delay_ms(2000);
            H_LCD_voidClearDisplay();


            H_LCD_voidSendString("Get Left Distance");
			/*get right distance*/
            left_distance = H_Ultrasonic_voidGetDistance();
			H_LCD_voidSetPosition(2,1);
			H_LCD_voidSendString("left_Distance=");
			H_LCD_SendNumber(left_distance);
			H_LCD_voidSendString(" ");
			H_LCD_voidSetPosition(2,18);
			H_LCD_voidSendString("cm");
			_delay_ms(2000);
            H_LCD_voidClearDisplay();


            /*go to default position*/
            H_LCD_voidSendString("Default Angle.");
			H_Servo_voidSetAngle(DEFAULT_ANGLE);
			_delay_ms(2000);
			H_LCD_voidClearDisplay();
			
			H_LCD_voidSendString("Right_Distance=");
			H_LCD_SendNumber(right_distance);
			H_LCD_voidSendString(" cm");
			H_LCD_voidSetPosition(2,1);
			H_LCD_voidSendString("left_Distance =");
			H_LCD_SendNumber(left_distance);
			H_LCD_voidSendString(" cm");
			
			/*compare two distance*/
			
			if(right_distance >= left_distance && right_distance>STOP_DISTANCE)
			{
                H_LCD_voidSetPosition(3,3);
				H_LCD_voidSendString("  Move Right");
				/*turn robot right*/
                CAR_voidTurnRight90();
				_delay_ms(2000);
				H_LCD_voidClearDisplay();
				
			}
			else if(left_distance > right_distance && left_distance>STOP_DISTANCE)
			{
				H_LCD_voidSetPosition(3,3);
				H_LCD_voidSendString("  Move Left");
				/*turn robot left*/
                CAR_voidTurnLeft90();
				_delay_ms(2000);
				H_LCD_voidClearDisplay();
			}
			else
			{
				//car reverse
			}
		}
		else
		{
			/*car move forward*/
			H_LCD_voidSendString("    'Move Forward'");
			CAR_vMoveForward();
			
		}

	}
	return 0;
}





