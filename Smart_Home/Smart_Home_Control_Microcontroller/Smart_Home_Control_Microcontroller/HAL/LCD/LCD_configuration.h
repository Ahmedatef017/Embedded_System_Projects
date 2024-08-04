/*
 * LCD_configuration.h
 *
 *  Created on: Sep 13, 2023
 *      Author: ahmed
 */

#ifndef LCD_LCD_CONFIGURATION_H_
#define LCD_LCD_CONFIGURATION_H_
/*-----------------------------------------------------------------------------*/
/*  Choose Mode Option :     1- LCD_4BIT     2- LCD_8BIT                       */
/*-----------------------------------------------------------------------------*/
#define LCD_SIZE  4
#define LCD_MODE  LCD_4BIT
/*control pins*/
#define RS_PIN  PINA3
#define EN_PIN  PINA2


#if LCD_MODE == LCD_4BIT
/*data pins for 4bit mode*/
#define D4_PIN  PINB0
#define D5_PIN  PINB1
#define D6_PIN  PINB2
#define D7_PIN  PINB4

#else
/*data pins for 8bit mode*/
#define D0_PIN  PINA0
#define D1_PIN  PINA1
#define D2_PIN  PINA2
#define D3_PIN  PINA3
#define D4_PIN  PINA4
#define D5_PIN  PINA5
#define D6_PIN  PINA6
#define D7_PIN  PINA7
#endif


#endif /* LCD_LCD_CONFIGURATION_H_ */
