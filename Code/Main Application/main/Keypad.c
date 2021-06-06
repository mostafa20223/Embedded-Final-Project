#include "Keypad.h"
#include "DIO.h"

static const uint8_t KEY_PINs[KEY_NPINs] = {0, 1, 2, 3, 4, 5, 6, 7};
static uint8_t counter1 = 0;
static uint8_t counter2 = 0;
const char arr[N_Row][N_Col] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'} };

void keypad_vInit(void)
{
	for (counter1 = 0; counter1 < KEY_NPINs - 4; ++counter1)
	{
		DIO_vsetPINDir(Keypad_PORT, counter1, 1);
	}
	for (counter2 = 4; counter2 < KEY_NPINs; ++counter2)
	{
		DIO_vsetPINDir(Keypad_PORT, counter2, 0);
	}
	DIO_vconnectpullup(Keypad_PORT, 4, 1);
	DIO_vconnectpullup(Keypad_PORT, 5, 1);
	DIO_vconnectpullup(Keypad_PORT, 6, 1);
	DIO_vconnectpullup(Keypad_PORT, 7, 1);
}

char keypad_u8check_press(void)
{
	char row = 0;
	char coloumn = 0;
	char x = 0;
	char returnval = NOTPRESSED;
	 
	for(row = 0; row < N_Row; ++row)
	{
		DIO_write(Keypad_PORT, 0, 1);
		DIO_write(Keypad_PORT, 1, 1);
		DIO_write(Keypad_PORT, 2, 1);
		DIO_write(Keypad_PORT, 3, 1);
		DIO_write(Keypad_PORT, row, 0);

		for(coloumn = 0; coloumn < N_Col; ++coloumn)
		{
			x = DIO_u8read(Keypad_PORT, (coloumn + N_Col));
		
			if (x == 0)
			{
				returnval = arr[row][coloumn];
				break;
			}  
		}
		
		if (x == 0)
		{
			break;
		}
	}
	
	return returnval;
}