/*
 Tema: PWM
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 10.3
 */ 

#include "AVR/avrlib.h"
#include "Timer/timer.h"
#include "ADC/adc.h"

void init() {
	adcInit(); // inicijalizacija AD pretvorbe
	pinMode(B1, OUTPUT); // PB1 konfiguriran kao izlazni pin (crvena LED dioda)
	pinMode(B2, OUTPUT); // PB2 konfiguriran kao izlazni pin (žuta LED dioda)

}

int main(void) {
	
	init(); // inicijalizacija mikroupravlja?a
	while (1) {

	}
}