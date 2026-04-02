/*
 Tema: Digitalni ulazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 5.5
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"

#define LED_CRVENO B1
#define LED_ZUTO B2
#define LED_ZELENO B3
#define TIPKALO1 D4
#define TIPKALO2 D2
#define TIPKALO3 D5

void init() {
	// PB1 konfiguriran kao izlaz (crvena LED dioda)
	pinMode(LED_CRVENO, OUTPUT);
	// PB2 konfiguriran kao izlaz (zuta LED dioda)
	pinMode(LED_ZUTO, OUTPUT);
	// PB3 konfiguriran kao izlaz (zelena LED dioda)
	pinMode(LED_ZELENO, OUTPUT);
	// tipkalo T1
	pinMode(TIPKALO1, INPUT_PULLUP); // PD4 konfiguriran kao ulaz
	// uklju?en pull up otpornik na pinu PD4
	// tipkalo T2
	pinMode(TIPKALO2, INPUT_PULLUP); // PD2 konfiguriran kao ulaz
	// uklju?en pull up otpornik na pinu PD2
	// tipkalo T3
	pinMode(TIPKALO3, INPUT_PULLUP); // PD5 konfiguriran kao ulaz
	// uklju?en pull up otpornik na pinu PD5

}

int main(void) {
	
	init(); // inicijalizacija mikroupravlja?a

	while (1) { // beskona?na petlja

	}
	return 0;
}