/*
 * io.h
 *
 *  Created on: 23.08.2015
 *      Author: admin
 */

#ifndef IO_H_
#define IO_H_

#define b 0
#define c 1
#define d 2

#define INPUT 1
#define OUTPUT 0

/*
 * Port: 	0->b 1->c 2->d
 * Pin: 	0-7
 * Modus:	1->Input 0->Output
 */
void io_init(char port, char pin, char modus) ;

/*
 * Im Output Modus, um Pins auszulesen
 */
char io_read(char port, char pin);

/*
 * Output on
 */
void io_on(char port, char pin);

/*
 * Output off
 */
void io_off(char port, char pin);

/*
 * Output toggle
 */
void io_toggle(char port, char pin);

#endif /* IO_H_ */
