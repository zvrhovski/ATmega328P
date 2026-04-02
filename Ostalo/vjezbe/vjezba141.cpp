/*
 Tema: EEPROM memorija
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 14.1
 */ 

#include "AVR/avrlib.h"
#include "Interrupt/interrupt.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"
#include <avr/eeprom.h>

bool parametriUpdate = false;
bool lcdUpdate = true;
// lcdPrikaz = false - parametri
// lcdPrikaz = true - formula
bool lcdPrikaz = true;

// prekidna rutina za PCINT2
ISR(PCINT2_vect) {
	// detekcija promjene brida na portu D
	uint8_t PINDChanged = pcintPINDOld ^ PIND;
	// ako se dogodio brid na pinu PD2 (tipkalo T2)
	if (PINDChanged & (1 << PD2)) {
		// padajuci brid (pritisnuto tipkalo)
		if (get_pin(PIND, PD2) == false) {
			lcdUpdate = true;
			lcdPrikaz = !lcdPrikaz;
		}
	}
	// ako se dogodio brid na pinu PD4 (tipkalo T1)
	if (PINDChanged & (1 << PD4)) {
		// padajuci brid (pritisnuto tipkalo)
		if (get_pin(PIND, PD4) == false) {
			parametriUpdate = true;
		}
	}
	// osvjezenje stare vrijednosti registra PIND
	pcintPINDOld = PIND;
}
// osvjezenje EEPROM memorije
void eepromUpdate(int8_t K1, uint16_t K2, float K3) {
	eeprom_write_byte((uint8_t*)0, K1);
	eeprom_write_word((uint16_t*)1, K2);
	eeprom_write_float((float*)3, K3);
}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	interruptEnable(); // globalno omogucenje prekida
	// pin PD2 konfiguriran kao ulaz + ukljucen pritezni otpornik
	pinMode(D2, INPUT_PULLUP);
	// pin PD4 konfiguriran kao ulaz + ukljucen pritezni otpornik
	pinMode(D4, INPUT_PULLUP);
	// omoguci PCINT prekid na pinovima iz skupine PCINT23..16
	pcintEnable23to16();
	pcintPinEnable23to16(PCINT18); // omoguci PCINT prekid na pinu PCINT18 (PD2)
	pcintPinEnable23to16(PCINT20); // omoguci PCINT prekid na pinu PCINT20 (PD4)
	// spremanje inicijalnih vrijednosti registara PINB, PINC i PIND
	pcintInit();
	// inicijalne vrijednosti eeprom memorije
	eepromUpdate(-15, 300, 14.5665);
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	// parametri
	int8_t K1;
	uint16_t K2;
	float K3;

	uint16_t adc0, adc0Old = 0;
	float x; // rezultat formule
	// citanje parametara iz EEPROM memorije
	K1 = eeprom_read_byte((uint8_t*)0);
	K2 = eeprom_read_word((uint16_t*)1);
	K3 = eeprom_read_float((float*)3);
	
	while (1) {
		// AD pretvorba i izracun forumle
		adc0 = adcRead(ADC0);
		x = adc0 * K3 / K2 + K1;
		
		// omoguci ispis ako se promjeni ADC0
		if (adc0Old != adc0) {
			if (lcdPrikaz) {
				lcdUpdate = true;	
			}
			adc0Old = adc0;
		}
		// ispis na LCD
		if (lcdUpdate) {
			if (lcdPrikaz == false) {
				lcdClrScr();
				lcdprintf("K1=%d K2=%u\n", K1, K2);
				lcdprintf("K3=%.4f", K3);
				lcdUpdate = false;
			} 
			else {
				lcdClrScr();
				lcdprintf("x(%d)=%.4f", adc0, x);
				lcdUpdate = false;
				_delay_ms(500);
			}
			
		}
		// novi parametri u EEPROM memoriji		
		if (parametriUpdate) {
			K1 = -10;
			K2 = 260;
			K3 = 11.709;
			eepromUpdate(K1, K2, K3);
			parametriUpdate = false;
			lcdUpdate = true;
		}
		
	}
}

