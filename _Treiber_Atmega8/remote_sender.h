/*
 * remote_sender.h
 *
 *  Created on: 16.08.2015
 *      Author: admin
 */

#ifndef REMOTE_SENDER_H_
#define REMOTE_SENDER_H_

void USART_Init(void);

void USART_vSendByte(uint8_t u8Data);

void Send_Packet(uint8_t addr, uint8_t cmd);

void delayms(uint8_t t);	//delay in ms


#endif /* REMOTE_SENDER_H_ */
