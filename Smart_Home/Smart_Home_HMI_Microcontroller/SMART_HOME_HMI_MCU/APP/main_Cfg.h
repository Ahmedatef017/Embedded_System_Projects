/*
 * main_Cfg.h
 *
 * Created: 1/25/2024 12:30:43 AM
 *  Author: ahmed
 */ 


#ifndef MAIN_CFG_H_
#define MAIN_CFG_H_

#define NOT_STORED   0xFF
#define NOT_SELECTED 0xFF

#define BLOCK_MODE_TIME		   (u32)20000
#define CHARACTER_PREVIEW_TIME (u16)200
#define DEGREES_SYMBOL		   (u8)0xDF

/*********************************** PIN Configuration ***********************************/
#define PASS_SIZE       (u8)4
#define TRIES_ALLOWED   (u8)3
#define PASSWORD_SYMBOL (u8)'*'
#define ASCII_ZERO      (u8)'0'

#define PASS_NOT_SET (u8)0xFF
#define PASS_SET     (u8)0x01

#define EEPROM_PASS_STATUS_ADDRESS (u16)0X60
#define EEPROM_ADMIN_ADDRESS       (u16)0X70
#define EEPROM_GUEST_ADDRESS       (u16)0X80
#define LOGIN_BLOCKED_ADDRESS      (u16)0X90
/*****************************************************************************************/

/************************************   Login configurations *****************************/
#define NO_MODE (u8)0
#define ADMIN   (u8)1
#define GUEST   (u8)2
/*****************************************************************************************/

/************************************   Logic values *************************************/
#define FALSE   (u8)0
#define TRUE    (u8)1
/*****************************************************************************************/

#define CHECK_ADMIN_MODE        (u8)'0'
#define CHECK_GUEST_MODE        (u8)'1'

#define SELECT_ROOM1            (u8)'1'
#define SELECT_ROOM2            (u8)'2'
#define SELECT_ROOM3            (u8)'3'
#define SELECT_ROOM4            (u8)'4'
#define ADMIN_MORE_OPTION       (u8)'4'

#define SELECT_ROOM4_ADMIN      (u8)'1'
#define SELECT_TV               (u8)'2'
#define SELECT_AIR_CONDITIONING (u8)'3'
#define ADMIN_RET_OPTION        (u8)'4'

#define SELECT_SET_TEMPERATURE  (u8)'1'
#define SELECT_AIR_COND_CTRL    (u8)'2'
#define SELECT_AIR_COND_RET     (u8)'0'

/****************************   number of ticks to run timeout ***************************/
#define ADMIN_TIMEOUT (u16)1800
#define GUEST_TIMEOUT (u16)900
/*****************************************************************************************/

/****************************   Show menu codes  *****************************************/
#define MAIN_MENU            (u8)1
#define MORE_MENU            (u8)2
#define ROOM1_MENU           (u8)3
#define ROOM2_MENU           (u8)4
#define ROOM3_MENU           (u8)5
#define ROOM4_MENU           (u8)6
#define TV_MENU              (u8)7
#define AIRCONDITIONING_MENU (u8)8
#define AIRCOND_CTRL_MENU    (u8)9
#define TEMPERATURE_MENU     (u8)10
/*****************************************************************************************/


#endif /* MAIN_CFG_H_ */