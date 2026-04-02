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

// prekidana rutina za INT0
ISR(INT0_vect) {

}


void init() {
	lcdInit(); // inicijalizacija LCD displeja
	
}

int main(void) {
	
	init(); // inicijalizacija mikroupravlja?a
	
	while (1) {

	}
}