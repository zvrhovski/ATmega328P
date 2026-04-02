/*
 Tema: LCD displej
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 6.5
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"

#define TIPKALO1 D4
#define TIPKALO2 D2
#define TIPKALO3 D5

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	// tipkalo T1
	pinMode(TIPKALO1, INPUT_PULLUP); // PD4 konfiguriran kao ulaz
	// ukljucen pull up otpornik na pinu PD4
	// tipkalo T2
	pinMode(TIPKALO2, INPUT_PULLUP); // PD2 konfiguriran kao ulaz
	// ukljucen pull up otpornik na pinu PD2
	pinMode(TIPKALO3, INPUT_PULLUP); // PD5 konfiguriran kao ulaz
	// ukljucen pull up otpornik na pinu PD5
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	uint8_t izbornik = 0;
	// parametri unutar izbornika
	// p[0], pMin[0], pMax[0], pStep[0] -> frekvencija
	// p[1], pMin[1], pMax[1], pStep[1] -> napon
	// p[2], pMin[2], pMax[2], pStep[2] -> struja 1
	// p[3], pMin[3], pMax[3], pStep[3] -> struja 2
	int16_t p[4] = {}; // inicijalno su svi parametri 0
	// minimalne vrijednosti parametara
	const int16_t pMin[4] = {0, -12, -1000, -20000};
	// maksimalne vrijednosti parametara
	const int16_t pMax[4] = {50, 12, 1000, 20000};
	// korak promjene parametara
	const int16_t pStep[4] = {2, 1, 50, 500};
	// varijabla kojom se omogucuje ispis na LCD	
	bool ispisNaLcd = true;
	// imena izbornika koji se ispisuju na LCD
	const char imeIzbornika[4][12] = {
		"Frekvencija",
		"Napon",
		"Struja 1",
		"Struja 2",
	};
	// imena parametara koji se ispisuju na LCD
	const char imeParametra[4][3] = {
		"f",
		"u",
		"i1",
		"i2",
	};
	// imena mjernih jedinica koji se ispisuju na LCD
	const char imeMjerneJedinice[4][3] = {
		"Hz",
		"V",
		"mA",
		"mA",
	};
		
	while (1) { // beskonacna petlja
		// ako se pojavio padajuci brid na tipkalu T1
		if (isFallingEdge(TIPKALO1)) {
			p[izbornik] -= pStep[izbornik]; // smanji za korak
			// ogranici parametar odozdo
			if (p[izbornik] < pMin[izbornik]) {
				p[izbornik] = pMin[izbornik];
			} else {
				ispisNaLcd = true; // omoguci ispis na LCD
			}
		}
		// ako se pojavio padajuci?i brid na tipkalu T2
		if (isFallingEdge(TIPKALO2)) {
			p[izbornik] += pStep[izbornik]; // povecaj za korak
			// ogranici parametar odozgo
			if (p[izbornik] > pMax[izbornik]) {
				p[izbornik] = pMax[izbornik];
				} else {
				ispisNaLcd = true; // omoguci ispis na LCD
			}
		}
		// ako se pojavio padajuci brid na tipkalu T3
		if (isFallingEdge(TIPKALO3)) {
			izbornik++; // povecaj brojac za 1
			// cirkularna promjena izbornika
			if (izbornik >= 4) {
				izbornik = 0;
			}
			ispisNaLcd = true; // omoguci ispis na LCD
		}		
		// ako je omogucen ispis
		if (ispisNaLcd) { 
			// brisanje znakova LCD displeja +  home pozicija kursora
			lcdClrScr(); 
			// switch case za prikaz izbornika
			switch (izbornik) {
				case 0: 
					lcdprintf("Frekvencija\n"); 					
					lcdprintf("f = %d Hz", p[izbornik]);
					break;
				case 1:
					lcdprintf("Napon\n");
					lcdprintf("u = %d V", p[izbornik]);
					break;
				case 2:
					lcdprintf("Struja 1\n");
					lcdprintf("i1 = %d mA", p[izbornik]);
					break;
				case 3:
					lcdprintf("Struja 2\n");
					lcdprintf("i2 = %d mA", p[izbornik]);
					break;
				default:
					break;
			}
			ispisNaLcd = false;	// onemoguci ispis na LCD
		}
		/* // drugi nacin 
		if (ispisNaLcd) {
			// brisanje znakova LCD displeja +  home pozicija kursora
			lcdClrScr();
			lcdprintf("%s\n", imeIzbornika[izbornik]);
			lcdprintf("%s = %d %s", imeParametra[izbornik], p[izbornik],
			imeMjerneJedinice[izbornik]);
			ispisNaLcd = false;	// onemoguci ispis na LCD
		}
		// */
	}
	return 0;
}