#include <avr/io.h>
#include "Timer.h"

void T0delay(void)
{
	TCCR0 = (1 << CS02) | (1 << CS00); /* Timer0, normal mode, /1024 prescalar */
	TCNT0 = 0x64; // 0xb2;  		/* Load TCNT0, count for 10ms */
	while((TIFR & 0x01) == 0);  /* Wait for TOV0 to roll over */
	TCCR0 = 0;
	TIFR = 0x1;  		/* Clear TOV0 flag */
}