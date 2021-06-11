#include "APPL/app.h"

int main(void)
{
	WDT_OFF();
	Init();
	Welcome_Screen();

	//init_timer_CTC(1, 1);
	//sei();
	
    /* Replace with your application code */
    while (1)
    {
		
		schedule();
		
    }

}