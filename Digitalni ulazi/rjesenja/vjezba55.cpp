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
	// pocetno ukljucena crvenu LED diodu
	digitalWrite(LED_CRVENO, HIGH);	
	while (1) { // beskonacna petlja
		// provjera padajuceg brida tipkala T1
		if (isFallingEdge(TIPKALO1)) {
			digitalWrite(LED_ZELENO, HIGH); // ukljuci zelenu LED diodu
		}
		// provjera rastuceg brida tipkala T2
		if (isRisingEdge(TIPKALO2)) {
			digitalWrite(LED_ZELENO, LOW); // iskljuci zelenu LED diodu
		}
		// provjera padajuceg brida tipkala T3
		if (isFallingEdge(TIPKALO3)) {
			digitalToggle(LED_CRVENO); // promijeni stanje crvene LED diode
			digitalToggle(LED_ZUTO); // promijeni stanje zute LED diode
		}
	}
	return 0;
}