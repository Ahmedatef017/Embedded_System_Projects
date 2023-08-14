#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "Utiles.h"
static void InitPin(DIO_Pin_type pin,DIO_PinMode_type mode)
{
	u8 pin_num;
	DIO_Port_type port;
	pin_num = pin%8;
	port = pin/8;
	switch(mode)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case INPULL:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			SET_BIT(PORTD,pin_num);
			break;
		}
		break;
	}
}
void DIO_WritePin(DIO_Pin_type pin,DIO_PinVoltage_type volt)
{
	u8 pin_num;
	DIO_Port_type port;
	pin_num = pin%8;
	port = pin/8;
	if(volt==HIGH)
	{
		switch(port)
		{
			case PA:
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(PORTD,pin_num);
			break;
		}
	}
	else if(volt==LOW)
	{
		switch(port)
		{
			case PA:
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(PORTD,pin_num);
			break;
		}
	}
}
DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type pin)
{
	u8 pin_num;
	DIO_Port_type port;
	pin_num = pin%8;
	port = pin/8;
	DIO_PinVoltage_type volt = LOW;
	switch(port)
	{
		case PA:
		volt = READ_BIT(PINA,pin_num);
		break;
		case PB:
		volt = READ_BIT(PINB,pin_num);
		break;
		case PC:
		volt = READ_BIT(PINC,pin_num);
		break;
		case PD:
		volt = READ_BIT(PIND,pin_num);
		break;
	}
	return volt;	
}
void DIO_TogglePin(DIO_Pin_type pin_num)
{
	if( pin_num<=7 )
	{
		TOG_BIT(PORTA,pin_num);
	}
	else if(pin_num>=8 && pin_num<=15)
	{
		TOG_BIT(PORTB,(pin_num-8));
	}
	else if(pin_num>=16 && pin_num<=23 )
	{
		TOG_BIT(PORTC,(pin_num-16));
	}
	else if(pin_num>=24 && pin_num<=31 )
	{
		TOG_BIT(PORTD,(pin_num-24));
	}
}
void DIO_WritePort(DIO_Port_type port,u8 value)
{
	if (port==PA)
	{
		PORTA=value;
	}
	else if (port==PB)
	{
		PORTB=value;
	}
	else if (port==PC)
	{
		PORTC=value;
	}
	else if (port==PD)
	{
		PORTD=value;
	}
}
u8 DIO_ReadPort(DIO_Port_type port)
{
	
	u8 value=0;
	if (port==PA)
	{
		value=PINA;
	}
	else if (port==PB)
	{
		value=PINB;
	}
	else if (port==PC)
	{
		value=PINC;
	}
	else if (port==PD)
	{
		value=PIND;
	}
	return value;
}

void DIO_InIt(void)
{
	DIO_Pin_type i;
	for(i=PINA0;i<TOTAL_PINS;i++)
	{
		InitPin(i,PinsModeArray[i]);
	}
}
