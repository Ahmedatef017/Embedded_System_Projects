/*
 * CAR.h
 *
 *  Created on: Jan 31, 2024
 *      Author: ahmed
 */

#ifndef CAR_CAR_H_
#define CAR_CAR_H_

typedef enum{
	NO_SPEED=0,
	LOW_SPEED=15,
	HALF_SPEED=50,
	HIGH_SPEED=80,
	MAX_SPEED=100
	}Speed_t;

void CAR_voidInit(void);
void CAR_vMoveForward(void);
void CAR_vMoveBackward(void);
void CAR_vMoveLeft(void);
void CAR_vMoveRight(void);
void CAR_voidStop(void);
void CAR_voidTurnRight90(void);
void CAR_voidTurnLeft90(void);
void CAR_Reverse(void);
void CAR_Speed(Speed_t speed);

#endif /* CAR_CAR_H_ */
