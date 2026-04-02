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
	
	while (1) { // beskonacna petlja
	
	}
	
	return 0;
}