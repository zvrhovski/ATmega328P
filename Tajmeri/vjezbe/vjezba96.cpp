/*
 Tema: Tajmeri i broja?i
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 9.6
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"

// prekidna rutina za brojac 0
ISR(TIMER0_OVF_vect) {

}

void init() {
	lcdInit(); // inicijalizacija LCD displeja

}

int main(void) {
	
	init(); // inicijalizacija mikroupravlja?a
	while (1) {

	}
}
