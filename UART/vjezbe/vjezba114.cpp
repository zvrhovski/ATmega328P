/*
 Tema: UART komunikacija
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 11.4
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "UART/uart.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	uartInit(19200); // inicijalizacija UART komunikacij
	interruptEnable(); // globalno omoguceni prekidi
	pinMode(B1, OUTPUT); // PB1 konfiguriran kao izlazni pin (crvena LED dioda)
	pinMode(B2, OUTPUT); // PB2 konfiguriran kao izlazni pin (zuta LED dioda)
	// postavljanje Phase Correct PWM nacina rada za timer1 - 8 bit
	timer1PhaseCorrectPWM8bit();
	// djelitelj frekvencije F_CPU / 8
	timer1SetPrescaler(TIMER1_PRESCALER_8);
}

int main(void) {
	
	init(); // inicijalizacija mikroupravlja?a
	int dutyCrvena = 0;
	int dutyZuta = 0;
	bool DUpdate = false;
	char pin, stanje;
	while (1) {
		if (uartIsMessageRecived())	{
			lcdClrScr();
			// prikaz primljene poruke
			lcdprintf("%s", uartBuffer);
		}
	}
}