/*
 Tema: LCD displej
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 6.2
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
}

int main(void) {

	int intVar = 125; // cjelobrojni tip s predznakom, velicina 16 bitova
	float floatVar = 9.5828; // realni tip, velicina 32 bitova
	int8_t int8Var = -300; // cjelobrojni tip s predznakom, velicina 8 bitova
	uint8_t uint8Var = 450; // cjelobrojni tip bez predznakom, velicina 8 bitova
	int32_t int32Var = -250250; // cjelobrojni tip s predznakom, velicina 32 bitova
	uint16_t uint16Var = 100000; // cjelobrojni tip bez predznakom, velicina 16 bitova
		
	init(); // inicijalizacija mikroupravljaca

	while (1) { // beskonacna petlja
		lcdClrScr(); // brisanje znakova LCD displeja +  home pozicija kursora
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdprintf("int: %d\n", intVar);
		lcdprintf("float: %.3f", floatVar);	
		_delay_ms(2000); // kasnjenje 2000 ms
		
		lcdClrScr(); // brisanje znakova LCD displeja +  home pozicija kursora
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdprintf("int8: %d\n", int8Var);
		lcdprintf("uint8: %u", uint8Var);
		_delay_ms(2000); // kasnjenje 2000 ms		

		lcdClrScr(); // brisanje znakova LCD displeja +  home pozicija kursora
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdprintf("int32: %ld\n", int32Var);
		lcdprintf("uint16: %u", uint16Var);
		_delay_ms(2000); // kasnjenje 2000 ms

	}
	
	return 0;
}