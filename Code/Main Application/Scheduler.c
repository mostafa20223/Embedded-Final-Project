#include "Scheduler.h"

static u16 ms_elapsed = 0;
static u8 minutes_elapsed = 0;
static u16 minute_counter = 0;

// ______________________

// FLAGS
static char countMinutes = 0;
static char checkTemp = 0;
static char voltModule = 0;
static char overHeating = 0;

// FLAG setter
void setCountMinutes(void)
{
	countMinutes = 1;
}
void setCheckTemp(void)
{
	checkTemp = 1;
}
void setVoltModule(void)
{
	voltModule = 1;
}
void setOverHeating(void)
{
	overHeating = 1;
}

// FLAG clear
void clearCountMinutes(void)
{
	countMinutes = 0;
	minute_counter = 0;
	minutes_elapsed = 0;
}
void clearCheckTemp(void)
{
	checkTemp = 0;
}
void clearVoltModule(void)
{
	voltModule = 0;
}
void clearOverHeating(void)
{
	overHeating = 0;
}

// ______________________

ISR(TIMER2_COMP_vect)
{
	schedule();
}

void schedule(void)
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
			GetVt();
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
