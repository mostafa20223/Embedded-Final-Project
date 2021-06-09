#include <avr/interrupt.h>
#include "Basic_Types.h"
#include "timer8bit.h"

//#include "Interrupts.h"
//#include "Interrupt_names.h"
//#include "INT_R.h"

ISR(INT0_vect)
{
	//PORTA= 0xFF;
	//*((u8 *)(0x3B)) = ~(*((u8 *)(0x3B)));
	//for(u8 i = 0; i < 255; ++i){ ; }
	
}

int main(void)
{
    /* Replace with your application code */
	init_timer_CTC(1, 1);
	(SREG) |= (1 << 7);
	
	/*
	*((u8 *)DDRA) = 0xFF;
	*((u8 *)DDRD) = 0x00;
	*((u8 *)GICR) |= (1 << INT0);
	*((u8 *)MCUCR) |= (1 << ISC00);
	*((u8 *)MCUCR) &= (0 << ISC01);
	(SREG) |= (1 << 7);
	*/

	while (1) 
    {
    }
}
