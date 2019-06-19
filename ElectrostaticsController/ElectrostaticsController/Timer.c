/*
 * Timer.c
 *
 * Created: 5/5/2017 12:39:32 AM
 *  Author: Zac
 */ 

#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LEDs.h"

//max timer length is ~1 hour

//#define NOPRESCALER     (1<<CS00)                    //16us
#define PRESCALER8		(1<<CS01)				//128us
//#define PRESCALER64		(1<<CS01)|(1<<CS00)		//TIMER INTERVAL ISR 1024us
//#define PRESCALER256	(1<<CS02)				//TIMER INTERVAL ISR 4096us
//#define PRESCALER1024	(1<<CS02)|(1<<CS00)		//TIMER INTERVAL ISR 16384us

#ifdef NOPRESCALER
	#define PRESCALER	NOPRESCALER
#elif PRESCALER8
	#define PRESCALER	PRESCALER8
#elif PRESCALER64
	#define PRESCALER	PRESCALER64
#elif PRESCALER256
	#define PRESCALER	PRESCALER256
#elif PRESCALER1024
	#define PRESCALER	PRESCALER1024
#else
	#define PRESCALER	PRESCALER256		//Default interval 4ms
#endif

volatile unsigned long globalTime=0;

void (*timerFunction)(void);
bool timerFunctionDefined = 0;
timer_t * FuntionTimer;  

void setTimerInterval(timer_t * t, unsigned long long l)
{
	t->timerLength=l;
}

void setTimerIntervalandFunction(timer_t * t, unsigned long long l, void (*inputFunction)(void)) {
	t->timerLength=l; 
	timerFunction = inputFunction;
	FuntionTimer = t;
	timerFunctionDefined = 1;  
}

void resetTimer(timer_t * t)
{
	unsigned long long timenow=globalTime;
	t->prevTime=timenow;
}

bool timerDone(timer_t * t)
{
	unsigned long long timenow=globalTime;
	if(timenow >= t->prevTime+t->timerLength)
	{
		t->prevTime=timenow;
		return true;
	}
	else
	{
		return false;
	}
}

void initTimer0(void)
{
	TCCR0A = PRESCALER;		//Set the prescaler
	TIMSK0 = (1<<TOIE0);		//ENABLE Timer Overflow interrupt
}

ISR(TIMER0_OVF_vect)
{
	#ifdef PRESCALER1024
		globalTime+=16384;
	#elif PRESCALER256
		globalTime+=4096;
	#elif PRESCALER64
		globalTime+=1024;
	#elif PRESCALER8
		globalTime+=128;
	#elif NOPRESCALER
		globalTime+=16; 
	#endif
	
	if(timerFunctionDefined && timerDone(FuntionTimer)) {
		timerFunction();
		resetTimer(FuntionTimer);
	}


	TIFR0 = (0<<TOV0);	//Reset timer0 overflow interrupt flag
}