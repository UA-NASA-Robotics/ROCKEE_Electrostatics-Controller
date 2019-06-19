/*
 * LEDs.h
 *
 * Created: 4/19/2018 
 *  Author: Reed (based on Zac's version from router card)
 */ 


#ifndef LEDS_H_
#define LEDS_H_
#include "Config.h"

#include <stdbool.h>

#define ON  true
#define OFF false

#define NUMBER_OF_LEDS 8
typedef enum{
	LED0=0,
	LED1,
	LED2,
	LED3,
	LED4,
	LED5,
	LED6,
	LED7
}LEDs_ENUMED_t;


#define LED0_P_HIGH	0x10	//4	//A4	-	0
#define LED1_P_HIGH	0x20	//5	//A5	-	1
#define LED2_P_HIGH	0x40	//6	//A6	-	2
#define LED3_P_HIGH	0x80	//7	//A7	-	3
#define LED4_P_HIGH	0x80	//7	//C7	-	4
#define LED5_P_HIGH	0x40	//6	//C6	-	5
#define LED6_P_HIGH	0x20	//5	//C5	-	6
#define LED7_P_HIGH	0x10	//4	//C4	-	7



#define LED0_P_LOW	0xEF	//4	//A4	-	0
#define LED1_P_LOW	0xDF	//5	//A5	-	1
#define LED2_P_LOW	0xBE	//6	//A6	-	2
#define LED3_P_LOW	0x7F	//7	//A7	-	3
#define LED4_P_LOW	0x7F	//7	//C7	-	4
#define LED5_P_LOW	0xBF	//6	//C6	-	5
#define LED6_P_LOW	0xDF	//5	//C5	-	6
#define LED7_P_LOW	0xEF	//4	//C4	-	7




void setLED(LEDs_ENUMED_t ledNumber, bool state);
void toggleLED(LEDs_ENUMED_t ledNumber);

#endif /* LEDS_H_ */