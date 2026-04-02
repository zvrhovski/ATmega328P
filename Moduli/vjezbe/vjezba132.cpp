/*
 Tema: Povezivanje odabranih elektronickih modula na mikroupravljac - Tranzistor kao sklopka i relej
 Autor: Danijel Radocaj
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 13.2
*/ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"
#include <avr/io.h>
#include <util/delay.h>

void init() {
	// inicijalizacija LCD displeja
	// inicijalizacija AD pretvorbe
	
	// PD4 konfiguriran kao ulazni pin
	// PD1 konfiguriran kao izlazni pin
	// ukljucen pritezni otpornik za pin PD4
}

int main(void) {
	
	init();		// inicijalizacija mikroupravljaca
	
	uint16_t varPot = 0;		// varijabla - AD pretvorbe
	uint8_t relayFlag = 0;		// varijabla - stanje releja
	
	while (1) {
		// AD pretvorba - kanal ADC0
		if (varPot >= 800)		// iznad 800, relej -> ON
		{
			// ukljucivanje releja pin PD1
			relayFlag = 1;
		}
		else if (!get_pin(PIND, PD4))	// provjera pina PD4
		{
			// ukljucivanje releja PD1
			relayFlag = 1;
		}
		else
		{
			// iskljucivanje releja PD1
			relayFlag = 0;
		}
		
		// ispis stanja releja
		// ispis AD pretvorbe
		_delay_ms(150);
	}
}