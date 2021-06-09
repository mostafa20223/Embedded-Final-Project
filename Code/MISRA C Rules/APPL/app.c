#include "app.h"
static u8 shift = 0;

void Init(void)
{
	LCD_vInit();
	keypad_vInit();
	SPI_masterInit();
	TC72_Init();
	_delay_ms(150);
	initADC0();
}

void Welcome_Screen(void)
{
	LCD_vSend_cmd(0x0c);
	LCD_movecursor(1, 1);
	
	for (shift = 1; shift < 16; ++shift)
	{
		LCD_clearscreen();
		LCD_SendStringRowCol(1, shift, "WELCOME");
		_delay_ms(100);
		LCD_clearscreen();
	}

	for (shift = 16; shift > 0; --shift)
	{
		LCD_clearscreen();
		LCD_SendStringRowCol(1, shift, "WELCOME");
		_delay_ms(100);
		LCD_clearscreen();
	}
	
	_delay_ms(250);
	LCD_clearscreen();
}

void IDLE_Screen(void)
{
	_delay_ms(20);
	LCD_SendStringRowCol(1, 1, "SET:25");
	LCD_SendStringRowCol(1, 11, "CRT:");
	LCD_SendStringRowCol(2, 1, "STATE:STANDBY");
}

void StartApp(void)
{
	LCD_SendStringRowCol(2, 1, "STATE:OPERATION");
	CRT_Temp();
}

void UsrGetVal(void)
{
	u8 val = 0;
	static u8 col = 5;
	LCD_movecursor(1, col);
	val = getKey();
	if (val != '*' && val != '#')
	{
		LCD_vSend_char(val);
		_delay_ms(100);
		col = col + 1;
		UsrGetVal();
	}
	else
	{
		/* Do nothing */
		StartApp();
	}
}

c8 tc72_read(void)
{
    c8 MSB = 0;
	
	while(1)
	{
		/* MSB */
		PORTB |= (1 << SS);
		SPI_masterTransmit(0x02);            /* Read will be from MSB temperature register */
		SPI_masterTransmit(0x00);
		PORTB &= ~(1 << SS);

		_delay_ms(1);
		MSB = SPI_masterReceive();
		
		return MSB;
	}
}

//void SET_Temp(void)
//{	
	//LCD_movecursor(1, 5);
	//LCD_vSend_string(val);
//}

void CRT_Temp(void)
{
	while(1)
	{
		c8 CurrentTempString[2];
		c8 MSB = tc72_read();
		itoa(MSB, CurrentTempString, 10);
	
		LCD_movecursor(1, 15);
		LCD_vSend_string(CurrentTempString);
	}
}

float64_t getADCVal(void)
{
	u32 result = adc_read();
	float64_t Vr = sampleToVolts(result);
	
	return Vr;
}