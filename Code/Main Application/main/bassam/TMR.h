#ifndef TMR_H
#define TMR_H

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define NUM_TIMERS 2
#define TIMER_VALUE 1 // Timer value in milli second
#define PRESCALAR 1024

#define OCR0 0x5C
#define OCIE0 0x01
#define TCCR0 0x53
#define TCNT0 0x52

#define OCR2 0x43
#define OCIE2 0x07
#define TCCR2 0x45
#define TCNT2 0x44

#define TIMSK 0x59

#endif