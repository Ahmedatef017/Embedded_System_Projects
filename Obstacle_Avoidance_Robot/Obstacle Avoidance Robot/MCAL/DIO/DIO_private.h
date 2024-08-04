/*
 * DIO_private.h
 *
 *  Created on: Sep 9, 2023
 *      Author: Ahmed Atef
 */

#ifndef INCLUDE_MCAL_DIO_DIO_PRIVATE_H_
#define INCLUDE_MCAL_DIO_DIO_PRIVATE_H_

#define PORTA    *(volatile unsigned char*)0x3B
#define DDRA     *(volatile unsigned char*)0x3A
#define PINA     *(volatile unsigned char*)0x39

#define PORTB    *(volatile unsigned char*)0x38
#define DDRB     *(volatile unsigned char*)0x37
#define PINB     *(volatile unsigned char*)0x36

#define PORTC    *(volatile unsigned char*)0x35
#define DDRC     *(volatile unsigned char*)0x34
#define PINC     *(volatile unsigned char*)0x33

#define PORTD    *(volatile unsigned char*)0x32
#define DDRD     *(volatile unsigned char*)0x31
#define PIND     *(volatile unsigned char*)0x30

#endif /* INCLUDE_MCAL_DIO_DIO_PRIVATE_H_ */
