/*
 * TIMER0_private.h
 *
 *  Created on: Sep 17, 2023
 *      Author: ahmed
 */

#ifndef TIMER_0_TIMER0_PRIVATE_H_
#define TIMER_0_TIMER0_PRIVATE_H_

/******************** Timer 0 Registers ********************/
#define TCCR0   (*(volatile u8*)0x53)
#define TCNT0   (*(volatile u8*)0x52)
#define OCR0    (*(volatile u8*)0x5C)
#define TIMSK   (*(volatile u8*)0x59)
#define TIFR    (*(volatile u8*)0x58)

/************************** PINS ***************************/

/************************** TCCR0 **************************/
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

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

/************************* SFIOR ***************************/
#define ADTS2   7
#define ADTS1   6
#define ADTS0   5
#define ACME    3
#define PUD     2
#define PSR2    1
#define PSR10   0


/*********************** MODES OPTION **********************/
/********************* PRESCALER OPTION ********************/
#define TIMER0_TIMER_STOP                     0
#define TIMER0_PRESCALER_1                    1
#define TIMER0_PRESCALER_8                    2
#define TIMER0_PRESCALER_64                   3
#define TIMER0_PRESCALER_256                  4
#define TIMER0_PRESCALER_1024                 5
#define TIMER0_PRESCALER_EXTCLK_FALLING_EDGE  6
#define TIMER0_PRESCALER_EXTCLK_RISING_EDGE   7
/******************** TIMERS MODE OPTION *******************/
#define TIMER0_NORMAL_MODE          0
#define TIMER0_CTC_MODE             2
#define TIMER0_FAST_PWM             3
#define TIMER0_PHASE_CORRECT_PWM    1


/********************** OC0 MODE OPTION ********************/
/*************   FOR NON PWM MODE (NORMAL & CTC)************/
#define OC0_DISCONNECTED            0
#define TOGGLE_OC0_ON_COMPARE_MATCH 1
#define CLEAR_OC0_ON_COMPARE_MATCH  2
#define SET_OC0_ON_COMPARE_MATCH    3

/************ FOR PWM MODE (FAST & PHASE CORRECT)***********/

#define OC0_NON_INVERTING_MODE      0b00100000
#define OC0_INVERTING_MODE          0b00110000

/************************* MASKING *************************/
#define TIMER0_PRESCALER_MASK      0xF8
#define TIMER0_OC0_MASK            0xCF

/******************* Interrupt vectors *********************/
#define TIMER0_OC_vect	      	__vector_10
/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect			__vector_11

/**************** Interrupt ISR Functions ******************/
#  define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)

#endif /* TIMER_0_TIMER0_PRIVATE_H_ */
