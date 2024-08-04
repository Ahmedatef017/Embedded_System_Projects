/*
 * TWI_Interface.h
 *
 *  Created on: Sep 28, 2023
 *      Author: ahmed atef
 */

#ifndef MCAL_TWI_TWI_INTERFACE_H_
#define MCAL_TWI_TWI_INTERFACE_H_

/*Master Transmitter Mode*/
#define TWI_MT_START_SUCCESS                0x08
#define TWI_MT_REPEATED_START_SUCCESS       0x10
#define TWI_MT_SLA_WRITE_WITH_ACK           0x18
#define TWI_MT_SLA_WRITE_WITH_NOACK         0x20
#define TWI_MT_DATA_TRANSMITTED_WITH_ACK    0x28
#define TWI_MT_DATA_TRANSMITTED_WITH_NOACK  0x30
#define TWI_MT_ARBITRATION_LOST             0x38
/*Master Receiver Mode*/
#define TWI_MR_START_SUCCESS                0x08
#define TWI_MR_REPEATED_START_SUCCESS       0x10
#define TWI_MR_SLA_READ_WITH_ACK            0x40
#define TWI_MR_SLA_WREAD_WITH_NOACK         0x48
#define TWI_MR_DATA_RECIEVED_WITH_ACK       0x50
#define TWI_MR_DATA_RECIEVED_WITH_NOACK     0x58
#define TWI_MR_ARBITRATION_LOST             0x38


void M_TWI_voidInit(void);
void M_TWI_voidSendStart(void);
void M_TWI_voidSendStop(void);
void M_TWI_voidSendByte(u8 copy_u8data);//Send SLA + R/W in the same byte
void M_TWI_voidRecieveByte_Ack(u8*ptr);
void M_TWI_voidRecieveByte_NoAck(u8*ptr);
u8 M_TWI_u8GetStatus(void);

#endif /* MCAL_TWI_TWI_INTERFACE_H_ */
