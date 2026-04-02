/*
 Tema: Povezivanje odabranih elektronickih modula na mikroupravljac - Rotacijski enkoder
 Autor: Danijel Radocaj
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 13.1
*/ 

#include <avr/io.h>
#include "AVR/avrlib.h"
#include "Interrupt/interrupt.h"
#include "LCD/lcd.h"

// najmanja moguca vrijednost enkodera
// najveca moguca vrijednost enkodera

// zastavica koja oznacava trenutni smjer vrtnje enkodera
// zastavica koja oznacava promijenu vrijednosti enkodera
// varijabla za spremanje trenutne vrijednosti enkodera

// funkcija za azuriranje trenutne vrijednosti enkodera
void updateEncoder(int8_t dir) {
	if (dir == 1) {	// smjer u smjeru kazaljke na satu
	
		// ako je vrijednost enkodera manja od najvece moguce
		
		// uvecaj vrijednost enkodera za 1
	} else {
		// ako je vrijednost enkodera veca od najmanje moguce
		
		// smanji vrijednost enkodera za 1
	}
	
	// postavi zastavicu u logicku istinu, kad zavrsi azuriranje
}

// prekidna rutina -> promjena signala na kanalu A
ISR(INT0_vect) {
	
	if (get_pin(PIND, PD4)) {		// ako je B - HIGH
	// smjer jkazaljke na satu
	} else {
	// smjer suprotnom kazaljci na satu
	}
	// poziv funkcije za azuriranje vrijednosti enkodera
	
}

void init() {		// inicijalizacija mikroracunala
	
	// inicijalizacija LCD displeja
	
	// INT0 na pinu PD2 je omogucen
	// padajuci brid PD2 aktivira
	// globalno omogucavanje prekida
	
	config_input(DDRD, PD2);	// pin PD2 ulazni
	config_input(DDRD, PD4);	// pin PD4 ulazni
	config_input(DDRD, PD5);	// pin PD5 ulazni
	
	pull_up_on(PORTD, PD2);		// pull-up ulazni pin PD2
	pull_up_on(PORTD, PD4);		// pull-up ulazni pin PD4
	pull_up_on(PORTD, PD5);		// pull-up ulazni pin PD5
}

int main(void) {
	
	init();		// inicijalizacija uC
	
	uint8_t loading = 0;	// varijabla za simulaciju loading
	char dirChar;		// pomocna varijabla za znak strelice
	
	while (1) {
		
		if(encUpdated) {
			
			// ciscenje cijelog LCD displeja
			// pokazivac LCD na koordinate 0,0
			// ispis trenutne vrijednosti enkodera na displej
			
			if (encDir == 1) {	// smjer kazaljke na satu
				dirChar = 62;	// ASCII kod strelica desno >
			} else {
				dirChar = 60;	// ASCII kod strelica lijevo <
			}
			lcdGotoXY(1,11);	// pokazivac LCD na koordinate 1,11
			// ispis trenutnog smjera enkodera na displej
			
			// izracun vrijednosti za prikaz loading bara

			// ispis loading bara na LCD displej
			for(uint8_t i = 0; i < loading; i++) {
				lcdChar(255);
			}
			
			encUpdated = false;		// zastavica za ispis
		}
		
		// pritisnuto tipkalo enkodera, padajuci brid detekcija
		if(isFallingEdge(D5))
		{
			encValue = 0;	// postavi vrijednost na nulu
			encUpdated = true;	// zastavica za azuriranje aktivna
		}
	}
}