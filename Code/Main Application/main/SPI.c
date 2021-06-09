#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "std_macros.h"
#include "DIO.h"
#include "SPI.h"
#include "LCD.h"

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

void displayTemperature(c8 msb, c8 lsb)
{
	c8 ssd[16] = {0x3f, 0x06, 0x5B, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
	c8 sign;
	lsb = lsb >> 6;
	c8 TempVal = 0;

	if(msb & 0x80)
	{
		msb = (~msb) + 1;
		sign = 1;
		if(lsb != 0)
		{
			lsb = (75 / lsb);
		}
		else
		{
			/* Do nothing */
		}
	}
	else
	{
		sign = 0;
		lsb = (lsb * 25);
	}

	if(sign == 1)
	{
		TempVal = 0x40;
	}
	else if(msb >= 100)
	{
		TempVal = ssd[msb / 100];
	}
	else
	{
		TempVal = 0x00;
	}
	_delay_ms(5);
	
	if(msb >= 10)
	{
		TempVal = ssd[(msb % 100) / 10];
	}
	else
	{
		TempVal = 0;
	}
	_delay_ms(5);

	TempVal = ssd[msb % 10] | 0x80;
	_delay_ms(5);

	TempVal = ssd[lsb / 10];
	_delay_ms(5);

	TempVal = ssd[lsb % 10];
	_delay_ms(5);

	TempVal = 0x63;
	_delay_ms(5);

	TempVal = ssd[12];
	_delay_ms(5);
	
	LCD_vSend_char(ssd[msb / 100]);
}