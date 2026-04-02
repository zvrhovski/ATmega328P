/*
 Tema: PWM
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 10.4
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "Timer/timer.h"
#include "ADC/adc.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	pinMode(B1, OUTPUT); // PB1 konfiguriran kao izlazni pin (crvena LED dioda)
	pinMode(D4, INPUT); // PD4 konfiguriran kao ulazni pin (tipkalo T1)
	pullUpOn(D4); // ukljuci pull up na pinu PD4
	// postavljanje Phase Correct PWM na?ina rada za timer1 - ICR1
	timer1PhaseCorrectPWMICR1(625);  // f =  50 Hz
	// djelitelj frekvencije F_CPU / 256
	timer1SetPrescaler(TIMER1_PRESCALER_256);
	// neinvertirajuci PWM signal na PB1 (OC1A)
	timer1OC1AEnableNonInvertedPWM();
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	float D; // faktor vodenja
	while (1) {
		// ako nije pritisnuto tipkalo S1
		if (digitalRead(D4)) {
			// neinvertirajuci PWM signal na PB1 (OC1A)
			timer1OC1AEnableNonInvertedPWM();
			} else {
			// iskljuci PWM signal na PB1 (OC1A)
			timer1OC1ADisable();
		}
		// AD rezultat skalira se u raspon [0, 100.0]
		D = adcReadScale0To100(ADC0);
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdHome();
		lcdprintf("D = %.1f%%      \n", D);
		lcdprintf("f = %dHz", F_CPU / 256 / 2 / ICR1);
		// osvjezavanje faktora vodenja kroz registar OCR1A
		timer1OC1ADutyCycle(D);
	}
}

