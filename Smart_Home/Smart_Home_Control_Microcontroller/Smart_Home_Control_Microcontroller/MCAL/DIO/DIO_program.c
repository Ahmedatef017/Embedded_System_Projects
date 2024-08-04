/*----------------------------------------------------------------------------*/
/*-- @breief: DIO_program.c          -----------------------------------------*/
/*-- @Author: Ahmed Atef Abdelrahman -----------------------------------------*/
/*-- @date:    Sep 9, 2023           -----------------------------------------*/
/*----------------------------------------------------------------------------*/
#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"

#include "DIO_private.h"
#include "DIO_configuration.h"
#include "DIO_interface.h"
/************************** software implementation ****************************/
void M_DIO_voidSetPinDirection(u8 Copy_u8PinId,u8 Copy_u8Direction)
{
	u8 port;
	u8 pin;
	port = Copy_u8PinId / 8;
	pin  = Copy_u8PinId % 8;
	switch(Copy_u8Direction)
	{
		case OUTPUT:
		switch(port)
		{
			case PORT_A:
			SET_BIT(DDRA,pin);
            break;
			case PORT_B:
			SET_BIT(DDRB,pin);
			break;
			case PORT_C:
			SET_BIT(DDRC,pin);
			break;
			case PORT_D:
			SET_BIT(DDRD,pin);
			break;
		}
		break;
		case INPUT:
		switch(port)
		{
			case PORT_A:
			CLEAR_BIT(DDRA,pin);
			break;
			case PORT_B:
			CLEAR_BIT(DDRB,pin);
			break;
			case PORT_C:
			CLEAR_BIT(DDRC,pin);
			break;
			case PORT_D:
			CLEAR_BIT(DDRD,pin);
			break;
		}
		break;
	}
}
void M_DIO_voidSetPinValue(u8 Copy_u8PinId,u8 Copy_u8Value)
{
	u8 port;
		u8 pin;
		port = Copy_u8PinId/8;
		pin  = Copy_u8PinId%8;
		switch(Copy_u8Value)
		{
			case HIGH:
			switch(port)
			{
				case PORT_A:
				SET_BIT(PORTA,pin);
				break;
				case PORT_B:
				SET_BIT(PORTB,pin);
				break;
				case PORT_C:
				SET_BIT(PORTC,pin);
				break;
				case PORT_D:
				SET_BIT(PORTD,pin);
				break;
			}
			break;
			case LOW:
			switch(port)
			{
				case PORT_A:
				CLEAR_BIT(PORTA,pin);
				break;
				case PORT_B:
				CLEAR_BIT(PORTB,pin);
				break;
				case PORT_C:
				CLEAR_BIT(PORTC,pin);
				break;
				case PORT_D:
				CLEAR_BIT(PORTD,pin);
				break;
			}
			break;
		}

}
u8 M_DIO_u8GetPinValue(u8 Copy_u8PinId)
{
	u8 port;
		u8 pin;
		u8 volt = LOW;
		port = Copy_u8PinId/8;
		pin  = Copy_u8PinId%8;
		switch(port)
		{
			case PORT_A:
			volt = READ_BIT(PINA,pin);
			break;
			case PORT_B:
			volt = READ_BIT(PINB,pin);
			break;
			case PORT_C:
			volt = READ_BIT(PINC,pin);
			break;
			case PORT_D:
			volt = READ_BIT(PIND,pin);
			break;
		}
		return volt;
}

void  M_DIO_voidTogglePinValue(u8 Copy_u8PinId)
{
	if(M_DIO_u8GetPinValue(Copy_u8PinId)==LOW)
	{
		M_DIO_voidSetPinValue(Copy_u8PinId,HIGH);
	}
	else
	{
		M_DIO_voidSetPinValue(Copy_u8PinId,LOW);
	}
}

void M_DIO_voidSetPortDirection(u8 Copy_u8PortId,u8 Copy_u8Direction)
{
	switch(Copy_u8Direction)
	{
		case OUTPUT:
		switch(Copy_u8PortId)
		{
			case PORT_A:
			DDRA = 0xFF;
			break;
			case PORT_B:
			DDRB = 0xFF;
			break;
			case PORT_C:
			DDRC = 0xFF;
			break;
			case PORT_D:
			DDRD = 0xFF;
			break;
		}
		break;
		case INPUT:
		switch(Copy_u8PortId)
		{
			case PORT_A:
			DDRA = 0x00;
			break;
			case PORT_B:
			DDRB = 0x00;
			break;
			case PORT_C:
			DDRC = 0x00;
			break;
			case PORT_D:
			DDRD = 0x00;
			break;
		}
		break;
	}
}
void M_DIO_voidSetPortValue(u8 Copy_u8PortId,u8 Copy_u8Value)
{
	switch(Copy_u8PortId)
		{
			case PORT_A:
			PORTA = Copy_u8Value;
			break;
			case PORT_B:
			PORTB = Copy_u8Value;
			break;
			case PORT_C:
			PORTC = Copy_u8Value;
			break;
			case PORT_D:
			PORTD = Copy_u8Value;
			break;
		}
}
u8 M_DIO_u8GetPortValue(u8 Copy_u8PortId)
{
	u8 value = 0 ;
		switch(Copy_u8PortId)
		{
			case PORT_A:
			value = PINA;
			break;
			case PORT_B:
			value = PINB;
			break;
			case PORT_C:
			value = PINC;
			break;
			case PORT_D:
			value = PIND;
			break;
		}
		return value;

}
