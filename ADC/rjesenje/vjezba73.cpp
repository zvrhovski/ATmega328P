/*
 Tema: AD pretvorba
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 7.3
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"
#include "Senzori/lm35.h"
// konstanta koja se koristi umjesto ADC0
#define LM35 ADC0

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	DDRB |= (1 << PB1); // PB1 konfiguriran kao izlazni pin
	DDRB |= (1 << PB2); // PB2 konfiguriran kao izlazni pin
	DDRB |= (1 << PB3); // PB3 konfiguriran kao izlazni pin
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	
	uint16_t adc0; // digitalna rijec ADC0
	uint16_t adc0Old; // digitalna rijec ADC0
	float T; // temperatura u okolini senzora LM35
	bool ispisNaLcd = true; // omogucavanje ispisa
	int brojac_vremena = 0; // brojac za sekunde
	
	T = readTempLM35(LM35); // citaj temperaturu na LM35
	while (1) { // beskonacna petlja
		// ako je brojac = 100, prosla je jedna sekunda
		if (++brojac_vremena == 100) {
			adc0 = adcRead(LM35); // AD pretvorba na pinu ADC0
			T = adcConvertToTempLM35(adc0); // pretvori rezultat ADC u temperaturu
			brojac_vremena = 0; // vrati brojac na 0 za novu sekundu
		}
		// ako se promijenila vrijednost AD pretvorbe i ako je prosla sekunda		
		if ((adc0 != adc0Old) && (brojac_vremena == 0)) {
			ispisNaLcd = true; // omoguci ispis na LCD
			adc0Old = adc0; // osvjezi staru vrijednost adc0
		}
		// uvjetni ispis na LCD displej i izmjena stanja LED dioda
		if (ispisNaLcd) {
			// brisanje znakova LCD displeja +  home pozicija kursora
			lcdClrScr(); 
			// ispis na LCD displej (sintaksa funkcije printf())
			lcdprintf("T = %.2f%c", T, 223);
			if (T < 22.0) {
				PORTB &= ~(1 << PB1); // LED crvena off
				PORTB &= ~(1 << PB2); // LED zuta off
				PORTB |= (1 << PB3); // LED zelena on
			}
			if (T >= 22.0 && T < 25.0) {
				PORTB &= ~(1 << PB1); // LED crvena off
				PORTB |= (1 << PB2); // LED zuta on
				PORTB |= (1 << PB3); // LED zelena on
			}
			if (T >= 25.0) {
				PORTB |= (1 << PB1); // LED crvena on
				PORTB |= (1 << PB2); // LED zuta on
				PORTB |= (1 << PB3); // LED zelena on
			}
			ispisNaLcd = false; //onemoguci ispis na LCD
		}
		_delay_ms(10);
	}
	return 0;
}