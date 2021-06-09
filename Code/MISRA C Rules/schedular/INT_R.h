#ifndef INT_R_H
#define INT_R_H

#include <avr/io.h>

#define GICR 0x5B
#define MCUCR 0x55

//#define SREG 0x5F
#define INTERRUPT 0x07

#define INT0 6
#define INT1 7
#define INT2 5

#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#endif /* INT_R_H */