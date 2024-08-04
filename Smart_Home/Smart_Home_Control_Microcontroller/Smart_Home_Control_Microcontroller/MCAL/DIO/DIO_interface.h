/*
 * DIO_interface.h
 *
 *  Created on: Sep 9, 2023
 *      Author:Ahmed Atef
 */

#ifndef INCLUDE_MCAL_DIO_DIO_INTERFACE_H_
#define INCLUDE_MCAL_DIO_DIO_INTERFACE_H_

/**************************** macros definitions ********************************/
/*define port*/
#define PORT_A  0
#define PORT_B  1
#define PORT_C  2
#define PORT_D  3
/*define pins*/
#define PINA0   0
#define PINA1   1
#define PINA2   2
#define PINA3   3
#define PINA4   4
#define PINA5   5
#define PINA6   6
#define PINA7   7
#define PINB0   8
#define PINB1   9
#define PINB2   10
#define PINB3   11
#define PINB4   12
#define PINB5   13
#define PINB6   14
#define PINB7   15
#define PINC0   16
#define	PINC1   17
#define	PINC2   18
#define	PINC3   19
#define	PINC4   20
#define	PINC5   21
#define	PINC6   22
#define	PINC7   23
#define PIND0   24
#define	PIND1   25
#define	PIND2   26
#define	PIND3   27
#define	PIND4   28
#define	PIND5   29
#define	PIND6   30
#define	PIND7   31
/*define direction of pins*/
#define OUTPUT  1
#define INPUT   0
/*define output voltage of pins*/
#define HIGH    1
#define LOW     0
/**************************** software declaration ******************************/
void M_DIO_voidSetPinDirection(u8 Copy_u8PinId,u8 Copy_u8Direction);
void M_DIO_voidSetPinValue(u8 Copy_u8PinId,u8 Copy_u8Value);
u8   M_DIO_u8GetPinValue(u8 Copy_u8PinId);
void  M_DIO_voidTogglePinValue(u8 Copy_u8PinId);

void M_DIO_voidSetPortDirection(u8 Copy_u8PortId,u8 Copy_u8Direction);
void M_DIO_voidSetPortValue(u8 Copy_u8PortId,u8 Copy_u8Value);
u8   M_DIO_u8GetPortValue(u8 Copy_u8PortId);

#endif /* INCLUDE_MCAL_DIO_DIO_INTERFACE_H_ */
