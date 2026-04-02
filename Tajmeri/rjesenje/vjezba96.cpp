/*
 Tema: Tajmeri i broja?i
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 9.6
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"

volatile uint16_t brojPrekida = 0;
// prekidna rutina za brojac 0
ISR(TIMER0_OVF_vect) {
	brojPrekida++;
}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	config_input(DDRD, PD4); // konfiguriranje ulaza PD4
	pull_up_on(PORTD, PD4); // pull up ukljucen na ulazu PD4
	interruptEnable(); // globalno omogucenje prekida
	// postavljanje normalnog nacina rada
	timer0NormalMode();
	// djelitelj frekvencije F_CPU / 1024
	timer0SetPrescaler(TIMER0_EXTERNAL_FALL_EDGE);
	timer0InterruptOVFEnable(); // omogucenje prekida preljevom za timer0
	timer0SetValue(0); // pocetna vrijednost TCNT0
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	// aktualni i stari broj impulsa rotacijskog enkodera
	int brojImpulsa = 0;
	int brojImpulsaOld = 0;
	// brisanje znakova LCD displeja +  home pozicija kursora
	lcdClrScr();
	// ispis na LCD displej (sintaksa funkcije printf())
	lcdprintf("BrImp = %d", brojImpulsa);
    while (1) {
		//izra?un ukupnog broja impulsa
		brojImpulsa = brojPrekida * 256 + timer0GetValue();
		if (brojImpulsa != brojImpulsaOld) { 
			// brisanje znakova LCD displeja +  home pozicija kursora
			lcdClrScr();
			// ispis na LCD displej (sintaksa funkcije printf())
			lcdprintf("BrImp = %d", brojImpulsa);
			// postavljanje stare vrijednosti broja impulsa
			brojImpulsaOld = brojImpulsa;
		}
    }
}
