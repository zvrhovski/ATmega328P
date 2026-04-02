/*
 Tema: Digitalni ulazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 5.3
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"

void init() {
	
	config_output(DDRB, PB1); // PB1 konfiguriran kao izlaz (crvena LED dioda)
	config_output(DDRB, PB2); // PB2 konfiguriran kao izlaz (žuta LED dioda)
	// tipkalo T1
	config_input(DDRD, PD4); // PD4 konfiguriran kao ulaz
	pull_up_on(PORTD, PD4); // ukljucen pull up otpornik na ulazu PD4
	// tipkalo T2
	config_input(DDRD, PD2); // PD2 konfiguriran kao ulaz
	pull_up_on(PORTD, PD2); // ukljucen pull up otpornik na ulazu PD2
	// tipkalo T3
	config_input(DDRD, PD5); // PD5 konfiguriran kao ulaz
	pull_up_on(PORTD, PD5); // ukljucen pull up otpornik na ulazu PD5
}

int main(void) {
	
	init(); // inicijalizacija mikroupravlja?a
	
	while (1) { // beskona?na petlja

	}
	
	return 0;
}