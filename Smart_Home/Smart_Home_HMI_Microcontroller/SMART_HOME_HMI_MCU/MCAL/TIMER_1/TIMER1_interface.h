/*
 * TIMER1_interface.h
 *
 *  Created on: Sep 22, 2023
 *      Author: ahmed
 */

#ifndef MCAL_TIMER_1_TIMER1_INTERFACE_H_
#define MCAL_TIMER_1_TIMER1_INTERFACE_H_

typedef enum{
	RISING,
	FALLING
}ICU_Edge_t;

typedef enum{
	TIMER1_OVF_INTERRUPT,
	TIMER1_ICU_INTERRUPT,
	TIMER1_OC1A_INTERRUPT,
	TIMER1_OC1B_INTERRUPT
}TIMER1_Iterrupt_t;


void M_TIMER1_voidInit(void);
void M_TIMER1_voidStart(void);
void M_TIMER1_voidStop(void);

void M_Timer1_ICU_voidInterruptEnable(void);
void M_Timer1_ICU_voidInterruptDisable(void);

void M_Timer1_OVF_voidInterruptEnable(void);
void M_Timer1_OVF_voidInterruptDisable(void);

void M_Timer1_OCA_voidInterruptEnable(void);
void M_Timer1_OCA_voidInterruptDisable(void);

void M_Timer1_OCB_voidInterruptEnable(void);
void M_Timer1_OCB_voidInterruptDisable(void);

void M_TIMER1_ICU_voidSetTrigger(ICU_Edge_t edge);
u16  M_TIMER1_ICU_u16takeReading(void);
void M_TIMER1_voidSetCallBack(TIMER1_Iterrupt_t InterruptSource,
		                    void (*ptr_func)(void));

u16  M_TIMER1_GetTimerValue(void);
F32  M_TIMER1_f32GetTickTime(void);
void TIMER1_ClearTCNT(void);

void M_TIMER1_void_Set_OCR1B_Value(u16 value);
u16  M_TIMER1_u16GetTopValue(void);

/*
void M_TIMER1_voidInit(void);
void M_TIMER1_voidStart(void);
void M_TIMER1_voidStop(void);
void M_Timer1_ICU_voidInterruptEnable(void);
void M_Timer1_ICU_voidInterruptDisable(void);
void M_Timer1_ICU_voidSetCallBack(TIMER1_Iterrupt_t InterruptSource,void (*ptr_func)(void));
u16  M_TIMER1_ICU_u16takeReading(void);
void M_TIMER1_ICU_voidSetTrigger(ICU_Edge_t edge);
u16  M_TIMER1_GetTimerValue(void);
void M_TIMER1_ClearTCNT(void);
F32 M_TIMER1_f32GetTickTime(void);
*/
#endif /* MCAL_TIMER_1_TIMER1_INTERFACE_H_ */
