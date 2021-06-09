#ifndef LCD_H
#define LCD_H

#include "../standard/Basic_Types.h"

#define CLR_SCREEN 0x01
#define CURSOR_ON_DISPLAN_ON 0x0e
#define CURSOR_OFF_DISPLAN_OFF 0x0c
#define RETURN_HOME 0x02
#define ENTRY_MODE 0x06

#if defined four_bits_mode
	#define EN_PIN 0 /* Enable */
	#define RS_PIN 1 /* Register Selection */
	#define RW_PIN 2 /* Read/Write */
	#define FOUR_BITS 0x28
#elif defined eight_bits_mode
	#define EN_PIN 0 /* Enable */
	#define RS_PIN 1 /* Register Selection */
	#define RW_PIN 2 /* Read/Write */
	#define EIGHT_BITS 0x38
#endif

/*
	Function Name        : LCD_vInit
	Function Returns     : void
	Function Arguments   : void
	Function Description : Returns 1 if the '#' Key is Pressed and 0 if not
*/
void LCD_vInit(void);

/*
	Function Name        : send_falling_edge
	Function Returns     : void
	Function Arguments   : void
	Function Description : Returns 1 if the '#' Key is Pressed and 0 if not
*/
void send_falling_edge(void);

/*
	Function Name        : LCD_vSend_cmd
	Function Returns     : void
	Function Arguments   : char cmd
	Function Description : Returns 1 if the '#' Key is Pressed and 0 if not
*/
void LCD_vSend_cmd(c8 cmd);

/*
	Function Name        : LCD_vSend_char
	Function Returns     : void
	Function Arguments   : char data
	Function Description : Returns 1 if the '#' Key is Pressed and 0 if not
*/
void LCD_vSend_char(c8 data);

/*
	Function Name        : LCD_vSend_string
	Function Returns     : void
	Function Arguments   : char * data
	Function Description : Returns 1 if the '#' Key is Pressed and 0 if not
*/
void LCD_vSend_string(c8 * data);

/*
	Function Name        : LCD_clearscreen
	Function Returns     : void
	Function Arguments   : void
	Function Description : Returns 1 if the '#' Key is Pressed and 0 if not
*/
void LCD_clearscreen(void);

/*
	Function Name        : LCD_movecursor
	Function Returns     : void
	Function Arguments   : char row, char coloumn
	Function Description : Returns 1 if the '#' Key is Pressed and 0 if not
*/
void LCD_movecursor(c8 row, c8 coloumn);

/*
	Function Name        : LCD_SendCharRowCol
	Function Returns     : void
	Function Arguments   : u8 row, u8 col, c8 data
	Function Description : Returns 1 if the '#' Key is Pressed and 0 if not
*/
void LCD_SendCharRowCol(u8 row, u8 col, c8 data);

/*
	Function Name        : LCD_SendStringRowCol
	Function Returns     : void
	Function Arguments   : u8 row, u8 col, c8 * str
	Function Description : Returns 1 if the '#' Key is Pressed and 0 if not
*/
void LCD_SendStringRowCol(u8 row, u8 col, c8 * data);

#endif /* LCD_H */