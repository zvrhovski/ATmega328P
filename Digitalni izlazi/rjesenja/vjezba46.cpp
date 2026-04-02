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
		
		digitalWrite(ZELENO, HIGH); // ukljuceno zeleno svjetlo na 12 s
		_delay_ms(12000); // cekanje 12 s
		
		// izmjenjivanje stanja zelenog svjetla svakih 500 ms
		digitalWrite(ZELENO, LOW); 
		_delay_ms(500); // cekanje 500 ms
		digitalWrite(ZELENO, HIGH);
		_delay_ms(500); // cekanje 500 ms
		digitalWrite(ZELENO, LOW);
		_delay_ms(500); // cekanje 500 ms
		digitalWrite(ZELENO, HIGH);
		_delay_ms(500); // cekanje 500 ms
		digitalWrite(ZELENO, LOW);
		_delay_ms(500); // cekanje 500 ms
		digitalWrite(ZELENO, HIGH);
		_delay_ms(500);	// cekanje 500 ms
				
		digitalWrite(ZELENO, LOW); // iskljuceno zeleno svjetlo
		digitalWrite(ZUTO, HIGH); // ukljuceno zuto svjetlo na 3 s
		_delay_ms(3000); // cekanje 3 s
		
		digitalWrite(ZUTO, LOW); // iskljuceno zuto svjetlo
		digitalWrite(CRVENO, HIGH); // ukljuceno crveno svjetlo na 10 s
		_delay_ms(7000); // cekanje 7 s		 				
		digitalWrite(ZUTO, HIGH); // ukljuceno zuto svjetlo na 3 s
		_delay_ms(3000); // cekanje 3 s
	
		digitalWrite(ZUTO, LOW); // iskljuceno zuto svjetlo
		digitalWrite(CRVENO, LOW); // iskljuceno crveno svjetlo
	}
	
	return 0;
}