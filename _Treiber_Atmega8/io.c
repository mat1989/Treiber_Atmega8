/*
 * io.c
 *
 *  Created on: 23.08.2015
 *      Author: admin
 */

#include <avr/io.h>

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
void io_init(char port, char pin, char modus) {
	if (modus) {
		switch (port) { //Switch (Input)
		case b:
			DDRB = DDRB & ~(1 << pin);
			PORTB |= (1 << pin);                   //Interne Pull-Up einschalten
			break;
		case c:
			DDRC = DDRC & ~(1 << pin);
			PORTC |= (1 << pin);
			break;
		case d:
			DDRD = DDRD & ~(1 << pin);
			PORTD |= (1 << pin);
			break;
		}
	} else {
		switch (port) { // LED (Output)
		case b:
			DDRB |= (1 << pin);
			break;
		case c:
			DDRC |= (1 << pin);
			break;
		case d:
			DDRD |= (1 << pin);
			break;
		}
	}

}

/*
 * Im Output Modus, um Pins auszulesen
 */
char io_read(char port, char pin) {
	switch (port) {
	case b:
		if ((PINB & (1 << pin)) == 0) {
			return 1;
		} else {
			return 0;
		}
		break;
	case c:
		if ((PINC & (1 << pin)) == 0) {
			return 1;
		} else {
			return 0;
		}
		break;
	case d:
		if ((PIND & (1 << pin)) == 0) {
			return 1;
		} else {
			return 0;
		}
		break;
	}
	return 0;
}

/*
 * Output on
 */
void io_on(char port, char pin) {
	switch (port) {
	case b:
		PORTB |= (1 << pin);
		break;
	case c:
		PORTC |= (1 << pin);
		break;
	case d:
		PORTD |= (1 << pin);
		break;
	}
}

/*
 * Output off
 */
void io_off(char port, char pin) {
	switch (port) {
	case b:
		PORTB &= ~(1 << pin);
		break;
	case c:
		PORTC &= ~(1 << pin);
		break;
	case d:
		PORTD &= ~(1 << pin);
		break;
	}
}

/*
 * Output toggle
 */
void io_toggle(char port, char pin) {
	switch (port) {
	case b:
		PORTB ^= (1 << pin);
		break;
	case c:
		PORTC ^= (1 << pin);
		break;
	case d:
		PORTD ^= (1 << pin);
		break;
	}
}
