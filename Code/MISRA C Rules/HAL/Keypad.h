#ifndef KEYPAD_H
#define KEYPAD_H

#include <avr/io.h>
#include <util/delay.h>
#include "../MCAL/DIO.h"
#include "../standard/std_macros.h"
#include "../standard/Basic_Types.h"

#define KEYPAD_PORT 'C'			/* KEYPAD on PORTC */
#define KEYPAD_PORTC PORTC		/* KEYPAD on PORTC */
#define KEYPAD_PINs PINC		/* KEYPAD PINC */
#define NOTPRESSED 0xff			/* No button pressed (High) */
#define N_Col 3					/* Number of Cols: 3 */
#define N_Row 4					/* Number of Rows: 4 */

/************************************************************************************
	Function Name        : keypad_vInit
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize Keypad PORT
************************************************************************************/
void keypad_vInit(void);

/************************************************************************************
	Function Name        : Keypad_u8Scan
	Function Returns     : u8
	Function Arguments   : void
	Function Description : Loop checks all Elements in Keypad (4 * 3)
************************************************************************************/
u8 Keypad_u8Scan(void);

/************************************************************************************
	Function Name        : getKey
	Function Returns     : u8
	Function Arguments   : void
	Function Description : Returns the pressed button
************************************************************************************/
u8 getKey(void);

#endif /* KEYPAD_H */
