/*
 Tema: Digitalni izlazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 4.4
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"
#include <util/delay.h>

void init() {
	
	// PB1, PB2 i PB3 konfigurirani kao izlazni pinovi
	DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3);
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	while (1) { // beskonacna petlja
		
		set_pin_off(PORTB, PB3); // pin PB3 postavljen u nisko stanje
		set_pin_on(PORTB, PB1); // pin PB1 postavljen u visoko stanje
		_delay_ms(250); // zakasni 250 ms
		set_pin_off(PORTB, PB1); // pin PB1 postavljen u nisko stanje
		set_pin_on(PORTB, PB2); // pin PB2 postavljen u visoko stanje
		_delay_ms(250);	// zakasni 250 ms
		set_pin_off(PORTB, PB2); // pin PB2 postavljen u nisko stanje
		set_pin_on(PORTB, PB3); // pin PB3 postavljen u visoko stanje
		_delay_ms(250); // zakasni 250 ms
	}
	
	return 0;
}