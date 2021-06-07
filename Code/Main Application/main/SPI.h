#ifndef SPI_H
#define SPI_H

#define SPI_PORT 'B'
#define SPI_NPINs 3

void SPI_masterInit(void);
char SPI_masterReceive(void);
void SPI_masterTransmit(char);
void TC72_Init(void);

#endif /* SPI_H */