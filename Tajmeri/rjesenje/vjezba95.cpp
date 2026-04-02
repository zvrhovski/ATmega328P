/*
 Tema: Tajmeri i broja?i
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 9.5
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"
#include "Senzori/lm35.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"
// konstanta koja se koristi umjesto ADC0
#define LM35 ADC0

volatile bool uzmiUzorak = false;

// prekidna rutina za timer 1
ISR(TIMER1_OVF_vect) {
	timer1SetValue(3036); // pocetna vrijednost TCNT1 za 1000 ms
	uzmiUzorak = true; // omoguci mjerenje temperature 
}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	interruptEnable(); // globalno omogucenje prekida
	// postavljanje normalnog nacina rada
	timer1NormalMode();
	// djelitelj frekvencije F_CPU / 256
	timer1SetPrescaler(TIMER1_PRESCALER_256);
	timer1InterruptOVFEnable(); // omogucenje prekida preljevom za timer1
	timer1SetValue(3036); // pocetna vrijednost TCNT1 za 1000 ms
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	float T; // temperatura u okolini senzora LM35
	while (1) {
		if (uzmiUzorak)	{
			T = readTempLM35(LM35); // citaj temperaturu na LM35
			// brisanje znakova LCD displeja +  home pozicija kursora
			lcdClrScr();
			// ispis na LCD displej (sintaksa funkcije printf())
			lcdprintf("T = %.2f%c", T, 223);
			// onemogu?i mjerenje temperature sljede?ih 1000 ms
			uzmiUzorak = false; 
		}
	}
}
