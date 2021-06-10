#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include "Scheduler.h"
#include "../standard/Basic_Types.h"

/********************************************************************
	Function Name        : setState
	Function Returns     : void
	Function Arguments   : void
	Function Description : Determine which state will be evaluated
********************************************************************/
void setState(void);

/********************************************************************
	Function Name        : setErrorFlag
	Function Returns     : void
	Function Arguments   : void
	Function Description : Raise flag by 1 when an error occurred
********************************************************************/
void setErrorFlag(void);

#endif /* SYSTEMSTATE_H */