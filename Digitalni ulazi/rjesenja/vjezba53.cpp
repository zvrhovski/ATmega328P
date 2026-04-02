/*
 Tema: Digitalni ulazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 5.3
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"

#define LED_CRVENO B1
#define LED_ZUTO B2

#define TIPKALO1 D4
#define TIPKALO2 D2
#define TIPKALO3 D5

void init() {
	
	pinMode(LED_CRVENO, OUTPUT); // PB1 konfiguriran kao izlaz
	pinMode(LED_ZUTO, OUTPUT); // PB2 konfiguriran kao izlaz
	
	// tipkalo T1
	pinMode(TIPKALO1, INPUT); // PD4 konfiguriran kao ulaz
	pullUpOn(TIPKALO1); // ukljucen pull up otpornik na ulazu PD4
	// tipkalo T2
	pinMode(TIPKALO2, INPUT_PULLUP); // PD2 konfiguriran kao ulaz
	// ukljucen pull up otpornik na ulazu PD2
	// tipkalo T3
	pinMode(TIPKALO3, INPUT_PULLUP);  // PD5 konfiguriran kao ulaz
	// ukljucen pull up otpornik na ulazu PD5
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	while (1) { // beskonacna petlja
		// provjera stanja digitalnog ulaza PD4
		if ((digitalRead(TIPKALO1) == false) && (digitalRead(TIPKALO2) == false)) {
			digitalWrite(LED_CRVENO, HIGH); // ukljuci crvenu LED diodu
			} else {
			digitalWrite(LED_CRVENO, LOW); // iskljuci crvenu LED diodu
		}
		// provjera stanja tipkala T3
		if (digitalRead(TIPKALO3) == true) {
			digitalWrite(LED_ZUTO, HIGH); // ukljuci zutu LED diodu
			} else {
			digitalWrite(LED_ZUTO, LOW); // iskljuci zutu LED diodu
		}
	}
	
	return 0;
}