/*
 Tema: PWM
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 10.4
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "Timer/timer.h"
#include "ADC/adc.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	pinMode(B1, OUTPUT); // PB1 konfiguriran kao izlazni pin (crvena LED dioda)
	pinMode(D4, INPUT); // PD4 konfiguriran kao ulazni pin (tipkalo T1)
	pullUpOn(D4); // ukljuci pull up na pinu PD4

}

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	float D; // faktor vodenja
	while (1) {

	}
}

