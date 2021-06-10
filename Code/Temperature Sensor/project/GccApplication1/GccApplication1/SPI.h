/*
 * SPI.h
 *
 * Created: 6/6/2021 1:18:27 PM
 *  Author: Lenovo
 */ 


#ifndef SPI_H_
#define SPI_H_




void SPI_masterInit(void);
char SPI_masterReceive(void);
void SPI_masterTransmit(char );

void TC72_Init(void);

void displayTemperature(char msb,char lsb);
#endif /* SPI_H_ */