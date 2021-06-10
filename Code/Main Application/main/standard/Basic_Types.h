#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************* Global Types ********************************/
/*
	Type name: c8
	Type Description: char type
	Type Range: 0 .. 255
*/
typedef char c8;

/*
	Type name: u8
	Type Description: unsigned char type
	Type Range: 0 .. 255
*/
typedef unsigned char u8;

/*
	Type name: u16
	Type Description: unsigned short int type
	Type Range: 0 .. 65535
*/
typedef unsigned short int u16;

/*
	Type name: u32
	Type Description: unsigned long int type
	Type Range: 0 .. 4294967295
*/
typedef unsigned long int u32;

/*
	Type name: float64_t
	Type Description: double type
	Type Range: 0 .. 1.844e^19
*/
typedef double float64_t;

#endif /* BASIC_TYPES_H */
