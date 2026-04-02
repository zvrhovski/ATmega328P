/*
Tema: LCD displej
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 6.3
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include <math.h>
#define PI 3.14159265L // definirana konstanta za broj pi

void init() {
	lcdInit(); // inicijalizacija LCD displeja
}

int main(void) {

	init(); // inicijalizacija mikroupravljaca

	while (1) { // beskonacna petlja

		_delay_ms(1000); // kasnjenje 1000 ms
	}
	
	return 0;
}