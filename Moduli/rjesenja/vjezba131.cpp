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
#define ENCODER_LOW_THRESHOLD 0
// najveca moguca vrijednost enkodera
#define ENCODER_HIGH_THRESHOLD 100

// zastavica koja oznacava trenutni smjer vrtnje enkodera
volatile int8_t encDir = 0;
// zastavica koja oznacava promijenu vrijednosti enkodera
volatile bool encUpdated = true;
// varijabla za spremanje trenutne vrijednosti enkodera
volatile int8_t encValue = 0;

// funkcija za azuriranje trenutne vrijednosti enkodera
void updateEncoder(int8_t dir) {

	if (dir == 1) {	// smjer u smjeru kazaljke na satu
		// ako je vrijednost enkodera manja od najvece moguce
		if (encValue < ENCODER_HIGH_THRESHOLD) {
			encValue++;		// uvecaj vrijednost enkodera za 1
		}
	} else {
		// ako je vrijednost enkodera veca od najmanje moguce
		if (encValue > ENCODER_LOW_THRESHOLD) {
			encValue--;		// smanji vrijednost enkodera za 1
		}
	}
	// postavi zastavicu u logicku istinu, kad zavrsi azuriranje
	encUpdated = true;
}

// prekidna rutina -> promjena signala na kanalu A
ISR(INT0_vect) {
	
	if (get_pin(PIND, PD4)) {		// ako je B - HIGH
		encDir = 1;		// smjer jkazaljke na satu
		} else {
		encDir = 0;		// smjer suprotnom kazaljci na satu
	}
	// poziv funkcije za azuriranje vrijednosti enkodera
	updateEncoder(encDir);
}


void init() {		// inicijalizacija mikroracunala
	
	lcdInit();		// inicijalizacija LCD displeja
	
	int0Enable();	// INT0 na pinu PD2 je omogucen
	int0FallingEdge();	// padajuci brid PD2 aktivira
	interruptEnable();	// globalno omogucavanje prekida
	
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
			
			lcdClrScr();	// ciscenje cijelog LCD displeja
			lcdHome();		// pokazivac LCD na koordinate 0,0
			// ispis trenutne vrijednosti enkodera na displej
			lcdprintf("Enc: %d", encValue);
			
			if (encDir == 1)	// smjer kazaljke na satu
				dirChar = 62;	// ASCII kod strelica desno >
			else
				dirChar = 60;	// ASCII kod strelica lijevo <
			
			lcdGotoXY(1,11);	// pokazivac LCD na koordinate 1,11
			// ispis trenutnog smjera enkodera na displej
			lcdprintf("Dir: %c\n", dirChar);
			
			// izracun vrijednosti za prikaz loading bara
			loading = 16 * encValue / 100.0;
			
			// ispis loading bara na LCD displej
			for(uint8_t i = 0; i < loading; i++) {
				lcdChar(255);
			}
			
			encUpdated = 0;		// zastavica za ispis
		}
		
		// pritisnuto tipkalo enkodera, padajuci brid detekcija
		if(isFallingEdge(D5))
		{
			encValue = 0;	// postavi vrijednost na nulu
			encUpdated = 1;	// zastavica za azuriranje aktivna
		}
	}
}