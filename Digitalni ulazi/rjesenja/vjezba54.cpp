/*
 Tema: Digitalni ulazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 5.4
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"

#define LED_ZELENO B3
#define TIPKALO2 D2

void init() {
	
	pinMode(LED_ZELENO, OUTPUT); // PB3 konfiguriran kao izlaz (zelena LED dioda)
	// tipkalo T2
	pinMode(TIPKALO2, INPUT_PULLUP); // PD2 konfiguriran kao ulaz
	// ukljucen pull up otpornik na pinu PD2
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	while (1) { // beskonacna petlja
		// provjera stanja tipkala T2
		if (filteredPinState(TIPKALO2, false, 50) == false) {
			digitalWrite(LED_ZELENO, HIGH); // ukljuci zelenu LED diodu
			} else {
			digitalWrite(LED_ZELENO, LOW); // iskljuci zelenu LED diodu
		}
	}
	
	return 0;
}