/*
 * KEYPAD_configuration.h
 *
 *  Created on: Sep 11, 2023
 *      Author: ahmed
 */

#ifndef KEYPAD_KEYPAD_CONFIGURATION_H_
#define KEYPAD_KEYPAD_CONFIGURATION_H_



#define KEYPAD_ROW0_PIN  PIND3
#define KEYPAD_ROW1_PIN  PIND5
#define KEYPAD_ROW2_PIN  PINC2
#define KEYPAD_ROW3_PIN  PINC3

#define KEYPAD_COL0_PIN  PINC4
#define KEYPAD_COL1_PIN  PINC5
#define KEYPAD_COL2_PIN  PINC6
#define KEYPAD_COL3_PIN  PINC7



#define KEYPAD_ARR1 {{1,2,3,4},\
                    {5,6,7,8}, \
                    {9,10,11,12},\
	                {13,14,15,16}}

#define KEYPAD_ARR2 {{'7','8','9','/'},\
	                 {'4','5','6','*'},\
                     {'1','2','3','+'},\
					 {'c','0','=','-'}}

#define KEYPAD_ARR  KEYPAD_ARR2

#endif /* KEYPAD_KEYPAD_CONFIGURATION_H_ */
