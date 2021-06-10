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

void WriteVolt(void)
{
	DIO_vsetPINDir(ADC_PORT, 0, 1);
	u32 result = adc_read();
	float64_t Vr = sampleToVolts(result);
	
	if (Vr > 2.5)
	{
		DIO_write(ADC_PORT, 0, 0);
	}
	else
	{
		DIO_write(ADC_PORT, 0, 1);
		//PORTD = 0b00100000;
	}
	_delay_ms(1000);
}