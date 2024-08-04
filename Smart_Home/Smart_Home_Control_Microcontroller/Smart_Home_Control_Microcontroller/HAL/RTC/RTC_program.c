/*
 * RTC_program.c
 *
 *  Created on: Sep 30, 2023
 *      Author: ahmed
 */


#include  "../../LIB/StdTypes.h"
#include  "../../MCAL/TWI/TWI_Interface.h"
#include  "RTC_private.h"
#include  "RTC_configuration.h"
#include  "RTC_interface.h"


void RTC_Init(void) {
	M_TWI_voidInit();
	M_TWI_voidSendStart();
	M_TWI_voidSendByte(0xD0);
	M_TWI_voidSendByte(0x07);
	M_TWI_voidSendByte(0x00);
	M_TWI_voidSendStop();
}
void RTC_Set_Time(u8 sec, u8 min, u8 hour) {
	M_TWI_voidSendStart();
	M_TWI_voidSendByte(0xD0);
	M_TWI_voidSendByte(0);
	M_TWI_voidSendByte(sec);
	M_TWI_voidSendByte(min);
	M_TWI_voidSendByte(hour);
	M_TWI_voidSendStop();
}
void RTC_Get_Time(u8 *sec, u8 *min, u8 *hour) {
	M_TWI_voidSendStart();
	M_TWI_voidSendByte(0xD0);
	M_TWI_voidSendByte(0);
	M_TWI_voidSendStop();
	M_TWI_voidSendStart();
	M_TWI_voidSendByte(0xD1);
	M_TWI_voidRecieveByte_Ack(sec);
	M_TWI_voidRecieveByte_Ack(min);
	M_TWI_voidRecieveByte_NoAck(hour);
	M_TWI_voidSendStop();
}

void RTC_Set_Date(u8 day, u8 mon, u8 year) {
	M_TWI_voidSendStart();
	M_TWI_voidSendByte(0xD0);
	M_TWI_voidSendByte(0x04);
	M_TWI_voidSendByte(day);
	M_TWI_voidSendByte(mon);
	M_TWI_voidSendByte(year);
	M_TWI_voidSendStop();
}
void RTC_Get_Date(u8 *day, u8 *mon, u8 *year) {
	M_TWI_voidSendStart();
	M_TWI_voidSendByte(0xD0);
	M_TWI_voidSendByte(0x04);
	M_TWI_voidSendStop();
	M_TWI_voidSendStart();
	M_TWI_voidSendByte(0xD1);
	M_TWI_voidRecieveByte_Ack(day);
	M_TWI_voidRecieveByte_Ack(mon);
	M_TWI_voidRecieveByte_NoAck(year);
	M_TWI_voidSendStop();
}
