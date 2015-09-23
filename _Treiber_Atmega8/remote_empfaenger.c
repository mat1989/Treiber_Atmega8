/*
 * remote_empfaenger.c
 *
 *  Created on: 16.08.2015
 *      Author: admin
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 4000000							//define cpu clock speed if not defined
#endif

#define BAUDRATE 1200							//set desired baud rate
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)		//calculate UBRR value

//define receive parameters
#define SYNC 0XAA// synchro signal

void USART_Init(void){
	//Set baud rate
	UBRRL = (uint8_t) UBRRVAL;		//low byte
	UBRRH = (UBRRVAL >> 8);			//high byte
	//Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size
	UCSRC = (1 << URSEL) | (0 << UMSEL) | (0 << UPM1) | (0 << UPM0)
			| (0 << USBS) | (0 << UCSZ2) | (1 << UCSZ1) | (1 << UCSZ0);
	//Enable Transmitter and Receiver and Interrupt on receive complete
	UCSRB = (1 << RXEN) | (1 << RXCIE);	//|(1<<TXEN);
	//enable global interrupts
}

uint8_t USART_vReceiveByte(void) {
	// Wait until a byte has been received
	while ((UCSRA & (1 << RXC)) == 0)
		;
	// Return received data
	return UDR;
}
