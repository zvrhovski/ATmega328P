/*
 Tema: Vanjski prekidi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 12.1
 */ 

#include "AVR/avrlib.h"
#include "Interrupt/interrupt.h"
#include "LCD/lcd.h"

volatile int brojac = 0;
volatile bool lcdUpdate = true;

// prekidana rutina za INT0
ISR(INT0_vect) {
	brojac++;
	lcdUpdate = true;
}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	// pin PD2 konfiguriran kao ulaz + ukljucen pritezni otpornik
	pinMode(D2, INPUT_PULLUP); 
	interruptEnable(); // globalno omogu?eni prekidi
	// vanjski prekid INT0
	int0Enable();  // omoguci prekid INT0
	// rastuci brid generira prekid  na INT0
	int0RisingFallingEdge();
	
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	while (1) {
		if (lcdUpdate) {
			lcdClrScr();
			lcdprintf("INT = %d", brojac);
			lcdUpdate = false;
		}
	}
}

/*
	int0Enable();
	int0FallingEdge();
*/