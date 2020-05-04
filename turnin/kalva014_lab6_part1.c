/*	Author: kennethalvarez
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include "timer.h"

enum States {Start, Init, Led2, Led3} state;
unsigned char tmpB;

void Tick() {
	switch(state) { //transitions
		case Start:
			state = Init;
			break;
		case Init:
			state = Led2;
			break;
		case Led2:
			state = Led3;
			break;
		case Led3:
			state = Init;
		default:
			break;
	}
	
	switch(state) { //actions
		case Start:
			break;
		case Init:
			tmpB = 0x01;
			break;
		case Led2:
			tmpB = 0x02;
			break;
		case Led3:
			tmpB = 0x04;
			break;	
		default:
			break;		
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0x0F;
	PORTB = 0x00;
	state = Start;

	TimerSet(1000);
	TimerOn();

    /* Insert your solution below */
    while (1) {
	tmpB = ~tmpB; //This might be wrong
	Tick();	
	PORTB = tmpB;

	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
