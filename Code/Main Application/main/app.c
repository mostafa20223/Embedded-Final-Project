#include "app.h"
#include "std_macros.h"
#include <avr/io.h>
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

/*void Start_Communication(void)
{
	c8 msb = 0;
	c8 lsb = 0;
	c8 TempVal;

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
		msb <<= 1;
		//LCD_movecursor(1, 15);
		//LCD_vSend_char(msb);
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
		c8 CurrentTempString[2];
		//itoa(lsb,CurrentTempString,10);
		lsb >>= 7;
		//PORTD = lsb;
		//LCD_movecursor(1, 15);
		//LCD_vSend_string(CurrentTempString);
		TempVal = (msb | lsb);
		itoa(TempVal,CurrentTempString,10);
		LCD_movecursor(1, 15);
		LCD_vSend_string(CurrentTempString);
		//TempVal = msb ;
		
		//LCD_movecursor(1, 15);
		//LCD_vSend_char('4');
		//LCD_movecursor(1, 16);
		//LCD_vSend_char('3');
		////LCD_movecursor(1, 15);
		////LCD_vSend_char(TempVal);
		//_delay_ms(20);
	}
}*/

void tc72_read(void){
    char LSB = 0;        /* store temperature value */
    char MSB = 0;
	char CurrentTempString[4];
    char tempValue = 0;
    /* ----------- LSB ---------- */
	while(1){
    PORTB |= (1 << 4);
    SPI_masterTransmit(0x01);
    SPI_masterTransmit(0x00);
    PORTB &= ~(1 << 4);

    _delay_ms(1);
    LSB = SPI_masterReceive();

    /* ----------- MSB ---------- */

    PORTB |= (1 << 4);
    SPI_masterTransmit(0x02);            /* read will be from MSB temperature register */
    SPI_masterTransmit(0x00);
    PORTB &= ~(1 << 4);

    _delay_ms(1);
    MSB = SPI_masterReceive();

    LSB >>= 7;
    //MSB <<= 1;
    tempValue = MSB | LSB;
	
	itoa(MSB,CurrentTempString,10);
    LCD_movecursor(1, 15);
    LCD_vSend_string(CurrentTempString);
	}
}
