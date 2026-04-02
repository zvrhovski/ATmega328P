/*
 Datoteka: rgbLED.cpp
 Namjena biblioteke: RGB LE dioda
 Autor: Danijel Radocaj
 Licenca: Ovo djelo je dano na koristenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */

#include "rgbLED.h"

// USER CODE

void rgbINIT()		// funkcija za inicijalizaciju RGB LE diode
{
	// timer 1 - djelitelj frekvencije postavljen na 64
	TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
	TCCR1B |= ((0 << CS12) | (1 << CS11) | (1 << CS10));
	
	// timer 2 - djelitelj frekvencije postavljen na 64
	TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
	TCCR2B |= ((1 << CS22) | (0 << CS21) | (0 << CS20));
	
	// timer 1 - phase correct nacin rada - 8-bit counting
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));
	TCCR1A |= (0 << WGM11) | (1 << WGM10);
	TCCR1B |= (0 << WGM13) | (0 << WGM12);
	
	// timer 2 - phase correct nacin rada - 8-bit counting
	TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
	TCCR2B &= ~(1 << WGM22);
	TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) | (1 << COM2B0));
	TCCR2A |= (0 << WGM21) | (1 << WGM20);
	TCCR2B |= (0 << WGM22);
	
	//timer 1 - OC1A neinvertirajuci PWM izlaz omogucen
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
	TCCR1A |= (1 << COM1A1) | (0 << COM1A0);
	
	//timer 1 - OC1B neinvertirajuci PWM izlaz omogucen
	TCCR1A &= ~((1 << COM1B1) | (1 << COM1B0));
	TCCR1A |= (1 << COM1B1) | (0 << COM1B0);
	
	//timer 2 - OC2A neinvertirajuci PWM izlaz omogucen
	TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0));
	TCCR2A |= (1 << COM2A1) | (0 << COM2A0);
	
	DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3);	// izlazni PWM - OC1A, OC1B, OC2A
}

void rgbCHwrite(uint8_t chR, uint8_t chG, uint8_t chB)		// funkcija za postavljanje duty cycle vrijednosti za PWM kanale  - OC1A, OC1B, OC2A
{
	// timer 1 - OC1A - Duty Cycle skaliran s 100 na 255
	OCR1A = chR * 255 / 100;
	
	/// timer 1 - OC1B - Duty Cycle skaliran s 100 na 255
	OCR1B = chG * 255 / 100;
	
	/// timer 2 - OC2A - Duty Cycle skaliran s 100 na 255
	OCR2A = chB * 255 / 100;
}

// END USER CODE