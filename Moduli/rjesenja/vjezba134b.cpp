/*
 Tema: Povezivanje odabranih elektronickih modula na mikroupravljac - Numericki displej i posmacni registri
 Autor: Danijel Radocaj
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 13.4.b
*/ 

#include "AVR/avrlib.h"
#include "ADC/adc.h"
#include "Peripheral/SBR_7seg.h"

void init() {
	sbr_init();		// inicijalizacija SBR/7seg.
}

int main(void) {
	init();		// inic. mikroupravljaca
	
	// posalji 4B podataka odjednom
	// na sva cetiri 7-seg. displeja
	sbr_send_4B(NUM_5, NUM_6, NUM_7, NUM_8);
}