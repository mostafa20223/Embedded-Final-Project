#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <util/delay.h>
#include "../standard/Basic_Types.h"
#include "DIO.h"

#define ADC_PORT 'D' /* Initialize ADC on PORTD */

/*******************************************************************************
	Function Name        : initADC0
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize ADC PORT
*******************************************************************************/
void initADC0(void);

/*******************************************************************************
	Function Name        : adc_read
	Function Returns     : u32
	Function Arguments   : void
	Function Description : Read value from ADC
*******************************************************************************/
u32 adc_read(void);

/*******************************************************************************
	Function Name        : sampleToVolts
	Function Returns     : u8
	Function Arguments   : u32 sample
	Function Description : Convert ADC value to voltage
*******************************************************************************/
u8 sampleToVolts(u32 sample);

#endif /* ADC_H */