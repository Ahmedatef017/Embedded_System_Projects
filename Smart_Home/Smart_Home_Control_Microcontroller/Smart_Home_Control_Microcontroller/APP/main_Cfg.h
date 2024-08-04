/*
 * main_Cfg.h
 *
 * Created: 1/28/2024 6:27:20 PM
 *  Author: ahmed
 */ 


#ifndef MAIN_CFG_H_
#define MAIN_CFG_H_

#define AIR_CONDTIONING_ON  (u8)0x01
#define AIR_CONDTIONING_OFF	(u8)0x00

#define LDR_LED_0        PINC0
#define LDR_LED_1        PINC1
#define LDR_LED_2        PINC2
#define LDR_LED_3        PINC3
#define LDR_LED_4        PINC4
#define LDR_LED_5        PINC5
#define LDR_LED_6        PINC6
#define LDR_LED_7        PINC7

#define LED_RED_PIN      PINA4
#define LED_GREEN_PIN    PINA5
#define LED_ORANGE_PIN   PINA6

#define ROOM1_LED_PIN    PIND2
#define ROOM2_LED_PIN    PIND3
#define ROOM3_LED_PIN    PIND4
#define ROOM4_LED_PIN    PIND5
#define TV_LED_PIN       PIND6
#define AIR_COND_LED_PIN PIND7

#define HYSTERESIS               6 //10 counts = 10*32ms = 320ms
#define TEMPERATURE_FIRE_DEGREE  60
//#define TEMPERATURE_HEAT_DEGREE  40
//#define TEMPERATURE_FINE_DEGREE  20

#define DEGREES_SYMBOL		   (u8)0xDF

#endif /* MAIN_CFG_H_ */