/*
 Tema: LCD displej
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 6.4
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"

#define TIPKALO1 D4
#define TIPKALO2 D2

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	// tipkalo T1
	pinMode(TIPKALO1, INPUT_PULLUP); // PD4 konfiguriran kao ulaz
	// uklju?en pull up otpornik na pinu PD4
	// tipkalo T2
	pinMode(TIPKALO2, INPUT_PULLUP); // PD2 konfiguriran kao ulaz
	// uklju?en pull up otpornik na pinu PD2
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	// varijable za brojanje broj pritisaka tipkala
	uint16_t brojacTipkalo1 = 0;
	uint16_t brojacTipkalo2 = 0;
	// varijable za stare vrijednosti broja pritisaka tipkala
	uint16_t brojacTipkalo1Old = 0;
	uint16_t brojacTipkalo2Old = 0;
	// boolean varijabla kojom se omogucje ispis na LCD
	bool ispisNaLcd = true; 
	// ispis fiksnog teksta na LCD
	lcdClrScr();
	lcdprintf("T1: \n");
	lcdprintf("T2: ");
	
	while (1) { // beskonacna petlja
		// ako se pojavio padajuci brid na tipkalu T1
		if (isFallingEdge(TIPKALO1)) {
			brojacTipkalo1++; // povecaj brojac za 1
		}
		// ako se pojavio padajuci?i brid na tipkalu T2
		if (isFallingEdge(TIPKALO2)) {
			brojacTipkalo2++; // povecaj brojac za 1
		}
		// ako je bilo promjene broja?a za tipkalo T1
		if (brojacTipkalo1 != brojacTipkalo1Old) {
			ispisNaLcd = true; // omoguci ispis na LCD
		}		
		// ako je bilo promjene broja?a za tipkalo T2
		if (brojacTipkalo2 != brojacTipkalo2Old) {
			ispisNaLcd = true;  // omogu?i ispis na LCD
		}
		// ako je omogu?en ispis
		if (ispisNaLcd) { 
			// ispis na LCD displej (sintaksa funkcije printf())
			lcdGotoXY(1, 5); // pozicioniranje kursora u 1. red, 5. stupac
			lcdprintf("%u    ", brojacTipkalo1); // ispiši broj i obriši 4 mjesta
			lcdGotoXY(2, 5); // pozicioniranje kursora u 2. red, 5. stupac
			lcdprintf("     "); // izbriši 5 mjesta (prepiši sa Space)		
			lcdGotoXY(2, 5); // pozicioniranje kursora u 2. red, 5. stupac
			lcdprintf("%u", brojacTipkalo2); // ispiši broj		
			ispisNaLcd = false;	// onemogu?i ispis na LCD
		}
		// na kraju while petlje pripremmiti stare vrijednosti za novi ciklus
		brojacTipkalo1Old = brojacTipkalo1;
		brojacTipkalo2Old = brojacTipkalo2; 
	}
	return 0;
}