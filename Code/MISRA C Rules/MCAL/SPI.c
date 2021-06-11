#include "SPI.h"

void SPI_masterInit(void)
{
	/* Enable MOSI, SCK and SS Output */
	DDRB = (1 << MOSI) | (1 << SCK) | (1 << SS);
	
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

void SPI_masterTransmit(c8 data)
{
	/* Start the Transmission */
	SPDR = data;
	
	/* Wait for Completion */
	while(!(SPSR & (1 << SPIF)));
}

c8 SPI_masterReceive(void)
{
	/* wait for the SPI buffer's full */
	while(!(SPSR & (1 << SPIF)));
	/* return SPI buffer */
	return SPDR;
}

void TC72_Init(void)
{
	SET_BIT(SPI_PORT, SS);
	/* Select control register */
	SPI_masterTransmit(0x80);
	
	/* Select Continuous temperature conversion */
	SPI_masterTransmit(0x40);
	CLR_BIT(SPI_PORT, SS);
	
	_delay_ms(150);
}