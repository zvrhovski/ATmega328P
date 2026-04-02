/*
 Tema: Watchdog tajmer
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 14.2
 */ 

#include "AVR/avrlib.h"
#include "Interrupt/interrupt.h"
#include "LCD/lcd.h"
#include "AVR/watchdog.h"
#include <avr/eeprom.h>

uint8_t watchdogBroj;

// watchdog prekidna rutina
ISR(WDT_vect){
	lcdHome();
	lcdprintf("WDT reset\n");
	lcdprintf("Spremam podatke");
	// spemi varijablu watchdogBroj prije reseta
	eeprom_write_byte((uint8_t*)0, watchdogBroj);
}

void init() {
	watchdogOff(); // iskljuci Watchdog tajmer
	_delay_ms(2000);
	lcdInit(); // inicijalizacija LCD displeja
	// pin PD2 konfiguriran kao ulaz + ukljucen pritezni otpornik
	pinMode(D2, INPUT_PULLUP);
	watchdogInterruptAndSystemResetOn(WATCHDOG_TIME_2S);
	// ucitaj spremljeni podatak iz EEPROM memorije
	watchdogBroj = eeprom_read_byte((uint8_t*)0);
	interruptEnable(); // globalno omogucenje prekida
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	while (1) {
		// ispis na LCD displej
		lcdClrScr();
		lcdprintf("%u", watchdogBroj++);
		_delay_ms(1000);
		
		// dodatno kasnjenje koje ce pokrenuti watchdog tajmer
		if(isFallingEdge(D2)) {
			_delay_ms(60000);
		}
		// resetiranje watchdoga za novi ciklus
		watchdogReset();
	}
}
