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

void init(){
	
}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	float U;
	while (1) {

	}
}