/*
 Tema: Povezivanje odabranih elektronickih modula na mikroupravljac - Numericki displej i posmacni registri
 Autor: Danijel Radocaj
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 13.4.a
*/ 

#include "AVR/avrlib.h"
#include "ADC/adc.h"

void init() {
	// inic. serijskog ulaza (SI) SBR
	// inic. register clock ulaza (RCK) SBR
	// inic. serial clock ulaza (SCK) SBR
}

int main(void) {
	
	init();
	
	uint8_t data = 0xB6;	// testni podatak
	
	// 4x ispis -> ispis na sva 4 displeja
	for (uint8_t i = 0; i < 4; i++)
	{
		// provjera svih 8 bitova podatka
		for (uint8_t j = 0; j < 8; j++)
		{
			if (data & 0x01)	// maskiranje LSB
			{
				// SI - true
			}
			else
			{
				// SI - false
			}
			
			data = data >> 1;	// posmak za 1 >>
			
			// SCK puls - 1 us

		}

		data = 0xFF;	// reinicijalizacija podatka
		
		// RCK puls - 1us

	}
}