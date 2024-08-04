/*
 * TWI_program.c
 *
 *  Created on: Sep 28, 2023
 *      Author: ahmed
 */
#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"
#include "TWI_private.h"
#include "TWI_configuration.h"
#include "TWI_Interface.h"

void M_TWI_voidInit(void)
{

	// Set Prescaler = 1
	CLEAR_BIT(TWSR,TWPS1);
	CLEAR_BIT(TWSR,TWPS0);
	// Adjust Bit Rate
	TWBR = 0x02; //8MHZ  PRESCALER_1
	// Enable TWI
	SET_BIT(TWCR,TWEN);
}
void M_TWI_voidSendStart(void)
{
	//clear flag - start condition - enable TWI
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	//wait until job finished
	while(READ_BIT(TWCR,TWINT)==0);
}
void M_TWI_voidSendStop(void)
{
	//clear flag - stop condition - enable TWI
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
void M_TWI_voidSendByte(u8 copy_u8data)
{
	//load data to data reg  data can be SLA+R/W or message(data)
	TWDR = copy_u8data;
	//clear flag - enable TWI
	TWCR = (1<<TWINT) | (1<<TWEN);
	//wait until job finished
	while(READ_BIT(TWCR,TWINT)==0);

}
void M_TWI_voidRecieveByte_Ack(u8*ptr)
{
	//clear flag - enable ACK - enable TWI
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	//wait until job finished
	while(READ_BIT(TWCR,TWINT)==0);
	//return data
	*ptr = TWDR;

}
void M_TWI_voidRecieveByte_NoAck(u8*ptr)
{
	//disable ACK
	CLEAR_BIT(TWCR,TWEA);
	//clear flag - enable TWI
	TWCR = (1<<TWINT)|(1<<TWEN);
	//wait until job finished
	while(READ_BIT(TWCR,TWINT)==0);
	//return data
	*ptr = TWDR;
}
u8 M_TWI_u8GetStatus(void)
{
  return (TWSR & TWI_STATUS_MUSK);
}
