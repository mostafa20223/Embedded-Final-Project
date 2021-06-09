#include "Scheduler.h"
#include "Basic_Types.h"
#include "systemState.h"

#include <avr/interrupt.h>

static u16 ms_elapsed = 0;
static u8 minutes_elapsed = 0;
static u16 minute_counter = 0;

// This is not used but it is here in case we need it
typedef void (*fun_ptr)(int);

// ______________________

// FLAGS
static char countMinutes = 0;
static char checkTemp = 0;
static char voltModule = 0;
static char overHeating = 0;

// FLAG setter
void setCountMinutes() { countMinutes = 1; }
void setCheckTemp() { checkTemp = 1; }
void setVoltModule() { voltModule = 1; }
void setOverHeating() { overHeating = 1; }

// FLAG clear
void clearCountMinutes()
{
	countMinutes = 0;
	minute_counter = 0;
	minutes_elapsed = 0;
}
void clearCheckTemp() { checkTemp = 0; }
void clearVoltModule() { voltModule = 0; }
void clearOverHeating() { overHeating = 0; }

// ______________________

// Functions called during timer interrupt

// TODO delete this
void TURN_point1()
{
	//*((u8 *)(0x3B)) = ~(*((u8 *)(0x3B)));
	*((u8 *)(0x3B)) = 0xFF;
}

// TODO delete this
void TURN_point2()
{
	//*((u8 *)(0x3B)) = ~(*((u8 *)(0x3B)));
	*((u8 *)(0x3B)) = 0x00;
}

// TODO implement this
void readTemprature()
{
	;
}

// TODO implement this
void drivePWM()
{
	;
}

// ______________________


ISR(TIMER2_COMP_vect)
{
	schedule();
}

static int index = 0;

void schedule()
{
	ms_elapsed += 1;

	if (ms_elapsed % 50)
	{
		setState();
	}
	if (ms_elapsed % 100)
	{
		//fnc_array[1](3);
	}

	if (ms_elapsed % 200)
	{
		if (checkTemp)
		{
			readTemprature();
		}
		if (voltModule)
		{
			drivePWM();
		}

	}

	if (minutes_elapsed % 3)
	{
		if (overHeating)
		{
			setErrorFlag();
		}
	}

	// ______________________

	if (countMinutes)
	{
		minute_counter += 1;
	}
	if (minute_counter >= 60000)
	{
		minute_counter = 0;
		minutes_elapsed += 1;
	}
}
