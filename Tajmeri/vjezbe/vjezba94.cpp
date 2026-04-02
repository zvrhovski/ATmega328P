/*
 Tema: Tajmeri i broja?i
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 9.4
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"
#include "Senzori/lm35.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"

// konstanta koja se koristi umjesto ADC0
#define LM35 ADC0

// prekidna rutina za timer 0
ISR(TIMER0_OVF_vect) {

}

// prekidna rutina za timer 1
ISR(TIMER1_OVF_vect) {

}

// prekidna rutina za timer 2
ISR(TIMER2_OVF_vect) {

}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	// PB1 konfiguriran kao izlazni pin (crvena LED dioda)
	pinMode(B1, OUTPUT);
	// PB2 konfiguriran kao izlazni pin (zuta LED dioda)
	pinMode(B2, OUTPUT);
	// PB3 konfiguriran kao izlazni pin (zelena LED dioda)
	pinMode(B3, OUTPUT);
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