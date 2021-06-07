#include "DIO.h"
#include "Keypad.h"

static const u8 OUT_PINs[N_Row] = {0, 1, 2, 3};
static const u8 IN_PINs[N_Col] = {4, 5, 6};
static const u8 kp[N_Row][N_Col] =
{
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'},
	{'*', '0', '#'}
};
static u8 counter1 = 0;
static u8 counter2 = 4;

void keypad_vInit(void)
{
	//for (counter1 = 0; counter1 < sizeof(OUT_PINs); ++counter1)
	//{
		//// Set Output Pins
		//DIO_vsetPINDir(Keypad_PORT, OUT_PINs[counter1], 1);
	//}
	//for (counter2 = 4; counter2 < sizeof(IN_PINs); ++counter2)
	//{
		//// Set Input
		//DIO_vsetPINDir(Keypad_PORT, IN_PINs[counter2], 0);
		//// Pull Up
		//DIO_vconnectpullup(Keypad_PORT, IN_PINs[counter2], 1);
	//}
	// Set Output Pins
	DIO_vsetPINDir(Keypad_PORT, 0, 1);
	DIO_vsetPINDir(Keypad_PORT, 1, 1);
	DIO_vsetPINDir(Keypad_PORT, 2, 1);
	DIO_vsetPINDir(Keypad_PORT, 3, 1);
	 
	// Set Input
	DIO_vsetPINDir(Keypad_PORT, 4, 0);
	DIO_vsetPINDir(Keypad_PORT, 5, 0);
	DIO_vsetPINDir(Keypad_PORT, 6, 0);
	 
	// Pull Up
	DIO_vconnectpullup(Keypad_PORT, 4, 1);
	DIO_vconnectpullup(Keypad_PORT, 5, 1);
	DIO_vconnectpullup(Keypad_PORT, 6, 1);
}

u8 keypad_u8check_press(void)
{
	u8 row;
	u8 coloumn; 
	u8 x;
	u8 returnval = NOTPRESSED;
	 
	/* Matrix Loop Check for each Keypad Element */
	for(row = 0; row < N_Row; ++row)
	{
		//for (counter1 = 0; counter1 < sizeof(OUT_PINs); ++counter1)
		//{
			///* Set Output Pins */
			//DIO_write(Keypad_PORT, OUT_PINs[counter1], 1);
		//}
		// Set Output Pins HIGH
		DIO_write(Keypad_PORT, 0, 1);
		DIO_write(Keypad_PORT, 1, 1);
		DIO_write(Keypad_PORT, 2, 1);
		DIO_write(Keypad_PORT, 3, 1);

		/* Send Signal LOW */
		DIO_write(Keypad_PORT, row, 0);
		 
		for(coloumn = 0; coloumn < N_Col; ++coloumn)
		{
			/* Read Sent Signal */ 	 
			x = DIO_u8read(Keypad_PORT, (coloumn + N_Row));
			 
			/* Button Pressed */
			if(x == 0)
			{
				returnval = kp[row][coloumn];
				break;
			}
			else
			{
				/* Current Element is not Pressed */
			}
		}		
		/* Break Higher Loop */
		if(x == 0)
		{
			break;
		}
		else
		{
			/* Do Nothing */
		}
	}
	
	/* Return Pressed Key */
	return returnval;	 
}

u8 check_OPKey(void)
{
	char val;
	u8 pressed = 0;

	//for (counter1 = 0; counter1 < sizeof(OUT_PINs) - 1; ++counter1)
	//{
		///* Read signal from a row */
		//DIO_write(Keypad_PORT, OUT_PINs[counter1], 1);
	//}
//
	//DIO_write(Keypad_PORT, OUT_PINs[sizeof(OUT_PINs) - 1], 1);
	
	// Send Signal in Specified Cow
	DIO_write(Keypad_PORT, 0, 1);
	DIO_write(Keypad_PORT, 1, 1);
	DIO_write(Keypad_PORT, 2, 1);
	DIO_write(Keypad_PORT, 3, 0);
	
	// Read from Specified Column
	val = DIO_u8read(Keypad_PORT, 6);
	
	if (val == 0)
	{
		pressed = 1;
	}
	else
	{
		/* Do Nothing ('#' is not pressed) */
	}
	
	return pressed;
}