#include "app.h"

static u8 shift = 0;
static u16 SetTemp = 0;
static u16 CrtTemp = 0;
static u8 temp[2];
enum sysStates {STANDBY, OPERATION, NORMAL, ERROR};
const c8 * StatesName[] = {"STANDBY", "OPERATION", "NORMAL", "ERROR"};
static enum sysStates curState = STANDBY;
static c8 hash_pressed = 0;
static c8 errorFlag = 0;
static u16 ms_elapsed = 0;
static u8 minutes_elapsed = 0;
static u16 minute_counter = 0;

// FLAGS
static char countMinutes = 0;
static char checkTemp = 0;
static char voltModule = 0;
static char overHeating = 0;

void Init(void)
{
	SPI_masterInit();
	TC72_Init();
	_delay_ms(150);
	initADC0();
	InitPWM();
}

void Welcome_Screen(void)
{
	LCD_vInit();
	for (shift = 1; shift < 16; ++shift)
	{
		LCD_clearscreen();
		LCD_movecursor(1, shift);
		LCD_vSend_string("WELCOME");
		_delay_ms(90);
		LCD_clearscreen();
	}

	for (shift = 16; shift > 0; --shift)
	{
		LCD_clearscreen();
		LCD_movecursor(1, shift);
		LCD_vSend_string("WELCOME");
		_delay_ms(90);
		LCD_clearscreen();
	}
	
	_delay_ms(150);
	LCD_clearscreen();
}

void IDLE_Screen(void)
{
	LCD_vInit();
	_delay_ms(20);
	LCD_movecursor(1, 1);
	LCD_vSend_string("SET:25");
	LCD_movecursor(1, 11);
	LCD_vSend_string("CRT:");
	LCD_movecursor(2, 1);
	LCD_vSend_string("STATE:STANDBY");
}
	
void UsrGetVal(void)
{
	keypad_vInit();
	u8 val = 0;
	static const u8 col = 5;
	static u8 counter = 0;
	
	LCD_movecursor(1, (counter + col));
	val = getKey();
	
	if (val != '*' && val != '#')
	{
		LCD_vSend_char(val);
		_delay_ms(100);
		temp[counter] = val;
		counter = counter + 1;
		counter = counter % 2;
		UsrGetVal();
	}
	else
	{
		SetTemp = atoi(temp);
		LCD_movecursor(2, 1);
		LCD_vSend_string("STATE:OPERATION");
	}
}

c8 tc72_read(void)
{
    c8 MSB = 0;
	
	while(1)
	{
		/* MSB */
		SPI_PORT |= (1 << SS);
		SPI_masterTransmit(0x02);            /* Read will be from MSB temperature register */
		SPI_masterTransmit(0x00);
		SPI_PORT &= ~(1 << SS);

		_delay_ms(1);
		MSB = SPI_masterReceive();
		
		return MSB;
	}
}

void CRT_Temp(void)
{
	u8 value = 0;

	c8 CurrentTempString[2];
	c8 MSB = tc72_read();
	itoa(MSB, CurrentTempString, 10);
		
	LCD_movecursor(1, 15);
	LCD_vSend_string(CurrentTempString);
	CrtTemp = atoi(CurrentTempString);
}

u16 getCurrentTemp(void)
{
	return CrtTemp;
}

u16 getSetTemp(void)
{
	return SetTemp;
}

float64_t GetVt(void)
{
	float64_t Vt = 0.0;
	Vt = (float64_t) ((getSetTemp() - getCurrentTemp()) / 100.0) * 10.0;
	return Vt;
}

float64_t getADCVal(void)
{
	u32 result = adc_read();
	float64_t Vr = sampleToVolts(result);
	
	return Vr;
}

void drivePWM(void)
{
	float64_t Vt = GetVt();
	float64_t Vr = getADCVal();
	SetPWMOutput(Vr, Vt);
}

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
			CRT_Temp();
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
			LCD_movecursor(2, 1);
			LCD_vSend_string("STATE:OPERATION");
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
			else if ((currentTemp > setTemp) && ((currentTemp - setTemp) > 10))
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
			LCD_movecursor(2, 1);
			LCD_vSend_string("STATE:NORMAL");
			setCheckTemp();
			clearVoltModule();
			break;
		}

		case ERROR:
		{
			LCD_movecursor(2, 1);
			LCD_vSend_string("STATE:ERROR");
			clearCheckTemp();
			clearVoltModule();
			break;
		}
		
		default:
			break;
	}
}