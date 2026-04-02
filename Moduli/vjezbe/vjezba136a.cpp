/*
 Tema: Povezivanje odabranih elektronickih modula na mikroupravljac - RGB LE dioda
 Autor: Danijel Radocaj
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 13.6.a
*/

#include "AVR/avrlib.h"
#include "Timer/timer.h"
#include "LCD/lcd.h"
#include "Interrupt/interrupt.h"
#include <avr/io.h>
#include <util/delay.h>

void init() {
	
	// inicijalizacija LCD displeja

	// djelitelj frekvencije
	// djelitelj frekvencije
	
	// timer 1 - phase correct u 8bit
	// timer 2 - phase correct

	// neinvertirajuci PWM pin OC1A
	// neinvertirajuci PWM pin OC1B
	// neinvertirajuci PWM pin OC2A
	
	// pinovi izlazni PWM
	
	// globalno omoguci prekidne rutine
}

int main(void) {

	init();		// poziv funkcije za inicijalizaciju mikroracunala
	
	uint8_t RGB[3] = {10, 10, 10};		// polje RGB kanala LED diode
	
	while(1) {
		
		timer1OC1ADutyCycle(RGB[0]);	// PWM signal na kanalu OC1A - PB1
		timer1OC1BDutyCycle(RGB[1]);	// PWM signal na kanalu OC1B - PB2
		timer2OC2ADutyCycle(RGB[2]);	// PWM signal na kanalu OC2A - PB3
		
		lcdClrScr();	// ocisti LCD displej
		lcdHome();		// postavljanje pokazivaca LCD displeja
		lcdprintf("R%u G%u B%u", RGB[0], RGB[1], RGB[2]);	// ispis
		
		_delay_ms(250);
		
	}
}