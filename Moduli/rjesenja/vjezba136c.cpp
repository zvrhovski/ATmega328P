/*
 Tema: Povezivanje odabranih elektronickih modula na mikroupravljac - RGB LE dioda
 Autor: Danijel Radocaj
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 13.6.c
*/

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "Interrupt/interrupt.h"
#include "Peripheral/rgbLED.h"
#include "UART/uart.h"
#include <avr/io.h>
#include <util/delay.h>

void init() {		// inicijalizacija mikroracunala
	
	rgbINIT();		// inicijalizacija RGB LE diode
	lcdInit();		// inicijalizacija LCD displeja
	uartInit(9600);	// inicijalizacija serijske komunikacije
	interruptEnable();	// globalne prekidne rutine
	
}	

int main(void) {
	
	init();		// poziv inicijalizacije mikroupravljaca
	
	uint8_t RGB[3] = {0, 0, 0};		// polje vrijednosti RGB kanala
	
	while (1) {

		if(uartIsMessageRecived()) {		// ako je pristigla poruka
			
			lcdClrScr();		// ocisti LCD
			lcdHome();		// pokazivac LCD postavi koordinate 1,1
			lcdprintf("%s\n", uartBuffer);	// ispisi poruku na LCD izvorno
			
			if(uartBuffer[0] == 'L') {	// prvi znak L -> RGB
				
				RGB[0] = 0;		// postavi R kanal RGB diode na 0
				RGB[1] = 0;		// postavi G kanal RGB diode na 0
				RGB[2] = 0;		// postavi B kanal RGB diode na 0
				
				// izdvajanje informacija iz poruke npr. L25-50-75e
				// (R kanal: 25%, G kanal: 50%, B kanal: 75%)
				
				for(uint8_t i = 1, j = 0; uartBuffer[i] != 'e'; i++) {
					if (uartBuffer[i] != '-') {		// znak za razdvajanje
						// spajanje znamenki
						RGB[j] = RGB[j] * 10  + (uartBuffer[i] - 48);
					}
					else {
						j++;	// iduca vrijednost
					}
				}
				// azuriranje vrijednosti kanala RGB
				rgbCHwrite(RGB[0], RGB[1], RGB[2]);
				// ispis izdvojenih R, G i B
				lcdprintf("%u %u %u e", RGB[0], RGB[1], RGB[2]);
				
				_delay_ms(100);
			}
		}
	}
}