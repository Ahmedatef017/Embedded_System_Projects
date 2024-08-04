/*
 * ADC_interface.h
 *
 *  Created on: Sep 15, 2023
 *      Author: ahmed
 */

#ifndef ADC_ADC_INTERFACE_H_
#define ADC_ADC_INTERFACE_H_

#define  VoltRef   5000
typedef enum{
	ADC_AREF=0,
	ADC_VCC=1,
	ADC_256V=3
	}ADC_Vref_type;

typedef enum{
	ADC_SCALER_2=0,
	ADC_SCALER_4=2,
	ADC_SCALER_8=3,
	ADC_SCALER_16=4,
	ADC_SCALER_32=5,
	ADC_SCALER_64=6,
	ADC_SCALER_128=7,
	}ADC_Scaler_type;

typedef enum{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7,
	}ADC_Channel_type;

void M_ADC_voidInit(ADC_Vref_type vref,ADC_Scaler_type scaler);
u16  M_ADC_u16GetReading(ADC_Channel_type ch);
u16  M_ADC_u16GetVolt(ADC_Channel_type ch);
void M_ADC_voidStartConversion(ADC_Channel_type ch);
u16  M_ADC_u16GetRead(void);
u8   M_ADC_GetReadPeriodicCheak(u8*pdata);



#endif /* ADC_ADC_INTERFACE_H_ */
