#include <htc.h>
#include <stdlib.h>
#include <stdio.h>

#include "const.h"
#include "random.h"

__CONFIG(FOSC_INTOSCIO & MCLRE_ON & WDTE_OFF & PWRTE_ON); // & MCLRE_OFF
 
#define _XTAL_FREQ 4000000
#define BOOL unsigned char
#define FALSE 0x00
#define TRUE 0xFF

#define SWITCH_ON RB0
#define RAND_SEED_ADDR_LSB 0
#define RAND_SEED_ADDR_MSB 1



void init(){	
	TRISA=0b00111111; //RA6 & RA7 as outputs
	TRISB=0b11111111;
	PCON = 0b00001000; //4 MHz internal oscillator

	T1CON = 0b00110000; //Setup Timer 1 with prescale 8

	initRandom();
}

void goOut(){
	PORTA = ((PORTA | 0b01000000) & 0b01111111);
}

void goIn(){
	PORTA = ((PORTA | 0b10000000) & 0b10111111);
}

void stop(){
	PORTA = (PORTA | 0b11000000);
}

void delay_ms(unsigned int delayms){
	TMR1IF = 0;
	TMR1IE = 1; //Activate Timer1 interrupts
	GIE = 1; //Activate global interrupts

	for(int i = 0; i < delayms; i++){
		TMR1 = 65420;//6565535 - 125 = 65410 for 1ms loop + some instructions

		TMR1ON = 1; //Starts timer
	
		while(!TMR1IF); //Wait for timer interrupt
		TMR1ON = 0; //Stops timer
		TMR1IF = 0;
	}
}


void main(void){

	init();

	stop();

	int delayms = (int)((random() / 32767.0) * MAX_START_DELAY);  //Get random number between 0 and 5000

	
	if(SWITCH_ON){
		delay_ms(delayms);
	}

	while (1){

		if(SWITCH_ON){
			goOut();
 		} else {
			goIn();
		}
	}

}