/*
 * MOTOR_interface.h
 *
 *  Created on: Jan 14, 2024
 *      Author: ahmed
 */

#ifndef HAL_DC_MOTOR_MOTOR_INTERFACE_H_
#define HAL_DC_MOTOR_MOTOR_INTERFACE_H_

typedef enum{
	Motor_1=0,
	Motor_2,
	Motor_3,
	Motor_4,
	MAX_MOTOR_NUM
	}MOTOR_type;

void H_MOTOR_voidInit(void);
void H_MOTOR_voidCW(MOTOR_type);
void H_MOTOR_voidCCW(MOTOR_type);
void H_MOTOR_voidStop(MOTOR_type);

#endif /* HAL_DC_MOTOR_MOTOR_INTERFACE_H_ */
