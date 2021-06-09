#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <avr/io.h>

// FLAGS setter
void setCountMinutes(void);
void setCheckTemp(void);
void setVoltModule(void);
void setOverHeating(void);

// FLAG clearer
void clearCountMinutes(void);
void clearCheckTemp(void);
void clearVoltModule(void);
void clearOverHeating(void);

void schedule(void);

#endif
