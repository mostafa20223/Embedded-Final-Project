#ifndef APP_H
#define APP_H

#define F_CPU 16000000UL /* 16 MHz Clock Speed */

#include <avr/io.h>
#include <util/delay.h>

#include "Basic_Types.h"
#include "DIO.h"
#include "LCD_config.h"
#include "LCD.h"
#include "Keypad.h"
#include "SPI.h"

void Welcome_Screen(void);
void IDLE_Screen(void);
void UsrGetVal(void);
void Start_Communication(void);

#endif /* APP_H */