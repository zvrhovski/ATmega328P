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
	
	lcdInit();	// inicijalizacija LCD displeja
	adcInit();	// inicijalizacija AD pretvorbe
	
	config_input(DDRD, PD4);	// PD4 konfiguriran kao ulazni pin
	config_output(DDRD, PD1);	// PD1 konfiguriran kao izlazni pin
	pull_up_on(PORTD, PD4);	// ukljucen pritezni otpornik za pin PD4
	
}

int main(void) {
	init();		// inicijalizacija mikroupravljaca
	
	uint16_t varPot = 0;		// pomocna varijabla - AD pretvorbe
	uint8_t relayFlag = 0;		// pomocna varijabla - stanje releja
	
	while (1) {
		
		varPot = adcRead(ADC0);

		if (varPot >= 800)		// iznad 800, ukljuciti relej, inace ne
		{
			set_pin_on(PORTD, PD1);		// ukljucivanje releja pin PD1
			relayFlag = 1;
		}
		
		else if (!get_pin(PIND, PD4))	// provjera  ulaznog pina PD4
		{
			set_pin_on(PORTD, PD1);		// ukljucivanje releja pin PD1
			relayFlag = 1;
		}
		
		else
		{
			set_pin_off(PORTD, PD1);	// iskljucivanje releja pin PD1
			relayFlag = 0;
		}
		
		lcdClrScr();
		lcdHome();
		lcdprintf("Relay: %u", relayFlag);		// ispis stanja releja
		lcdprintf("\nThreshold: %u", varPot);	// ispis AD pretvorbe
		_delay_ms(150);
	}
}