/*
 * pwm.c
 *
 *  Created on: 26.08.2015
 *      Author: matthias
 */

#include <util/delay.h>
#include <avr/io.h>
#include "io.h"
#include "def.h"

#define B 0
#define C 1
#define D 2

/*
 * pwmOut:  DDB1 (für OC1A)
 * 			DDB2 (für OC1B)
 */
void pwm_init() {
	DDRB |= (1 << DDB1);         //Ausgang an OC1A siehe Schema, LED an PB1 !!
	DDRB |= (1 << DDB2);

	TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1); //PMW-Phase Correkt-8-bit ,nicht invertierend
	TCCR1B = (1 << CS11);              						//Prescaler 8

	OCR1A = 0;										//Hightime auf Null setzten
	OCR1B = 0;
}

void pwm_update(char pwmOut, unsigned short hightime) {
	switch (pwmOut) {
	case 1:
		OCR1A = hightime;
		break;
	case 2:
		OCR1B = hightime;
		break;
	}
}

void pwm_vor(char portL, char pinL, char portR, char pinR) {
	io_on(portL, pinL);
	io_off(portR, pinR);
}

void pwm_rueck(char portL, char pinL, char portR, char pinR) {
	io_off(portL, pinL);
	io_on(portR, pinR);
}

void pwm_stop(char portL, char pinL, char portR, char pinR) {
	io_off(motor1_left_port, motor1_left_pin);
	io_off(motor1_right_port, motor1_right_pin);
}

void motor1stop() {
	io_off(motor1_left_port, motor1_left_pin);
	io_off(motor1_right_port, motor1_right_pin);
}

void motor1vor() {
	io_on(motor1_left_port, motor1_left_pin);
	io_off(motor1_right_port, motor1_right_pin);
}

void motor1rueck() {
	io_off(motor1_left_port, motor1_left_pin);
	io_on(motor1_right_port, motor1_right_pin);
}

void motor2stop() {
	io_off(motor2_left_port, motor2_left_pin);
	io_off(motor2_right_port, motor2_right_pin);
}

void motor2vor() {
	io_on(motor2_left_port, motor2_left_pin);
	io_off(motor2_right_port, motor2_right_pin);
}

void motor2rueck() {
	io_off(motor2_left_port, motor2_left_pin);
	io_on(motor2_right_port, motor2_right_pin);
}
