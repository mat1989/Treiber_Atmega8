/*
 * num.c
 *
 *  Created on: 22.09.2015
 *      Author: matthias
 */

#include "io.h"
#include "num.h"

char num_read_all() {
	io_off(COL1_Port, COL1_Pin);
	io_on(COL2_Port, COL2_Pin);
	io_on(COL3_Port, COL3_Pin);
	if (io_read(ROW1_Port, ROW1_Pin)) {
		return 1;
	}
	if (io_read(ROW2_Port, ROW2_Pin)) {
		return 4;
	}
	if (io_read(ROW3_Port, ROW3_Pin)) {
		return 7;
	}
	if (io_read(ROW4_Port, ROW4_Pin)) { // *
		return 10;
	}

	io_on(COL1_Port, COL1_Pin);
	io_off(COL2_Port, COL2_Pin);
	io_on(COL3_Port, COL3_Pin);
	if (io_read(ROW1_Port, ROW1_Pin)) {
		return 2;
	}
	if (io_read(ROW2_Port, ROW2_Pin)) {
		return 5;
	}
	if (io_read(ROW3_Port, ROW3_Pin)) {
		return 8;
	}
	if (io_read(ROW4_Port, ROW4_Pin)) {
		return 0;
	}

	io_on(COL1_Port, COL1_Pin);
	io_on(COL2_Port, COL2_Pin);
	io_off(COL3_Port, COL3_Pin);
	if (io_read(ROW1_Port, ROW1_Pin)) {
		return 3;
	}
	if (io_read(ROW2_Port, ROW2_Pin)) {
		return 6;
	}
	if (io_read(ROW3_Port, ROW3_Pin)) {
		return 9;
	}
	if (io_read(ROW4_Port, ROW4_Pin)) { // #
		return 11;
	}
	return 12; //Fehler
}

char num_read_10() {
	io_off(COL1_Port, COL1_Pin);
	io_on(COL2_Port, COL2_Pin);
	io_on(COL3_Port, COL3_Pin);
	if (io_read(ROW4_Port, ROW4_Pin)) { // *
		return 10;
	}
	return 12; //Fehler
}

char num_read_11() {
	io_on(COL1_Port, COL1_Pin);
	io_on(COL2_Port, COL2_Pin);
	io_off(COL3_Port, COL3_Pin);
	if (io_read(ROW4_Port, ROW4_Pin)) { // #
		return 11;
	}
	return 12; //Fehler
}

char num_read() {
	io_off(COL1_Port, COL1_Pin);
	io_on(COL2_Port, COL2_Pin);
	io_on(COL3_Port, COL3_Pin);
	if (io_read(ROW1_Port, ROW1_Pin)) {
		return 1;
	}
	if (io_read(ROW2_Port, ROW2_Pin)) {
		return 4;
	}
	if (io_read(ROW3_Port, ROW3_Pin)) {
		return 7;
	}

	io_on(COL1_Port, COL1_Pin);
	io_off(COL2_Port, COL2_Pin);
	io_on(COL3_Port, COL3_Pin);
	if (io_read(ROW1_Port, ROW1_Pin)) {
		return 2;
	}
	if (io_read(ROW2_Port, ROW2_Pin)) {
		return 5;
	}
	if (io_read(ROW3_Port, ROW3_Pin)) {
		return 8;
	}
	if (io_read(ROW4_Port, ROW4_Pin)) {
		return 0;
	}

	io_on(COL1_Port, COL1_Pin);
	io_on(COL2_Port, COL2_Pin);
	io_off(COL3_Port, COL3_Pin);
	if (io_read(ROW1_Port, ROW1_Pin)) {
		return 3;
	}
	if (io_read(ROW2_Port, ROW2_Pin)) {
		return 6;
	}
	if (io_read(ROW3_Port, ROW3_Pin)) {
		return 9;
	}
	return 12; //Fehler
}
