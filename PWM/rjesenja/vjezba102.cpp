/*
 Tema: PWM
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 10.2
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "Timer/timer.h"
#include "ADC/adc.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	DDRB |= (1 << PB3); // PB3 konfiguriran kao izlazni pin (zelena LED dioda)
	// postavljanje Phase Correct PWM nacina rada za timer2
	timer2PhaseCorrectPWM();
	// djelitelj frekvencije F_CPU / 8
	timer2SetPrescaler(TIMER2_PRESCALER_8);
	// neinvertirajuci PWM signal na PB3 (OC2A)
	timer2OC2AEnableNonInvertedPWM();
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	float D;
	while (1) {
		// promjena faktora vodenja pomocu ADC0
		D = adcReadScale0To100(ADC0);
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdHome();
		lcdprintf("D = %.1f%%      ", D);
		// osvjezavanje faktora vodenja kroz registar OCR2A
		timer2OC2ADutyCycle(D);
		_delay_ms(100);
	}
}