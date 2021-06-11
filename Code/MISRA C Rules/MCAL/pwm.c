#include "pwm.h"

void InitPWM(void)
{
	TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00);
	PWM_DDR |= (1 << PWM_PIN);
	OCR1A = 3000;
	//TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00);
	//PWM_DDR |= (1 << PWM_PIN);  /*set OC0 pin as output*/
	//OCR1A = 3000;
}

void SetPWMOutput(float64_t vr, float64_t vt)
{
	float64_t duty = 0;
	duty = (((vr * 2) / 10) * vt) / 10;
	OCR0 = duty;
}

//void Wait(void)
//{
	//_delay_loop_2(3600);
//}
