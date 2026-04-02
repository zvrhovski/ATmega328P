/*
 Tema: LCD displej
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 6.1
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include <util/delay.h>
// s obzirom da se #include <util/delay.h> nalazi u lcd.h, ova se linija smije izostaviti

void init() {
	lcdInit(); // inicijalizacija LCD displeja
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca

	while (1) { // beskonacna petlja
		lcdClrScr(); // brisanje znakova LCD displeja +  home pozicija kursora
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdprintf("Marija\n"); 
		lcdprintf("Horvat");	
		_delay_ms(3000); // kasnjenje 3000 ms
		
		lcdClrScr(); // brisanje znakova LCD displeja +  home pozicija kursora
		lcdGotoXY(1,2); // pozicioniranje kursora u 1. red, 2. stupac
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdprintf("Mikroupravljac");
		lcdGotoXY(2, 4); // pozicioniranje kursora u 2. red, 4. stupac
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdprintf("ATmega328P");
		_delay_ms(3000); // kasnjenje 3000 ms		
	}
	
	return 0;
}