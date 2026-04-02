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

	uint8_t kut = 0; // po?etni kut je 0
	float coskuta;
			
	init(); // inicijalizacija mikroupravljaca

	while (1) { // beskonacna petlja
		
		coskuta = cos(kut * PI / 180.0);
		lcdClrScr(); // brisanje znakova LCD displeja + home pozicija kursora
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdprintf("Kut: %u%c\n", kut, 223);
		lcdprintf("Cos(%u): %.4f", kut, coskuta);	
		
		kut++; // povecaj stupanj za 1
		// ako je kut ve?i od 180, vratite ga na 0
		if(kut > 180) {
			kut = 0;
		}
		_delay_ms(1000); // kasnjenje 1000 ms
	}
	
	return 0;
}