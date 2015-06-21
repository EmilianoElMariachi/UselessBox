#include <htc.h>
#include <stdlib.h>
#include <stdio.h>

__CONFIG(FOSC_INTOSCIO & MCLRE_ON & WDTE_OFF & PWRTE_ON); // & MCLRE_OFF
 
#define _XTAL_FREQ 4000000
#define BOOL unsigned char
#define FALSE 0x00
#define TRUE 0xFF

#define SWITCH_ON RB0



void init(){	

	TRISA=0b00111111; //RA6 & RA7 as outputs
	TRISB=0b11111111;
	PCON = 0b00001000; //4 MHz internal oscillator

	T1CON = 0b00110000; //Setup Timer 1 with prescale 8


}

void goIn(){
	PORTA = ((PORTA | 0b01000000) & 0b01111111);
}

void goOut(){
	PORTA = ((PORTA | 0b10000000) & 0b10111111);
}

void stop(){
	PORTA = (PORTA | 0b11000000);
}


void delay(unsigned int delay){

	TMR1IF = 0;
	TMR1 = delay;
	TMR1IE = 1; //Activate Timer1 interrupts
	GIE = 1; //Activate global interrupts

	TMR1ON = 1; //Starts timer
	while(!TMR1IF); //Wait for timer interrupt

	TMR1ON = 0;
	TMR1IF = 0;
}


void main(void){

	init();

	stop();

	//srand(15);

	int delay_ms = 1;//rand();

	delay(delay_ms);


	while (1){

		if(SWITCH_ON){
			goOut();
 		} else {
			goIn();
		}
	}

}