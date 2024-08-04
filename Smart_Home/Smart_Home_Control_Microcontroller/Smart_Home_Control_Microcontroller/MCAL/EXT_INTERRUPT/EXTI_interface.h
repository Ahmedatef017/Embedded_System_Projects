/*
 * EXTI_interface.h
 *
 *  Created on: Sep 15, 2023
 *      Author: ahmed
 */

#ifndef EXT_INTERRUPT_EXTI_INTERFACE_H_
#define EXT_INTERRUPT_EXTI_INTERFACE_H_

typedef enum{
	EX_INT0,
	EX_INT1,
	EX_INT2,
}EXInterruptSource_t;

typedef enum{
	LOW_LEVEL=0,
	RISING_EDGE,
	FALLING_EDGE,
	ANY_LOGIC_CHANGE
}EXTISense_t;

void M_EXT_voidInit(EXInterruptSource_t Copy_u8EXTINo,EXTISense_t Copy_u8EXTISense);

void M_EXTI_voidEXTIEnable(EXInterruptSource_t Copy_u8EXTINo);

void M_EXTI_voidEXTIDisable(EXInterruptSource_t Copy_u8EXTINo);

void M_EXTI_voidSetCallBack(EXInterruptSource_t Copy_u8EXTINo , void(*Copy_PtrToFunc)(void) );

#endif /* EXT_INTERRUPT_EXTI_INTERFACE_H_ */
