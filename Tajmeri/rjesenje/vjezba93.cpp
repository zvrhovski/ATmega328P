/*
 Tema: Tajmeri i broja?i
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 9.3
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"
#include "Senzori/lm35.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"
// konstanta koja se koristi umjesto ADC0
#define LM35 ADC0

volatile uint8_t timer2PrazanHod = 0;
// prekidna rutina za timer 2
ISR(TIMER2_OVF_vect) {
	timer2SetValue(131); // pocetna vrijednost TCNT2 za 8 ms
	timer2PrazanHod++; // povecaj broj poziva za 1
	if (timer2PrazanHod == 15 )	{ // ako je timer2PrazanHod = 15 * 8 ms = 120 ms
		timer2PrazanHod = 0; // vrati broj poziva na 0
		toggle_pin(PORTB, PB1); // promjena stanja na crvene LED diode
	}
}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	// PB1 konfiguriran kao izlazni pin (crvena LED dioda)
	config_output(DDRB, PB1);
	interruptEnable(); // globalno omogucenje prekida
	// postavljanje normalnog nacina rada
	timer2NormalMode();
	// djelitelj frekvencije F_CPU / 1024
	timer2SetPrescaler(TIMER2_PRESCALER_1024);
	timer2InterruptOVFEnable(); // omogucenje prekida preljevom za timer2
	timer2SetValue(131); // pocetna vrijednost TCNT2 za 8 ms
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