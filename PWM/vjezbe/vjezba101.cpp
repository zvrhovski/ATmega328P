/*
 Tema: PWM
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 10.1
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	DDRB |= (1 << PB3); // PB3 konfiguriran kao izlazni pin (zelena LED dioda)
}

int main(void) {
	
	init(); // inicijalizacija mikroupravlja?a
	float D = 0.0;
	while (1) {

		_delay_ms(1000);
	}
}