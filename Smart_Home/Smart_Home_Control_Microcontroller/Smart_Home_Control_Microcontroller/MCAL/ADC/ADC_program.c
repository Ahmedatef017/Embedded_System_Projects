/*----------------------------------------------------------------------------*/
/*-- @breief: ADC_program.c          -----------------------------------------*/
/*-- @Author: Ahmed Atef Abdelrahman -----------------------------------------*/
/*-- @date:    Sep 15, 2023          -----------------------------------------*/
/*----------------------------------------------------------------------------*/

/*--------------------------------- Includes ---------------------------------*/
#include <stdlib.h>
#include "util/delay.h"

/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"
/*----------------------------------- MCAL -----------------------------------*/

/*----------------------------------- HAL ------------------------------------*/
#include "ADC_private.h"
#include "ADC_configuration.h"
#include "ADC_interface.h"
/*---------------------------- Software Interfaces ---------------------------*/
/*ADC Initialization*/


void  M_ADC_voidInit(ADC_Vref_type vref,ADC_Scaler_type scaler)
{
	//vref
	switch (vref)
	{
		case ADC_AREF:
		CLEAR_BIT(ADMUX,REFS1);
		CLEAR_BIT(ADMUX,REFS0);
		break;
		case ADC_VCC:
		CLEAR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
		case ADC_256V:
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
	}

	//prescaler
	ADCSRA = ADCSRA & 0xf8;//0b11111000
	scaler = scaler & 0x07;
	ADCSRA = ADCSRA|scaler;
	//adjust read to the right  ADLAR=0
	CLEAR_BIT(ADMUX,ADLAR);
	//enable
	SET_BIT(ADCSRA,ADEN);
}

u16   M_ADC_u16GetReading(ADC_Channel_type ch)
{
	//channel
	ADMUX=ADMUX&0xe0;
	//ch=ch&0x1f;
	ADMUX=ADMUX|ch;
	//start conversion
	SET_BIT(ADCSRA,ADSC);
	while(READ_BIT(ADCSRA,ADSC));//busy
	//reading
	return ADC;

}

u16  M_ADC_u16GetVolt(ADC_Channel_type ch)
{
	u16 adc = M_ADC_u16GetReading(ch);
	u16 volt = (((u32)adc*VoltRef)/1023);
	return volt;
}
static u8 read_flag=1;
void M_ADC_voidStartConversion(ADC_Channel_type ch)
{
	if(read_flag==1)
	{
		//channel
		ADMUX=ADMUX&0xe0;
		//ch=ch&0x1f;
		ADMUX=ADMUX|ch;
		//start conversion
		SET_BIT(ADCSRA,ADSC);
		read_flag=0;
	}

}
u16 M_ADC_u16GetRead(void)
{
	while(READ_BIT(ADCSRA,ADSC));//busy
	read_flag=1;
	//reading
	return ADC;
}

u8 M_ADC_GetReadPeriodicCheak(u8*pdata)
{
	if(READ_BIT(ADCSRA,ADSC)==0)
	{
		*pdata=ADC;
		read_flag=1;
		return 1;
	}
	else
	{
		return 0;
	}
}
