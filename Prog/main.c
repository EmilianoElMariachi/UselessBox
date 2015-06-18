#include <htc.h>

__CONFIG(FOSC_INTOSCIO & MCLRE_ON & WDTE_OFF & PWRTE_ON); // & MCLRE_OFF

#define _XTAL_FREQ 4000000

//#define MOTP RA6
//#define MOTM RA7

void init(){
	TRISA=0b00000000;
	TRISB=0b11111111;
	PCON = 0b00001000; //Défini à 4 Mhz
}

//void runMotorR(){
////	PORTA = ((PORTA | 0b01000000) & 0b01111111);
////	PORTA = 0xFF;
//	MOTP = 1;
//	MOTM = 0;
//}
//
//void runMotorL(){
////	PORTA = ((PORTA | 0b10000000) & 0b10111111);
////	PORTA = 0x00;
//	MOTP = 0;
//	MOTM = 1;
//}
//
//
//void stopMotor(){
////	PORTA = (PORTA | 0b11000000);
////	PORTA = 0xFF;
//	MOTP = 1;
//	MOTM = 1;
//
//}



void main(void){
	//stopMotor();
	init();
	
	RA6 = 0;
	RA7 = 0;


	while (1){

		if(RB0){
			PORTA = 0xFF;
 		} else {
			PORTA = 0x81;
		}


//		runMotorL();
//		__delay_ms(1000);
//		runMotorR();
//		__delay_ms(1000);
//		stopMotor();
//		__delay_ms(1000);
	}

}