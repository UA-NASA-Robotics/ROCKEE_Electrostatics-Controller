/*
 * ElectrostaticsController.cpp
 *
 * Created: 4/19/2018 9:18:16 PM
 * Author : reed
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//#define CHECKCOMMS

extern "C" {
	#include "can.h"
	#include "LEDs.h"
	#include "Config.h"
	#include "Timer.h"
	#include "Init.h"
	#include "Electrostatics.h"
	#include "CommsDefenition.h"
	#include "Comms.h"
	#include "general.h"
	#include "assert.h"
	#include "CANFastTransfer.h"
}

#define  F_CPU 16000000


#define __AVR_CAN90CAN128

extern timer_t ledTimer;

int main(void)
{
	initialize();
	
	initializeHBridge();
    
    /* Replace with your application code */
    while (1) 
    {
		checkFault(); //if a fault occurs, stop toggling everything and shut down until chip reset. 
		_delay_ms(5);
		#ifdef CHECKCOMMS
		if(checkCommsReceived()) {
			if(checkEnabled()) {
				enableHV();
				beginHBridgeToggle(); //start toggling hbridge
			}
			else {
				disableHV(); 
				stopBridgeToggle(); 
			}
			int asker = checkRequestStatus(); //returns who is asking for status (returns 0 if nobody)
			if(asker > 0) { //if somebody asked our current status
				sendStatus(asker); //send them our status (0 is everything functioning normally)
			}
		}
		#else
		if( getState() < 0) {
			enableHV();
			beginHBridgeToggle(); //start toggling hbridge
		}
		
		if(timerDone(&ledTimer)) {
			toggleLED(LED0);
			resetTimer(&ledTimer); 
		}
		#endif
    }
	
}

