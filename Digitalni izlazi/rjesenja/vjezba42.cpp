/*
 Tema: Digitalni izlazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 4.2
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"

void init() {
	
	config_output(DDRB, PB2); // PB2 konfiguriran kao izlazni pinovi
	config_output(DDRB, PB3); // PB3 konfiguriran kao izlazni pinovi
	set_pin_on(PORTB, PB2); // pin PB2 postavljen u visoko stanje
	set_pin_on(PORTB, PB3); // pin PB3 postavljen u visoko stanje
}

int main(void) {
	
	init();
	
	return 0;
}