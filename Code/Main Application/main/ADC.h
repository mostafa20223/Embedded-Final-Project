#include "Basic_Types.h"
#ifndef ADC_H_
#define ADC_H_

void initADC0();
u32 adc_read();
float64_t sampleToVolts(u32 sample);

#endif /* ADC_H_ */