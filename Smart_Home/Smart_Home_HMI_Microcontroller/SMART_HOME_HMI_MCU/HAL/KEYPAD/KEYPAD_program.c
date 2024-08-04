
/*----------------------------------------------------------------------------*/
/*-- @breief: KEYPAD_program.c       -----------------------------------------*/
/*-- @Author: Ahmed Atef Abdelrahman -----------------------------------------*/
/*-- @date:    Sep 12, 2023          -----------------------------------------*/
/*----------------------------------------------------------------------------*/

/*--------------------------------- Includes ---------------------------------*/

/*----------------------------------- LIB ------------------------------------*/
#include "../../LIB/StdTypes.h"
//#include "../../LIB/BitMath.h"
#define  F_CPU  8000000
#include "util/delay.h"
/*----------------------------------- MCAL -----------------------------------*/
#include "../../MCAL/DIO/DIO_interface.h"
/*----------------------------------- HAL ------------------------------------*/
#include "KEYPAD_private.h"
#include "KEYPAD_configuration.h"
#include "KEYPAD_interface.h"
/*---------------------------- Software Interfaces ---------------------------*/


u8 LOCAL_ARR[4][4] = KEYPAD_ARR;


u8 arr_row[4] = {KEYPAD_ROW0_PIN,KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN};

u8 arr_col[4] = {KEYPAD_COL0_PIN,KEYPAD_COL1_PIN,KEYPAD_COL2_PIN,KEYPAD_COL3_PIN};

u8 r,c;

void H_KEYPAD_voidInit(void)
{
	for (r = 0; r < 4; r++)
		{
		    //step 1  config rows as output
		M_DIO_voidSetPinDirection(arr_row[r], OUTPUT);
			//step 2  config cols as input
		M_DIO_voidSetPinDirection(arr_col[r], INPUT);
			//step 3  config cols as high  //pullup resistor
		M_DIO_voidSetPinValue(arr_col[r], HIGH);  //comment this line if there are pullup resitors on the hardware
			                                        //or in the simulation else use this internal pullup resistor
			//step 4  config initial value of rows as high
		M_DIO_voidSetPinValue(arr_row[r], HIGH);
		}
}

u8 H_KEYPAD_u8_getPressedKey(void) {

	u8 key=NO_PRESSED_KEY;

	for (r = 0; r < 4; r++)
	{
		M_DIO_voidSetPinValue(arr_row[r] , LOW); //first row R0 = 0;
	    for(c=0;c<4;c++)
	    {//cheak column
	    	if(M_DIO_u8GetPinValue(arr_col[c])==BUTTON_PRESSED)
	    	{
	    		while(M_DIO_u8GetPinValue(arr_col[c])==BUTTON_PRESSED);
	    		key=LOCAL_ARR[r][c];
	    	}
	    }
	    M_DIO_voidSetPinValue(arr_row[r] , HIGH);//R0=1 AGAIN and try for another row
    }
	return key;
}

