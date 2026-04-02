/*
 Tema: Vanjski prekidi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 12.2
 */ 

#include "AVR/avrlib.h"
#include "Interrupt/interrupt.h"
#include "LCD/lcd.h"
#include "Timer/timer.h"
#include "ADC/adc.h"
#include <string.h>

volatile bool lcdUpdate = true;
char LCDispis[6] = "READY";

// prekidna rutina za PCINT0
ISR(PCINT0_vect) {

}

// prekidna rutina za PCINT2
ISR(PCINT2_vect) {

}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	//konfiguracija izlaza PB1 i PB3
	DDRB |= (1 << PB1) | (1 << PB3);
	//konfiguracija ulaza PD2, PD4 i PD5
	DDRD &= ~((1 << PD2) | (1 << PD4) | (1 << PD5));
	//pull up otpornici ukljuceni na PD2, PD4 i PD5
	PORTD |= (1 << PD2) | (1 << PD4) | (1 << PD5);
	// postavljanje Phase Correct PWM na?ina rada za timer1 - 10 bit
	timer1PhaseCorrectPWM10bit();
	// djelitelj frekvencije F_CPU / 8
	timer1SetPrescaler(TIMER1_PRESCALER_64);
	// neinvertirajuci PWM signal na PB1 (OC1A)
	timer1OC1AEnableNonInvertedPWM();
	interruptEnable(); // globalno omogu?enje prekida
}

int main(void) {
	
	init(); // inicijalizacija mikroupravlja?a
	float D;
	while (1) {
		// ispis na LCD displej

		D = adcReadScale0To100(ADC0);
		// osvjezavanje faktora vodenja kroz registar OCR1A
		timer1OC1ADutyCycle(D);
	}
}