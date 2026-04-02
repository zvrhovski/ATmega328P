/*
 Tema: LCD displej
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 6.7
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	// kreiranje samo onih znakova koji su potrebni
	lcdCreateChar(1, customChar2); // znak c (ch)
	lcdCreateChar(2, customChar3); // znak c (tj)
	lcdCreateChar(4, customChar5); // znak s (sh)
	lcdCreateChar(5, customChar6); // znak z (zh)
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	uint8_t brojac = 0;
	
	lcdClrScr(); // obrisi LCD displej
	// isisi tekst duzine 28 znakova
	lcdprintf("Mikroupravlja%ci su naj%ce%c%ci!", 1, 5, 4, 2);
			
	while (1) { // beskonacna petlja

		_delay_ms(500); // kasnjenje 500 ms		
	}
	return 0;
}