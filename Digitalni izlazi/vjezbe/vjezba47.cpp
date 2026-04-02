/*
 Tema: Digitalni izlazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 4.7
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"
#include <util/delay.h>

// aliasi za crveno svjetlo
#define CRVENO_DDR DDRB
#define CRVENO_PORT PORTB
#define CRVENO_PIN PB1

void init() {
	//PB1 konfiguriran kao izlazni pin 
	config_output(CRVENO_DDR, CRVENO_PIN);

}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca

	while (1) { // beskonacna petlja
	
	}
	
	return 0;
}