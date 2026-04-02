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
	// PB3 konfiguriran kao izlaz (zelena LED dioda)
	pinMode(LED_ZELENO, OUTPUT);
	// tipkalo T2
	pinMode(TIPKALO2, INPUT_PULLUP); // PD2 konfiguriran kao ulaz
	// uklju?en pull up otpornik na pinu PD2
}

int main(void) {
	
	init(); // inicijalizacija mikroupravlja?a
	
	while (1) { // beskona?na petlja
		// provjera stanja tipkala T2
		if (digitalRead(TIPKALO2) == false) {
			digitalWrite(LED_ZELENO, HIGH); // uklju?i zelenu LED diodu
			} else {
			digitalWrite(LED_ZELENO, LOW); // isklju?i zelenu LED diodu
		}
	}
	
	return 0;
}