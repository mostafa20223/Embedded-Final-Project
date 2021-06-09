#include "app.h"

int main(void)
{
	Init();
	Welcome_Screen();
	IDLE_Screen();
	
    /* Replace with your application code */
    while (1)
    {
		LCD_vSend_char('A');
		T0delay();
		LCD_vSend_char('B');
		T0delay();
		
	    //u8 val = UsrGetVal();
	    //
	    //if (val == '#')
	    //{
			//LCD_SendStringRowCol(2, 1, "STATE:OPERATION");
			//LCD_movecursor(1, 5);
			//u8 value = UsrGetVal();
			//Start_Communication();
	    //}
		//else
		//{
			///* Do nothing */
		//}
		
    }

}