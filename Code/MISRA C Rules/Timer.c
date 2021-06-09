#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"

void T0delay(void)
{
	TCCR0 = (1 << CS02) | (1 << CS00); /* Timer0, normal mode, /1024 prescalar */
	TCNT0 = 0x64; // 0xb2;  		/* Load TCNT0, count for 10ms */
	while((TIFR & 0x01) == 0);  /* Wait for TOV0 to roll over */
	TCCR0 = 0;
	TIFR = 0x1;  		/* Clear TOV0 flag */
}

void timer_CTC_init_interrupt(void)
{
	/* select CTC mode*/
	SET_BIT(TCCR0, WGM01);
	/* load a value in OCR0 */
	OCR0 = 80;
	/* select timer clock */
	SET_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS02);
	/* enable interrupt*/
	sei();
	SET_BIT(TIMSK, OCIE0);
}

void timer_wave_nonPWM(void)
{
	/* set OC0 as output pin */
	SET_BIT(DDRB, 3);
	/* select CTC mode*/
	SET_BIT(TCCR0, WGM01);
	/* load a value in OCR0 */
	OCR0 = 64;
	/* select timer clock */
	SET_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS02);
	/* toggle OC0 on compare match*/
	SET_BIT(TCCR0, COM00);
}

void timer_wave_fastPWM(void)
{
	/* set OC0 as output pin */
	SET_BIT(DDRB, 3);
	/* select fast PWM mode*/
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
	/* load a value in OCR0 */
	OCR0 = 64;
	/* select timer clock */
	SET_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS02);
	/* Set OC0 on compare match, clear OC0 at BOTTOM,(inverting mode)*/
	SET_BIT(TCCR0, COM00);
	SET_BIT(TCCR0, COM01);
}

void timer_wave_phasecorrectPWM(void)
{
	/* set OC0 as output pin */
	SET_BIT(DDRB, 3);
	/* select phase correct PWM mode*/
	SET_BIT(TCCR0, WGM00);
	/* load a value in OCR0 */
	OCR0 = 64;
	/* select timer clock */
	SET_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS02);
	/* Set OC0 on compare match when up-counting. Clear OC0 on compare match when down counting.*/
	SET_BIT(TCCR0, COM00);
	SET_BIT(TCCR0, COM01);
}