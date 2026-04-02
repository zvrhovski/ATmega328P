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
		
	return 0;	
}