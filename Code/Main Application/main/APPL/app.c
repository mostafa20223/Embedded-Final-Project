#include "app.h"

static u8 shift = 0;
static u16 SetTemp = 0;
static u16 CrtTemp = 0;
static u8 temp[2];
enum sysStates {STANDBY, OPERATION, NORMAL, ERROR};
//const c8 * StatesName[] = {"STANDBY", "OPERATION", "NORMAL", "ERROR"};
static enum sysStates curState = STANDBY;
static c8 hash_pressed = 0;
static c8 errorFlag = 0;
static u16 ms_elapsed = 0;
static u8 minutes_elapsed = 0;
static u16 minute_counter = 0;

// FLAGS
static c8 countMinutes = 0;
static c8 checkTemp = 0;
static c8 voltModule = 0;
static c8 overHeating = 0;
static c8 poteinVal = 0;

/* Voltages */
static float64_t Vt = 0.0;
static float64_t Vr = 0.0;

/* Temp Variables */
static u16 currentTemp = 0;
static u16 setTemp = 0;
static u8 keyPress = 0;

void Init(void)
{
	LCD_vInit();
	keypad_vInit();
	SPI_masterInit();
	TC72_Init();
	_delay_ms(150);
}

void Welcome_Screen(void)
{
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
	_delay_ms(15);
	LCD_movecursor(1, 1);
	LCD_vSend_string("SET:25");
	LCD_movecursor(1, 11);
	LCD_vSend_string("CRT:");
	LCD_movecursor(2, 1);
	LCD_vSend_string("STATE:STANDBY");
}

void UsrGetVal(void)
{
	keyPress = 1;
	u8 val = 0;
	static const u8 col = 5;
	static u8 counter = 0;
	
	LCD_movecursor(1, (counter + col));
	
	while (val != '*' && val != '#')
	{
		//val != '*' && val != '#'
		val = getKey();
		
		if (val != '*' && val != '#')
		{
			LCD_vSend_char(val);
		}
		else
		{
			break;
		}
		
		temp[counter] = val;
		counter = counter + 1;
		counter = counter % 2;
	}

	SetTemp = atoi(temp);
	hash_pressed = 1;
	keyPress = 0;
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
	Vt = (float64_t) ((getSetTemp() - getCurrentTemp()) / 100.0) * 10.0;
	return Vt;
}

float64_t getADCVal(void)
{
	initADC0();
	u32 result = adc_read();
	Vr = sampleToVolts(result);
	
	return Vr;
}

void drivePWM(void)
{
	InitPWM();
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
void setPoteinVal(void)
{
	poteinVal = 1;
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
void clearPoteinVal(void)
{
	poteinVal = 0;
}

// ______________________

ISR (TIMER2_COMP_vect)
{
	if (keyPress == 0)
	{
		schedule();
	}
	else
	{
		
	}
}

void schedule(void)
{
	ms_elapsed = ms_elapsed + 1;
	setState();

	//if (!(ms_elapsed % 1))
	//{
		//setState();
	//}

	if (!(ms_elapsed % 200))
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
	
	if (!(ms_elapsed % 500))
	{
		if (poteinVal)
		{
			getADCVal();
		}
		else
		{
			/* Do nothing */
		}
	}

	if (!(minutes_elapsed % 3))
	{
		if (overHeating)
		{
			setErrorFlag();
		}
	}

	if (countMinutes)
	{
		minute_counter = minute_counter + 1;
	}
	if (!(minute_counter % 60000))
	{
		minute_counter = 0;
		minutes_elapsed = minutes_elapsed + 1;
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
			IDLE_Screen();
			UsrGetVal();
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
			LCD_movecursor(2, 1);
			LCD_vSend_string("STATE:OPERATION");
			setCheckTemp();
			setVoltModule();
			setPoteinVal();
			CRT_Temp();

			currentTemp = getCurrentTemp();
			setTemp = getSetTemp();
			
			//if (setTemp <= currentTemp)
			//{
				///* Do nothing for now */
			//}
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
			else if ((setTemp > currentTemp) && ((setTemp - currentTemp) > 5))
			{
				setCountMinutes();
				setOverHeating();
			}
			else
			{
				/* Do nothing */
			}

			//if (hash_pressed == 1)
			//{
				//curState = STANDBY;
			//}
			if (errorFlag == 1)
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
			setPoteinVal();
			clearVoltModule();
			CRT_Temp();
			
			currentTemp = getCurrentTemp();
			setTemp = getSetTemp();
			
			if ((setTemp > currentTemp) && (setTemp - currentTemp) > 5)
			{
				curState = OPERATION;
			}
			else if ((currentTemp > setTemp) && ((currentTemp - setTemp) > 10))
			{
				curState = ERROR;
			}
			else
			{
				/* Do nothing */
			}
			
			if (errorFlag)
			{
				curState = ERROR;
			}
			break;
		}

		case ERROR:
		{
			LCD_movecursor(2, 1);
			LCD_vSend_string("STATE:ERROR");
			clearCheckTemp();
			clearVoltModule();
			clearPoteinVal();
			break;
		}
		
		default:
			break;
	}
}