/*
 Tema: Tajmeri i broja?i
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 9.1
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"
#include "Senzori/lm35.h"

// konstanta koja se koristi umjesto ADC0
#define LM35 ADC0

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	DDRB |= (1 << PB2); // PB2 konfiguriran kao izlazni pin (žuta LED dioda)
}

int main(void) {
	
	init(); // inicijalizacija mikroupravlja?a
	float T; // temperatura u okolini senzora LM35
	while (1) {
		T = readTempLM35(LM35); // ?itaj temperaturu na LM35
		// brisanje znakova LCD displeja +  home pozicija kursora
		lcdClrScr();
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdprintf("T = %.2f%c", T, 223);
		_delay_ms(1000);
	}
}