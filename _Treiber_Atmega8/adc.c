/*
 * adc.c
 *
 *  Created on: 20.03.2015
 *      Author: mrohner
 */

#include <avr/io.h>

void initADC(void) {									// select channel
		ADMUX |= ((1 << REFS1) | (1 << REFS0)); // internal 2.56V Voltage Reference
		ADCSRA = (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS2); // 64 bit Prescale
		//DIDR0 = 1<<channel;    								// disable DIO 0
}

unsigned int readADC(char channel) {
	unsigned char i;
	unsigned int value;
	value = 0;
	if (channel <= 7 && channel >= 0) {		// ADC 0-7
		ADMUX = ADMUX & 11110000;			// hintere 4 Bit löschen
		ADMUX = ADMUX | channel;			// hintere 4 Bit setzten

		ADCSRA |= (1 << ADEN);				// ADC eingeschaltet
		for (i = 0; i < 5; i++) {
			ADCSRA |= (1 << ADSC);        	// single conversion mode ein
			while (ADCSRA & (1 << ADSC)) {}	// Leer Schleife zum warten bis konvertierung abgeschlosen
//			value += ADCW;                	// Aufsummierung der samplewerte
			value += (unsigned short) ADCL+(unsigned short)(ADCH<<8); // Werte zwischen 0-1023
		}
		value /= 5;                     	// Aritmethisches Mittel der Samplewerte
	}
	return value;
}
