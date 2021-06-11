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
	DIO_set_port_direction(KEYPAD_PORT, 0x0f);
	CLR_BIT(SFIOR, PUD);
	DIO_write_port(KEYPAD_PORT, 0xff);
}

u8 Keypad_u8Scan(void)
{
	u8 row = 0;
	u8 column = 0;
	u8 scan = 0;
	u8 buttonPressed = 0;

	for(row = 0; row < N_Row; ++row)
	{
		KEYPAD_PORTC |= 0x0f;
		CLR_BIT(KEYPAD_PORTC, row);
		
		for(column = 4; column < (N_Row + N_Col); ++column)
		{
			scan = READ_BIT(KEYPAD_PINs, column);
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
	while (Keypad_u8Scan() != 0)
	{
		_delay_ms(10);
		//key = 0;
	}

	/* Wait for new key press */
	do
	{
		key = Keypad_u8Scan();

	} while(key == 0);

	return key;
}