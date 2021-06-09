#include <avr/io.h>
#include <util/delay.h>
#include "../MCAL/DIO.h"
#include "../standard/std_macros.h"
#include "Keypad.h"

static const u8 kp[N_Row][N_Col] =
{
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'},
	{'*', '0', '#'}
};

void keypad_vInit(void)
{
	DDRC = 0x0f;
	CLR_BIT(SFIOR, PUD);
	PORTC = 0xff;
}

u8 Keypad_u8Scan(void)
{
	u8 row = 0;
	u8 column = 0;
	u8 scan = 0;
	u8 buttonPressed = 0;

	for(row = 0; row < N_Row; ++row)
	{
		PORTC |= 0x0f;
		CLR_BIT(PORTC, row);
		for(column = 4; column < (N_Row + N_Col); ++column)
		{
			scan = READ_BIT(PINC, column);
			if(scan == 0)
			{
				buttonPressed = kp[row][column - 4];
			}
		}
	}
	
	return buttonPressed;
}

u8 getKey(void)
{
	u8 key = 0;

	/* Wait for key release if pressed on entry */
	while(Keypad_u8Scan() != 0)
	{
		_delay_ms(10);
	}

	/* Wait for new key press */
	do
	{
		key = Keypad_u8Scan();

	} while(key == 0);

	return key;
}