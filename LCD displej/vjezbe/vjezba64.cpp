/*
 Tema: LCD displej
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 6.4
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"

#define TIPKALO1 D4
#define TIPKALO2 D2

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	// tipkalo T1
	pinMode(TIPKALO1, INPUT_PULLUP); // PD4 konfiguriran kao ulaz
	// uklju?en pull up otpornik na pinu PD4
	// tipkalo T2
	pinMode(TIPKALO2, INPUT_PULLUP); // PD2 konfiguriran kao ulaz
	// uklju?en pull up otpornik na pinu PD2
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	
	while (1) { // beskonacna petlja

	}
	return 0;
}