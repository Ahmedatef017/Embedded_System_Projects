/*
 * RTC_interface.h
 *
 *  Created on: Sep 30, 2023
 *      Author: ahmed
 */

#ifndef HAL_RTC_RTC_INTERFACE_H_
#define HAL_RTC_RTC_INTERFACE_H_

void RTC_Init(void);
void RTC_Set_Time(u8 sec, u8 min, u8 hour);
void RTC_Get_Time(u8 *sec, u8 *min, u8 *hour);
void RTC_Set_Date(u8 day, u8 mon, u8 year);
void RTC_Get_Date(u8 *day, u8 *mon, u8 *year);

#endif /* HAL_RTC_RTC_INTERFACE_H_ */
