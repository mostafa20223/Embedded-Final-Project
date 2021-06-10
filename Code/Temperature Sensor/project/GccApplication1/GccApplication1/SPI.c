/*
 * SPI.c
 *
 * Created: 6/6/2021 1:17:59 PM
 *  Author: Lenovo
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define SET_BIT(reg,bit)    reg|=(1<<bit)
#define CLR_BIT(reg,bit)    reg&=(~(1<<bit))
#include <util/delay.h>


void SPI_masterInit(void){
	
	/*  Enable MOSI, SCK and SS output */
	DDRB = (1<<7)|(1<<5)|(1<<4);
	
	/* Enable Master Mode */
	SET_BIT(SPCR,MSTR);
	/* Set clock to fosc/16*/
	SET_BIT(SPCR,SPR0);
	SET_BIT(SPCR,SPR1);
	SET_BIT(SPCR,CPHA);
	/* Enable SPI */
	SET_BIT(SPCR,SPE);
	/* Enable interrupt */
	SET_BIT(SPCR,SPIE);
	

}

void SPI_masterTransmit(char data){
	
	/* Start the transmission */
	SPDR = data;
	
	/* Wait for completion */
	while(!(SPSR&(1<<SPIF)));
	
}

char SPI_masterReceive(void){
	
	/* wait for the SPI buffer's full */
	while(!(SPSR&(1<<SPIF)));
	/* return SPI buffer */
	return SPDR;
	
	
}

void displayTemperature(char msb,char lsb){
	char ssd[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,
	0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
	char sign;
	lsb>>=6;

	if(msb&0x80) {
		msb=(~msb)+1;
		sign=1;
		if(lsb!=0) lsb=75/lsb;
	}
	else {
		sign=0;
		lsb*=25;
	}

	PORTD=0x00;
	if(sign==1) PORTC=0x40;
	else if(msb>=100) PORTC=ssd[msb/100];
	else PORTC=0x00;
	PORTD=(1<<0);
	_delay_ms(5);
	
	PORTD=0x00;
	if(msb>=10)
	PORTC=ssd[(msb%100)/10];
	else PORTC=0;
	PORTD=(1<<1);
	_delay_ms(5);

	PORTD=0x00;
	PORTC=ssd[msb%10]|0x80;
	PORTD=(1<<2);
	_delay_ms(5);

	PORTD=0x00;
	PORTC=ssd[lsb/10];
	PORTD=(1<<3);
	_delay_ms(5);

	PORTD=0x00;
	PORTC=ssd[lsb%10];
	PORTD=(1<<4);
	_delay_ms(5);

	PORTD=0x00;
	PORTC=0x63;
	PORTD=(1<<5);
	_delay_ms(5);

	PORTD=0x00;
	PORTC=ssd[12];
	PORTD=(1<<6);
	_delay_ms(5);
}


void TC72_Init(void){
	
	SET_BIT(PORTB,4);
	/* Select control register */
	SPI_masterTransmit(0x80);
	
	/* Select Continous temperature conversion */
	SPI_masterTransmit(0x04);
	CLR_BIT(PORTB,4);
	
	_delay_ms(150);
	
}