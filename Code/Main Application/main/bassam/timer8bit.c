#include "TMR.h"
#include "timer8bit.h"
#include "Basic_Types.h"
//#include "Interrupts.h"
//#include "Interrupt_names.h"
//#include "INT_R.h"
#include <avr/interrupt.h>

/*
volatile u8 * const OCRs[] = {OCR0, OCR2};
volatile u8 const OCIEs[] = {OCIE0, OCIE2};
volatile u8 * const TCCRs[] = {TCCR0, TCCR2};
volatile u8 * const TCNTs[] = {TCNT0, TCNT2};
*/

void init_timer_CTC(u8 id, u8 TimerValue)
{
	// TimerValue is the time value in milli seconds
	if (id >= NUM_TIMERS) { setErrorFlag(); return; }
	u16 counts = (TimerValue * (0.001 * (F_CPU / PRESCALAR))) - 1;
	
	if (counts > 255)
	{
		setErrorFlag();
		return;
	}
	if (id == 0)
	{
		OCR0 = (u8) counts;
		TCCR0 = 0b0001101;
		TIMSK |= (1 << OCIE0);
	}else if (id == 1)
	{
		OCR2 = (u8) counts;
		TCCR2 = 0b0001101;
		TIMSK |= (1 << OCIE2);
	}
	
	/*
	*((u8 *)(OCRs[id])) = (u8) counts;
	// CTC mode with 1024 prescalar
	*((u8 *)(TCCRs[id])) = 0b0001101;
	*((u8 *)(TIMSK)) |= (1 << OCIEs[id]);
	*/
}
