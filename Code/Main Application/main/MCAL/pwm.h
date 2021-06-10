#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <util/delay.h>
#include "../standard/Basic_Types.h"
#include "DIO.h"

#define PWM_DDR DDRB		/* Initialize PWM on DDRB */
#define PWM_PORT PORTB		/* Initialize PWM on PORTB */
#define PWM_PIN PINB3		/* Initialize PWM on PINB3 */

/********************************************************************
	Function Name        : InitPWM
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize PWM PORT
********************************************************************/
void InitPWM(void);

/********************************************************************
	Function Name        : SetPWMOutput
	Function Returns     : void
	Function Arguments   : float64_t vr, float64_t vt
	Function Description : Set output of PWM (Duty Cycle)
********************************************************************/
void SetPWMOutput(float64_t vr, float64_t vt);

/********************************************************************
	Function Name        : Wait
	Function Returns     : void
	Function Arguments   : void
	Function Description : Waiting for a response
********************************************************************/
void Wait(void);

#endif /* PWM_H */