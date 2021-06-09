#include "systemState.h"
#include "Scheduler.h"
#include "Basic_Types.h"

enum sysStates {STANDBY, OPERATION, NORMAL, ERROR};
const char * StatesName[] = {"STANDBY", "OPERATION", "NORMAL", "ERROR"};

static enum sysStates curState = STANDBY;

static char hash_pressed = 0;

static char errorFlag = 0;

void setErrorFlag()
{
	errorFlag = 1;
}

void clearErrorFlag()
{
	errorFlag = 0;
}

// TODO
int getCurrentTemp()
{
	;
}
int getSetTemp()
{
	;
}

void setState()
{
	switch (curState)
	{
		case STANDBY:
		{
			clearVoltModule();
			clearCheckTemp();

			if (hash_pressed == 1)
			{
				curState = OPERATION;
			}
			break;
		}

		case OPERATION:
		{
			setCheckTemp();
			setVoltModule();

			u8 currentTemp = getCurrentTemp();
			u8 setTemp = getSetTemp();
			if ((currentTemp > setTemp) && ((currentTemp - setTemp) <= 5))
			{
				curState = NORMAL;
				clearCountMinutes();
				clearOverHeating();
			}
			else if ((currentTemp < setTemp) && ((setTemp - currentTemp) <= 5))
			{
				curState = NORMAL;
				clearCountMinutes();
				clearOverHeating();
			}
			else if((currentTemp > setTemp) && ((currentTemp - setTemp) > 10))
			{
				curState = ERROR;
			}
			else if ((setTemp > currentTemp) && ((setTemp - currentTemp) > 5))
			{
				setCountMinutes();
				setOverHeating();
			}

			if (hash_pressed == 1)
			{
				curState = STANDBY;
			}
			if(errorFlag)
			{
				curState = ERROR;
			}
			break;
		}

		case NORMAL:
		{
			setCheckTemp();
			clearVoltModule();
			break;
		}

		case ERROR:
		{
			clearCheckTemp();
			clearVoltModule();
			break;
		}
		default:
		break;
	}
}