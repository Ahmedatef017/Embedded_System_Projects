/*
 * SERVO_program.c
 *
 *  Created on: Jan 17, 2024
 *      Author: ahmed
 */


/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"
/*----------------------------------- MCAL -----------------------------------*/
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TIMER_1/TIMER1_interface.h"
#include "../../MCAL/GIE/GIE_interface.h"
/*----------------------------------- HAL ------------------------------------*/
#include "SERVO_private.h"
#include "SERVO_configuration.h"
#include "SERVO_interface.h"

void H_Servo_voidInit(void)
{
	//init servo pin as output
	//init timer1
	/*will do the following*/
	/*
	 * set timer in fast pwm mode ocra top set top value by 19999
	 * set ocr1b value by 999
	 * */
	M_DIO_voidSetPinDirection(SERVO_PIN, OUTPUT);
	//M_TIMER1_voidInit();  //timer 1 is initialized in the ultrasonic init function
	//M_TIMER1_voidStart();
	M_TIMER1_void_Set_OCR1B_Value(999);
	//enable GIE
	M_Global_Interrupt_Enable();
}
void H_Servo_voidSetAngle(u8 angle)
{
	M_TIMER1_void_Set_OCR1B_Value(((angle*(u32)1000)/180)+999);
}
