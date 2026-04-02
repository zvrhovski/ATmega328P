/*
 Tema: UART komunikacija
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 11.5
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "UART/uart.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"
#include "ADC/adc.h"

volatile uint32_t vrijemeRada = 0;

ISR(TIMER1_OVF_vect) {
	timer1SetValue(3036); // pocetna vrijednost TCNT1 za 1 s

}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	uartInit(19200); // inicijalizacija UART komunikacij
	interruptEnable(); // globalno omogu?eni prekidi
	pinMode(B3, OUTPUT); // PB3 konfiguriran kao izlazni pin (zelena LED dioda)
	pinMode(D4, INPUT); // PD4 konfiguriran kao ulazni pin (tipkalo T1)
	pullUpOn(D4); // uklju?en pull up na pinu PD4
	// postavljanje normalnog nacina rada
	timer1NormalMode();
	// djelitelj frekvencije F_CPU / 64
	timer1SetPrescaler(TIMER1_PRESCALER_256);
	timer1InterruptOVFEnable(); // omogu?enje prekida preljevom za timer1
	timer1SetValue(3036); // po?etna vrijednost TCNT1 za 250 ms
}

int main(void) {
	
	init(); // inicijalizacija mikroupravlja?a

	float U, P;
	while (1) {
		if (uartIsMessageRecived())	{
			lcdClrScr();
			// prikaz primljene poruke
			lcdprintf("%s", uartBuffer);
		}
	}
}