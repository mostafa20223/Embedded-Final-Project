#ifndef TIMER8BIT_H
#define TIMER8BIT_H

#include <avr/interrupt.h>
#include <util/delay.h>
#include "../standard/Basic_Types.h"
#include "TMR.h"
#include "Scheduler.h"

/********************************************************************
	Function Name        : init_timer_CTC
	Function Returns     : void
	Function Arguments   : u8 id, u8 TimerValue
	Function Description : Initialize Timer0 or Timer1
********************************************************************/
void init_timer_CTC(u8 id, u8 TimerValue);

void WDT_ON(void);

void WDT_OFF(void);

#endif /* TIMER8BIT_H */