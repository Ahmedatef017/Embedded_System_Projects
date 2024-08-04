
/*-------------------------------------------- Includes ------------------------------------------------*/
#define  F_CPU  8000000  //define cpu clock for delay function
#include <util/delay.h>  //contain delay function _delay_ms()
#include "../LIB/StdTypes.h"
#include "../LIB/BitMath.h"
#include "../LIB/Std_Uart_Messages.h"
/*---------------------------------------------- MCAL --------------------------------------------------*/
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/TIMER_0/TIMER0_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/EXT_INTERRUPT/EXTI_interface.h"
/*----------------------------------------------- HAL---------------------------------------------------*/
#include "../HAL/LED/LED_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/SSD/SSD_interface.h"
#include "../HAL/EEPROM/EEPROM_interface.h"
#include "../HAL/KEYPAD/KEYPAD_interface.h"
#include "../HAL/BUZZER/BUZZER_interface.h"
/*--------------------------------------------- SERVICES -----------------------------------------------*/
#include "../SERVICES/UART_SERVICES/UartServices.h"
/*----------------------------------------------- APP --------------------------------------------------*/
#include "main_cfg.h"
#include "menu.h"

/*------------------------------------------------------------------------------------------------------*/
extern volatile u16 session_counter;//indicate session time
u8 timeout_flag = FALSE;//stores if the session is still valid or outdated
u8 login_counter=20;
u8 response=DEFAULT_ACK;
/*------------------------------------------------------------------------------------------------------*/
void Reset_voidFunc(void);
int main(void)
{
	u8 temperature = 0;//The average temperature of the room
	u8 temp_ones = NOT_SELECTED;//The entered right number of the temperature
	u8 temp_tens = NOT_SELECTED;//The entered left number of the temperature
	
	u8 login_mode = NO_MODE; //Store the current user mode admin or guest or not logged in
	u8 block_mode_flag = FALSE;//is true if the login is blocked or false if not blocked
	u8 key_pressed = NO_PRESSED_KEY;//
	/*****************  INITIALIZE  ***********************/
	H_LED_voidInit(ADMIN_LED_PIN);//initializes the led of admin
	H_LED_voidInit(GUEST_LED_PIN);//initializes the led of guest
	H_LED_voidInit(BLOCK_LED_PIN);//initializes the led of block
	H_SSD_voidInit();
	H_KEYPAD_voidInit();
	H_BUZZER_voidInit();
	H_LCD_voidInit();
	H_EEPROM_voidInit();
	M_UART_voidInit();
	M_EXT_voidInit(EX_INT0,RISING_EDGE);
	M_EXTI_voidSetCallBack(EX_INT0,Reset_voidFunc);
	M_EXTI_voidEXTIEnable(EX_INT0);
	M_Timer0_Init();
	M_TIMER0_EnableInt(TIMER0_OVF_INTERRUPT);
	M_Timer0_start();
	M_Global_Interrupt_Enable();
    S_UART_void_ReceiveCharAsynch(&response);//the sender micro controller asks for the status
	/******************************************************/
	/* Printing Welcome screen */
	H_LCD_voidSendString("Welcome to smart");
	H_LCD_voidSetPosition(2,1);
	H_LCD_voidSendString("home system");
	_delay_ms(1000);//Halt the system for the given time in (ms)
	H_LCD_voidClearDisplay();
	H_LCD_voidSendString("by:");
	H_LCD_voidSetPosition(2,4);
	H_LCD_voidSendString("Ahmed Atef");
	_delay_ms(1000);//Halt the system for the given time in (ms)
	H_LCD_voidClearDisplay();
	/***************************/
	/*Setting Admin and Guest passwords if not set */
	//read the state of the the passwords of the admin and guest if both are set or not set
	u8 pass_status_location;

	H_EEPROM_u8Read_Byte(EEPROM_PASS_STATUS_ADDRESS, &pass_status_location);
	_delay_ms(10);//delay until the cpu get reading from the eeprom throught the i2c protocol
	if ( (pass_status_location==PASS_NOT_SET) )
	{
		H_LCD_voidSendString("Login for");//printing login menu
		H_LCD_voidSetPosition(2,1);//move the cursor to the second line
		H_LCD_voidSendString("first time");
		_delay_ms(1000);//Halt the system for the given time in (ms)
		H_LCD_voidClearDisplay();
		H_LCD_voidSendString("Set Admin pass");//printing the set admin password menu
		H_LCD_voidSetPosition(2,1);
		H_LCD_voidSendString("Admin pass:");

		/********************************* setting Admin password **********************************************/
		u8 pass_counter=0;//the counter of the characters of the password
		u8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};//the array where it stored the password
		while (pass_counter<PASS_SIZE)//loop till the user finish inserting the pass
		{
			key_pressed = NO_PRESSED_KEY;//return the variable that holds the pressed key from keypad to its initial value
			while (key_pressed == NO_PRESSED_KEY)//repeat till the user press any key
			{
				key_pressed = H_KEYPAD_u8_getPressedKey();//if the user pressed any button in keypad save the value in key_pressed
			}		
			H_BUZZER_voidTurnOn();
			_delay_ms(40);
			H_BUZZER_voidTurnOff();
			pass[pass_counter]=key_pressed;//add the entered character to the pass array
			H_LCD_voidSendChar(key_pressed);//print the entered character
			_delay_ms(CHARACTER_PREVIEW_TIME);//Halt the system for the given time in (ms)
			H_LCD_voidSetPosition(2,12+pass_counter);//move the lcd cursor to the previous location to write the password symbol over the character
			H_LCD_voidSendChar(PASSWORD_SYMBOL); // to display (Password sign *)
			_delay_ms(100);//Halt the system for the given time in (ms)
			H_EEPROM_u8Write_Byte(EEPROM_ADMIN_ADDRESS+pass_counter,key_pressed);
			_delay_ms(10);
			pass_counter++;//increase the characters count
		}

		H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		H_LCD_voidSendString("Pass Saved");// show pass saved message
		_delay_ms(500);//Halt the system for the given time in (ms)
		H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row

		/********************************* setting guest password **********************************************/
		pass_counter=0;//reset password counter which count the characters of the pass
		H_LCD_voidSendString("Set Guest Pass");//printing the set admin password menu
		H_LCD_voidSetPosition(2,1);
		H_LCD_voidSendString("Guest Pass:");
		while (pass_counter<PASS_SIZE)//loop till the user finish inserting the pass
		{
			key_pressed = NO_PRESSED_KEY;//return the variable that holds the pressed key from keypad to its initial value
			while (key_pressed == NO_PRESSED_KEY)//repeat till the user press any key
			{
				key_pressed = H_KEYPAD_u8_getPressedKey();//if the user pressed any button in keypad save the value in key_pressed
			}
			H_BUZZER_voidTurnOn();
			_delay_ms(40);
			H_BUZZER_voidTurnOff();
			pass[pass_counter]=key_pressed;//add the entered character to the pass array
			H_LCD_voidSendChar(key_pressed);//print the entered character
			_delay_ms(CHARACTER_PREVIEW_TIME);//Halt the system for the given time in (ms)
			H_LCD_voidSetPosition(2,12+pass_counter);//move the lcd cursor to the previous location to write the password symbol over the character
			H_LCD_voidSendChar(PASSWORD_SYMBOL); // to display (Password sign *)
			_delay_ms(100);//Halt the system for the given time in (ms)
			H_EEPROM_u8Write_Byte(EEPROM_GUEST_ADDRESS+pass_counter,key_pressed);//save the entire password as a block to the EEPROM
			_delay_ms(10);
			pass_counter++;//increase the characters count
		}	
		H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		H_LCD_voidSendString("Pass Saved");//move the lcd cursor to the previous location
		_delay_ms(500);//Halt the system for the given time in (ms)
		H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		H_EEPROM_u8Write_Byte(EEPROM_PASS_STATUS_ADDRESS,PASS_SET);//write the status of pass as it is set
		_delay_ms(10);
		H_EEPROM_u8Write_Byte(LOGIN_BLOCKED_ADDRESS,FALSE);
		_delay_ms(10);
	}//The end of if admin and guest password is set
	else//this code of else run only if the system is not running for the first time (ADMIN and GUEST passwords are set)
	{
		H_EEPROM_u8Read_Byte(LOGIN_BLOCKED_ADDRESS,&block_mode_flag); //read the blocked location from EEPROM
		_delay_ms(10);
	}
	while (1)//The start of the periodic code
	{
		key_pressed = NO_PRESSED_KEY;//return the variable that holds the pressed key from keypad to its initial value
		u8 pass_tries_count=0;//stores how many times the user tried to log in to the system and failed
		
		if ( timeout_flag==TRUE )//check for timeout
		{//if timeout flag was raised
			M_Timer0_stop();//stop the timer that increase the session counter
			session_counter = 0;//clear session counter
			timeout_flag=FALSE;//clear time out flag
			login_mode=NO_MODE;//log the user out
			key_pressed = NO_PRESSED_KEY;//clear the key_pressed to avoid unwanted selection in the menu switch
			H_LED_voidTurnOff(GUEST_LED_PIN);//turnoff the led of the guest
			H_LED_voidTurnOff(ADMIN_LED_PIN);//turnoff the led of the admin
			H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
			H_LCD_voidSendString("Session Timeout");//print session timeout message
			H_BUZZER_voidTurnOn();
			_delay_ms(1000);//Halt the system for the given time in (ms)
			H_BUZZER_voidTurnOff();
			
		}
		while (login_mode==NO_MODE)//The user can only leave the loop only in case of he was logged in as guest or admin
		{
			if(block_mode_flag==TRUE)//if the login process was blocked wait till the end of the block period
			{
				login_counter=20;
				H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
				H_LCD_voidSendString("Login blocked");
				H_LCD_voidSetPosition(2,1);
				H_LCD_voidSendString("wait 20 seconds");
				H_LED_voidTurnOn(BLOCK_LED_PIN);//Turn on the led of Blocked
				for(s8 i=20;i>=0;i--){
					H_BUZZER_voidTurnOn();
					_delay_ms(50);
					H_BUZZER_voidTurnOff();
					H_SSD_voidDisplayNumForAtime(login_counter,1000);//Halt the system for the given time in (ms)
					if(i==0)
					{
						H_BUZZER_voidTurnOn();
						_delay_ms(1000);
						H_BUZZER_voidTurnOff();
					}
					login_counter--;

				}

				login_counter=0;
				//_delay_ms(BLOCK_MODE_TIME);//Halt the system for the given time in (ms)
				pass_tries_count = 0; //Clear the count on number of wrong tries
				block_mode_flag = FALSE;//Disable block of runtime
				H_LED_voidTurnOff(BLOCK_LED_PIN);//Turn off the led of Blocked
				H_EEPROM_u8Write_Byte(LOGIN_BLOCKED_ADDRESS,FALSE);//write false at blocked location in EEPROM
			}
			H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
			H_LCD_voidSendString("Select mode :");
			H_LCD_voidSetPosition(2,1);
			H_LCD_voidSendString("0:Admin 1:Guest");
			while(key_pressed==NO_PRESSED_KEY)//wait for the selection of the mode
			{
				key_pressed = H_KEYPAD_u8_getPressedKey();//if the user pressed any button in keypad save the value in key_pressed
			}
			H_BUZZER_voidTurnOn();
			_delay_ms(40);
			H_BUZZER_voidTurnOff();
			if ( key_pressed!=CHECK_ADMIN_MODE && key_pressed!=CHECK_GUEST_MODE )
			{
				H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
				H_LCD_voidSendString("Wrong input.");//Prints error message on the LCD
				key_pressed = NO_PRESSED_KEY;//return the variable that holds the pressed key from keypad to its initial value
				_delay_ms(1000);//Halt the system for the given time in (ms)
				continue;//return to the loop of login #while (login_mode==NO_MODE)# line 128
			}

			u8 pass_counter=0;//counts the entered key of the password from the keypad
			u8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};//temporarily hold the entire password that will be entered by the user to be check
			u8 stored_pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};//temporarily hold the entire stored password that is written by the user for the first time
			
			switch(key_pressed)
			{
				/********************************* Admin login **********************************************/
				case CHECK_ADMIN_MODE:
				while(login_mode!=ADMIN)//this loop is to repeat the login for admin in case of wrong password
				{
					key_pressed = NO_PRESSED_KEY;//return the variable that holds the pressed key from keypad to its initial value
					H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					H_LCD_voidSendString("Admin mode");
					H_LCD_voidSetPosition(2,1);
					H_LCD_voidSendString("Enter Pass:");
					_delay_ms(200);//Halt the system for the given time in (ms)
					pass_counter=0;//counts the number of entered characters
					while(pass_counter<PASS_SIZE)
					{
						while (key_pressed == NO_PRESSED_KEY)//repeat till the user press any key
						{
							key_pressed = H_KEYPAD_u8_getPressedKey();//if the user pressed any button in keypad save the value in key_pressed
						}
						H_BUZZER_voidTurnOn();
						_delay_ms(40);
						H_BUZZER_voidTurnOff();
						pass[pass_counter]=key_pressed;//add the entered character to the pass array
						H_LCD_voidSendChar(key_pressed);//print the entered character
						_delay_ms(CHARACTER_PREVIEW_TIME);//Halt the system for the given time in (ms)
						H_LCD_voidSetPosition(2,12+pass_counter);//move the cursor of the lcd screen to the previous location
						H_LCD_voidSendChar(PASSWORD_SYMBOL);// to display (Password sign *)
						_delay_ms(100);//Halt the system for the given time in (ms)
						H_EEPROM_u8Read_Byte(EEPROM_ADMIN_ADDRESS+pass_counter,&stored_pass[pass_counter]);//Save the entire password in the EEPROM
						_delay_ms(10);
						pass_counter++;//increase the password counter that count the characters of the pass
						key_pressed = NO_PRESSED_KEY;//return the variable that holds the pressed key from keypad to its initial value
						
					}
					
					/*compare passwords*/
					if ((ui8ComparePass(pass,stored_pass,PASS_SIZE)) == TRUE)//in case of right password
					{
						M_UART_voidSend(RESET_FIRE_ALARM);
						login_mode = ADMIN;//set the login mode to admin mode
						pass_tries_count=0;//clear the counter of wrong tries
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						H_LCD_voidSendString("Right pass");
						H_LCD_voidSetPosition(2,1);
						H_LCD_voidSendString("Admin mode");
						_delay_ms(500);//Halt the system for the given time in (ms)
						H_LED_voidTurnOn(ADMIN_LED_PIN);//turn on the led of admin
						M_Timer0_start();//start the timer that counts the session time
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					}
					else//in case of wrong password
					{
						pass_tries_count++;//increase the number of wrong tries to block login if it exceeds the allowed tries
						login_mode = NO_MODE;//set the mode as not logged in
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						H_LCD_voidSendString("Wrong Pass");
						H_LCD_voidSetPosition(2,1);
						H_LCD_voidSendString("Tries left:");
						H_LCD_voidSendChar(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);//print the number of tries left before block mode to be activated
						_delay_ms(1000);//Halt the system for the given time in (ms)
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						if (pass_tries_count>=TRIES_ALLOWED)//if the condition of the block mode is true
						{
							H_EEPROM_u8Write_Byte(LOGIN_BLOCKED_ADDRESS,TRUE);//write to the EEPROM TRUE to the the block mode address
							_delay_ms(10);
							block_mode_flag = TRUE;//turn on block mode
							break;//break the loop of admin login #while(login_mode!=ADMIN)# at line 169
						}
					}
				}
				break;//bREAK SWITCH case
				/********************************* Guest login **********************************************/
				case  CHECK_GUEST_MODE:
				while(login_mode != GUEST)
				{
					key_pressed = NO_PRESSED_KEY;//return the variable that holds the pressed key from keypad to its initial value
					H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					H_LCD_voidSendString("Guest mode");
					H_LCD_voidSetPosition(2,1);
					H_LCD_voidSendString("Enter pass:");
					_delay_ms(200);//Halt the system for the given time in (ms)
					pass_counter=0;//counts the number of entered characters
					while(pass_counter<PASS_SIZE)
					{
						while (key_pressed == NO_PRESSED_KEY)//repeat till the user press any key
						{
							key_pressed = H_KEYPAD_u8_getPressedKey();//if the user pressed any button in keypad save the value in key_pressed
						}
						H_BUZZER_voidTurnOn();
						_delay_ms(40);
						H_BUZZER_voidTurnOff();
						pass[pass_counter]=key_pressed;//add the pressed key to the password string
						H_LCD_voidSendChar(key_pressed);//print the entered character
						_delay_ms(CHARACTER_PREVIEW_TIME);//Halt the system for the given time in (ms)
						H_LCD_voidSetPosition(2,12+pass_counter);//return the cursor to the location of the previous character to replace it with the password sign
						H_LCD_voidSendChar(PASSWORD_SYMBOL); // to display (Password sign *)
						_delay_ms(100);//Halt the system for the given time in (ms)
						H_EEPROM_u8Read_Byte(EEPROM_GUEST_ADDRESS+pass_counter,&stored_pass[pass_counter]);
						_delay_ms(10);
						pass_counter++;//increase the password counter that count the characters of the pass
						key_pressed = NO_PRESSED_KEY;//return the variable that holds the pressed key from keypad to its initial value
					}
					

					/*compare passwords*/
					if (ui8ComparePass(pass,stored_pass,PASS_SIZE)==TRUE)//in case of right password
					{
						login_mode = GUEST;
						pass_tries_count=0;//clear the counter of wrong tries
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						H_LCD_voidSendString("Right pass");
						H_LCD_voidSetPosition(2,1);
						H_LCD_voidSendString("Guest mode");
						_delay_ms(500);//Halt the system for the given time in (ms)
						H_LED_voidTurnOn(GUEST_LED_PIN);//turn the led of gust mode that is connected to the sender micro controller on
						M_Timer0_start();//start the counter of the session
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					}
					else//in case of wrong password
					{
						pass_tries_count++;//increase the number of wrong tries to block login if it exceeds the allowed tries
						login_mode = NO_MODE;//set the mode as not logged in
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						H_LCD_voidSendString("Wrong pass");
						H_LCD_voidSetPosition(2,1);
						H_LCD_voidSendString("Tries left:");
						H_LCD_voidSendChar(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);//print the number of tries left before block mode to be activated
						_delay_ms(1000);//Halt the system for the given time in (ms)
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						if (pass_tries_count>=TRIES_ALLOWED)//if the condition of the block mode is true
						{
							H_EEPROM_u8Write_Byte(LOGIN_BLOCKED_ADDRESS,TRUE);//write to the EEPROM TRUE to the the block mode address
							_delay_ms(10);
							block_mode_flag = TRUE;//turn on block mode
							break;//breaks the loop of insert guest password #while(login_mode != GUEST)# line 228
						}//end of if that check if the number of tries exceeds the maximum tries allowed
					}//end of the case of wrong password
				}//end of loop of guest login
				break;//break for CHECK_GUEST_MODE switch case
			}//end of switch
			
		}
		
		/*************************************************************************************************/
		u8 show_menu = MAIN_MENU;
		
		
		while(timeout_flag!=TRUE)//Show the menu in case of the time is not out
		{
			key_pressed = NO_PRESSED_KEY;//Set the key pressed by the user to its default value
			switch (show_menu)
			{
				case MAIN_MENU:
				do
				{
					/******************** print main Menu ******************/
					H_LCD_voidClearDisplay();
					H_LCD_voidSendString("1:Room1 2:Room2");
					H_LCD_voidSetPosition(2,1);
					if(login_mode==ADMIN)//check login mode
					{
						H_LCD_voidSendString("3:Room3 4:More ");//this menu options only printed if the logged in user is an admin
					}
					else if(login_mode==GUEST)//check login mode
					{
						H_LCD_voidSendString("3:Room3 4:Room4");//this menu options only printed if the logged in user is a guest
					}
					/*******************************************************/
					
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(100);//to avoid the duplication of the pressed key
					
					if (key_pressed == SELECT_ROOM1)//If key pressed is 1
					{
						show_menu = ROOM1_MENU;//Set the next menu to be shown to room1 menu
					}
					else if (key_pressed == SELECT_ROOM2)//If key pressed is 2
					{
						show_menu = ROOM2_MENU;//Set the next menu to be shown to room2 menu
					}
					else if (key_pressed == SELECT_ROOM3)//If key pressed is 3
					{
						show_menu = ROOM3_MENU;//Set the next menu to be shown to room3 menu
					}
					else if (key_pressed == SELECT_ROOM4 && login_mode == GUEST)//If key pressed is 4 and the logged in user is guest
					{
						show_menu = ROOM4_MENU;//Set the next menu to be shown to room4 menu
					}
					else if (key_pressed == ADMIN_MORE_OPTION && login_mode == ADMIN)//If key pressed is 4 and the logged in user is admin
					{
						show_menu = MORE_MENU;//Set the next menu to be shown to more menu
					}
					else if(key_pressed != NO_PRESSED_KEY)//show wrong input message if the user pressed wrong key
					{
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						H_LCD_voidSendString("Wrong input");//print error message
						_delay_ms(500);//Halt the system for the given time in (ms)
					}
				} while ( ((key_pressed < '1') || (key_pressed > '4') ) && (timeout_flag == FALSE) );//break the loop in case of valid key or time is out
				
				break;//End of main menu case
				
				case MORE_MENU:
				do
				{
					/******************** print more Menu ******************/
					H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					H_LCD_voidSendString("1:Room4    2:TV   ");
					H_LCD_voidSetPosition(2,1);
					H_LCD_voidSendString("3:Air Cond.4:RET");
					/*******************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(100);//to avoid the duplication of the pressed key
					
					if (key_pressed == SELECT_ROOM4_ADMIN)//If key pressed is 1
					{
						show_menu = ROOM4_MENU;//Set the next menu to be shown to room4 menu
					}
					else if (key_pressed == SELECT_TV)//If key pressed is 2
					{
						show_menu = TV_MENU;//Set the next menu to be shown to TV menu
					}
					else if (key_pressed == SELECT_AIR_CONDITIONING)//If key pressed is 3
					{
						show_menu = AIRCONDITIONING_MENU;//Set the next menu to be shown to Air conditioning menu
					}
					else if (key_pressed == ADMIN_RET_OPTION)//If key pressed is 4 (RET)
					{
						show_menu = MAIN_MENU;//Set the next menu to be shown to main menu
					}
					else if(key_pressed != NO_PRESSED_KEY)//show wrong input message if the user pressed wrong key
					{
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						H_LCD_voidSendString("Wrong input");//print error message
						_delay_ms(500);//Halt the system for the given time in (ms)
					}
				} while (( (key_pressed < '1') || (key_pressed > '4') ) && (timeout_flag == FALSE));//break the loop in case of valid key or time is out
				
				break;//End of more menu case
				
				case AIRCONDITIONING_MENU:
				do
				{
					/******************** print more Menu ******************/
					H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					H_LCD_voidSendString("1:Set temperature ");
					H_LCD_voidSetPosition(2,1);
					H_LCD_voidSendString("2:Control  0:RET");
					/*******************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(100);//to avoid the duplication of the pressed key
					
					if (key_pressed == SELECT_SET_TEMPERATURE)//If key pressed is 1
					{
						show_menu = TEMPERATURE_MENU;//Set the next menu to be shown to set temperature menu
					}
					else if (key_pressed == SELECT_AIR_COND_CTRL)//If key pressed is 2
					{
						show_menu = AIRCOND_CTRL_MENU;//Set the next menu to be shown to air conditioning control menu
					}
					else if (key_pressed == SELECT_AIR_COND_RET)//If key pressed is 0
					{
						show_menu = MORE_MENU;//Set the next menu to be shown to more menu
					}
					else if(key_pressed != NO_PRESSED_KEY)//show wrong input message if the user pressed wrong key
					{
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						H_LCD_voidSendString("Wrong input");//print error message
						_delay_ms(500);//Halt the system for the given time in (ms)
					}
				} while (( (key_pressed < '0') || (key_pressed > '2') ) && (timeout_flag == FALSE));//break the loop in case of valid key or time is out
				break;//End of air conditioning menu case
				
				case ROOM1_MENU:
				vMenuOption(ROOM1_MENU,login_mode);//call the function that show the menu of room 1
				show_menu = MAIN_MENU;//Set the next menu to be shown to main menu
				break;//End of room1 menu case
				
				case ROOM2_MENU:
				vMenuOption(ROOM2_MENU,login_mode);//call the function that show the menu of room 2
				show_menu = MAIN_MENU;//Set the next menu to be shown to main menu
				break;//End of room2 menu case
				
				case ROOM3_MENU:
				vMenuOption(ROOM3_MENU,login_mode);//call the function that show the menu of room 3
				show_menu = MAIN_MENU;//Set the next menu to be shown to main menu
				break;//End of room3 menu case
				
				case ROOM4_MENU:
				vMenuOption(ROOM4_MENU,login_mode);//call the function that show the menu of room 4
				if (login_mode == GUEST)//in case of guest is logged in
				{
					show_menu = MAIN_MENU;//Set the next menu to be shown to main menu
				}
				else//in case of admin is logged in
				{
					show_menu = MORE_MENU;//Set the next menu to be shown to more menu
				}
				break;//End of room4 menu case
				
				case TV_MENU:
				vMenuOption(TV_MENU,login_mode);//call the function that show the menu of tv
				show_menu = MORE_MENU;//Set the next menu to be shown to more menu
				break;//End of TV menu case
				
				case AIRCOND_CTRL_MENU:
				vMenuOption(AIRCOND_CTRL_MENU,login_mode);//call the function that show the menu of Air conditioning control
				show_menu = AIRCONDITIONING_MENU;//Set the next menu to be shown to air conditioning menu
				break;//End of air conditioning control menu case
				
				case TEMPERATURE_MENU:
				temperature = 0;//clear the value of temperature
				while (temperature==0 && timeout_flag == FALSE)//start the loop that asks for the temperature from the user in case of the time is not out
				{
					key_pressed = NO_PRESSED_KEY;//set the key pressed to the default value
					H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					H_LCD_voidSendString("Set temp.:__ ");//print the format of inserting temperature
					H_LCD_voidSendChar(DEGREES_SYMBOL); // print the symbol of degree
					H_LCD_voidSendChar('C'); // print the C character
					H_LCD_voidSetPosition(1,11);//move the cursor to the place to write the entered temperature
					_delay_ms(200);//Halt the system for the given time in (ms)
					/*******************************************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(250);//to avoid the duplication of the pressed key

					if (timeout_flag == TRUE) //in case of the time is out before the user press a key
					{
						break;//break the loop that ask for temperature
					}
					if (key_pressed <'0' || key_pressed >'9')//show wrong input message if the user entered non numeric value
					{
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						H_LCD_voidSendString("Wrong input");//print error message
						_delay_ms(500);//Halt the system for the given time in (ms)
						continue;//return to #while (temperature==0)# line 672
					}
					else//if the value is valid
					{
						H_LCD_voidSendChar(key_pressed);//print the value on the lcd
						temp_tens = key_pressed-ASCII_ZERO;//save the entered value
						key_pressed = NO_PRESSED_KEY;//set the key pressed to the default value
					}
					/*******************************************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(250);//to avoid the duplication of the pressed key
					
					if (timeout_flag == TRUE)//if the user session is timeout
					{
						break;//break the loop that ask for temperature
					}
					if ((key_pressed <'0' || key_pressed >'9'))//show wrong input message if the user entered non numeric value
					{
						H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						H_LCD_voidSendString("Wrong input");//print error message
						_delay_ms(500);//Halt the system for the given time in (ms)
						continue;//repeat the loop that ask for the temperature
					}
					else//if the value is valid
					{
						H_LCD_voidSendChar(key_pressed);//print the value on the lcd
						temp_ones = key_pressed-ASCII_ZERO;//save the entered value
						key_pressed = NO_PRESSED_KEY;//set the key pressed to the default value
					}
					temperature = temp_tens*10 + temp_ones;//set the value of the temperature from the given separated values
					//M_UART_voidSend(SET_TEMPERATURE);//Send the code of set temperature
					//_delay_ms(200);//Halt the system to prevent write collision
					M_UART_voidSend(temperature);//send the entered temperature
					H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					H_LCD_voidSendString("Temperature Sent");//show the message
					_delay_ms(500);//Halt the system for the given time in (ms)
				}
				show_menu = AIRCONDITIONING_MENU;//Set the next menu to be shown to air conditioning menu
				break;//break from switch
			}//End of the switch
		}//End of while that repeats the menu after each successful action till session timeout
	}// end of the main while(1)
}//end of main function




/**************************************************************************************************************************/

u8 ui8ComparePass(const u8* pass1,const u8* pass2,const u8 size)
{
	u8 pin_counter=0;//the offset of the character of the pin
	u8 ret_value = TRUE;
	while (pin_counter<size)//loop till the pin is fully entered
	{
		if (*(pass1+pin_counter)!=*(pass2+pin_counter))//if the two characters of the entered pin and the stored pin are not equal
		{
			ret_value= FALSE;//returns false that means the two PINs are not equal
			break;//break the loop
		}
		pin_counter++;//increase thee offset by one
	}
	return ret_value;//returns false that means the two PINs are equal since all characters of the PINs are equal
}

void vMenuOption(const u8 u8SelectedRoom,const u8 u8LoginMode)
{
	u8 u8StatusCode  = 0;//demand status code
	u8 u8TurnOnCode  = 0;//turn on the room or the device code
	u8 u8TurnOffCode = 0;//turn off the device or room
	response      = DEFAULT_ACK;//the response of the receiver that is sent back based on the command of the sender
	u8 key_pressed   = NO_PRESSED_KEY;//the key that is entered by the user
	
	do
	{
		H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		
		/*********** ****************Set the commands to be sent to the receiver based on  the sent room or device ******************************/
		switch(u8SelectedRoom)
		{
			case ROOM1_MENU:
			u8StatusCode = ROOM1_STATUS;
			u8TurnOnCode = ROOM1_TURN_ON;
			u8TurnOffCode = ROOM1_TURN_OFF;
			H_LCD_voidSendString("Room1 S:");
			break;
			case ROOM2_MENU:
			u8StatusCode = ROOM2_STATUS;
			u8TurnOnCode = ROOM2_TURN_ON;
			u8TurnOffCode = ROOM2_TURN_OFF;
			H_LCD_voidSendString("Room2 S:");
			break;
			case ROOM3_MENU:
			u8StatusCode = ROOM3_STATUS;
			u8TurnOnCode = ROOM3_TURN_ON;
			u8TurnOffCode = ROOM3_TURN_OFF;
			H_LCD_voidSendString("Room3 S:");
			break;
			case ROOM4_MENU:
			u8StatusCode = ROOM4_STATUS;
			u8TurnOnCode = ROOM4_TURN_ON;
			u8TurnOffCode = ROOM4_TURN_OFF;
			H_LCD_voidSendString("Room4 S:");
			break;
			case TV_MENU:
			u8StatusCode = TV_STATUS;
			u8TurnOnCode = TV_TURN_ON;
			u8TurnOffCode = TV_TURN_OFF;
			H_LCD_voidSendString("TV S:");
			break;
			case AIRCOND_CTRL_MENU:
			u8StatusCode = AIR_COND_STATUS;
			u8TurnOnCode = AIR_COND_TURN_ON;
			u8TurnOffCode = AIR_COND_TURN_OFF;
			H_LCD_voidSendString("Air Cond. S:");
			break;
		}
		/****************************************************************************************************/
		
		M_UART_voidSend(u8StatusCode);//demand the status from the receiver
		_delay_ms(200);//Halt the system for the given time in (ms)
	
		if(response == ON_STATUS)//if the response from the receiver was on status
		{
			H_LCD_voidSendString("ON");//print the status on
		}
		else//if the response from the receiver was off status
		{
			H_LCD_voidSendString("OFF");//print the status off
		}

		H_LCD_voidSetPosition(2,1);//move the cursor to the start of the second line
		H_LCD_voidSendString("1-On 2-Off 0-RET");//print the sub menu
		
		/*******************************************************************************/
		
		key_pressed = u8GetKeyPressed(u8LoginMode);//wait for the user till key is pressed or the time is out
		_delay_ms(100);//to avoid the duplication of the pressed key
		
		/*there is no need to take any action in case of the user pressed 0(RET) key
		breaking the loop will be enough since it will be handled in the main*/
		
		if (key_pressed == '1')
		{
			M_UART_voidSend(u8TurnOnCode);//Send turn on signal from sender to receiver
		}
		else if (key_pressed == '2')
		{
			M_UART_voidSend(u8TurnOffCode);//Send turn off signal from sender to receiver
		}
		else if( (key_pressed != NO_PRESSED_KEY) && (key_pressed != '0') )//show wrong input message if the user entered non numeric value
		{
			H_LCD_voidClearDisplay();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
			H_LCD_voidSendString("Wrong input");//print error message
			_delay_ms(500);//Halt the system for the given time in (ms)
		}
	} while ( ( (key_pressed < '0') || (key_pressed > '2') ) && (timeout_flag == FALSE));//break the loop in case of valid key or time is out
}

u8 u8GetKeyPressed(const u8 u8LoginMode)
{
	u8 key_pressed = NO_PRESSED_KEY;
	while (key_pressed == NO_PRESSED_KEY)//repeat till the user press any key
	{
		if(timeout_flag == TRUE)
		{
			break;
		}
		if ( (session_counter >= ADMIN_TIMEOUT && u8LoginMode == ADMIN) || ( session_counter >= GUEST_TIMEOUT && u8LoginMode == GUEST ))//check for timeout
		{
			timeout_flag = TRUE;//set timeout flag to true
			break;//break the loop that wait for input from the user
		}
		
		key_pressed = H_KEYPAD_u8_getPressedKey();//if the user pressed any button in keypad save the value in key_pressed
	}
	H_BUZZER_voidTurnOn();
	_delay_ms(40);
	H_BUZZER_voidTurnOff();
	return key_pressed;
}



void Reset_voidFunc(void)
{
	timeout_flag = TRUE;
}







