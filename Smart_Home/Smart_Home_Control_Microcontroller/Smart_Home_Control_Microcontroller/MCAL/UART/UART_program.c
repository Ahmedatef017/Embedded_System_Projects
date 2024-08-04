/*
 * UART_program.c
 *
 *  Created on: Sep 24, 2023
 *      Author: ahmed
 */


#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"
#include "../../MCAL/GIE/GIE_interface.h"
#include "UART_private.h"
#include "UART_configuration.h"
#include "UART_interface.h"

/****************************Pointer to functions to be assigned to ISR*********************************/

static void (*UART_RX_Fptr) (void)=NULL;
static void (*UART_TX_Fptr) (void)=NULL;
/*********************************/

void M_UART_voidInit(void)
{
	//frame 8bit 1 stop bit no parity
	//baud rate
	UBRRL=51;
	//Baud rate 9600 for 8MHZ normal speed
	CLEAR_BIT(UCSRA,U2X);

	//enable TX and RX
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	//
	M_Global_Interrupt_Enable();

}
void M_UART_voidSend(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=data;
}
u8 M_UART_u8Receive(void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
}
u8 M_UART_u8ReceivePeriodic(u8*pdata)
{
	if(READ_BIT(UCSRA,RXC)==1)
	{
		*pdata=UDR;
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************Send and receive functions with no ckecking********************************/

void M_UART_voidSendNoBlock(u8 data)
{
	UDR = data;
}

u8 M_UART_u8ReceiveNoBlock(void)      // to be use in Interrupt
{
	return UDR;
}
/*****************************************Interrupt functions*********************************************/


void M_UART_void_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void M_UART_void_RX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB,RXCIE);
}

void M_UART_void_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void M_UART_void_TX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB,TXCIE);
}
/*****************************************Set Call Back Functions*********************************************/
void M_UART_void_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void M_UART_void_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}

 /****************************************************/
 ISR(UART_RX_vect)
 {
 	if (UART_RX_Fptr!=NULL)
 	{
 		UART_RX_Fptr();
 	}
 }

 ISR(UART_TX_vect)
 {
 	if (UART_TX_Fptr!=NULL)
 	{
 		UART_TX_Fptr();
 	}
 }


