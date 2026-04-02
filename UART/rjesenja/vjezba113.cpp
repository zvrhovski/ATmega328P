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
	uartInit(38400); // inicijalizacija UART komunikacij
	interruptEnable(); // globalno omoguceni prekidi
	pinMode(B1, OUTPUT); // PB1 konfiguriran kao izlazni pin (crvena LED dioda)
	pinMode(B2, OUTPUT); // PB2 konfiguriran kao izlazni pin (zuta LED dioda)
	pinMode(B3, OUTPUT); // PB3 konfiguriran kao izlazni pin (zelena LED dioda)
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	char port, pin, stanje;
	while (1) {
		if (uartIsMessageRecived())	{
			lcdClrScr();
			// prikaz primljene poruke
			lcdprintf("%s", uartBuffer);
			port = uartBuffer[0];
			pin = uartBuffer[1];
			stanje = uartBuffer[2];
			// provjera prvog znaka
			if (port == 'B') {
				// automat stanja za promjenu stanja dioda
				switch(pin) {
					case '1':
					if (stanje == '1') digitalWrite(B1, 1);
					if (stanje == '0') digitalWrite(B1, 0);
					break;
					case '2':
					if (stanje == '1') digitalWrite(B2, 1);
					if (stanje == '0') digitalWrite(B2, 0);
					break;
					case '3':
					if (stanje == '1') digitalWrite(B3, 1);
					if (stanje == '0') digitalWrite(B3, 0);
					break;
					default:
					break;
				}
			}			
		}
	}
}

