#include "app.h"

int main(void)
{
	LCD_vInit();
	keypad_vInit();
	
	Welcome_Screen();
	
    /* Replace with your application code */
    while (1)
    {
		IDLE_Screen();
		UsrGetVal();
		Start_Communication();
		//uint8_t Pressed_Value = keypad_u8check_press();
		//_delay_ms(100);
		//LCD_vSend_char(Pressed_Value);
		
    }
}