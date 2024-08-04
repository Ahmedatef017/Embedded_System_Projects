/*
 * EEPROM_program.c
 *
 *  Created on: Sep 29, 2023
 *      Author: ahmed
 */

#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"
#include "EEPROM_private.h"
#include "EEPROM_cofiguration.h"
#include "EEPROM_interface.h"
#include "../../MCAL/TWI/TWI_Interface.h"

void H_EEPROM_voidInit(void) {
	M_TWI_voidInit();
}
u8 H_EEPROM_u8Write_Byte(u16 copy_u16Address, u8 data) {
	u8 _3BIT_MSB;
	//send start
	M_TWI_voidSendStart();
	//cheak status
	if (!(M_TWI_u8GetStatus() == TWI_MT_START_SUCCESS)) {
		return 0;
	}
	//send SLA+W
	_3BIT_MSB = (u8) ((copy_u16Address & 0x0700) >> 7);
	M_TWI_voidSendByte(_3BIT_MSB | 0xA0);
	//cheak status

	if (!(M_TWI_u8GetStatus() == TWI_MT_SLA_WRITE_WITH_ACK)) {
		return 0;
	}
	//send rest address
	M_TWI_voidSendByte((u8)(copy_u16Address));
	//cheak status
	if (!(M_TWI_u8GetStatus() == TWI_MT_DATA_TRANSMITTED_WITH_ACK)) {
		return 0;
	}
	M_TWI_voidSendByte(data);
	//stop
	M_TWI_voidSendStop();
	return 1;
}

u8 H_EEPROM_u8Read_Byte(u16 copy_u16Address, u8 *ptr_data) {
	u8 _3BIT_MSB;
	//send start
	M_TWI_voidSendStart();
	//cheak status
	if (!(M_TWI_u8GetStatus() == TWI_MT_START_SUCCESS)) {
		return 0;
	}
	//send SLA+W
	_3BIT_MSB = (u8) ((copy_u16Address & 0x0700) >> 7);
	M_TWI_voidSendByte(_3BIT_MSB | 0xA0);
	//cheak status
	if (!(M_TWI_u8GetStatus() == TWI_MT_SLA_WRITE_WITH_ACK)) {
		return 0;
	}
	//send rest address
	M_TWI_voidSendByte((u8) (copy_u16Address));
	//cheak status
	if (!(M_TWI_u8GetStatus() == TWI_MT_DATA_TRANSMITTED_WITH_ACK)) {
		return 0;
	}
	//send repeated start
	M_TWI_voidSendStart();
	//cheak status
	if (!(M_TWI_u8GetStatus() == TWI_MR_REPEATED_START_SUCCESS)) {
		return 0;
	}
	//send SLA+R
	M_TWI_voidSendByte( 0xA0 | 1 );
	//cheak status
	if (!(M_TWI_u8GetStatus() == TWI_MR_SLA_READ_WITH_ACK)) {
		return 0;
	}
	//recieve
	M_TWI_voidRecieveByte_NoAck(ptr_data);
	//cheak status
	if (!(M_TWI_u8GetStatus() == TWI_MR_recieved_data_WITH_NOACK)) {
		return 0;
	}
	//send stop
	M_TWI_voidSendStop();
	return 1;
}
