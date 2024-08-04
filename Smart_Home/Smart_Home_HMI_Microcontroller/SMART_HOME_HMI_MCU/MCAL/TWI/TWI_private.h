/*
 * TWI_private.h
 *
 *  Created on: Sep 28, 2023
 *      Author: ahmed
 */

#ifndef MCAL_TWI_TWI_PRIVATE_H_
#define MCAL_TWI_TWI_PRIVATE_H_

#define TWDR  *(volatile u8*)0x23 //data register
#define TWAR  *(volatile u8*)0x22 //address register
#define TWCR  *(volatile u8*)0x56 //control register
#define TWSR  *(volatile u8*)0x21 //status register
#define TWBR  *(volatile u8*)0x20 //bit rate register

/********************************* TWCR *************************************/
#define TWINT  7  //interrupt flag
#define TWEA   6  //enable ack
#define TWSTA  5  //send start condition
#define TWSTO  4  //send stop condition
#define TWWC   3  //write collision flag
#define TWEN   2  // enable two wire interface
#define TWIE   0  // interrupt enable

/********************************* TWSR *************************************/
#define TWPS1  1  //prescaler_1
#define TWPS0  0  //prescaler_0

/********************************* TWAR *************************************/
#define TWGCE  0  //General Call Recognition

#define TWI_STATUS_MUSK  0b11111000
#endif /* MCAL_TWI_TWI_PRIVATE_H_ */
