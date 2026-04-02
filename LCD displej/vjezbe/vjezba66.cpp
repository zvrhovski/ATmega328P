/*
 Tema: LCD displej
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 6.6
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja

}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	while (1) { // beskonacna petlja
		_delay_ms(100);
	}
	return 0;
}