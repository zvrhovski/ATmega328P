/*
 Tema: Povezivanje odabranih elektronickih modula na mikroupravljac - Numericki displej i posmacni registri
 Autor: Danijel Radocaj
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 13.4.c
*/ 

#include "AVR/avrlib.h"
#include "ADC/adc.h"
#include "Peripheral/SBR_7seg.h"
#include <avr/io.h>
#include <util/delay.h>

void init() {
	sbr_init();	// inic. SBR
	adcInit();	// inic. ADC
}

int main(void) {
	
	init();		// inic. mikroupravljaca
	
	// varijabla - rezultat AD pretvorbe
	uint16_t adcVal = 0;
	// varijabla - izracunat napon - ADC0
	uint16_t vVal = 0;
	
	// varijable - ispis rezultata 7SEG
	uint8_t adcNum1 = 0;
	uint8_t adcNum2 = 0;
	uint8_t adcNum3 = 0;
	uint8_t adcNum4 = 0;
	
	// varijable - ispis napona - ADC0
	uint8_t vNum1 = 0;
	uint8_t vNum2 = 0;
	uint8_t vNum3 = 0;
	uint8_t vNum4 = 0;
	
	while (1)
	{
		// AD pretvorba
		adcVal = adcRead(ADC0);
		// izracuna napona na ADC0 pinu
		vVal = adcVal * 5000.0 / 1023.0;
		
		// izdvajanje znamenki rezultata ADC
		adcNum1 = adcVal / 1000;
		adcNum2 = (adcVal / 100) % 10;
		adcNum3 = (adcVal / 10) % 10;
		adcNum4 = adcVal % 10;
		
		// izdvajanje znamenki izrac. napona
		vNum1 = vVal / 1000;
		vNum2 = (vVal / 100) % 10;
		vNum3 = (vVal / 10) % 10;
		vNum4 = vVal % 10;
		
		// ispis rezultata ADC na 7SEG
		sbr_send_4B(charset[adcNum1], charset[adcNum2], charset[adcNum3], charset[adcNum4]);
		_delay_ms(1000);
		
		// ispis izrac. napona na 7SEG
		sbr_send_4B(charset[vNum1] | NUM_DOT, charset[vNum2], charset[vNum3], charset[vNum4]);
		_delay_ms(1000);
	}
}