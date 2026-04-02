/*
 Tema: Digitalni izlazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 4.1
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"

void init() {
	
	pinMode(B1, OUTPUT);
	digitalWrite(B1, HIGH);
}

int main(void) {
	
	init();
		
	return 0;	
}