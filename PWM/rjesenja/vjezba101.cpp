/*
 Tema: PWM
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 10.1
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "Timer/timer.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	DDRB |= (1 << PB3); // PB3 konfiguriran kao izlazni pin (zelena LED dioda)
	// postavljanje Fast PWM nacina rada za timer2
	timer2FastPWM();
	// djelitelj frekvencije F_CPU / 8
	timer2SetPrescaler(TIMER2_PRESCALER_8);
	// neinvertirajuci PWM signal na PB3 (OC2A)
	timer2OC2AEnableNonInvertedPWM();
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	float D = 0.0;
	while (1) {
		// brisanje znakova LCD displeja +  home pozicija kursora
		lcdClrScr();
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdprintf("D = %.1f%%\n", D);
		lcdprintf("f = %.2fHz\n", F_CPU / 8.0 / 256);
		// osvjezavanje faktora vo?enja kroz registar OCR2A
		timer2OC2ADutyCycle(D);
		// uvecaj faktor za 10%
		D += 10.0;
		// ako je faktor vodenja veci od 100%
		if (D > 100.0) {
			D = 0.0; // vrati faktor vo?enja na 0%
		}
		_delay_ms(1000);
	}
}