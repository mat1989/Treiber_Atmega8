/*
 * num.h
 *
 *  Created on: 22.09.2015
 *      Author: matthias
 */

#include <avr/io.h>

#ifndef NUM_H_
#define NUM_H_

#define B 0
#define C 1
#define D 2

#define INPUT 	1
#define OUTPUT 	0

#define COL1_Port	B
#define COL1_Pin	PB0
#define COL2_Port	D
#define COL2_Pin	PD7
#define COL3_Port	D
#define COL3_Pin	PD6

#define ROW1_Port	C
#define ROW1_Pin	PC2
#define ROW2_Port	C
#define ROW2_Pin	PC3
#define ROW3_Port	C
#define ROW3_Pin	PC4
#define ROW4_Port	C
#define ROW4_Pin	PC5

char num_read_all(); 	//alle Taster werden abgefragt (Fehler: Wert = 12)
char num_read_10();		//nur Taste "*" wird abgefragt (Wert = 10)
char num_read_11();		//nur Taste "#" wird abgefragt (Wert = 11)
char num_read();		//nur Zahlen werden abgefragt

#endif /* NUM_H_ */
