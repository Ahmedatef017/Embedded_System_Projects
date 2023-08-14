


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO_Interface.h"

/****************************************** Config*************************/

#define FIRST_OUTPUT       PINB4  //
#define FIRST_INPUT        PIND4
#define COLS 4
#define ROWS 4
#define NO_KEY 'N'


 static u8 KeysArray[ROWS][COLS]=  {{'7','8','9','A'},  //for converter
 							    	{'4','5','6','B'},
 								    {'1','2','3','D'},
 							    	{'C','0','=','F'}
 							    	};		

/*************************************************************************/

u8 KEYPAD_GetKey(void);
s32 KEYPAD_ScanDecimel(u8 k,s32 num);
s32 KEYPAD_ScanHex(u8 k,s32 num);
s32 KEYPAD_ScanBinary(u8 k,s32 num);
#endif /* KEYPAD_H_ */