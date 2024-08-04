/*
 * ULTRASONIC_program.c
 *
 *  Created on: Jan 15, 2024
 *      Author: ahmed
 */
#define  F_CPU  8000000
#include "util/delay.h"
/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
/*----------------------------------- MCAL -----------------------------------*/
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TIMER_1/TIMER1_interface.h"
#include "../../MCAL/GIE/GIE_interface.h"
/*----------------------------------- HAL ------------------------------------*/

#include "ULTRASONIC_private.h"
#include "ULTRASONIC_configuration.h"
#include "ULTRASONIC_interface.h"

void H_Ultra_ICU_Func(void);

static volatile u8 flag = 0;
static volatile u16 Reading1 = 0;
static volatile u16 Reading2 = 0;


void H_Ultrasonic_voidInit(void)
{
	//TIMER 1 INIT

	//init timer 1 in normal mode
	M_TIMER1_voidInit();
	//set icu pin as input
	M_DIO_voidSetPinDirection(PIND6, INPUT);
	//Trig pin direction as output
	M_DIO_voidSetPinDirection(ULTRA_TRIG_PIN, OUTPUT);
	//Set icu trigger
	M_TIMER1_ICU_voidSetTrigger(RISING);
	//set callback
	M_TIMER1_voidSetCallBack(TIMER1_ICU_INTERRUPT, H_Ultra_ICU_Func);
	//enable interrupt
	M_Timer1_ICU_voidInterruptEnable();
	//timer start
	M_TIMER1_voidStart();

	//enable GIE
	M_Global_Interrupt_Enable();

}
u16 H_Ultrasonic_voidGetDistance(void)
{
	u16 Distance;
	u16 Time;

	flag = 0;

	M_TIMER1_ICU_voidSetTrigger(RISING);
	//send trigger
	M_DIO_voidSetPinValue(PINB7, HIGH);
	_delay_us(10);
	M_DIO_voidSetPinValue(PINB7, LOW);

	while(flag<2);

	//calculate pwm parameter
	u16 NumOfCounts = Reading2 - Reading1;
	Time = NumOfCounts * M_TIMER1_f32GetTickTime() ; //time in micro sec
	Distance = Time/58; //converting meter to cm and sec to micro sec
	return Distance;
}


void H_Ultra_ICU_Func(void) {
	if (flag == 0) {
		Reading1 = M_TIMER1_ICU_u16takeReading();
		M_TIMER1_ICU_voidSetTrigger(FALLING);
		flag = 1;
	} else if (flag == 1) {
		Reading2 = M_TIMER1_ICU_u16takeReading();
		flag = 2;
	}
}


#if 0
#include "ULTRASONIC_private.h"
#include "ULTRASONIC_configuration.h"
#include "ULTRASONIC_interface.h"

void H_Ultra_ICU_Func(void);
void H_Ultra_OVF_Func(void);

static volatile u8 flag = 0;
static volatile u16 Reading1 = 0;
static volatile u16 Reading2 = 0;
 volatile u8 Counter;
 volatile u8 Ovf_Counter;

void H_Ultrasonic_voidInit(void)
{
	//TIMER 1 INIT

	//init timer 1 in fast pwm ocr1a top mode
	M_TIMER1_voidInit();
	//set icu pin as input
	M_DIO_voidSetPinDirection(PIND6, INPUT);
	//Trig pin direction as output
	M_DIO_voidSetPinDirection(ULTRA_TRIG_PIN, OUTPUT);
	//Set icu trigger
	M_TIMER1_ICU_voidSetTrigger(RISING);
	//set callback of icu vector
	M_TIMER1_voidSetCallBack(TIMER1_ICU_INTERRUPT, H_Ultra_ICU_Func);
	//set callback of ovf vector
	M_TIMER1_voidSetCallBack(TIMER1_OVF_INTERRUPT, H_Ultra_OVF_Func);
	//enable icu interrupt
	M_Timer1_ICU_voidInterruptEnable();
	//enable ovf interrupt
	M_Timer1_OVF_voidInterruptEnable();
	//timer start
	M_TIMER1_voidStart();

	//enable GIE
	M_Global_Interrupt_Enable();

}
u16 H_Ultrasonic_voidGetDistance(void)
{
	u16 Distance;
	u16 Time;

	flag = 0;
	//enable icu interrupt
	M_Timer1_ICU_voidInterruptEnable();
	M_TIMER1_ICU_voidSetTrigger(RISING);
	//send trigger
	M_DIO_voidSetPinValue(PINB7, HIGH);
	_delay_us(10);
	M_DIO_voidSetPinValue(PINB7, LOW);

	while(flag<2);

	//calculate pwm parameter
	//u16 NumOfCounts = Reading2 - Reading1;
	//Time = NumOfCounts * M_TIMER1_f32GetTickTime() ; //time in micro sec
	u16 Timer_Counts = ( Reading2 - Reading1 + ((u32)Ovf_Counter * M_TIMER1_u16GetTopValue())) ;
	Time = ((u32)Timer_Counts * M_TIMER1_f32GetTickTime()) ; //time in micro sec
	Distance = Time/58; //converting meter to cm and sec to micro sec

	return Distance;
}


void H_Ultra_ICU_Func(void) {
	if (flag == 0) {
		Reading1 = M_TIMER1_ICU_u16takeReading();
		Counter = 0;
		M_TIMER1_ICU_voidSetTrigger(FALLING);
		flag = 1;
	} else if (flag == 1) {
		Reading2 = M_TIMER1_ICU_u16takeReading();
		Ovf_Counter = Counter;
		//disable icu interrupt
		M_Timer1_ICU_voidInterruptDisable();
		flag = 2;
	}
}

void H_Ultra_OVF_Func(void)
{
	Counter++;
}
#endif
