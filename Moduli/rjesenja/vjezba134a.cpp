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
	DDRC |= (1 << PC1);
	// inic. register clock ulaza (RCK) SBR
	DDRC |= (1 << PC2);
	// inic. serial clock ulaza (SCK) SBR
	DDRC |= (1 << PC3);
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
			if (data & 0x01)		// maskiranje LSB
			{
				PORTC |= (1 << PC1);	// SI - true
			}
			else
			{
				PORTC &= ~(1 << PC1);	// SI - false
			}
			
			data = data >> 1;		// posmak za 1 >>
			
			PORTC |= (1 << PC3);	// SCK puls - 1 us
			_delay_us(1);
			PORTC &= ~(1 << PC3);
			_delay_us(1);
		}

		data = 0xB6;	// reinicijalizacija podatka
		
		PORTC |= (1 << PC2);	// RCK puls - 1us
		_delay_us(1);
		PORTC &= ~(1 << PC2);
		_delay_us(1);
	}
}