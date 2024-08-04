/*
 * SENSORS_interface.h
 *
 *  Created on: Sep 16, 2023
 *      Author: ahmed
 */

#ifndef SENSORS_SENSORS_INTERFACE_H_
#define SENSORS_SENSORS_INTERFACE_H_

void H_SENSORS_voidInit(void);
u16  H_LM35_GetTemp(void);
u8   POT_GetPerc(void);
u16  LDR_GetVolt(void);

#endif /* SENSORS_SENSORS_INTERFACE_H_ */
