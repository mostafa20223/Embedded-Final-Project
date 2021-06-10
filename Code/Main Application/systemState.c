#include "systemState.h"

enum sysStates {STANDBY, OPERATION, NORMAL, ERROR};
const c8 * StatesName[] = {"STANDBY", "OPERATION", "NORMAL", "ERROR"};
static enum sysStates curState = STANDBY;
static c8 hash_pressed = 0;
static c8 errorFlag = 0;

void setErrorFlag(void)
{
	errorFlag = 1;
}

void setState(void)
{
	switch (curState)
	{
		case STANDBY:
		{
			clearVoltModule();
			clearCheckTemp();

			if (getKey() == '#')
			{
				curState = OPERATION;
			}
			break;
		}

		case OPERATION:
		{
			setCheckTemp();
			setVoltModule();

			u16 currentTemp = getCurrentTemp();
			u16 setTemp = getSetTemp();
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

			if (getKey() == '#')
			{
				curState = STANDBY;
			}
			if (errorFlag)
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