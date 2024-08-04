/*
 * Smart_Home_Control_Microcontroller.c
 *
 * Created: 1/28/2024 3:44:33 PM
 * Author : ahmed
 */ 


#define F_CPU 8000000
#include <util/delay.h>

#include "../LIB/StdTypes.h"
#include "../LIB/BitMath.h"
#include "../LIB/Std_Uart_Messages.h"

#include "../MCAL/UART/UART_interface.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/TIMER_0/TIMER0_interface.h"
#include "../MCAL/TIMER_0/TIMER0_private.h"
#include "../MCAL/GIE/GIE_interface.h"

#include "../HAL/LED/LED_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/SENSORS/SENSORS_interface.h"
#include "../HAL/DC_MOTOR/MOTOR_interface.h"
#include "../HAL/BUZZER/BUZZER_interface.h"

#include "../SERVICES/UART_SERVICES/UartServices.h"
#include "main_Cfg.h"

u8 temp_reading;
u8 data_recieved=24;
u8 data_send;
u8 fire_flag;
volatile u8 Reset_fire_flag;
u8 smoke_reading;

volatile u8 required_temperature=24; // the required temperature which sent from sender with initial value 24
volatile u16 temp_sensor_reading=0; // the temperature of the room
volatile u8  counter=0; // the counter which determine the periodic time of implementing ISR
volatile u8  last_air_conditioning_value=AIR_CONDTIONING_OFF; // last air conditioning value which will help in hysteresis

int main(void)
{
	M_DIO_voidSetPortDirection(PORT_C,OUTPUT);
	H_LED_voidInit(LED_RED_PIN);
	H_LED_voidInit(LED_GREEN_PIN);
	H_LED_voidInit(LED_ORANGE_PIN);
	H_LED_voidInit(ROOM1_LED_PIN);
	H_LED_voidInit(ROOM2_LED_PIN);
	H_LED_voidInit(ROOM3_LED_PIN);
	H_LED_voidInit(ROOM4_LED_PIN);
	H_LED_voidInit(TV_LED_PIN);
	H_LED_voidInit(AIR_COND_LED_PIN);

	H_BUZZER_voidInit();
	H_MOTOR_voidInit();
	H_SENSORS_voidInit();
	H_LCD_voidInit();
	M_UART_voidInit();
	M_Timer0_Init();
	M_TIMER0_EnableInt(TIMER0_OVF_INTERRUPT);
	M_Global_Interrupt_Enable();
	S_UART_void_ReceiveCharAsynch(&data_recieved);
	
	u8 room1_status = OFF_STATUS;
	u8 room2_status = OFF_STATUS;
    u8 room3_status = OFF_STATUS;
	u8 room4_status = OFF_STATUS;
	u8 TV_status    = OFF_STATUS;	
	u8 AC_status    = OFF_STATUS;
	
	u16 volt=0;
    while (1) 
    {
		volt= LDR_GetVolt();
	    if(volt<=454 && volt>=0)
		{
			//turn all
	        M_DIO_voidSetPortValue(PORT_C, 0b11111111);
					
		}
		else if(volt<=1665 && volt>=460)
		{
			//turn on first 6
			M_DIO_voidSetPortValue(PORT_C, 0b01111111);
		}
		else if(volt<=2500 && volt>1665)
		{
			//turn on first 4
			M_DIO_voidSetPortValue(PORT_C, 0b00111111);
		}
		else if(volt<=3330 && volt>2500)
		{
			//turn on first 2
			M_DIO_voidSetPortValue(PORT_C, 0b00011111);
		}
		else if(volt<=4165 && volt>3330)
		{
			//turn off all leds
			M_DIO_voidSetPortValue(PORT_C, 0b00001111);
		}
		else if(volt<=4760 && volt>4165)
		{
			//turn off all leds
			M_DIO_voidSetPortValue(PORT_C, 0b00000111);
		}
		else if(volt<=4902 && volt>4760)
		{
			//turn off all leds
			M_DIO_voidSetPortValue(PORT_C, 0b00000011);
		}
		else if(volt<=4951 && volt>4902)
		{
			//turn off all leds
			M_DIO_voidSetPortValue(PORT_C, 0b00000001);
		}
		else if(volt<=4975 && volt>4951)
		{
			//turn off all leds
			M_DIO_voidSetPortValue(PORT_C, 0b00000000);
		}		
		temp_sensor_reading=(H_LM35_GetTemp()/10);
		H_LCD_voidSetPosition(1,33);
		H_LCD_voidSendString("CT:");
		H_LCD_voidSetPosition(1,36);
		H_LCD_SendNumber(temp_sensor_reading);
		H_LCD_voidSendChar(DEGREES_SYMBOL); // print the symbol of degree
		H_LCD_voidSendChar('C'); // print the C character
		
		H_LCD_voidSetPosition(2,33);
		H_LCD_voidSendString("RT:");
		H_LCD_voidSetPosition(2,36);
		H_LCD_SendNumber(required_temperature);
		H_LCD_voidSendChar(DEGREES_SYMBOL); // print the symbol of degree
		H_LCD_voidSendChar('C'); // print the C character
		
		smoke_reading = POT_GetPerc();
		H_LCD_voidSetPosition(2,21);
		H_LCD_voidSendString("Smoke :");
		H_LCD_voidSetPosition(2,28);
		H_LCD_SendNumber(smoke_reading);
		H_LCD_voidSendChar('%');
		

		H_LCD_voidSetPosition(1,0);
		H_LCD_voidSendString("R1:");
		H_LCD_voidSetPosition(1,3);
		//print room1 status
		if(room1_status==OFF_STATUS)
		{
			H_LCD_voidSendString("off");
		}
		else
		{
			H_LCD_voidSendString("on ");
		}
		
		H_LCD_voidSetPosition(2,0);
		H_LCD_voidSendString("R2:");
		H_LCD_voidSetPosition(2,3);
		if(room2_status==OFF_STATUS)
		{
			H_LCD_voidSendString("off");
		}
		else
		{
			H_LCD_voidSendString("on ");
		}
		
				
		H_LCD_voidSetPosition(1,7);
		H_LCD_voidSendString("R3:");
		H_LCD_voidSetPosition(1,10);
		if(room3_status==OFF_STATUS)
		{
			H_LCD_voidSendString("off");
		}
		else
		{
			H_LCD_voidSendString("on ");
		}
		
				
		H_LCD_voidSetPosition(2,7);
		H_LCD_voidSendString("R4:");
		H_LCD_voidSetPosition(2,10);	
		if(room4_status==OFF_STATUS)
		{
			H_LCD_voidSendString("off");
		}
		else
		{
			H_LCD_voidSendString("on ");
		}		
	    //TV
		H_LCD_voidSetPosition(1,14);
		H_LCD_voidSendString("TV:");
		H_LCD_voidSetPosition(1,17);
		if(TV_status==OFF_STATUS)
		{
			H_LCD_voidSendString("off");
		}
		else
		{
			H_LCD_voidSendString("on ");
		}		
		
		//AC
		H_LCD_voidSetPosition(2,14);
		H_LCD_voidSendString("AC:");
		H_LCD_voidSetPosition(2,17);
		if(AC_status==OFF_STATUS)
		{
			H_LCD_voidSendString("off");
		}
		else
		{
			H_LCD_voidSendString("on ");
		}
		
		H_LCD_voidSetPosition(1,21);
		H_LCD_voidSendString("Status:");
		/*---------------------------------Fire System------------------------------------*/
		
		if(temp_sensor_reading<=40 && fire_flag == 0)
		{
			H_LCD_voidSetPosition(1,28);
			H_LCD_voidSendString("Fine");
			H_LED_voidTurnOn(LED_GREEN_PIN);
			H_LED_voidTurnOff(LED_ORANGE_PIN);
			H_LED_voidTurnOff(LED_RED_PIN);
		}
		else
		{

			if(smoke_reading <=50 && fire_flag == 0)
			{
				H_LCD_voidSetPosition(1,28);
				H_LCD_voidSendString("Heat");
				H_LED_voidTurnOn(LED_ORANGE_PIN);
				H_LED_voidTurnOff(LED_GREEN_PIN);
				H_LED_voidTurnOff(LED_RED_PIN);
			}
			else //if(POT_GetPerc()>50)
			{
				H_LCD_voidSetPosition(1,28);
				H_LCD_voidSendString("Fire");
				H_LED_voidTurnOn(LED_RED_PIN);
			    H_LED_voidTurnOff(LED_ORANGE_PIN);
			    H_LED_voidTurnOff(LED_GREEN_PIN);
				H_MOTOR_voidCW(Motor_1);
				H_BUZZER_voidTurnOn();
				fire_flag = 1;				
			}
		}
		if(Reset_fire_flag==1)
		{
			H_LCD_voidSetPosition(1,28);
			H_LCD_voidSendString("Done");
			fire_flag=0;
			Reset_fire_flag=0;
			H_MOTOR_voidStop(Motor_1);
			H_LED_voidTurnOff(LED_RED_PIN);
			H_BUZZER_voidTurnOff();
		}

		switch(data_recieved)
		{
			//commands related to send the current status back to the sender
			case ROOM1_STATUS:
			if (M_DIO_u8GetPinValue(ROOM1_LED_PIN)==0)//if the led is turned off
			{
				data_send = OFF_STATUS;//set the data_recieved as off status
			}
			else if (M_DIO_u8GetPinValue(ROOM1_LED_PIN)==1)//if the led is turned on
			{
				data_send = ON_STATUS;//set the data_recieved as on status
			}
			else
			{
			}
			M_UART_voidSend(data_send);//data_recieved to the transmitter with the status

			break;//break the switch case
			case ROOM2_STATUS:
			if (M_DIO_u8GetPinValue(ROOM2_LED_PIN)==0)//if the led is turned off
			{
				data_send = OFF_STATUS;//set the data_recieved as off status
			}
			else if (M_DIO_u8GetPinValue(ROOM2_LED_PIN)==1)//if the led is turned on
			{
				data_send = ON_STATUS;//set the data_recieved as on status
			}
			else
			{
			}
			M_UART_voidSend(data_send);//data_recieved to the transmitter with the status

			break;//break the switch case
			case ROOM3_STATUS:
			if (M_DIO_u8GetPinValue(ROOM3_LED_PIN)==0)//if the led is turned off
			{
				data_send = OFF_STATUS;//set the data_recieved as off status
			}
			else if (M_DIO_u8GetPinValue(ROOM3_LED_PIN)==1)//if the led is turned on
			{
				data_send = ON_STATUS;//set the data_recieved as on status
			}
			else
			{
			}
			M_UART_voidSend(data_send);//data_recieved to the transmitter with the status

			break;//break the switch case
			case ROOM4_STATUS:
			if (M_DIO_u8GetPinValue(ROOM4_LED_PIN)==0)//if the led is turned off
			{
				data_send = OFF_STATUS;//set the data_recieved as off status
			}
			else if (M_DIO_u8GetPinValue(ROOM4_LED_PIN)==1)//if the led is turned on
			{
				data_send = ON_STATUS;//set the data_recieved as on status
			}
			else
			{
			}
			M_UART_voidSend(data_send);//data_recieved to the transmitter with the status

			break;//break the switch case
			case AIR_COND_STATUS:
			if (M_DIO_u8GetPinValue(AIR_COND_LED_PIN)==0)//if the led is turned off
			{
				data_send = OFF_STATUS;//set the data_recieved as off status
			}
			else if (M_DIO_u8GetPinValue(AIR_COND_LED_PIN)==1)//if the led is turned on
			{
				data_send = ON_STATUS;//set the data_recieved as on status
			}
			else
			{
			}
			M_UART_voidSend(data_send);//data_recieved to the transmitter with the status
			break;
			case TV_STATUS:
			if (M_DIO_u8GetPinValue(TV_LED_PIN)==0)//if the led is turned off
			{
				data_send = OFF_STATUS;//set the data_recieved as off status
			}
			else if (M_DIO_u8GetPinValue(TV_LED_PIN)==1)//if the led is turned on
			{
				data_send = ON_STATUS;//set the data_recieved as on status
			}
			else
			{
			}
			M_UART_voidSend(data_send);//data_recieved to the transmitter with the status
			break;//break the switch case

			/*********************************   TURN ON COMMANDS ********************************/
			case ROOM1_TURN_ON:
			H_LED_voidTurnOn(ROOM1_LED_PIN);//turn on the led of room 1
			room1_status=ON_STATUS;
			break;//break the switch case
			case ROOM2_TURN_ON:
			H_LED_voidTurnOn(ROOM2_LED_PIN);//turn on the led of room 2
			room2_status=ON_STATUS;
			break;//break the switch case
			case ROOM3_TURN_ON:
			H_LED_voidTurnOn(ROOM3_LED_PIN);//turn on the led of room 3
			room3_status=ON_STATUS;
			break;//break the switch case
			case ROOM4_TURN_ON:
			H_LED_voidTurnOn(ROOM4_LED_PIN);//turn on the led of room 4
			room4_status=ON_STATUS;
			break;//break the switch case
			case AIR_COND_TURN_ON:
			M_Timer0_start();
			if(temp_sensor_reading>required_temperature)
			{
				H_LED_voidTurnOn(AIR_COND_LED_PIN);//turn on the led of air conditioning
				AC_status=ON_STATUS;				
			}

			break;//break the switch case
			case TV_TURN_ON:
			H_LED_voidTurnOn(TV_LED_PIN);//turn on the led of the TV
			TV_status=ON_STATUS;
			break;//break the switch case

			/*********************************   TURN OFF COMMANDS ********************************/
			case ROOM1_TURN_OFF:
			H_LED_voidTurnOff(ROOM1_LED_PIN);//turn off the led of room 1
			room1_status=OFF_STATUS;
			break;//break the switch case
			case ROOM2_TURN_OFF:
			H_LED_voidTurnOff(ROOM2_LED_PIN);//turn off the led of room 2
			room2_status=OFF_STATUS;
			break;//break the switch case
			case ROOM3_TURN_OFF:
			H_LED_voidTurnOff(ROOM3_LED_PIN);//turn off the led of room 3
			room3_status=OFF_STATUS;
			break;//break the switch case
			case ROOM4_TURN_OFF:
			H_LED_voidTurnOff(ROOM4_LED_PIN);//turn off the led of room 4
			room4_status=OFF_STATUS;
			break;//break the switch case
			case AIR_COND_TURN_OFF:
			M_Timer0_stop();
			H_LED_voidTurnOff(AIR_COND_LED_PIN);//turn off the led of air conditioning
			AC_status=OFF_STATUS;
			break;//break the switch case
			case TV_TURN_OFF:
			H_LED_voidTurnOff(TV_LED_PIN);//turn off the led of the TV
			TV_status=OFF_STATUS;
			break;//break the switch case
            case RESET_FIRE_ALARM:
			Reset_fire_flag=1;
			data_recieved = NO_ACTION;
			break;
			case NO_ACTION:
			data_recieved=NO_ACTION;
			break;
			/*********************************   Set temperature   ********************************/
            default:
			required_temperature = data_recieved;
			data_recieved=NO_ACTION;
			break;//break the switch case
		}
    }
}

ISR(TIMER0_OVF_vect)
{
	counter++;//count the ticks of the timer zero
	if(counter>=HYSTERESIS)//do that code every 10 ticks
	{
		counter=0;//clear the counter of ticks
		temp_sensor_reading=(H_LM35_GetTemp()/10);//read the temperature from the temperature sensor connected to the ADC of the micro controller
		if (temp_sensor_reading>=(required_temperature+1))//do that code if the read temperature if greater than required temperature by one or more
		{
			H_LED_voidTurnOn(AIR_COND_LED_PIN);//turn on the led of the air conditioning
			last_air_conditioning_value=AIR_CONDTIONING_ON;//save the value of the state of the air conditioning
		}
		else if (temp_sensor_reading<=(required_temperature-1))//do that code if the read temperature if lesser than required temperature by one or more
		{
			H_LED_voidTurnOff(AIR_COND_LED_PIN);//turn off the led of the air conditioning
			last_air_conditioning_value=AIR_CONDTIONING_OFF;//save the value of the state of the air conditioning
		}
		else if (required_temperature==temp_sensor_reading)//do that code if the read temperature is equal to the required temperature
		{
			if (last_air_conditioning_value==AIR_CONDTIONING_ON)//in the case of the last saved status of the air conditioning was on
			{
				H_LED_voidTurnOn(AIR_COND_LED_PIN);//turn on the led of the air conditioning
			}
			else if (last_air_conditioning_value==AIR_CONDTIONING_OFF)//in the case of the last saved status of the air conditioning was off
			{
				H_LED_voidTurnOff(AIR_COND_LED_PIN);//turn off the led of the air conditioning
			}
		}
	}
}