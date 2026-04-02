/*
 Tema: LCD displej
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 6.6
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	// kreiranje samo onih znakova koji su potrebni
	lcdCreateChar(0, customChar1); // znak like (FB)
	lcdCreateChar(1, customChar2); // znak c (ch)
	lcdCreateChar(2, customChar3); // znak c (tj)
	lcdCreateChar(3, customChar4); // znak d (dj)
	lcdCreateChar(4, customChar5); // znak š (sh)
	lcdCreateChar(5, customChar6); // znak ž (zh)
	lcdCreateChar(6, customChar7); // znak :-) (emotikon)
	lcdCreateChar(7, customChar8); // znak :-( (emotikon)
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	// prikazi kreirane znakove 
	lcdClrScr(); // obrisi LCD 
	lcdChar(0); // ispisi znak na adresi 0 
	// ispisi znakove na adresama 1, 2, 3, 4, 5, 6 i 7 
	lcdprintf("%c%c%c%c%c%c%c", 1,2,3,4,5,6,7);
	_delay_ms(5000);	
	
	lcdClrScr(); // obrisi LCD 
	lcdGotoXY(1,2); // ispis u 1. redak, 2. stupac
	lcdprintf("Mikroupravlja%ci\n", 1);	// adresa slova c je 1 
	lcdGotoXY(2,3); // ispis u 2. redak, 3. stupac
	// adresa slova z je 5, s je 4 i c je 2
	lcdprintf("su naj%ce%c%ci!", 5, 4, 2);	
	
	while (1) { // beskonacna petlja
		_delay_ms(100);
	}
	return 0;
}