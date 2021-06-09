#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include "../standard/Basic_Types.h"

/*
	Function Name        : initADC0
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize essential functions in our application
*/
void initADC0(void);

/*
	Function Name        : adc_read
	Function Returns     : u32
	Function Arguments   : void
	Function Description : Initialize essential functions in our application
*/
u32 adc_read(void);

/*
	Function Name        : sampleToVolts
	Function Returns     : float64_t
	Function Arguments   : u32 sample
	Function Description : Initialize essential functions in our application
*/
float64_t sampleToVolts(u32 sample);

#endif /* ADC_H */