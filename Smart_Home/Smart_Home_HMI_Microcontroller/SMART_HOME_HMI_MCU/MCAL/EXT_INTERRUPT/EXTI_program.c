/*----------------------------------------------------------------------------*/
/*-- @breief: EXTI_program.c       -----------------------------------------*/
/*-- @Author: Ahmed Atef Abdelrahman -----------------------------------------*/
/*-- @date:    Sep 15, 2023          -----------------------------------------*/
/*----------------------------------------------------------------------------*/

/*--------------------------------- Includes ---------------------------------*/

/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"
/*----------------------------------- MCAL -----------------------------------*/

/*----------------------------------- HAL ------------------------------------*/
#include "EXTI_private.h"
#include "EXTI_configuration.h"
#include "EXTI_interface.h"
/****************************Pointer to functions to be assigned to ISR*********************************/
void (*PTR_FUNC_INT0)(void) = NULL;
void (*PTR_FUNC_INT1)(void) = NULL;
void (*PTR_FUNC_INT2)(void) = NULL;

/*---------------------------- Software Interfaces ---------------------------*/

void M_EXT_voidInit(EXInterruptSource_t Copy_u8EXTINo, EXTISense_t Edge) {

	// SET INTX TO EDGE OR SENSE TYPE
	switch (Copy_u8EXTINo) {
	case EX_INT0:
		switch (Edge) {
		case LOW_LEVEL:
			CLEAR_BIT(MCUCR, ISC00);
			CLEAR_BIT(MCUCR, ISC01);
			break;
		case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR, ISC00);
			CLEAR_BIT(MCUCR, ISC01);
			break;
		case FALLING_EDGE:
			CLEAR_BIT(MCUCR, ISC00);
			SET_BIT(MCUCR, ISC01);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR, ISC00);
			SET_BIT(MCUCR, ISC01);
			break;

		}
		break;
	case EX_INT1:
		switch (Edge) {
		case LOW_LEVEL:
			CLEAR_BIT(MCUCR, ISC10);
			CLEAR_BIT(MCUCR, ISC11);
			break;
		case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR, ISC10);
			CLEAR_BIT(MCUCR, ISC11);
			break;
		case FALLING_EDGE:
			CLEAR_BIT(MCUCR, ISC10);
			SET_BIT(MCUCR, ISC11);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR, ISC10);
			SET_BIT(MCUCR, ISC11);
			break;
		}
		break;
	case EX_INT2:
		switch (Edge) {
		case FALLING_EDGE:
			CLEAR_BIT(MCUCSR, ISC2);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCSR, ISC2);
			break;
		default:
			CLEAR_BIT(MCUCSR, ISC2);
		}
		break;
	}
   
}

void M_EXTI_voidEXTIEnable(EXInterruptSource_t Copy_u8EXTINo)
{
	switch (Copy_u8EXTINo) {
	case EX_INT0:
		SET_BIT(GICR, INT0);
		break;
	case EX_INT1:
		SET_BIT(GICR, INT1);
		break;
	case EX_INT2:
		SET_BIT(GICR, INT2);
		break;
	}
}

void M_EXTI_voidEXTIDisable(EXInterruptSource_t Copy_u8EXTINo) {
	switch (Copy_u8EXTINo) {
	case EX_INT0:
		CLEAR_BIT(GICR, INT0);
		break;
	case EX_INT1:
		CLEAR_BIT(GICR, INT1);
		break;
	case EX_INT2:
		CLEAR_BIT(GICR, INT2);
		break;
	}
}

void M_EXTI_voidSetCallBack(EXInterruptSource_t Copy_u8EXTINo, void (*Copy_PtrToFunc)(void)) {
	if (Copy_PtrToFunc != NULL) {
		switch (Copy_u8EXTINo) {
		case EX_INT0:
			PTR_FUNC_INT0 = Copy_PtrToFunc;
			break;
		case EX_INT1:
			PTR_FUNC_INT1 = Copy_PtrToFunc;
			break;
		case EX_INT2:
			PTR_FUNC_INT2 = Copy_PtrToFunc;
			break;
		}
	}
}

/***********************************EXTI0 ISR***********************************/

ISR(INT0_vect) {
	if (PTR_FUNC_INT0 != NULL) {
		PTR_FUNC_INT0();
	}
}

/***********************************EXTI1 ISR***********************************/
ISR(INT1_vect) {
	if (PTR_FUNC_INT1 != NULL) {
		PTR_FUNC_INT1();
	}
}
/***********************************EXTI2 ISR***********************************/
ISR(INT2_vect) {
	if (PTR_FUNC_INT2 != NULL) {
		PTR_FUNC_INT2();
	}
}
