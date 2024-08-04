/*
 * ADC.c
 *
 *  Created on: Sep 16, 2023
 *      Author: ahmed
 */


#define F_CPU 8000000
#include <util/delay.h>
/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"

/*----------------------------------- MCAL -----------------------------------*/
//#include "../../MCAL/ADC/ADC_interface.h"
/*----------------------------------- HAL ------------------------------------*/
#include "../../HAL/LCD/LCD_interface.h"
#include "../../HAL/SENSORS/SENSORS_interface.h"
/*----------------------------------- APP ------------------------------------*/

u16 adc_reading;
u16 temp;

void GET_TEMP_INIT(void) {
	//M_ADC_voidInit(ADC_VCC,ADC_SCALER_64);
	H_SENSORS_voidInit();
	H_LCD_voidInit();
}

void GET_TEMP_RANABLE(void) {

	H_LCD_voidSetPosition(1, 1);
	H_LCD_voidSendString("Temp =");
	temp = H_LM35_GetTemp();
	H_LCD_voidSetPosition(1, 8);
	H_LCD_SendNumber(temp/ 10);
//	H_LCD_voidSendChar('.');
//	H_LCD_SendNumber(temp % 10);
//	H_LCD_voidSendChar(' ');
//	H_LCD_voidSendChar('C');
	//_delay_ms(300);

}

