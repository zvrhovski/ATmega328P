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

volatile uint8_t timer0PrazanHod = 0;

// prekidna rutina za timer 0
ISR(TIMER0_OVF_vect) {
	timer0SetValue(6); // pocetna vrijednost TCNT0 za 16 ms
	timer0PrazanHod++; // povecaj broj poziva za 1
	if (timer0PrazanHod == 25)	{ // ako je timer0PrazanHod = 25 * 16 ms = 400 ms
		timer0PrazanHod = 0; // vrati broj poziva na 0
		digitalToggle(B1); // promjena stanja na crvene LED diode
	}
}

// prekidna rutina za timer 1
ISR(TIMER1_OVF_vect) {
	timer1SetValue(40536); // pocetna vrijednost TCNT1 za 400 ms
	digitalToggle(B2); // promjena stanja na zute LED diode
}

volatile uint8_t timer2PrazanHod = 0;

// prekidna rutina za timer 2
ISR(TIMER2_OVF_vect) {
	timer2SetValue(6); // pocetna vrijednost TCNT2 za 8 ms
	timer2PrazanHod++; // povecaj broj poziva za 1
	if (timer2PrazanHod == 25)	{ // ako je timer2PrazanHod = 25 * 16 ms = 400 ms
		timer2PrazanHod = 0; // vrati broj poziva na 0
		digitalToggle(B3); // promjena stanja na zelene LED diode
	}
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
	interruptEnable(); // globalno omogucenje prekida
	// postavljanje normalnog nacina rada
	timer0NormalMode();
	timer1NormalMode();
	timer2NormalMode();
	// djelitelji frekvencije
	timer0SetPrescaler(TIMER0_PRESCALER_1024); // F_CPU / 1024
	timer1SetPrescaler(TIMER1_PRESCALER_256); //  F_CPU / 256
	timer2SetPrescaler(TIMER2_PRESCALER_1024); //  F_CPU / 1024
	timer0InterruptOVFEnable(); // omogucenje prekida preljevom za timer0
	timer1InterruptOVFEnable(); // omogucenje prekida preljevom za timer1
	timer2InterruptOVFEnable(); // omogucenje prekida preljevom za timer2
	timer0SetValue(6); // pocetna vrijednost TCNT0 za 16 ms
	timer1SetValue(40536); // pocetna vrijednost TCNT1 za 400 ms
	timer2SetValue(6); // pocetna vrijednost TCNT2 za 16 ms
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	float T; // temperatura u okolini senzora LM35
	while (1) {
		T = readTempLM35(LM35); // citaj temperaturu na LM35
		// brisanje znakova LCD displeja +  home pozicija kursora
		lcdClrScr();
		// ispis na LCD displej (sintaksa funkcije printf())
		lcdprintf("T = %.2f%c", T, 223);
		_delay_ms(1000);
	}
}