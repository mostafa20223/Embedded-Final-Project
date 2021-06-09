/*
 * CFile1.c
 *
 * Created: 6/9/2021 8:49:12 PM
 *  Author: Donia
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "Basic_Types.h"
void InitPWM()
{
	TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00);
	DDRB|=(1<<PB3);
	OCR1A = 3000;
}
void SetPWMOutput(float64_t vr,float64_t vt)
{
	uint8_t duty = 0;
	duty =  (((vr * 2)/10) *vt) / 10;
	OCR0=duty;
}
void Wait()
{
	_delay_loop_2(3600);
}