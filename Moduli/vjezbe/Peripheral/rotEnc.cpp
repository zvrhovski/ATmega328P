/*
 Datoteka: rotEnc.cpp
 Namjena biblioteke: Rotacijski enkoder
 Autor: Danijel Radocaj
 Licenca: Ovo djelo je dano na koristenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */
#include "rotEnc.h"

// USER CODE

void rotEncINIT()
{
	EIMSK |= (1 << INT0);	// vanjska prekidna rutina INT0 na pinu PD2 je omogucena
	
	EICRA &= ~((1 << ISC01) | (1 << ISC00));
	EICRA |= (1 << ISC01) | (0 << ISC00);	// padajuci brid signala na pinu PD2 ce aktivirati prekidnu rutinu
	
	DDRD &= ~(1 << PD2);	// inicijalizacija pina PD2 kao ulaznog pina
	DDRD &= ~(1 << PD4);	// inicijalizacija pina PD4 kao ulaznog pina
	DDRD &= ~(1 << PD5);	// inicijalizacija pina PD5 kao ulaznog pina
	
	PORTD |= (1 << PD2);	// ukljucivanje pull-up otpornika za ulazni pin PD2
	PORTD |= (1 << PD4);	// ukljucivanje pull-up otpornika za ulazni pin PD4
	PORTD |= (1 << PD5);	// ukljucivanje pull-up otpornika za ulazni pin PD5
}

bool rotEncBTN()			// funkcija za detekciju stanja tipkala rotacijskog enkodera
{
	if(isFallingEdge(D5))	// na padajuci brid ulaznog pina PD5 vrati bool = 1
		return 1;
	else
		return 0;			// inace bool = 0
}

bool rotEncDIR()		// funkcija za detekciju smjera okretanja rotacijskog enkodera
{
	if (get_pin(PIND, PD4))		// ako je kanal B enkodera u visokom stanju
		return 1;				// smjer je u smjeru kazaljke na satu
	else
		return 0;				// smjer je u u smjeru suprotnom kazaljci na satu
}

uint8_t rotEncUPDATEnREAD(uint8_t enc)		// azuriranje i citanje vrijednosti RE u varijablu
{
	if (rotEncDIR() == 1)	// smjer u smjeru kazaljke na satu
	{
		if (enc < ENCODER_HIGH_THRESHOLD)	// ako je trenutna vrijednost enkodera manja od najvece moguce
			enc = enc + 10;					// uvecaj trenutnu vrijednost enkodera za 1
	}
	
	else
	{
		if (enc > ENCODER_LOW_THRESHOLD)	// ako je trenutna vrijednost enkodera veca od najmanje moguce
			enc = enc - 10;					// smanji trenutnu vrijednost enkodera za 1
	}
	
	return enc;
}

// END USER CODE