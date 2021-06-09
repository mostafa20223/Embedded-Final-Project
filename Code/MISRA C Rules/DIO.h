#ifndef DIO_H
#define DIO_H

#include "Basic_Types.h"

/*
	Function Name        : DIO_vsetPINDir
	Function Returns     : void
	Function Arguments   : u8 portname, u8 pinnumber, u8 direction
	Function Description : Set the direction of the given pin in the given port (direction 0 = input : 1 = output)
*/
void DIO_vsetPINDir(u8 portname, u8 pinnumber, u8 direction);

/*
	Function Name        : DIO_write
	Function Returns     : void
	Function Arguments   : u8 portname, u8 pinnumber, u8 outputvalue
	Function Description : Set the value of the given pin in the given port (outputvalue 0 = low : 1 = high) 
*/
void DIO_write(u8 portname, u8 pinnumber, u8 outputvalue);

/*
	Function Name        : DIO_u8read
	Function Returns     : u8
	Function Arguments   : u8 portname, u8 pinnumber
	Function Description : Returns 1 if the value of the given pin is high and zero if the value is low
*/
u8 DIO_u8read(u8 portname, u8 pinnumber);

/*
	Function Name        : DIO_toggle
	Function Returns     : void
	Function Arguments   : u8 portname, u8 pinnumber
	Function Description : Reverse the value of the given pin in the given port.
*/
void DIO_toggle(u8 portname, u8 pinnumber);

/*
	Function Name        : DIO_set_port_direction
	Function Returns     : void
	Function Arguments   : u8 portname, u8 direction
	Function Description : set the direction of whole port
*/
void DIO_set_port_direction(u8 portname, u8 direction);

/*
	Function Name        : DIO_write_port
	Function Returns     : void
	Function Arguments   : u8 portname, u8 portvalue
	Function Description : Write the value to all port pins.
*/
void DIO_write_port(u8 portname, u8 portvalue);

/*
	Function Name        : DIO_read_port
	Function Returns     : u8
	Function Arguments   : u8 portname
	Function Description : read the value of the port .
*/
u8 DIO_read_port(u8 portname);

/*
	Function Name        : DIO_vconnectpullup
	Function Returns     : void
	Function Arguments   : char portname ,char pinnumber, char connect_pullup
	Function Description : Connect and disconnect pull up resistor to the given pin at the given port 
*/
void DIO_vconnectpullup(char portname ,char pinnumber, char connect_pullup);

/*
	Function Name        : write_low_nibble
	Function Returns     : void
	Function Arguments   : u8 portname, u8 value
	Function Description : write a value to the low nibble of the port 
*/
void write_low_nibble(u8 portname, u8 value);

/*
	Function Name        : write_high_nibble
	Function Returns     : void
	Function Arguments   : u8 portname, u8 value
	Function Description : write a value to the high nibble of the port 
*/
void write_high_nibble(u8 portname, u8 value);

#endif /* DIO_H */

