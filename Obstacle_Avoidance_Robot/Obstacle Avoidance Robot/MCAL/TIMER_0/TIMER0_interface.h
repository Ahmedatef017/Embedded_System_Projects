/*
 * TIMER0_interface.h
 *
 *  Created on: Sep 17, 2023
 *      Author: ahmed
 */

#ifndef TIMER_0_TIMER0_INTERFACE_H_
#define TIMER_0_TIMER0_INTERFACE_H_


typedef enum{
	TIMER0_OVF_INTERRUPT,
	TIMER0_OC_INTERRUPT
}TIMER0_Iterrupt_t;

Error_Status_t M_Timer0_Init(void);
Error_Status_t M_Timer0_start(void);
Error_Status_t M_Timer0_stop(void);
Error_Status_t M_Timer0_GetCounts(u16* copy_u8NumOfCounts);
Error_Status_t M_Timer0_SetDelayTimeMilliSec(u32  time_ms);
Error_Status_t M_Timer0_SetFastPWM(u8 duty);
Error_Status_t M_Timer0_SetPhaseCorrectPWM(u8 duty);
Error_Status_t M_TIMER0_EnableInt(TIMER0_Iterrupt_t InterruptSource);
Error_Status_t M_TIMER0_DisableInt(TIMER0_Iterrupt_t InterruptSource);
Error_Status_t M_TIMER0_SetCallBack(TIMER0_Iterrupt_t InterruptSource,void (*ptr_func)(void));
Error_Status_t M_TIMER0_void_Set_OCR0_Value(u8 value);

#endif /* TIMER_0_TIMER0_INTERFACE_H_ */
