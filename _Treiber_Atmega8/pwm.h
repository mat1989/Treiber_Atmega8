/*
 * pwm.h
 *
 *  Created on: 26.08.2015
 *      Author: matthias
 */

#ifndef PWM_H_
#define PWM_H_

void pwm_init();
void pwm_update(char pwmOut, unsigned short hightime);

void pwm_vor(char portL, char pinL, char portR, char pinR);
void pwm_rueck(char portL, char pinL, char portR, char pinR);
void pwm_stop(char portL, char pinL, char portR, char pinR);

void motor1stop();
void motor1vor();
void motor1rueck();

void motor2stop();
void motor2vor();
void motor2rueck();


#endif /* PWM_H_ */
