/*
 * menu.h
 *
 * Created: 1/29/2024 11:11:42 AM
 *  Author: ahmed
 */ 


#ifndef MENU_H_
#define MENU_H_

#define RED_LED_PIN     PINB3
#define GREEN_LED_PIN   PINA1
#define ADMIN_LED_PIN   PIND4
#define GUEST_LED_PIN   PINA0
#define BLOCK_LED_PIN   PINB7

/*
	Function Name        : ui8ComparePass
	Function Returns     : u8
	Function Arguments   : const u8* pass1,const u8* pass2,const u8 size
	Function Description : Compare two arrays of bytes and return True in case they are identical and return false in case they are different .
*/
u8 ui8ComparePass(const u8* pass1,const u8* pass2,const u8 size);

/*
	Function Name        : vMenuOption
	Function Returns     : void
	Function Arguments   : const u8 u8SelectedRoom,const u8 u8LoginMode
	Function Description : Show the sub menus of room 1 ,room 2 ,room 3,room 4 , tv
*/
void vMenuOption(const u8 u8SelectedRoom,const u8 u8LoginMode);

/*
	Function Name        : u8GetKeyPressed
	Function Returns     : u8
	Function Arguments   : const u8 u8LoginMode
	Function Description : Wait the user to press key then return the key pressed or return (NO_PRESSED_KEY = 0xFF) in case of timeout.
*/
u8 u8GetKeyPressed(const u8 u8LoginMode);



#endif /* MENU_H_ */