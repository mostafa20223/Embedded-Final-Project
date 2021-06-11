#ifndef TMR_H
#define TMR_H

#ifndef F_CPU
#define F_CPU 16000000UL	/* 16 MHz Clock Speed */
#endif

#define NUM_TIMERS 2		/* Timer0 and Tiemer2 */
#define TIMER_VALUE 1		/* Timer value in milli second */
#define PRESCALAR 1024		/* Pre-scale Value */

#endif /* TMR_H */