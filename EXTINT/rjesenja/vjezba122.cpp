/*
 Tema: Vanjski prekidi
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 12.2
 */ 

#include "AVR/avrlib.h"
#include "Interrupt/interrupt.h"
#include "LCD/lcd.h"
#include "Timer/timer.h"
#include "ADC/adc.h"
#include <string.h>

volatile bool lcdUpdate = true;
char LCDispis[6] = "READY";

// prekidna rutina za PCINT0
ISR(PCINT0_vect) {
	// detekcija promjene brida na portu B	
	uint8_t PINBChanged = pcintPINBOld ^ PINB;
	// ako se dogodio brid na pinu PB1
	if (PINBChanged & (1 << PB1)) {
		bool stanje = get_pin(PINB, PB1);
		if (stanje) {
			set_pin_on(PORTB, PB3);
		} 
		else {
			set_pin_off(PORTB, PB3);
		}
	}
	// osvjezenje stare vrijednosti registra PINB
	pcintPINBOld = PINB;
}

// prekidna rutina za PCINT2
ISR(PCINT2_vect) {
	// detekcija promjene brida na portu D
	uint8_t PINDChanged = pcintPINDOld ^ PIND;
	// ako se dogodio brid na pinu PD2
	if (PINDChanged & (1 << PD2)) {
		if (get_pin(PIND, PD2)) {
			strcpy(LCDispis, "PD2 R");
		} else {
			strcpy(LCDispis, "PD2 F");
		}	
	}
	// ako se dogodio brid na pinu PD4
	if (PINDChanged & (1 << PD4)) {
		if (get_pin(PIND, PD4)) {
			strcpy(LCDispis, "PD4 R");
			} else {
			strcpy(LCDispis, "PD4 F");
		}
	}
	// ako se dogodio brid na pinu PD5
	if (PINDChanged & (1 << PD5)) {
		if (get_pin(PIND, PD5)) {
			strcpy(LCDispis, "PD5 R");
			} else {
			strcpy(LCDispis, "PD5 F");
		}
	}	
	// omogucenje ispisa na LCD
	lcdUpdate = true;
	// osvjezenje stare vrijednosti registra PIND
	pcintPINDOld = PIND;
}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	//konfiguracija izlaza PB1 i PB3
	DDRB |= (1 << PB1) | (1 << PB3);
	//konfiguracija ulaza PD2, PD4 i PD5
	DDRD &= ~((1 << PD2) | (1 << PD4) | (1 << PD5));	
	//pull up otpornici ukljuceni na PD2, PD4 i PD5
	PORTD |= (1 << PD2) | (1 << PD4) | (1 << PD5);
	// postavljanje Phase Correct PWM nacina rada za timer1 - 10 bit
	timer1PhaseCorrectPWM10bit();
	// djelitelj frekvencije F_CPU / 8
	timer1SetPrescaler(TIMER1_PRESCALER_64);
	// neinvertirajuci PWM signal na PB1 (OC1A)
	timer1OC1AEnableNonInvertedPWM();
	interruptEnable(); // globalno omogucenje prekida
	// omoguci PCINT prekid na pinovima iz skupine PCINT7..0
	PCICR |= (1 << PCIE0);
	// omoguci PCINT prekid na pinovima iz skupine PCINT23..16
	PCICR |= (1 << PCIE2);
	// omogucenje pinova koji ce generirati prekid
	PCMSK0 |= (1 << PCINT1); // omoguci PCINT prekid na pinu PCINT1 (PB1)
	PCMSK2 |= (1 << PCINT18); // omoguci PCINT prekid na pinu PCINT18 (PD2)
	PCMSK2 |= (1 << PCINT20); // omoguci PCINT prekid na pinu PCINT20 (PD4)
	PCMSK2 |= (1 << PCINT21); // omoguci PCINT prekid na pinu PCINT21 (PD5)
	// spremanje inicijalnih vrijednosti registara PINB, PINC i PIND
	pcintPINBOld = PINB;
	pcintPINDOld = PIND;
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	float D;
	while (1) {
		// ispis na LCD displej
		if (lcdUpdate) {
			lcdHome();
			lcdprintf("%s", LCDispis);
			lcdUpdate = false;
		}
		D = adcReadScale0To100(ADC0);
		// osvjezavanje faktora vodenja kroz registar OCR1A
		timer1OC1ADutyCycle(D);
	}
}

/*
	// omoguci PCINT prekid na pinovima iz skupine PCINT7..0
	pcintEnable7to0();
	// omoguci PCINT prekid na pinovima iz skupine PCINT23..16
	pcintEnable23to16();
	pcintPinEnable7to0(PCINT1); // omogu?i PCINT prekid na pinu PCINT1 (PB1)
	pcintPinEnable23to16(PCINT18); // omogu?i PCINT prekid na pinu PCINT18 (PD2)
	pcintPinEnable23to16(PCINT20); // omogu?i PCINT prekid na pinu PCINT20 (PD4)
	pcintPinEnable23to16(PCINT21); // omogu?i PCINT prekid na pinu PCINT21 (PD5)
	// spremanje inicijalnih vrijednosti registara PINB, PINC i PIND
	pcintInit();
*/