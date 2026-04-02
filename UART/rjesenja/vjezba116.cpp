/*
 Tema: UART komunikacija
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 11.6
 */ 

#include "AVR/avrlib.h"
#include "UART/uart.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"
#include "ADC/adc.h" 

volatile bool sendADC = true;
volatile uint32_t vrijemeRada = 0;

ISR(TIMER1_OVF_vect) {
	timer1SetValue(3036); // pocetna vrijednost TCNT1 za 1 s
	vrijemeRada++;
	sendADC = true;
}


void init() {
	adcInit(); // inicijalizacija AD pretvorbe
	uartInit(19200); // inicijalizacija UART komunikacij
	interruptEnable(); // globalno omoguceni prekidi
	// postavljanje normalnog nacina rada
	timer1NormalMode();
	// djelitelj frekvencije F_CPU / 64
	timer1SetPrescaler(TIMER1_PRESCALER_256);
	timer1InterruptOVFEnable(); // omogucenje prekida preljevom za timer1
	timer1SetValue(3036); // pocetna vrijednost TCNT1 za 250 ms
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	float U;
	while (1) {
		if (sendADC) {
			U = adcReadVoltage(ADC0);
			uartprintf("t=%lus U=%.2fV\r", vrijemeRada, U);
			sendADC = false;
		}
	}
}