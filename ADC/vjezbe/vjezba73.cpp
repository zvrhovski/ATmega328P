/*
 Tema: AD pretvorba
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 7.3
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	DDRB |= (1 << PB1); // PB1 konfiguriran kao izlazni pin
	DDRB |= (1 << PB2); // PB2 konfiguriran kao izlazni pin
	DDRB |= (1 << PB3); // PB3 konfiguriran kao izlazni pin
}

int main(void) {
		
	init(); // inicijalizacija mikroupravljaca
	
	uint16_t adc0; // digitalna rijec ADC0
	uint16_t adc0Old; // digitalna rijec ADC0
	float T; // temperatura u okolini senzora LM35
	bool ispisNaLcd = true; // omogucavanje ispisa
	int brojac_vremena = 0; // brojac za sekunde
	

	while (1) { // beskonacna petlja

		// uvjetni ispis na LCD displej i izmjena stanja LED dioda
		if (ispisNaLcd) {
			// brisanje znakova LCD displeja +  home pozicija kursora
			lcdClrScr(); 
			// ispis na LCD displej (sintaksa funkcije printf())
			lcdprintf("T = %.2f%c", T, 223);
			ispisNaLcd = false; //onemoguci ispis na LCD
		}
		_delay_ms(10);
	}
	return 0;
}