/*
 Tema: PWM
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 10.3
 */ 

#include "AVR/avrlib.h"
#include "Timer/timer.h"
#include "ADC/adc.h"

void init() {
	adcInit(); // inicijalizacija AD pretvorbe
	pinMode(B1, OUTPUT); // PB1 konfiguriran kao izlazni pin (crvena LED dioda)
	pinMode(B2, OUTPUT); // PB2 konfiguriran kao izlazni pin (zuta LED dioda)
	// postavljanje Phase Correct PWM nacina rada za timer1 - 10 bit
	timer1PhaseCorrectPWM9bit();
	// djelitelj frekvencije F_CPU / 8
	timer1SetPrescaler(TIMER1_PRESCALER_8);
	// neinvertirajuci PWM signal na PB1 (OC1A)
	timer1OC1AEnableNonInvertedPWM();
	// invertirajuci PWM signal na PB2 (OC1B)
	timer1OC1BEnableInvertedPWM();	
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	float D;
	while (1) {
		// AD rezultat skalira se u raspon [0, 100.0]
		D = adcReadScale0To100(ADC0);
		// osvjezavanje faktora vodenja kroz registar OCR1A i OCR1B
		timer1OC1ADutyCycle(D);
		timer1OC1BDutyCycle(D);
	}
}