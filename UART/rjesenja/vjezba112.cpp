/*
 Tema: UART komunikacija
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 11.2
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "UART/uart.h"
#include "Interrupt/interrupt.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	uartInit(19200); // inicijalizacija UART komunikacij
	interruptEnable(); // globalno omoguceni prekidi
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca

	while (1) {
		if (uartIsMessageRecived())	{
			lcdClrScr();
			// prikaz primljene poruke
			lcdprintf("%s", uartBuffer);
			uartprintf("%s\r", uartBuffer);
		}
	}
}