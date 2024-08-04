/*
 * UART_interface.h
 *
 *  Created on: Sep 24, 2023
 *      Author: ahmed
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

void M_UART_voidInit(void);
void M_UART_voidSend(u8 data);
u8   M_UART_u8Receive(void);
u8   M_UART_u8ReceivePeriodic(u8*pdata);

void M_UART_voidSendNoBlock(u8 data);
u8   M_UART_u8ReceiveNoBlock(void);

void M_UART_void_RX_InterruptEnable(void);
void M_UART_void_RX_InterruptDisable(void);

void M_UART_void_TX_InterruptEnable(void);
void M_UART_voidTX_InterruptDisable(void);

void M_UART_void_RX_SetCallBack(void (*LocalFptr)(void));
void M_UART_void_TX_SetCallBack(void (*LocalFptr)(void));

#endif /* MCAL_UART_UART_INTERFACE_H_ */


