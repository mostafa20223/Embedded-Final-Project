#define F_CPU 16000000UL /* 16 MHz Clock Speed */

#include <avr/io.h>
#include <util/delay.h>

#include "Basic_Types.h"
#include "DIO.h"
#include "LCD.h"
#include "Keypad.h"
#include "SPI.h"

int main(void)
{
	LCD_vInit();
	keypad_vInit();
	
    /* Replace with your application code */
    while (1) 
    {
		char Pressed_Value = keypad_u8check_press();
		LCD_vSend_char(Pressed_Value);
		//LCD_movecursor(row, col);
		_delay_ms(1000);
		//LCD_clearscreen();
		//keypadValue = GetKeyPressed();
		//LCD_vSend_char(keypadValue);
		//_delay_ms(2000);
    }
}

/* SPI TC72

SPI_masterInit();
SPI_masterReceive();
//SPI_masterTransmit();
TC72_Init();
Start_Communication();

*/