/*
 Tema: UART komunikacija
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 11.1
 */ 

#include "AVR/avrlib.h"
#include <util/delay.h>
#include "UART/uart.h"

void init() {
	uartInit(19200); // inicijalizacija UART komunikacij
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	int brojPoruka = 1;
	while (1) {
		// ispis poruke sintaksom funkcije printf()
		uartprintf("%d. poruka\r", brojPoruka++);
		_delay_ms(1000);
		// ispis poruke sintaksom funkcije putchar()
		uartputchar('A');
		uartputchar('\r');
		_delay_ms(1000);
		// ispis poruke sintaksom funkcije puts()
		uartputs("ATmega328P ima 32 kB programske memorije!\r");
		_delay_ms(1000);
		// ispis poruke sintaksom funkcije printf()
		uartprintf("Temperatura: %.2f\r", 22.34);
		_delay_ms(1000);
		// ispis poruke sintaksom funkcije printf()
		uartprintf("Vlaga: %.2f%%\n\r", 57.82);
		_delay_ms(1000);
	}
}