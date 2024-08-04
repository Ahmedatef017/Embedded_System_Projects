/*
 * EXTI_private.h
 *
 *  Created on: Sep 15, 2023
 *      Author: ahmed
 */

#ifndef EXT_INTERRUPT_EXTI_PRIVATE_H_
#define EXT_INTERRUPT_EXTI_PRIVATE_H_

/************************EX_INTERRUPT REGISTERS ADDRESSES ********************************************/
#define  MCUCR   *(volatile unsigned char*) 0x55
#define  MCUCSR  *(volatile unsigned char*) 0x54
#define  GICR    *(volatile unsigned char*) 0x5B
#define  GIFR    *(volatile unsigned char*) 0x5A

/********************************** MCUCR ********************************************/
#define SE    7
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
/********************************** MCUCSR ********************************************/
#define JTD   7
#define ISC2  6
#define JTRF  4
#define WDRF  3
#define BORF  2
#define EXTRF 1
#define PORF  0
/********************************** GICR ********************************************/
#define IVCE  0
#define IVSEL 1
#define INT2  5
#define INT0  6
#define INT1  7

/*********************************************************************************/
/* Interrupt vectors */
/* External Interrupt Request 0 */
#define INT0_vect			__vector_1
/* External Interrupt Request 1 */
#define INT1_vect			__vector_2
/* External Interrupt Request 2 */
#define INT2_vect			__vector_3



#  define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)


#endif /* EXT_INTERRUPT_EXTI_PRIVATE_H_ */
