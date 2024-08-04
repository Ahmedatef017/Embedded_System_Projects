/*
 * UartServices.h
 *
 *  Created on: Jan 18, 2024
 *      Author: ahmed
 */

#ifndef UART_SERVICES_UARTSERVICES_H_
#define UART_SERVICES_UARTSERVICES_H_

void S_UART_void_ReceiveCharAsynch(u8*str);

void S_UART_ReceiveStringSynch(u8*str);
void S_UART_SendStringSynch(u8*str);

void S_UART_void_SendStringAsynch(u8*str);
void S_UART_void_ReceiveStringAsynch(u8*str);

#endif /* UART_SERVICES_UARTSERVICES_H_ */
