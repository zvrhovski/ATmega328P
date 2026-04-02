/*
 Tema: AD pretvorba
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 7.1
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
	float Uadc0; // napon na pinu ADC0
	
	while (1) { // beskonacna petlja
		adc0 = adcRead(ADC0); // AD pretvorba na pinu ADC0
		Uadc0 = adcReadVoltage(ADC0); // napon na pinu ADC0
		// brisanje znakova LCD displeja +  home pozicija kursora
		lcdClrScr(); 
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdprintf("ADC0: %d\n", adc0); 
		lcdprintf("UADC0: %.6fV\n", Uadc0);
		_delay_ms(500); // kasnjenje 500 ms
	}
	return 0;
}