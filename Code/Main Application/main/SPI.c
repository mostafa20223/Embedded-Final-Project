#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "std_macros.h"
#include "Basic_Types.h"
#include "DIO.h"
#include "SPI.h"

/* Enable MOSI, SCK and SS Output */
static const char SPI_PINs[3] = {4, 5, 7};
static uint8_t counter = 0;

void SPI_masterInit(void)
{
	/* Enable MOSI, SCK and SS Output */
	for (counter = 0; counter < 3; ++counter)
	{
		DIO_vsetPINDir(SPI_PORT, counter, 1);
	}
	
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
	while(!(SPSR &(1 << SPIF)));
}

char SPI_masterReceive(void)
{	
	/* wait for the SPI buffer's full */
	while(!(SPSR &(1 << SPIF)));
	/* return SPI buffer */
	return SPDR;
}

void TC72_Init(void)
{	
	SET_BIT(PORTB, 4);
	/* Select control register */
	SPI_masterTransmit(0x80);
	
	/* Select Continous temperature conversion */
	SPI_masterTransmit(0x04);
	CLR_BIT(PORTB, 4);
	
	_delay_ms(150);
}

void Start_Communication(void)
{
	DIO_set_port_direction('A', 0xFF);
	DIO_set_port_direction('D', 0xFF);
	DIO_set_port_direction('C', 0xFF);

	char msb = 0;
	char lsb = 0;

	SPI_masterInit();
	TC72_Init();
	_delay_ms(150);

	while (1)
	{
		PORTB |= (1 << 4);
		/* Read the MSB */
		SPI_masterTransmit(0x02);
		/* Issue one more clock frame to force data out */
		SPI_masterTransmit(0x00);
		PORTB &= ~(1 << 4);
		_delay_ms(1);
		msb = SPI_masterReceive();
		PORTB|=(1<<4);
		/* Read The LSB */
		SPI_masterTransmit(0x01);
		/* Issue one more clock frame to force data out */
		SPI_masterTransmit(0x00);
		PORTB &= ~(1 << 4);
		_delay_ms(1);
		lsb = SPI_masterReceive();
		PORTA = lsb;
	}
}