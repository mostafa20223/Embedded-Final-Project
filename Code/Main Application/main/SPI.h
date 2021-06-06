#ifndef SPI_H
#define SPI_H

#define SPI_PORT 'B'

void SPI_masterInit(void);
char SPI_masterReceive(void);
void SPI_masterTransmit(char);
void TC72_Init(void);
void Start_Communication(void);

#endif /* SPI_H */