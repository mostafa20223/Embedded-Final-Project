#include "app.h"

static u8 shift = 0;

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

u8 UsrGetVal(void)
{
	u8 keypadPress = getKey();
	
	if (keypadPress == '#')
	{
		_delay_ms(20);
	}
	else
	{
		LCD_vSend_char(keypadPress);
		_delay_ms(20);		
	}
	
	return keypadPress;
}

void Start_Communication(void)
{
	c8 msb;
	c8 lsb;

	while(1)
	{
		//DIO_vsetPINDir(SPI_PORT, 4, 1);
		PORTB |= (1 << 4);
		
		// Read the MSB
		SPI_masterTransmit(0x02);
		
		// Issue one more clock frame to force data out
		SPI_masterTransmit(0x00);
		
		//DIO_vsetPINDir(SPI_PORT, 4, 0);
		PORTB &= ~(1 << 4);
		_delay_ms(1);
		
		msb = SPI_masterReceive();
		//DIO_vsetPINDir(SPI_PORT, 4, 1);
		PORTB |= (1 << 4);
		
		// Read The LSB
		SPI_masterTransmit(0x01);
		
		// Issue one more clock frame to force data out
		SPI_masterTransmit(0x00);
		
		//DIO_vsetPINDir(SPI_PORT, 4, 0);
		PORTB &= ~(1 << 4);
		_delay_ms(1);
		
		lsb = SPI_masterReceive();
		//PORTD = lsb;
	
		//displayTemperature(msb, lsb);
	}
}
