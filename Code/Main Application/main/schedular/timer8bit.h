#ifndef TIMER8BIT_H
#define TIMER8BIT_H

#include <avr/interrupt.h>
#include <util/delay.h>
#include "../standard/Basic_Types.h"
#include "TMR.h"
#include "systemState.h"
//#include "Interrupts.h"
//#include "Interrupt_names.h"
//#include "INT_R.h"

/*
	Function Name        : init_timer_CTC
	Function Returns     : void
	Function Arguments   : u8 id, u8 TimerValue
	Function Description : Initialize essential functions in our application
*/
void init_timer_CTC(u8 id, u8 TimerValue);

#endif /* TIMER8BIT_H */