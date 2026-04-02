/*
 Biblioteka: watchdog.h
 Autor: Zoran Vrhovski
 Datum: 20. 4. 2022. 
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */ 

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include <avr/wdt.h>

// definicije vremena za watchdog - registar WDTCSR
#define WATCHDOG_TIME_16MS		 ((0 << WDP3) |(0 << WDP2) | (0 << WDP1) | (0 << WDP0))
#define WATCHDOG_TIME_32MS		 ((0 << WDP3) |(0 << WDP2) | (0 << WDP1) | (1 << WDP0))
#define WATCHDOG_TIME_64MS		 ((0 << WDP3) |(0 << WDP2) | (1 << WDP1) | (0 << WDP0))
#define WATCHDOG_TIME_125MS		 ((0 << WDP3) |(0 << WDP2) | (1 << WDP1) | (1 << WDP0))
#define WATCHDOG_TIME_250MS		 ((0 << WDP3) |(1 << WDP2) | (0 << WDP1) | (0 << WDP0))
#define WATCHDOG_TIME_500MS		 ((0 << WDP3) |(1 << WDP2) | (0 << WDP1) | (1 << WDP0))
#define WATCHDOG_TIME_1S		 ((0 << WDP3) |(1 << WDP2) | (1 << WDP1) | (0 << WDP0))
#define WATCHDOG_TIME_2S		 ((0 << WDP3) |(1 << WDP2) | (1 << WDP1) | (1 << WDP0))
#define WATCHDOG_TIME_4S		 ((1 << WDP3) |(0 << WDP2) | (0 << WDP1) | (0 << WDP0))
#define WATCHDOG_TIME_8S		 ((1 << WDP3) |(0 << WDP2) | (0 << WDP1) | (1 << WDP0))



// resetiranje Watchdog tajmera
void watchdogReset() {
	wdt_reset();
}


void watchdogOff(){
	
	interruptDisable();
	watchdogReset();
	/* Clear WDRF in MCUSR */
	MCUSR &= ~(1 << WDRF);
	/* Disable and clear all Watchdog settings.*/
	WDTCSR |= (1 << WDCE) | (1 << WDE);
	/* Turn off WDT */
	WDTCSR = 0x00;
	interruptEnable();
}


void watchdogSystemResetOn(uint8_t watchdogTime){
	
	interruptDisable();
	watchdogReset();
	// Setup Watchdog for system reset and not interrupt
	WDTCSR |= (1 << WDCE) | (1 << WDE);
	// Set new prescaler (time-out)
	WDTCSR = (1 << WDE) | watchdogTime;
	interruptEnable();
}


void watchdogInterruptAndSystemResetOn(uint8_t watchdogTime){
	
	interruptDisable();
	// Setup Watchdog for system reset and interrupt
	WDTCSR |= (1 << WDCE) | (1 << WDE);
	// Set new prescaler (time-out)
	WDTCSR = (1 << WDE) | (1 << WDIE) | watchdogTime;
	interruptEnable();
}


void watchdogInterruptOn(uint8_t watchdogTime){
	
	interruptDisable();
	// Setup Watchdog for interrupt and not system reset
	WDTCSR |= (1 << WDCE) | (1 << WDE);
	// Set new prescaler (time-out)
	WDTCSR = (1 << WDIE) | watchdogTime;
	interruptEnable();
}

// interrupt rutina za Wathdog
/*
ISR(WDT_vect){

}
*/



#endif /* WATCHDOG_H_ */