/*
 * TIMER1_configuration.h
 *
 *  Created on: Sep 22, 2023
 *      Author: ahmed
 */

#ifndef MCAL_TIMER_1_TIMER1_CONFIGURATION_H_
#define MCAL_TIMER_1_TIMER1_CONFIGURATION_H_

/*------------------------------------------------------------------------------
  CHOOSE PRESCALER:
  ------------------------------------------------------------------------------
    TIMER1_PRESCALER_1
    TIMER1_PRESCALER_8
    TIMER1_PRESCALER_64
    TIMER1_PRESCALER_256
    TIMER1_PRESCALER_1024
    TIMER1_EXTCLK_FALLING_EDGE
    TIMER1_EXTCLK_RISING_EDGE


  ------------------------------------------------------------------------------
  CHOOSE TIMER1 MODE:
  ------------------------------------------------------------------------------
  CHOOSE TIMER0 MODE:
 	TIMER1_NORMAL_MODE
	TIMER1_CTC_ICR_TOP_MODE
	TIMER1_CTC_OCRA_TOP_MODE
	TIMER1_FASTPWM_ICR_TOP_MODE
	TIMER1_FASTPWM_OCRA_TOP_MODE


  ------------------------------------------------------------------------------
  CHOOSE OC1A & OC1B MODE:
  ------------------------------------------------------------------------------
   OC1A Configuration:
   ********************
	OC1A_DISCONNECTED
	OC1A_TOGGLE
	OC1A_NON_INVERTING
	OC1A_INVERTING

   OC1B Configuration:
   ********************
	OC1B_DISCONNECTED
	OC1B_TOGGLE
	OC1B_NON_INVERTING
	OC1B_INVERTING
 */


#define  CPU_F                      8
#define  TIMER1_PRESCALER           TIMER1_PRESCALER_8
#define  TIMER1_MODE                TIMER1_FASTPWM_OCRA_TOP_MODE
#define  TIMER1_OC1A_MODE           OC1A_DISCONNECTED
#define  TIMER1_OC1B_MODE           OC1B_NON_INVERTING
#define  TIMER1_TOP_VALUE           19999



#endif /* MCAL_TIMER_1_TIMER1_CONFIGURATION_H_ */
