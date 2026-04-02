/*
 Tema: Digitalni ulazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 5.6
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
	// ukljucen pull up otpornik na pinu PD4
	// tipkalo T2
	pinMode(TIPKALO2, INPUT_PULLUP); // PD2 konfiguriran kao ulaz
	// ukljucen pull up otpornik na pinu PD2
	// tipkalo T3
	pinMode(TIPKALO3, INPUT_PULLUP); // PD5 konfiguriran kao ulaz
	// ukljucen pull up otpornik na pinu PD5

}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	int korak = 1; // 1 = crvena, 2 = zuta, 3 = zelena
	
	
	while (1) { // beskonacna petlja
		// provjera padajuceg brida tipkala T1
		if (isFallingEdge(TIPKALO1)) {
			korak++; // korak u desno
			if (korak == 4) {
				korak = 1;
			}
		}
		// provjera padajuceg brida tipkala T2
		if (isFallingEdge(TIPKALO2)) {
			korak--; // korak u lijevo
			if (korak == 0) {
				korak = 3;
			}
		}
		// provjera padajuceg brida tipkala T3
		if (isFallingEdge(TIPKALO3)) {
			korak = 1; //reset na pocetak
		}
		
		switch (korak) {
			case 1: 
			digitalWrite(LED_CRVENO, HIGH); // crvena LED dioda on
			digitalWrite(LED_ZUTO, LOW); // zuta LED dioda off
			digitalWrite(LED_ZELENO, LOW); // zelena LED dioda off
			break;
			case 2:
			digitalWrite(LED_CRVENO, LOW); // crvena LED dioda off
			digitalWrite(LED_ZUTO, HIGH); // zuta LED dioda on
			digitalWrite(LED_ZELENO, LOW); // zelena LED dioda off
			break;
			case 3:
			digitalWrite(LED_CRVENO, LOW); // crvena LED dioda off
			digitalWrite(LED_ZUTO, LOW); // zuta LED dioda off
			digitalWrite(LED_ZELENO, HIGH); // zelena LED dioda on
			break;
			default:
			break;
		}
	}
	return 0;
}