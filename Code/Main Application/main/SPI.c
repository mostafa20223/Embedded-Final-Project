#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "std_macros.h"
#include "Basic_Types.h"
#include "DIO.h"
#include "SPI.h"

/* Enable MOSI, SCK and SS Output */
static const u8 SPI_PINs[SPI_NPINs] = {4, 5, 7};
static u8 counter = 0;

void SPI_masterInit(void)
{
	/* Enable MOSI, SCK and SS Output */
	//for (counter = 0; counter < SPI_NPINs; ++counter)
	//{
		//DIO_vsetPINDir(SPI_PORT, SPI_PINs[counter], 0xff);
	//}
	
	DDRB = (1 << 7) | (1 << 5) | (1 << 4);
	
	/* Enable Master Mode */
	SET_BIT(SPCR, MSTR);
	/* Set clock to fosc/16*/
	SET_BIT(SPCR, SPR0);
	SET_BIT(SPCR, SPR1);
	SET_BIT(SPCR, CPHA);
	/* Enable SPI */
	SET_BIT(SPCR, SPE);
	/* Enable interrupt */
	SET_BIT(SPCR, SPIE);
}

void SPI_masterTransmit(char data)
{	
	/* Start the Transmission */
	SPDR = data;
	
	/* Wait for Completion */
	while(!(SPSR & (1 << SPIF)));
}

char SPI_masterReceive(void)
{	
	/* wait for the SPI buffer's full */
	while(!(SPSR & (1 << SPIF)));
	/* return SPI buffer */
	return SPDR;
}

void TC72_Init(void)
{	
	SET_BIT(PORTB, 4);
	/* Select control register */
	SPI_masterTransmit(0x80);
	
	/* Select Continuous temperature conversion */
	SPI_masterTransmit(0x04);
	CLR_BIT(PORTB, 4);
	
	_delay_ms(150);
}