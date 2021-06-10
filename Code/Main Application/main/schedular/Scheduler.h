#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../standard/Basic_Types.h"
#include "timer8bit.h"

/********************************************************************
	Function Name        : setState
	Function Returns     : void
	Function Arguments   : void
	Function Description : Determine which state will be evaluated
********************************************************************/
void setState(void);

/********************************************************************
	Function Name        : schedule
	Function Returns     : void
	Function Arguments   : void
	Function Description : Interrupt Evaluation
********************************************************************/
void schedule(void);

// FLAG clearer
void clearCountMinutes(void);
void clearCheckTemp(void);
void clearVoltModule(void);
void clearOverHeating(void);
void clearPoteinVal(void);

/******************************************************************** FLAGS setter
	Function Name        : setErrorFlag
	Function Returns     : void
	Function Arguments   : void
	Function Description : Raise flag by 1 when an error occurred
********************************************************************/
void setCountMinutes(void);
void setCheckTemp(void);
void setVoltModule(void);
void setOverHeating(void);
void setPoteinVal(void);
void setErrorFlag(void);

#endif /* SCHEDULER_H */
