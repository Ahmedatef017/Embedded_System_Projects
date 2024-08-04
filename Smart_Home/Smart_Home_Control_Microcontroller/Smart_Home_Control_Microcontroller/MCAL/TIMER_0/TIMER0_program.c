
/*----------------------------------------------------------------------------*/
/*-- @breief: TIMER0_program.c       -----------------------------------------*/
/*-- @Author: Ahmed Atef             -----------------------------------------*/
/*-- @date:    Sep 17, 2023          -----------------------------------------*/
/*----------------------------------------------------------------------------*/

/*--------------------------------- Includes ---------------------------------*/

/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"
#include  <math.h>
/*----------------------------------- MCAL -----------------------------------*/
#include "TIMER0_private.h"
#include "TIMER0_configuration.h"
#include "TIMER0_interface.h"

/*---------------------------- Software Interfaces ---------------------------*/

/************************GLOBAL VARIABLES*************************/
static u32 NumberOfOverFlows = 0;
static u8  NumberOfRemanningTicks = 0;
static u32 NumberOfCmpMatches = 0;
volatile u32 session_counter = 0;
/*****************************************************************/
void (*PTR_TIMER0_OVF)(void) = NULL;
void (*PTR_TIMER0_OC)(void) = NULL;
/*****************************************************************/

Error_Status_t M_Timer0_Init(void) {
	Error_Status_t state = NO_ERROR;
	/*set timer mode*/

#if  TIMER0_MODE == TIMER0_NORMAL_MODE
	CLEAR_BIT(TCCR0,WGM00);
	CLEAR_BIT(TCCR0,WGM01);

	/*set OC0 mode*/
#if (TIMER0_OC0_MODE >= OC0_DISCONNECTED && TIMER0_OC0_MODE<=SET_OC0_ON_COMPARE_MATCH)
	TCCR0 = TCCR0 & TIMER0_OC0_MASK;
	TCCR0 = TCCR0 | TIMER0_OC0_MODE << 4;
#else
#error("wrong OC0 mode");
#endif

#elif TIMER0_MODE == TIMER0_CTC_MODE
	CLEAR_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);

	/*set OC0 mode*/
#if (TIMER0_OC0_MODE >= OC0_DISCONNECTED && TIMER0_OC0_MODE<=SET_OC0_ON_COMPARE_MATCH)
	TCCR0 = TCCR0 & TIMER0_OC0_MASK;
	TCCR0 = TCCR0 | TIMER0_OC0_MODE << 4;
#else
#error("wrong OC0 mode");
#endif

#elif TIMER0_MODE == TIMER0_FAST_PWM
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);

	/*set OC0 mode*/
#if ( (TIMER0_OC0_MODE  ==  OC0_DISCONNECTED) || (TIMER0_OC0_MODE  == OC0_INVERTING_MODE) || (TIMER0_OC0_MODE  ==  OC0_NON_INVERTING_MODE))
	TCCR0 = TCCR0 & TIMER0_OC0_MASK;
	TCCR0 = TCCR0 | TIMER0_OC0_MODE;
#else
#error("wrong OC0 mode");
#endif

#elif TIMER0_MODE == TIMER0_PHASE_CORRECT_PWM
	SET_BIT(TCCR0,WGM00);
	CLEAR_BIT(TCCR0,WGM01);
	/*set OC0 mode*/
#if ( (TIMER0_OC0_MODE  ==  OC0_DISCONNECTED) || (TIMER0_OC0_MODE  == OC0_INVERTING_MODE) || (TIMER0_OC0_MODE  ==  OC0_NON_INVERTING_MODE))
	TCCR0 = TCCR0 & TIMER0_OC0_MASK;
	TCCR0 = TCCR0 | TIMER0_OC0_MODE;
#else
#error("wrong OC0 mode");
#endif

#else
#error("wrong timer mode");
#endif

	return state;
}
/*****************************************************************/

Error_Status_t M_Timer0_start(void) {
	Error_Status_t state = NO_ERROR;
	/*set prescaler or adjust clock*/
#if (TIMER0_PRESCALER>=TIMER0_TIMER_STOP && TIMER0_PRESCALER <= TIMER0_PRESCALER_EXTCLK_RISING_EDGE)
	TCCR0 = TCCR0 & TIMER0_PRESCALER_MASK;
	TCCR0 = TCCR0 | (TIMER0_PRESCALER & 0x07);
#else
#error ("WRONG PRESCALER VALUE PLEASE SELECT CORRECT PRESCALER FROM MENUE")
	   state = OUT_OF_RANGE_VALUE;
#endif
	return state;
}
/*****************************************************************/
Error_Status_t M_Timer0_stop(void) {
	Error_Status_t state = NO_ERROR;
//	CLEAR_BIT(TCCR0, CS00);
//	CLEAR_BIT(TCCR0, CS01);
//	CLEAR_BIT(TCCR0, CS02);
	TCCR0 = TCCR0 & TIMER0_PRESCALER_MASK;
	return state;
}
/*****************************************************************/

Error_Status_t M_Timer0_GetCounts(u16* copy_u8NumOfCounts) {
	Error_Status_t state = NO_ERROR;
	*copy_u8NumOfCounts=  TCNT0;
	return state;
}
/*****************************************************************/

Error_Status_t M_Timer0_SetDelayTimeMilliSec(u32  time_ms) {
	Error_Status_t state = NO_ERROR;

	//convert time to micro second
	u16 Arr[]={1,8,64,256,1024};
	u32 Time = time_ms*1000;
	//calculate tick time
	F32 TickTime = (F32)Arr[TIMER0_PRESCALER-1]/CPU_F;
	//calculate number of ticks
	u32 NumberOFticks = Time/TickTime;

#if TIMER0_MODE == TIMER0_NORMAL_MODE
	//calculate number of overflows
	 NumberOfOverFlows = NumberOFticks / 256;
     NumberOfRemanningTicks = NumberOFticks % 256;
	if(NumberOfRemanningTicks!=0)
	{
		TCNT0 = 256-NumberOfRemanningTicks;
		NumberOfOverFlows++;
	}
#elif(TIMER0_MODE == TIMER0_CTC_MODE)
	u8 local_u8Counter = 255;
	while((NumberOFticks % local_u8Counter)!=0)
	{
		local_u8Counter--;
	}
	OCR0 = local_u8Counter; //Preload ocr
	NumberOfCmpMatches = NumberOFticks / local_u8Counter ;

#endif
	return state;
}
/****************************************************************/

Error_Status_t M_Timer0_SetFastPWM(u8 duty)
{
	Error_Status_t state = NO_ERROR;
	if (duty>=0 && duty<=100)
	{
#if(TIMER0_MODE == TIMER0_FAST_PWM)
  #if(TIMER0_OC0_MODE == OC0_NON_INVERTING_MODE)
		if(duty == 0)
		{
			OCR0 = 1;
		}
		else{
			OCR0 = (((u16)duty * 256)/100) - 1;
		}


  #elif(TIMER0_OC0_MODE == OC0_INVERTING_MODE)
		if(duty == 100)
		{
			OCR0 = 255;
		}
		else
		{
			OCR0 = (255 - (((u16)duty * 256)/100))
		}

  #else
  #error("wrong OC0 mode")
  #endif


#endif
	}
	else
	{
		state = OUT_OF_RANGE_VALUE;
	}

	return state;
}



/******************************************************************/

Error_Status_t M_Timer0_SetPhaseCorrectPWM(u8 duty)
{
	Error_Status_t state = NO_ERROR;
	if (duty>=0 && duty<=100)
	{
#if(TIMER0_MODE == TIMER0_PHASE_CORRECT_PWM)
  #if(TIMER0_OC0_MODE == OC0_NON_INVERTING_MODE)
			OCR0 = (((u16)duty * 255)/100);
  #elif(TIMER0_OC0_MODE == OC0_INVERTING_MODE)
			OCR0 = (255 - (((u16)duty * 255)/100));
  #else
  #error("wrong OC0 mode")
  #endif


#endif
	}
	else
	{
		state = OUT_OF_RANGE_VALUE;
	}

	return state;
}

/*****************************************************************/

Error_Status_t M_TIMER0_EnableInt(TIMER0_Iterrupt_t InterruptSource) {
	Error_Status_t state = NO_ERROR;
	switch (InterruptSource) {
	case TIMER0_OVF_INTERRUPT: {
		SET_BIT(TIMSK, TOIE0);
		state = NO_ERROR;
		break;
	}
	case TIMER0_OC_INTERRUPT: {
		SET_BIT(TIMSK, OCIE0);
		state = NO_ERROR;
		break;
	}
	default: {
		state = OUT_OF_RANGE_VALUE;
		break;
	}
	}

	return state;
}
/*****************************************************************/

Error_Status_t M_TIMER0_DisableInt(TIMER0_Iterrupt_t InterruptSource) {
	Error_Status_t state = NO_ERROR;
	switch (InterruptSource) {
	case TIMER0_OVF_INTERRUPT: {
		CLEAR_BIT(TIMSK, TOIE0);
		state = NO_ERROR;
		break;
	}
	case TIMER0_OC_INTERRUPT: {
		CLEAR_BIT(TIMSK, OCIE0);
		state = NO_ERROR;
		break;
	}
	default: {
		state = OUT_OF_RANGE_VALUE;
		break;
	}
	}

	return state;
}
/*****************************************************************/

Error_Status_t M_TIMER0_SetCallBack(TIMER0_Iterrupt_t InterruptSource,void (*ptr_func)(void)) {
	Error_Status_t state = NO_ERROR;
	if(ptr_func!=NULL)
	{
		switch (InterruptSource) {
			case TIMER0_OVF_INTERRUPT: {
				PTR_TIMER0_OVF = ptr_func;
				state = NO_ERROR;
				break;
			}
			case TIMER0_OC_INTERRUPT: {
				PTR_TIMER0_OC = ptr_func;
				state = NO_ERROR;
				break;
			}
			default: {
				state = OUT_OF_RANGE_VALUE;
				break;
			}
			}
	}
	else
	{
		state = NULL_POINTER;
	}
	return state;
}

/***************************TIMER0 ISR*****************************/
/*
ISR(TIMER0_OVF_vect)
{
   static u32 OVFcounter = 0;
   OVFcounter++;
   session_counter++;
   if(OVFcounter == NumberOfOverFlows)
   {
	   TCNT0 = 256 - NumberOfRemanningTicks;// Preload TCNT
	   OVFcounter=0;
	   if(PTR_TIMER0_OVF!=NULL)  //call function in application layer
	   {
		   PTR_TIMER0_OVF();
	   }
   }
}
*/
ISR(TIMER0_OC_vect)
{
   static u32 cmpcounter = 0;
   cmpcounter++;
   session_counter++;
   if(cmpcounter == NumberOfCmpMatches)
   {
	   cmpcounter=0;
	   if(PTR_TIMER0_OC!=NULL)
	   {
		   PTR_TIMER0_OC();
	   }
   }
}

