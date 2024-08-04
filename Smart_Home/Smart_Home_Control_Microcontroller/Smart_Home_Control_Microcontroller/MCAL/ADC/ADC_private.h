/*
 * ADC_private.h
 *
 *  Created on: Sep 15, 2023
 *      Author: ahmed
 */

#ifndef ADC_ADC_PRIVATE_H_
#define ADC_ADC_PRIVATE_H_
/********************************** ADC REGISTERS ADDRESSES ********************************************/
#define  ADMUX   *(volatile unsigned char*) 0x27
#define  ADCSRA  *(volatile unsigned char*) 0x26
#define  SFIOR   *(volatile unsigned char*) 0x50
#define  ADCH    *(volatile unsigned char*) 0x25
#define  ADCL    *(volatile unsigned char*) 0x24
#define  ADC     *(volatile unsigned short*)0x24

/********************************** ADMUX ********************************************/
#define REFS1  7
#define REFS0  6
#define ADLAR  5
/********************************** ADCSRA ********************************************/
#define ADEN  7
#define ADSC  6
#define ADATE 5
#define ADIF  4
#define ADIE  3
/********************************** SFIOR ********************************************/
#define ACME  3
#define PUD   2
#define PSR2  1
#define PSR10 0



#endif /* ADC_ADC_PRIVATE_H_ */
