/*
 Tema: UART komunikacija
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 11.3
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "UART/uart.h"
#include "Interrupt/interrupt.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
}
int main(void) {
	
	init(); // inicijalizacija mikroupravlja?a
	char port, pin, stanje;
	while (1) {
		if (uartIsMessageRecived())	{
			lcdClrScr();
			// prikaz primljene poruke
			lcdprintf("%s", uartBuffer);
		}
	}
}

