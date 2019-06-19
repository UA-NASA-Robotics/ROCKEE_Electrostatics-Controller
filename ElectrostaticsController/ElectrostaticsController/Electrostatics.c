/*
 * Electrostatics.c
 *
 * Created: 4/21/2018 2:15:17 PM
 *  Author: reed
 */ 

#include "Electrostatics.h"
#include "Timer.h"
#include "LEDs.h"

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define  INA1 3
#define  INA2 3
#define  INB1 2
#define  INB2 2
#define  RESET1 0
#define  RESET2 0
#define  RESTART1 1
#define  RESTART2 1
#define  HVENABLE 4

#define  FAULT1_1 6 //portE
#define  FAULT1_2 7 //portE
#define  FAULT2_1 2 //portD
#define  FAULT2_2 3 //portD

#ifndef F_CPU
	#define  F_CPU 16000000
#endif
//#define enableDeadTime
#define deadTime 100 //us

#define toggleSpeed 10 //hz

#define ENABLEHV 4

char state = -1;
char faultStatus = 0; 

timer_t toggleTimer;

void initializeHBridge() {
	PORTC |= (1<<INB2); //INB2 high
	PORTA |= (1<<INB1); //INB1 high
	PORTA &= ~(1<<INA1); //turn off A1
	PORTC &= ~(1<<INA2); //turn off A2
	
	//reset on boot
	PORTC |= (1<<RESET2); 
	PORTA |= (1<<RESET1);
	_delay_ms(50);
	PORTA &= ~(1<<RESET1); 
	PORTC &= ~(1<<RESET2); 
	
	//restart on boot
	PORTC |= (1<<RESTART2);
	PORTA |= (1<<RESTART1);
	_delay_ms(50);
	PORTA &= ~(1<<RESTART1);
	PORTC &= ~(1<<RESTART2);
	
	unsigned long us = 500000/toggleSpeed;
	setTimerIntervalandFunction(&toggleTimer, us, &toggleHBridge);
}

char getState() {
	return state;
}

void beginHBridgeToggle() {
	state = 0; 
}

void stopBridgeToggle() {
	state = -1; 
	PORTA &= ~(1<<INA1); //turn off A1
	PORTC &= ~(1<<INA2); //turn off A2
}
void enableHV() {
	PORTB |= (1<<ENABLEHV); //enable HV
}

void disableHV() {
	PORTB &= ~(1<<ENABLEHV); 	
}
	
void faultReset() {
	PORTC |= (1<<RESET2); //RESET2 high
	PORTA |= (1<<RESET1); //RESET1 high
	_delay_us(10);
	PORTA &= ~(1<<RESET1); //turn off RESET1
	PORTC &= ~(1<<RESET2); //turn off RESET2
}
	
void restartHbridge() {
	PORTC |= (1<<RESTART2); //RESTART2 high
	PORTA |= (1<<RESTART1); //RESTART1 high
	_delay_us(10);
	PORTA &= ~(1<<RESTART1); //turn off RESTART1
	PORTC &= ~(1<<RESTART2); //turn off RESTART2
}

int checkFault() {
	bool fault1_1 = PINE & (1<<FAULT1_1);
	bool fault1_2 = PINE & (1<<FAULT1_2);
	bool fault2_1 = PIND & (1<<FAULT2_1);
	bool fault2_2 = PIND & (1<<FAULT2_2);
	
	if(fault1_1 || fault1_2 || fault2_1 || fault2_2) { //if there are any faults
		TIMSK0 = (0<<TOIE0); //disable timer overflow interrupt, effectively stopping toggling of pins
		PORTC &= ~(1<<INB2); //INB2 off
		PORTA &= ~(1<<INB1); //INB1 off
		PORTA &= ~(1<<INA1); //turn off A1
		PORTC &= ~(1<<INA2); //turn off A2
		
		setLED(LED4,fault1_1);
		setLED(LED5,fault1_2);
		setLED(LED6,fault2_1);
		setLED(LED7,fault2_2);
	}
	faultStatus = (fault2_2<<3 | fault2_1<<2 | fault1_2<<1 | fault1_1<<0);
	return faultStatus;
}

char getFaultStatus() {
	return faultStatus;
}

void toggleHBridge() {
	
	if(state == 1) {
		toggleLED(LED1);
		state = 0;
		PORTA &= ~(1<<INA1); //turn off A1
		#ifdef enableDeadTime
			_delay_us(deadTime);
		#endif
		PORTC |= (1<<INA2); //turn on A2
	}
	//else{
	else if (state == 0) {
		
		state = 1;
		PORTC &= ~(1<<INA2); //turn off A2
		#ifdef enableDeadTime
			_delay_us(deadTime);
		#endif
		PORTA |= (1<<INA1); //turn on A1
	}
}