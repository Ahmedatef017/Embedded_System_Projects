/*----------------------------------------------------------------------------*/
/*-- @breief: TIMER1_program.c       -----------------------------------------*/
/*-- @Author: Ahmed Atef Abdelrahman -----------------------------------------*/
/*-- @date:    Sep 22, 2023          -----------------------------------------*/
/*----------------------------------------------------------------------------*/

/*--------------------------------- Includes ---------------------------------*/

/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"

/*----------------------------------- MCAL -----------------------------------*/
#include "TIMER1_private.h"
#include "TIMER1_configuration.h"
#include "TIMER1_interface.h"

/****************Pointer to functions to be assigned to ISR***********************/
static void (*Timer1_OVF_ptr_func)(void) = NULL;
static void (*Timer1_OCA_ptr_func)(void) = NULL;
static void (*Timer1_OCB_ptr_func)(void) = NULL;
static void (*Timer1_ICU_ptr_func)(void) = NULL;
/******************************************************************************************/

void M_TIMER1_voidInit(void) {

	/*set timer mode*/
#if TIMER1_MODE == TIMER1_NORMAL_MODE
	CLEAR_BIT(TCCR1A, WGM10);
	CLEAR_BIT(TCCR1A, WGM11);
	CLEAR_BIT(TCCR1B, WGM12);
	CLEAR_BIT(TCCR1B, WGM13);

#elif TIMER1_MODE == TIMER1_CTC_ICR_TOP_MODE
	CLEAR_BIT(TCCR1A,WGM10);
	CLEAR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);

	/********** set top value **************/
	ICR1 = TIMER1_TOP_VALUE;


#elif TIMER1_MODE == TIMER1_CTC_OCRA_TOP_MODE
	CLEAR_BIT(TCCR1A,WGM10);
	CLEAR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLEAR_BIT(TCCR1B,WGM13);

	/********** set top value **************/
	OCR1A = TIMER1_TOP_VALUE;


#elif TIMER1_MODE == TIMER1_FASTPWM_ICR_TOP_MODE
	CLEAR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);

	/********** set top value **************/
	ICR1 = TIMER1_TOP_VALUE;

#elif TIMER1_MODE == TIMER1_FASTPWM_OCRA_TOP_MODE
	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);

	/********** set top value **************/
	OCR1A = TIMER1_TOP_VALUE;


#endif

	/*set ocr*/

#if   TIMER1_OC1A_MODE == OC1A_DISCONNECTED
	CLEAR_BIT(TCCR1A, COM1A0);
	CLEAR_BIT(TCCR1A, COM1A1);
#elif TIMER1_OC1A_MODE == OC1A_TOGGLE
	SET_BIT(TCCR1A,COM1A0);
	CLEAR_BIT(TCCR1A,COM1A1);
#elif TIMER1_OC1A_MODE == OC1A_NON_INVERTING
	CLEAR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#elif TIMER1_OC1A_MODE == OC1A_INVERTING
	SET_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#endif

#if   TIMER1_OC1B_MODE == OC1B_DISCONNECTED
	CLEAR_BIT(TCCR1A, COM1B0);
	CLEAR_BIT(TCCR1A, COM1B1);
#elif TIMER1_OC1B_MODE == OC1B_TOGGLE
	SET_BIT(TCCR1A,COM1B0);
	CLEAR_BIT(TCCR1A,COM1B1);
#elif TIMER1_OC1B_MODE == OC1B_NON_INVERTING
	CLEAR_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
#elif TIMER1_OC1B_MODE == OC1B_INVERTING
	SET_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
#endif

}

void M_TIMER1_voidStart(void)
{
#if (TIMER1_PRESCALER >= TIMER1_STOP && TIMER1_PRESCALER <= TIMER1_EXTCLK_RISING_EDGE)
	TCCR1B = TCCR1B & TIMER1_PRESCALER_MASK;
	TCCR1B = TCCR1B | (TIMER1_PRESCALER & 0x07);

#else
#error "WRONG PRESCALER VALUE PLEASE SELECT CORRECT PRESCALER FROM MENUE"
	    state = OUT_OF_RANGE_VALUE;
#endif
}
/************************************************************/
void M_TIMER1_voidStop(void)
{
	CLEAR_BIT(TCCR1B, CS10);
	CLEAR_BIT(TCCR1B, CS11);
	CLEAR_BIT(TCCR1B, CS12);
}
/************************************************************/
void M_Timer1_ICU_voidInterruptEnable(void)
{
	SET_BIT(TIMSK, TICIE1);
}
/************************************************************/
void M_Timer1_ICU_voidInterruptDisable(void)
{
	CLEAR_BIT(TIMSK, TICIE1);
}
/************************************************************/
void M_Timer1_OVF_voidInterruptEnable(void)
{
	SET_BIT(TIMSK, TOIE1);
}
/************************************************************/
void M_Timer1_OVF_voidInterruptDisable(void)
{
	CLEAR_BIT(TIMSK, TOIE1);
}
/************************************************************/
void M_Timer1_OCA_voidInterruptEnable(void)
{
	SET_BIT(TIMSK, OCIE1A);
}
/************************************************************/
void M_Timer1_OCA_voidInterruptDisable(void)
{
	CLEAR_BIT(TIMSK, OCIE1A);
}
/************************************************************/
void M_Timer1_OCB_voidInterruptEnable(void)
{
	SET_BIT(TIMSK, OCIE1B);
}
/************************************************************/
void M_Timer1_OCB_voidInterruptDisable(void) {

	CLEAR_BIT(TIMSK, OCIE1B);
}
/************************************************************/
void M_TIMER1_ICU_voidSetTrigger(ICU_Edge_t edge) {
	switch (edge) {
	case RISING:
		SET_BIT(TCCR1B, ICES1);
		break;
	case FALLING:
		CLEAR_BIT(TCCR1B, ICES1);
		break;
	default:
		break;
	}
}
/************************************************************/
u16 M_TIMER1_ICU_u16takeReading(void)
{
	return ICR1;
}
/************************************************************/

void M_TIMER1_voidSetCallBack(TIMER1_Iterrupt_t InterruptSource, void (*ptr_func)(void))
{
	if(ptr_func!=NULL)
	{
		switch (InterruptSource)
		{
			case TIMER1_OVF_INTERRUPT: {
				Timer1_OVF_ptr_func = ptr_func;
				break;
			}
			case TIMER1_ICU_INTERRUPT: {
				Timer1_ICU_ptr_func = ptr_func;
				break;

			}
			case TIMER1_OC1A_INTERRUPT: {
				Timer1_OCA_ptr_func = ptr_func;
				break;

			}
			case TIMER1_OC1B_INTERRUPT: {
				Timer1_OCB_ptr_func = ptr_func;
				break;

			}
			default: {
				break;
			}
		}
	}
}
/************************************************************/
u16  M_TIMER1_GetTimerValue(void)
{
	return TCNT1;
}
/************************************************************/
void  M_TIMER1_ClearTCNT(void)
{
	TCNT1 = 0;
}
/************************************************************/
F32 M_TIMER1_f32GetTickTime(void)
{
	u16 Arr[]={1,8,64,256,1024};
		//calculate tick time
		F32 TickTime = ((F32)Arr[TIMER1_PRESCALER-1]/CPU_F);
		//calculate number of ticks
		return TickTime;
}

/**************************************************************/
u16 M_TIMER1_u16GetTopValue(void)
{
	return TIMER1_TOP_VALUE;
}

void M_TIMER1_void_Set_OCR1B_Value(u16 value)
{
	OCR1B = value;
}

/************************************ ISR *************************************/
ISR(TIMER1_OVF_vect)
{
	if(Timer1_OVF_ptr_func!=NULL)
	{
		Timer1_OVF_ptr_func();
	}
}
ISR(TIMER1_OCA_vect)
{
	if(Timer1_OCA_ptr_func!=NULL)
	{
		Timer1_OCA_ptr_func();
	}
}
ISR(TIMER1_OCB_vect)
{
	if(Timer1_OCB_ptr_func!=NULL)
	{
		Timer1_OCB_ptr_func();
	}
}
ISR(TIMER1_ICU_vect)
{
	if(Timer1_ICU_ptr_func!=NULL)
	{
		Timer1_ICU_ptr_func();
	}
}















