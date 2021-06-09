#ifndef KEYPAD_H
#define KEYPAD_H

#include "Basic_Types.h"

#define KEY_NPINs 7
#define Keypad_PORT 'C'
#define NOTPRESSED 0xff
#define N_Col 3
#define N_Row 4

/*
	Function Name        : keypad_vInit
	Function Returns     : void
	Function Arguments   : void
	Function Description : Function Initiator for (4 * 3) Keypad on PORTC
*/
void keypad_vInit(void);

/*
	Function Name        : keypad_u8check_press
	Function Returns     : uint8_t
	Function Arguments   : void
	Function Description : Matrix Loop Function that checks all Elements in the Keypad Matrix (4*3) and Return the Pressed Element
*/
u8 keypad_u8check_press(void);

/*
	Function Name        : check_OPKey
	Function Returns     : uint8_t
	Function Arguments   : void
	Function Description : Returns 1 if the '#' Key is Pressed and 0 if not
*/
u8 check_OPKey(void);

u8 Keypad_u8Scan(void);
u8 getKey(void);

#endif /* KEYPAD_H */
