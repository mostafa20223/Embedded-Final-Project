#include "timer8bit.h"

void init_timer_CTC(u8 id, u8 TimerValue)
{
	// TimerValue is the time value in milli seconds
	if (id >= NUM_TIMERS)
	{
		setErrorFlag();
		return;
	}
	
	u16 counts = (TimerValue * (0.001 * (F_CPU / PRESCALAR))) - 1;
	
	if (counts > 255)
	{
		setErrorFlag();
		return;
	}
	if (id == 0) /* Timer0 */
	{
		OCR0 = (u8) counts;
		TCCR0 = 0b0001101;
		TIMSK |= (1 << OCIE0);
	}
	else if (id == 2) /* Timer2 */
	{
		OCR2 = (u8) counts;
		TCCR2 = 0b0001101;
		TIMSK |= (1 << OCIE2);
	}
}
