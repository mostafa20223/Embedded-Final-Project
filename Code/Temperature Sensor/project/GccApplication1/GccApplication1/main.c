/*
 * GccApplication1.c
 *
 * Created: 6/6/2021 1:08:51 PM
 * Author : Lenovo
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "SPI.h"


int main(void)
{
 char msb,lsb;
    DDRC=0xFF;
 DDRD=0xFF;
 DDRA=0xFF;
 SPI_masterInit();
 TC72_Init();
 _delay_ms(150);
    while (1) 
    {
  
  PORTB|=(1<<4);
  /*Read the MSB*/
  SPI_masterTransmit(0x02);
  /*Issue one more clock frame
  to force data out*/
  SPI_masterTransmit(0x00);
  PORTB&=~(1<<4);
  
  _delay_ms(1);
  msb=SPI_masterReceive();
  
  PORTB|=(1<<4);
  /*Read The LSB*/
  SPI_masterTransmit(0x01);
  /*Issue one more clock frame
  to force data out*/
  SPI_masterTransmit(0x00);
  PORTB&=~(1<<4);
  
  _delay_ms(1);
  lsb=SPI_masterReceive();
  PORTA=lsb;
  displayTemperature(msb,lsb);
    }
}

