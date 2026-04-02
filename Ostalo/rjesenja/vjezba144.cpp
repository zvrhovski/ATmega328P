/*
 Tema: Analogni komparator
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 14.4
 */ 

#include "AVR/avrlib.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"

volatile bool prekidAnaComp = false;

//prekidna rutina analognog komparatora (AIN0(PD6) - AIN1(PD7))
ISR(ANALOG_COMP_vect){
	// iskljuci PWM/motor
	timer1OC1ADisable();
	timer1OC1ADutyCycle(0);
	lcdClrScr();
	lcdprintf("Motor OFF!");
	// onemoguci prekid analognog komparatora
	ACSR &= ~(1 << ACIE);
	prekidAnaComp = true;
}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	pinMode(B1, OUTPUT); // PB1 konfiguriran kao izlazni pin (crvena LED dioda)
	// postavljanje Phase Correct PWM na?ina rada za timer1 - 10 bit
	timer1PhaseCorrectPWM10bit();
	// djelitelj frekvencije F_CPU / 8
	timer1SetPrescaler(TIMER1_PRESCALER_8);
	// neinvertiraju?i PWM signal na PB1 (OC1A)
	timer1OC1AEnableNonInvertedPWM();
	// omoguci prekid analognog komparatora
	ACSR |= (1 << ACIE);	
	// prekid kada napon na pinu AIN1 postane veci od napona na pinu AIN0
	ACSR |= (1 << ACIS1) | (0 << ACIS0);
	interruptEnable(); // lobalno omogucenje prekida
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	float D;
	lcdClrScr();
	lcdprintf("Motor ON!");
	while (1) {
		// promjena brzine vrtnje motora
		D = adcReadScale0To100(ADC0);
		// ako se nije dogodio prekid mijenjaj faktor vodenja
		if (prekidAnaComp == false) {
			timer1OC1ADutyCycle(D);
		}
		_delay_ms(1);
	}
}