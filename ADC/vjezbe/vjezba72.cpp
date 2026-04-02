/*
 Tema: AD pretvorba
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 7.2
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	uint16_t adc0; // digitalna rijec ADC0
	uint16_t adc0Old; // digitalna rijec ADC0
	float adc0Scale; // napon na pinu ADC0
	bool ispisNaLcd = true; // omogucavanje ispisa
	
	while (1) { // beskonacna petlja

		// uvjetni ispis na LCD displej
		if (ispisNaLcd) { 
			lcdClrScr(); // brisanje znakova LCD displeja +  home pozicija kursora
			// ispis na LCD displej (sintaksa funkcije printf())
			lcdprintf("ADC0: %d\n", adc0);
			lcdprintf("Scale: %.2f%%\n", adc0Scale);
			ispisNaLcd = false; //onemoguci ispis na LCD
		}
	}
	return 0;
}