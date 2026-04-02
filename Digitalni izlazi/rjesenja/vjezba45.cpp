/*
 Tema: Digitalni izlazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 4.5
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"
#include <util/delay.h>

void init() {
	
	pinMode(B1, OUTPUT); // PB1 konfiguriran kao izlazni pin
	pinMode(B2, OUTPUT); // PB2 konfiguriran kao izlazni pin
	pinMode(B3, OUTPUT); // PB3 konfiguriran kao izlazni pin
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	while (1) { // beskonacna petlja
		
		digitalWrite(B2, LOW); // pin PB2 postavljen u nisko stanje
		digitalWrite(B1, HIGH); // pin PB1 postavljen u visoko stanje
		_delay_ms(100); // zakasni 100 ms
		digitalWrite(B1, LOW); // pin PB1 postavljen u nisko stanje
		digitalWrite(B2, HIGH); // pin PB2 postavljen u visoko stanje
		_delay_ms(100); // zakasni 100 ms
		digitalWrite(B2, LOW); // pin PB2 postavljen u nisko stanje
		digitalWrite(B3, HIGH); // pin PB3 postavljen u visoko stanje
		_delay_ms(100); // zakasni 100 ms
		digitalWrite(B3, LOW); // pin PB3 postavljen u nisko stanje
		digitalWrite(B2, HIGH); // pin PB2 postavljen u visoko stanje
		_delay_ms(100); // zakasni 100 ms		
	}
	
	return 0;
}