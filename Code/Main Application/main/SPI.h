#ifndef SPI_H
#define SPI_H

#include "Basic_Types.h"

#define SPI_PORT 'B'
#define SPI_NPINs 3
#define MISO PINB6
#define MOSI PINB5
#define SCK PINB7
#define SS PINB4

void SPI_masterInit(void);
char SPI_masterReceive(void);
void SPI_masterTransmit(char);
void TC72_Init(void);
void displayTemperature(c8 msb, c8 lsb);

#endif /* SPI_H */