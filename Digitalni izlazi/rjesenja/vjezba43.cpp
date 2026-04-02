/*
 Tema: Digitalni izlazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 4.3
 */ 


#include <avr/io.h>
#include "AVR/avrlib.h"
#include <util/delay.h>

void init() {
	
	DDRB |= (1 << PB3); // PB3 konfiguriran kao izlazni pinovi
	
}
		
int main(void) {
		
	init(); // inicijalizacija mikroupravljaca
	
	PORTB |= (1 << PB3); // pin PB3 postavljen u visoko stanje
	_delay_ms(1000); // zakasni 1000 ms = 1 s
	PORTB &= ~(1 << PB3); // pin PB3 postavljen u nisko stanje
	_delay_ms(1000); // zakasni 1000 ms = 1 s
	set_pin_on(PORTB, PB3); // pin PB3 postavljen u visoko stanje
	_delay_us(1000000); // zakasni 1000000 us = 1 s
	set_pin_off(PORTB, PB3); // pin PB3 postavljen u nisko stanje
	_delay_us(1000000); // zakasni 1000000 us = 1 s
	digitalWrite(B3, HIGH); // pin PB3 postavljen u visoko stanje
	_delay_ms(1000); // zakasni 1000 ms = 1 s
	digitalWrite(B3, LOW); // pin PB3 postavljen u nisko stanje
	_delay_ms(1000); // zakasni 1000 ms = 1 s
	PORTB |= (1 << PB3); // pin PB3 postavljen u visoko stanje
	_delay_ms(1000); // zakasni 1000 ms = 1 s
	PORTB &= ~(1 << PB3); // pin PB3 postavljen u visoko stanje
	
	return 0;	
}