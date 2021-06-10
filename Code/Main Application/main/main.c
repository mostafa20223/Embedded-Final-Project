#include "APPL/app.h"

int main(void)
{
	Welcome_Screen();
	IDLE_Screen();
	UsrGetVal();

	Init();
	
	//StartApp();
	//sei();

	
	//init_timer_CTC(0, 200);
	//sei();
	
    /* Replace with your application code */
    while (1)
    {
		//LCD_vSend_char('A');
		//T0delay();
		//LCD_vSend_char('B');
		//T0delay();
		
		//WriteVolt();
		CRT_Temp();
		//drivePWM();
		
		//setState();

    }

}