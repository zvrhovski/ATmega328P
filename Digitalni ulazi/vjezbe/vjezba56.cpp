/*
 Tema: Digitalni ulazi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 5.6
 */ 

#include <avr/io.h>
#include "AVR/avrlib.h"

void init() {

}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	int korak = 1; // 1 = crvena, 2 = zuta, 3 = zelena
	
	while (1) { // beskonacna petlja
		// provjera padajuceg brida tipkala T1
		if (isFallingEdge(TIPKALO1)) {
			korak++; // korak u desno
			if (korak == 4) {
				korak = 1;
			}
		}
		// provjera padajuceg brida tipkala T2
		if (isFallingEdge(TIPKALO2)) {
			korak--; // korak u lijevo
			if (korak == 0) {
				korak = 3;
			}
		}
		// provjera padajuceg brida tipkala T3
		if (isFallingEdge(TIPKALO3)) {
			korak = 1; //reset na pocetak
		}
		
		switch (korak) {
			case 1: 
			digitalWrite(LED_CRVENO, HIGH); // crvena LED dioda on
			digitalWrite(LED_ZUTO, LOW); // zuta LED dioda off
			digitalWrite(LED_ZELENO, LOW); // zelena LED dioda off
			break;
			case 2:
			digitalWrite(LED_CRVENO, LOW); // crvena LED dioda off
			digitalWrite(LED_ZUTO, HIGH); // zuta LED dioda on
			digitalWrite(LED_ZELENO, LOW); // zelena LED dioda off
			break;
			case 3:
			digitalWrite(LED_CRVENO, LOW); // crvena LED dioda off
			digitalWrite(LED_ZUTO, LOW); // zuta LED dioda off
			digitalWrite(LED_ZELENO, HIGH); // zelena LED dioda on
			break;
			default:
			break;
		}
	}
	return 0;
}