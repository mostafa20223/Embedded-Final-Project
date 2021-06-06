#define F_CPU 16000000UL

#include "Basic_Types.h"
#include "DIO.h"
#include "LCD.h"
#include "LCD_config.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	LCD_vInit();
	uchar_t row = 1;
	uchar_t col = 8;
	
    /* Replace with your application code */
    while (1) 
    {
		LCD_vSend_string("WELCOME");
		LCD_movecursor(row, col);
		_delay_ms(100);
		LCD_clearscreen();
    }
}

