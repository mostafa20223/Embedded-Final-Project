#ifndef APP_H
#define APP_H

#define F_CPU 16000000UL /* 16 MHz Clock Speed */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/******************************* Included Libraries ***********************************/
#include "../standard/Basic_Types.h"
#include "../standard/std_macros.h"
#include "../HAL/LCD.h"
#include "../HAL/Keypad.h"
#include "../MCAL/SPI.h"
#include "../MCAL/ADC.h"
#include "../MCAL/pwm.h"
#include "../schedular/Scheduler.h"
#include "../MCAL/ADC.h"

/********************************************************************
	Function Name        : Init
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize all functions for our app
*********************************************************************/
void Init(void);

/********************************************************************
	Function Name        : Welcome_Screen
	Function Returns     : void
	Function Arguments   : void
	Function Description : Display moving "WELCOME" on LCD screen
********************************************************************/
void Welcome_Screen(void);

/********************************************************************
	Function Name        : IDLE_Screen
	Function Returns     : void
	Function Arguments   : void
	Function Description : Display IDLE Screen at first
********************************************************************/
void IDLE_Screen(void);

/********************************************************************
	Function Name        : UsrGetVal
	Function Returns     : u8
	Function Arguments   : void
	Function Description : Get entered value by user using keypad
********************************************************************/
void UsrGetVal(void);

/********************************************************************
	Function Name        : tc72_read
	Function Returns     : c8
	Function Arguments   : void
	Function Description : Start SPI communication with TC72 (Temperature Sensor)
********************************************************************/
c8 tc72_read(void); /* We have a problem with this function */

/********************************************************************
	Function Name        : CRT_Temp
	Function Returns     : void
	Function Arguments   : void
	Function Description : Get Current Temperature from TC72
********************************************************************/
void CRT_Temp(void);

/********************************************************************
	Function Name        : getCurrentTemp
	Function Returns     : u16
	Function Arguments   : void
	Function Description : Retrieve current temperature value
********************************************************************/
u16 getCurrentTemp(void);

/********************************************************************
	Function Name        : getSetTemp
	Function Returns     : u16
	Function Arguments   : void
	Function Description : Retrieve set temperature by user
********************************************************************/
u16 getSetTemp(void);

/********************************************************************
	Function Name        : GetVt
	Function Returns     : float64_t
	Function Arguments   : void
	Function Description : Get Vt (Volt from temperature difference)
********************************************************************/
float64_t GetVt(void);

/********************************************************************
	Function Name        : getADCVal
	Function Returns     : float64_t
	Function Arguments   : void
	Function Description : Get Vr (Volt from calibration resistor)
********************************************************************/
float64_t getADCVal(void);

/********************************************************************
	Function Name        : drivePWM
	Function Returns     : void
	Function Arguments   : void
	Function Description : Drive PWM pulses
********************************************************************/
void drivePWM(void);

#endif /* APP_H */