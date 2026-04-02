/*
 Tema: Digitalni ulazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 5.2
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"

void init() {
	
	pinMode(B1, OUTPUT); // PB1 konfiguriran kao izlaz
	pinMode(B2, OUTPUT); // PB2 konfiguriran kao izlaz
	pinMode(B3, OUTPUT); // PB3 konfiguriran kao izlaz
	// tipkalo T1
	pinMode(D4, INPUT); // PD4 konfiguriran kao ulaz
	pullUpOn(D4); // ukljucen pull up otpornik na ulazu PD4
	// tipkalo T2
	pinMode(D2, INPUT_PULLUP); // PD2 konfiguriran kao ulaz
	// ukljucen pull up otpornik na ulazu PD2
	// tipkalo T3
	pinMode(D5, INPUT_PULLUP);  // PD5 konfiguriran kao ulaz
	// ukljucen pull up otpornik na ulazu PD5
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
		// provjera stanja digitalnog ulaza PD2
		if (digitalRead(D2) == false) {
			digitalWrite(B2, HIGH); // ukljuci zutu LED diodu
			} else {
			digitalWrite(B2, LOW); // iskljuci zutu LED diodu
		}	
		// provjera stanja digitalnog ulaza PD5
		if (digitalRead(D5) == false) {
			digitalWrite(B3, HIGH); // ukljuci zelenu LED diodu
			} else {
			digitalWrite(B3, LOW); // iskljuci zelenu LED diodu
		}
	}
	
	return 0;
}