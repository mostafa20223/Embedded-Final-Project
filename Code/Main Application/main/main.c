#include "APPL/app.h"

int main(void)
{
	Init();
	Welcome_Screen();
	IDLE_Screen();
	UsrGetVal();

	//StartApp();
	//sei();
	
    /* Replace with your application code */
    while (1)
    {
		//LCD_vSend_char('A');
		//T0delay();
		//LCD_vSend_char('B');
		//T0delay();
		
		//CRT_Temp();
		float64_t Vr = getADCVal();
		

    }

}

//ISR(SPI_STC_vect)
//{
	//UsrGetVal();
//}