#include <util/delay.h>

#include "../MCAL/DIO.h"
#include "LCD_config.h"
#include "LCD.h"

static u8 counter = 0;

void LCD_vInit(void)
{
	_delay_ms(20);

	#if defined eight_bits_mode
		//for (counter = 0; counter < LCD_NPINs; ++counter)
		//{
			//DIO_vsetPINDir(LCD_PORT, counter, 1);
		//}
		DIO_vsetPINDir(LCD_PORT, 0, 1);
		DIO_vsetPINDir(LCD_PORT, 1, 1);
		DIO_vsetPINDir(LCD_PORT, 2, 1);
		DIO_vsetPINDir(LCD_PORT, 3, 1);
		DIO_vsetPINDir(LCD_PORT, 4, 1);
		DIO_vsetPINDir(LCD_PORT, 5, 1);
		DIO_vsetPINDir(LCD_PORT, 6, 1);
		DIO_vsetPINDir(LCD_PORT, 7, 1);
		DIO_vsetPINDir(LCD_PORT, EN_PIN, 1);
		DIO_vsetPINDir(LCD_PORT, RW_PIN, 1);
		DIO_vsetPINDir(LCD_PORT, RS_PIN, 1);
		DIO_write(RW_PORT, RW_PIN, 0);
		LCD_vSend_cmd(EIGHT_BITS); /* 8-bits Mode */
		_delay_ms(1);
		LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON); /* Display ON Cursor ON */
		_delay_ms(1);
		LCD_vSend_cmd(CLR_SCREEN); /* Clear Screen */
		_delay_ms(10);
		LCD_vSend_cmd(ENTRY_MODE); /* Entry Mode */
		_delay_ms(1);
	
	/* We will work on 4-bis Mode */
	#elif defined four_bits_mode
		//for (counter = 4; counter < LCD_NPINs; ++counter)
		//{
			//DIO_vsetPINDir(LCD_PORT, counter, 1);
		//}
		DIO_vsetPINDir(LCD_PORT, 4, 1);
		DIO_vsetPINDir(LCD_PORT, 5, 1);
		DIO_vsetPINDir(LCD_PORT, 6, 1);
		DIO_vsetPINDir(LCD_PORT, 7, 1);
		DIO_vsetPINDir(EN_PORT, EN_PIN, 1);
		DIO_vsetPINDir(RW_PORT, RW_PIN, 1);
		DIO_vsetPINDir(RS_PORT, RS_PIN, 1);
   		DIO_write(RW_PORT, RW_PIN, 0);
		LCD_vSend_cmd(RETURN_HOME); /* Return Home (row: 0, col: 0) */
		_delay_ms(10);
		LCD_vSend_cmd(FOUR_BITS); /* 4-bits Mode */
		_delay_ms(1);
		//LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON); /* Display ON Cursor ON */
		LCD_vSend_cmd(CURSOR_OFF_DISPLAN_OFF); /* Display OFF Cursor OFF */
		_delay_ms(1);
		LCD_vSend_cmd(CLR_SCREEN); /* Clear Screen */
		_delay_ms(10);
		LCD_vSend_cmd(ENTRY_MODE); /* Entry Mode */
		_delay_ms(1);

	#endif
}

void send_falling_edge(void)
{
	DIO_write(EN_PORT, EN_PIN, 1);
	_delay_ms(2);
	DIO_write(EN_PORT, EN_PIN, 0);
	_delay_ms(2);
}

void LCD_vSend_cmd(c8 cmd)
{
	#if defined eight_bits_mode
		DIO_write_port(LCD_PORT, cmd);
		DIO_write(RS_PORT, RS_PIN, 0);
		send_falling_edge();
	
	/* We will work on 4-bis Mode */
	#elif defined four_bits_mode
		write_high_nibble(LCD_PORT, cmd >> 4);
		DIO_write(RS_PORT, RS_PIN, 0);
		send_falling_edge();
		write_high_nibble(LCD_PORT, cmd);
		DIO_write(RS_PORT, RS_PIN, 0);
		send_falling_edge();

	#endif
	_delay_ms(1);
}

void LCD_vSend_char(c8 data)
{
	#if defined eight_bits_mode
		DIO_write_port(LCD_PORT, data);
		DIO_write(RS_PORT, RS_PIN, 1);
		send_falling_edge();
	
	/* We will work on 4-bis Mode */
	#elif defined four_bits_mode
		write_high_nibble(LCD_PORT, (data >> 4));
		DIO_write(RS_PORT, RS_PIN, 1);
		send_falling_edge();
		write_high_nibble(LCD_PORT, data);
		DIO_write(RS_PORT, RS_PIN, 1);
		send_falling_edge();

	#endif
	_delay_ms(1);
}

void LCD_vSend_string(c8 * data)
{
	/* (*data): Pointer to first char of string */
	//while((*data) != '\0')
	//{
		//LCD_vSend_char(*data);
		//data = data + 1; /* To next char */
	//}

    for(counter = 0; data[counter] != '\0'; ++counter)
    {
	    LCD_vSend_char(data[counter]);
    }
}

void LCD_clearscreen(void)
{
	LCD_vSend_cmd(CLR_SCREEN);
	_delay_ms(10);
}

void LCD_movecursor(c8 row, c8 coloumn)
{
	char data = 0;
	
	if (row > 2 || row < 1 || coloumn > 16 || coloumn < 1)
	{
		data = 0x80;
	}
	else if (row == 1)
	{
		data = 0x80 + coloumn - 1;
	}
	else if (row == 2)
	{
		data = 0xc0 + coloumn - 1;
	}
	
	LCD_vSend_cmd(data);
	_delay_ms(1);
}

void LCD_SendStringRowCol(u8 row, u8 col, c8 * data)
{
	LCD_movecursor(row, col);
    for(counter = 0; data[counter] != '\0'; ++counter)
    {
	    LCD_vSend_char(data[counter]);
    }
}

void LCD_SendCharRowCol(u8 row, u8 col, c8 data)
{
	LCD_movecursor(row, col);
	LCD_vSend_char(data);
}