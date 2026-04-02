/*
 Tema: Digitalni izlazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 4.6
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"
#include <util/delay.h>

#define CRVENO B1 // alias za crveno svjetlo
#define ZUTO B2 // alias za žuto svjetlo
#define ZELENO B3 // alias za zeleno svjetlo

void init() {
	
	pinMode(CRVENO, OUTPUT); // PB1 konfiguriran kao izlazni pin
	pinMode(ZUTO, OUTPUT); // PB2 konfiguriran kao izlazni pin
	pinMode(ZELENO, OUTPUT); // PB3 konfiguriran kao izlazni pin
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	int brojacCiklusa = 0;
	
	while (1) { // beskonacna petlja
		
		// zelena LED dioda se ukljucuje u: 0 s, 12.5 s, 13.5 s i 14.5 s
		if (brojacCiklusa == 0 || brojacCiklusa == 125 || brojacCiklusa == 135 || brojacCiklusa == 145) {
			digitalWrite(ZELENO, HIGH);
		} 
		// zelena LED dioda se iskljucuje u: 12 s, 13 s, 14 s i 15 s
		if (brojacCiklusa == 120 || brojacCiklusa == 130 || brojacCiklusa == 140 || brojacCiklusa == 150) {
			digitalWrite(ZELENO, LOW);
		}
		// zuta LED dioda se ukljucuje u: 15 s, 25 s		
		if (brojacCiklusa == 150 || brojacCiklusa == 250) {
			digitalWrite(ZUTO, HIGH);
		}
		// zuta LED dioda se iskljucuje u: 18 s, 28 s = 0 s
		if (brojacCiklusa == 180 || brojacCiklusa == 0) {
			digitalWrite(ZUTO, LOW);
		}
		// crvena LED dioda se ukljucuje u: 18 s
		if (brojacCiklusa == 180) {
			digitalWrite(CRVENO, HIGH);
		}
		// crvena LED dioda se iskljucuje u: 28 s = 0 s
		if (brojacCiklusa == 0) {
			digitalWrite(CRVENO, LOW);
		}		
		_delay_ms(100); // vrijeme jednog prolaza kroz petlju
		brojacCiklusa++;
		
		// 280 x 100 ms = 28 s
		// kada brojac dode do 28 s, ciklus se resetira na 0 s
		if (brojacCiklusa == 280) {
			brojacCiklusa = 0;
		}
	}
	
	return 0;
}