#ifndef KEYPAD_H
#define KEYPAD_H

#include <avr/io.h>

#define KEY_NPINs 8
#define Keypad_PORT 'C'
#define NOTPRESSED 0xFF
#define N_Col 3
#define N_Row 4

void keypad_vInit(void);
char keypad_u8check_press(void);

#endif /* KEYPAD_H */