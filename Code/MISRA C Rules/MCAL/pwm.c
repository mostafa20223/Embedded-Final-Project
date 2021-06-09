#include "pwm.h"

void InitPWM(void)
{
	TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00);
	DDRB |= (1 << PB3);
	OCR1A = 3000;
}

void SetPWMOutput(float64_t vr, float64_t vt)
{
	u8 duty = 0;
	duty = (((vr * 2) / 10) * vt) / 10;
	OCR0 = duty;
}

void Wait(void)
{
	_delay_loop_2(3600);
}