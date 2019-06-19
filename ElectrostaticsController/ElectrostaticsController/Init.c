/*
 * Init.c
 *
 * Created: 9/6/2017 10:57:22 AM
 *  Author: Zac
 */ 

#include "Init.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
//#include "AT90CAN_UART.h"
#include "CommsDefenition.h"
#include "general.h"
#include "LEDs.h"
#include "CANFastTransfer.h"
#include "can.h"
#include "Timer.h"

#ifndef F_CPU
	#define  F_CPU 16000000
#endif
//#include "commsReceive.h"

//static FILE mystdout = FDEV_SETUP_STREAM(USART0_put_C, NULL,
//_FDEV_SETUP_WRITE);

//Time keeps for comms management
timer_t ledTimer,  checkCANTimer;

void initialize(void)
{
		sei();
		//stdout = &mystdout;
		
		//Setup the I/O ports
		PORTA	= 0b11110000; //7-4 are LEDS, 3-0 are electrostatics control
		DDRA	= 0b11111111;
		PORTB   = 0b00000000; //7 is NC, 5-4 are electrostatics, remainder are spy and watchdog is 0
		DDRB    = 0b00010000;
		PORTC   = 0b11110000; //7-4 are LEDS, 3-0 are electrostatics control
		DDRC    = 0b11111111;
		PORTD   = 0b00000000; //7 and 4 are NC, 5 CAN TX, 6 is CAN RX, 2 and 3 are electrostatics, 1 is SDA and 0 is SCL
		DDRD    = 0b00000000;
		PORTE   = 0b00000000; //7,6,4, and 3 are electrostatics, remainder are NC
		DDRE    = 0b00000000;
		PORTF	= 0b00000000; //7-1 are NC, 0 is electrostatics control
		DDRF	= 0b00000000; 

		for(int i=0; i < NUMBER_OF_LEDS; i++)
		{
			setLED(i,ON);
			_delay_ms(50);
		} 
		
		for(int i=0; i < NUMBER_OF_LEDS; i++)
		{
			setLED(i,OFF);
			_delay_ms(50);
		}
		
		//Init the CAN here
		can_init();
		
		//Start communciations handlers
		initCANFastTransfer();
		
		////Initialize the timer0 and timer systems
		initTimer0();
		setTimerInterval(&ledTimer,500000);
		//setTimerInterval(&checkCANTimer,50);
		////printf("Go \r\n");	

}