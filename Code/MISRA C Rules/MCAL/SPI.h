#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../standard/std_macros.h"
#include "../standard/Basic_Types.h"

#define SPI_PORT PORTB	/* PORTB is for SPI communication */
#define MISO 6			/* MISO PINB6 on PORTB */
#define MOSI 5			/* MOSI PINB5 on PORTB */
#define SCK 7			/* SCK PINB7 on PORTB */
#define SS 4			/* SS PINB4 on PORTB */

/******************************************************************
	Function Name        : SPI_masterInit
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize SPI serial communication
******************************************************************/
void SPI_masterInit(void);

/******************************************************************
	Function Name        : SPI_masterReceive
	Function Returns     : c8
	Function Arguments   : void
	Function Description : Initialize master to receive
******************************************************************/
c8 SPI_masterReceive(void);

/******************************************************************
	Function Name        : SPI_masterTransmit
	Function Returns     : void
	Function Arguments   : c8
	Function Description : Initialize master to transmit
******************************************************************/
void SPI_masterTransmit(c8);

/******************************************************************
	Function Name        : TC72_Init
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize communication with TC72
******************************************************************/
void TC72_Init(void);

#endif /* SPI_H */