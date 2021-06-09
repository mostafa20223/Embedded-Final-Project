#include "ADC.h"

void initADC0(void)
{
	// Select the required channel
	ADMUX = 0x00;
	ADMUX |= (1U << REFS0);
	// Enable ADC, with a clock prescale of 1/128
	ADCSRA = (1U << ADEN) | (1U << ADPS2) | (1U << ADPS1) | (1U << ADPS0);
}

u32 adc_read(void)
{
	// start conversion
	ADCSRA |= (1U << ADSC);
	
	// read from ADC, waiting for conversion to finish
	while(ADCSRA & (1U << ADSC))
	{
		/* Do nothing */
	}
	
	return ADC;
}

float64_t sampleToVolts(u32 sample)
{
	return sample * (5.0 / 1023.0);
}