/*
 Tema: Tajmeri i broja?i
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 9.1
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
	timer0SetValue(6); // pocetna vrijednost TCNT0 za 16 ms 
	toggle_pin(PORTB, PB2); // promjena stanja na zute LED diode
}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	config_output(DDRB, PB2); // PB2 konfiguriran kao izlazni pin (zuta LED dioda)
	interruptEnable(); // globalno omogucenje prekida
	// postavljanje normalnog nacina rada
	timer0NormalMode();
	// djelitelj frekvencije F_CPU / 1024
	timer0SetPrescaler(TIMER0_PRESCALER_1024);
	timer0InterruptOVFEnable(); // omogucenje prekida preljevom za timer0
	timer0SetValue(6); // pocetna vrijednost TCNT0 za 16 ms
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
