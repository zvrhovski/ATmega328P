/*
 Tema: Sleep modovi i power modovi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 14.3
 */ 

#include "AVR/avrlib.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"
#include "LCD/lcd.h"
#include <avr/sleep.h>
#include <avr/power.h>

volatile uint8_t brojac = 1;

// prekidna rutina INT0 za wake up
ISR(INT0_vect){
	lcdClrScr();
	lcdprintf("Probudio sam se\n");
	lcdprintf("%d. puta!!!!", brojac++);
	// brojac se osvježava nakon wake up
}

// sklop Timer1 koji mijenja stanje žute LED diode
ISR(TIMER1_OVF_vect){
	timer1SetValue(3096);
	digitalToggle(B2);
}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	pinMode(B1, OUTPUT); // PB1 konfiguriran kao izlazni pin (crvena LED dioda)
	pinMode(B2, OUTPUT); // PB2 konfiguriran kao izlazni pin (žuta LED dioda)
	// pin PD2 konfiguriran kao ulaz + ukljucen pritezni otpornik
	pinMode(D2, INPUT_PULLUP);
	interruptEnable(); // globalno omogucenje prekida
	int0Enable(); // omoguci INT0 prekide
	int0FallingEdge(); // INT0 prekida na padajuci brid
	// postavljanje normalnog na?ina rada
	timer1NormalMode();
	timer1SetPrescaler(TIMER1_PRESCALER_64); // F_CPU/64
	// omogu?enje prekida preljevom za timer1
	timer1InterruptOVFEnable();
	// po?etna vrijednost TCNT1 za 250 ms
	timer1SetValue(3096);
	// konfiguracija sleep moda
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	// isklju?enje sklopa Timer/Counte1
	//power_timer1_disable();
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	// ispis statusne poruke
	lcdprintf("Sleep modovi!");

	while (1) {
		// sekvenca za crvenu LED diodu
		digitalWrite(B1, 1);
		_delay_ms(1000);
		digitalWrite(B1, 0);
		_delay_ms(1000);
		digitalWrite(B1, 1);
		_delay_ms(1000);
		digitalWrite(B1, 0);
		// ispis statusne poruke
		lcdClrScr();
		lcdprintf("Spavam %d. puta", brojac);
		// slanje mikroupravljaca u sleep
		sleep_mode();
	}
}