#ifndef APP_H
#define APP_H

#define F_CPU 16000000UL /* 16 MHz Clock Speed */

#include <avr/io.h>
#include <util/delay.h>

#include "Basic_Types.h"
#include "DIO.h"
#include "LCD_config.h"
#include "LCD.h"
#include "Keypad.h"
#include "SPI.h"
#include "Timer.h"

/*
	Function Name        : Init
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize essential functions in our application
*/
void Init(void);

/*
	Function Name        : Welcome_Screen
	Function Returns     : void
	Function Arguments   : void
	Function Description : Show "WELCOME" on LCD screen
*/
void Welcome_Screen(void);

/*
	Function Name        : IDLE_Screen
	Function Returns     : void
	Function Arguments   : void
	Function Description : Show IDLE Screen at the beginning of our application
*/
void IDLE_Screen(void);

/*
	Function Name        : UsrGetVal
	Function Returns     : u8
	Function Arguments   : void
	Function Description : Get entered value by user using keypad (Buttons)
*/
u8 UsrGetVal(void);

/*
	Function Name        : Start_Communication
	Function Returns     : c8
	Function Arguments   : void
	Function Description : Start SPI communication with TC72 (Temperature Sensor)
*/
void Start_Communication(void);

#endif /* APP_H */