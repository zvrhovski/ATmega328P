/*
 Tema: Digitalni ulazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 5.1
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"

void init() {
	
	pinMode(B1, OUTPUT); // PB1 konfiguriran kao izlaz
	pinMode(D4, INPUT); // PD4 konfiguriran kao ulaz
	
	pullUpOn(D4); // ukljucen pull up otpornik na ulazu PD4
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	while (1) { // beskonacna petlja
		 // provjera stanja digitalnog ulaza PD4
		if (digitalRead(D4) == false) {
			digitalWrite(B1, HIGH); // ukljuci crvenu LED diodu
			} else {
			digitalWrite(B1, LOW); // iskljuci crvenu LED diodu
		}
	}
	
	return 0;
}