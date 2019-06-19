/*
 * LEDs.c
 *
 * Created: 4/19/2018 
 *  Author: Reed (based on Zac's version from router card)
 */ 

#include "LEDs.h"
#include <avr/io.h>

void setLED(LEDs_ENUMED_t ledNumber, bool state)
{
	int ledToSwitch = -1;
	//HIGH SETS
	if(!state)
	{
		switch(ledNumber)
		{
			//LEDs on PORTA
			case LED0:
				ledToSwitch=LED0_P_HIGH;
				break;
			case LED1:
				ledToSwitch=LED1_P_HIGH;
				break;
			case LED2:
				ledToSwitch=LED2_P_HIGH;
				break;
			case LED3:
				ledToSwitch=LED3_P_HIGH;
				break;
			
			//LEDs on PORTC
			case LED4:
				ledToSwitch=LED4_P_HIGH;
				break;
			case LED5:
				ledToSwitch=LED5_P_HIGH;
				break;
			case LED6:
				ledToSwitch=LED6_P_HIGH;
				break;
			case LED7:
				ledToSwitch=LED7_P_HIGH;
				break;
		}
	}
	else
	{
		switch(ledNumber)
		{
			//LEDs on PORTA
			case LED0:
				ledToSwitch=LED0_P_LOW;
				break;
			case LED1:
				ledToSwitch=LED1_P_LOW;
				break;
			case LED2:
				ledToSwitch=LED2_P_LOW;
				break;
			case LED3:
				ledToSwitch=LED3_P_LOW;
				break;
				
			//LEDs on PORTC
			case LED4:
				ledToSwitch=LED4_P_LOW;
				break;
			case LED5:
				ledToSwitch=LED5_P_LOW;
				break;
			case LED6:
				ledToSwitch=LED6_P_LOW;
				break;
			case LED7:
				ledToSwitch=LED7_P_LOW;
				break;
		}
	}

	unsigned int portRead;
	switch(ledNumber)
	{
		case LED0:
		case LED1:
		case LED2:
		case LED3:
			portRead= PINA;
			//if you want the LED off
			if(!state)
			{
				//Turn it high (OFF)
				PORTA = portRead | (ledToSwitch);
			}
			else
			{
				//Turn it low (ON)
				PORTA = portRead & (ledToSwitch);
			}
			break;
		case LED4:
		case LED5:
		case LED6:
		case LED7:
			portRead= PINC;
			//If you want the LED off
			if(!state)
			{
				//Turn the port high (OFF)
				PORTC = portRead | (ledToSwitch);
			}
			else
			{
				//Turn the port low (ON)
				PORTC = portRead & (ledToSwitch);
			}
			break;
	}
	
}

void toggleLED(LEDs_ENUMED_t ledNumber)
{
	int ledToSwitch=0;
	switch(ledNumber)
	{
		//LEDs on PORTA
		case LED0:
			ledToSwitch=LED0_P_HIGH;
			break;
		case LED1:
			ledToSwitch=LED1_P_HIGH;
			break;
		case LED2:
			ledToSwitch=LED2_P_HIGH;
			break;
		case LED3:
			ledToSwitch=LED3_P_HIGH;
			break;
		
		//LEDs on PORTC
		case LED4:
			ledToSwitch=LED4_P_HIGH;
			break;
		case LED5:
			ledToSwitch=LED5_P_HIGH;
			break;
		case LED6:
			ledToSwitch=LED6_P_HIGH;
			break;
		case LED7:
			ledToSwitch=LED7_P_HIGH;
			break;
	}

		switch(ledNumber)
		{
			case LED0:
			case LED1:
			case LED2:
			case LED3:
				//Toggle pin State
				PORTA ^= (ledToSwitch);
				break;
			case LED4:
			case LED5:
			case LED6:
			case LED7:
				//Toggle pin State
				PORTC ^= (ledToSwitch);
				break;
		}

}