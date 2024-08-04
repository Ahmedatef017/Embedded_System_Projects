/*----------------------------------------------------------------------------*/
/*-- @breief: SENSORS_program.c      -----------------------------------------*/
/*-- @Author: Ahmed Atef Abdelrahman -----------------------------------------*/
/*-- @date:    Sep 16, 2023          -----------------------------------------*/
/*----------------------------------------------------------------------------*/

/*--------------------------------- Includes ---------------------------------*/
//#include <stdlib.h>

/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"

/*----------------------------------- MCAL -----------------------------------*/
#include "../../MCAL/ADC/ADC_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
/*----------------------------------- HAL ------------------------------------*/
#include "SENSORS_private.h"
#include "SENSORS_configuration.h"
#include "SENSORS_interface.h"
/*---------------------------- Software Interfaces ---------------------------*/
void H_SENSORS_voidInit(void)
{
	//INITIALIZATION OF ADC
	M_ADC_voidInit(ADC_VCC,ADC_SCALER_64);
	/*LM35 PIN INPUT*/
	M_DIO_voidSetPinDirection(LM35_PIN,INPUT);
	/*POT PIN INPUT*/
	M_DIO_voidSetPinDirection(POT_PIN,INPUT);
	/*LDR PIN INPUT*/
	M_DIO_voidSetPinDirection(LDR_PIN,INPUT);
}

u16 H_LM35_GetTemp(void)
{
	u16 volt = M_ADC_u16GetVolt(LM35_CHANNEL);
	u16 temp = volt;
	return temp;
}

u16  LDR_GetVolt(void)
{
	u16 volt = M_ADC_u16GetVolt(LDR_CHANNEL);
	return volt;
}

u8 POT_GetPerc(void)
{
	u8 perc;
	u16 adc_read = M_ADC_u16GetReading(POT_CHANNEL);
	perc = ((u32)adc_read*100)/1023;
	return perc;
}

