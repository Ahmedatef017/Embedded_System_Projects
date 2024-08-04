/*
 * TIMER1_private.h
 *
 *  Created on: Sep 22, 2023
 *      Author: ahmed
 */

#ifndef MCAL_TIMER_1_TIMER1_PRIVATE_H_
#define MCAL_TIMER_1_TIMER1_PRIVATE_H_

/******************** Timer 0 Registers ********************/
#define ICR1      *(volatile unsigned short*)0x46
#define ICR1L     *(volatile unsigned char*)0x46
#define ICR1H     *(volatile unsigned char*)0x47
#define OCR1B     *(volatile unsigned short*)0x48
#define OCR1BL    *(volatile unsigned char*)0x48
#define OCR1BH    *(volatile unsigned char*)0x49
#define OCR1A     *(volatile unsigned short*)0x4A
#define OCR1AL    *(volatile unsigned char*)0x4A
#define OCR1AH    *(volatile unsigned char*)0x4B
#define TCNT1     *(volatile unsigned short*)0x4C
#define TCNT1L    *(volatile unsigned char*)0x4C
#define TCNT1H    *(volatile unsigned char*)0x4D
#define TCCR1B    *(volatile unsigned char*)0x4E
#define TCCR1A    *(volatile unsigned char*)0x4F
#define SFIOR     *(volatile unsigned char*)0x50
#define OSCCAL    *(volatile unsigned char*)0x51
#define TIMSK   (*(volatile unsigned char*)0x59)
/************************** PINS ***************************/

/************************** TCCR1A **************************/
#define COM1A1   7
#define COM1A0   6
#define COM1B1   5
#define COM1B0   4
#define FOC1A    3
#define FOC1B    2
#define WGM11    1
#define WGM10    0

/************************** TCCR1B **************************/
#define ICNC1    7
#define ICES1    6
#define WGM13    4
#define WGM12    3
#define CS12     2
#define CS11     1
#define CS10     0

/************************* TIMSK ***************************/
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0


/************************* TIFR ***************************/
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0

/*********************** MODES OPTION **********************/
/********************* PRESCALER OPTION ********************/
#define TIMER1_STOP                 0
#define TIMER1_PRESCALER_1          1
#define TIMER1_PRESCALER_8          2
#define TIMER1_PRESCALER_64         3
#define TIMER1_PRESCALER_256        4
#define TIMER1_PRESCALER_1024       5
#define TIMER1_EXTCLK_FALLING_EDGE  6
#define TIMER1_EXTCLK_RISING_EDGE   7
/******************** TIMERS MODE OPTION *******************/
#define TIMER1_NORMAL_MODE           0
#define	TIMER1_CTC_ICR_TOP_MODE      12
#define	TIMER1_CTC_OCRA_TOP_MODE     4
#define	TIMER1_FASTPWM_ICR_TOP_MODE  14
#define	TIMER1_FASTPWM_OCRA_TOP_MODE 15

/********************** OC MODE OPTION ********************/
/*************   FOR NON PWM MODE (NORMAL & CTC)************/

#define OC1A_DISCONNECTED          0
#define OC1A_TOGGLE                1
#define OC1A_NON_INVERTING         2
#define OC1A_INVERTING             3

/************ FOR PWM MODE (FAST & PHASE CORRECT)***********/
#define OC1B_DISCONNECTED          0
#define OC1A_TOGGLE                1
#define OC1B_NON_INVERTING         2
#define OC1AB_INVERTING            3

/************************* MASKING *************************/
#define TIMER1_PRESCALER_MASK      0xF8


/******************* Interrupt vectors *********************/
#define TIMER1_ICU_vect		__vector_6
/* Timer/Counter1 Compare Match A */
#define TIMER1_OCA_vect		__vector_7
/* Timer/Counter1 Compare Match B */
#define TIMER1_OCB_vect		__vector_8
/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect		__vector_9

/**************** Interrupt ISR Functions ******************/
#  define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)

#endif /* MCAL_TIMER_1_TIMER1_PRIVATE_H_ */
