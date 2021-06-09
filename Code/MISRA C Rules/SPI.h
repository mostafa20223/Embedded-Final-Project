#ifndef SPI_H
#define SPI_H

#include "Basic_Types.h"

#define SPI_PORT 'B'
#define SPI_NPINs 3
#define MISO PINB6
#define MOSI PINB5
#define SCK PINB7
#define SS PINB4

/*
	Function Name        : SPI_masterInit
	Function Returns     : void
	Function Arguments   : void
	Function Description : Function Initiator for (4 * 3) Keypad on PORTC
*/
void SPI_masterInit(void);

/*
	Function Name        : SPI_masterReceive
	Function Returns     : void
	Function Arguments   : void
	Function Description : Function Initiator for (4 * 3) Keypad on PORTC
*/
char SPI_masterReceive(void);

/*
	Function Name        : SPI_masterTransmit
	Function Returns     : void
	Function Arguments   : void
	Function Description : Function Initiator for (4 * 3) Keypad on PORTC
*/
void SPI_masterTransmit(char);

/*
	Function Name        : TC72_Init
	Function Returns     : void
	Function Arguments   : void
	Function Description : Function Initiator for (4 * 3) Keypad on PORTC
*/
void TC72_Init(void);

/*
	Function Name        : displayTemperature
	Function Returns     : c8
	Function Arguments   : c8 msb, c8 lsb
	Function Description : Function Initiator for (4 * 3) Keypad on PORTC
*/
c8 displayTemperature(c8 msb, c8 lsb);

#endif /* SPI_H */