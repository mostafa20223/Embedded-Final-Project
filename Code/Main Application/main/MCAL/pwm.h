#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <util/delay.h>
#include "../standard/Basic_Types.h"

void InitPWM(void);
void SetPWMOutput(float64_t vr, float64_t vt);
void Wait(void);

#endif /* PWM_H */