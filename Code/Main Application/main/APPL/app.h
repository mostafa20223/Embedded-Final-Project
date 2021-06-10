#ifndef APP_H
#define APP_H

#define F_CPU 16000000UL /* 16 MHz Clock Speed */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../standard/Basic_Types.h"
#include "../standard/std_macros.h"
#include "../HAL/LCD.h"
#include "../HAL/Keypad.h"
#include "../MCAL/SPI.h"
#include "../MCAL/ADC.h"
#include "../MCAL/pwm.h"
#include "../schedular/Scheduler.h"
#include "../MCAL/ADC.h"

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
	Function Name        : StartApp
	Function Returns     : void
	Function Arguments   : void
	Function Description : Get entered value by user using keypad (Buttons)
*/
void StartApp(void);

/*
	Function Name        : UsrGetVal
	Function Returns     : u8
	Function Arguments   : void
	Function Description : Get entered value by user using keypad (Buttons)
*/
void UsrGetVal(void);

/*
	Function Name        : tc72_read
	Function Returns     : c8
	Function Arguments   : void
	Function Description : Start SPI communication with TC72 (Temperature Sensor)
*/
c8 tc72_read(void);

/*
	Function Name        : SET_Temp
	Function Returns     : void
	Function Arguments   : void
	Function Description : Start SPI communication with TC72 (Temperature Sensor)
*/
void SET_Temp(void);

/*
	Function Name        : CRT_Temp
	Function Returns     : void
	Function Arguments   : void
	Function Description : Start SPI communication with TC72 (Temperature Sensor)
*/
void CRT_Temp(void);

/*
	Function Name        : getCurrentTemp
	Function Returns     : void
	Function Arguments   : void
	Function Description : Get temperature from TC72 temperature sensor
*/
u16 getCurrentTemp(void);

/*
	Function Name        : getSetTemp
	Function Returns     : void
	Function Arguments   : void
	Function Description : Get temperature entered by the user using keypad
*/
u16 getSetTemp(void);

/*
	Function Name        : getSetTemp
	Function Returns     : void
	Function Arguments   : void
	Function Description : Get temperature entered by the user using keypad
*/
float64_t GetVt(void);

/*
	Function Name        : getADCVal
	Function Returns     : float64_t
	Function Arguments   : void
	Function Description : Start SPI communication with TC72 (Temperature Sensor)
*/
float64_t getADCVal(void);

/*
	Function Name        : getSetTemp
	Function Returns     : void
	Function Arguments   : void
	Function Description : Get temperature entered by the user using keypad
*/
void drivePWM(void);

#endif /* APP_H */