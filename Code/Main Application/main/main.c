#include "app.h"
#include "ADC.h"
int main(void)
{
	Init();
	Welcome_Screen();
	IDLE_Screen();
	initADC0();
	
    /* Replace with your application code */
    while (1)
    {
		//LCD_vSend_char('A');
		//T0delay();
		//LCD_vSend_char('B');
		//T0delay();
		
		u32 result = adc_read();
		float64_t Vr = sampleToVolts(result);
		
	    u8 val = UsrGetVal();
	    
	    if (val == '#')
	    {
			LCD_SendStringRowCol(2, 1, "STATE:OPERATION");
			LCD_movecursor(1, 5);
			//u8 value = UsrGetVal();
			//Start_Communication();
			tc72_read();
	    }
		else
		{
			/* Do nothing */
		}
		
    }

}