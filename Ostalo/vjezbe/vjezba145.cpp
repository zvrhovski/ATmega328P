/*
 Tema: I2C
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 14.5
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "I2C/i2c.h"

#define DS1621_ADDRESS 0x68 // DS1621 - Slave adresa
#define DS1621_START_CNV 0xEE // instrukcija za pokretanje mjerenja temperature
#define DS1621_RD_TEMP 0xAA // instrukcija za ocitanje temperature

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	i2cInit(); // inicijalizacija I2C komunikacije
}

int main(void) {
	
	// dva bajta za ocitanje temperature
	uint8_t tempLowByte, tempHighByte;
	// temperatura realan broj
	float T;
	init(); // inicijalizacija mikroupravljaca
	
	// pokretanje mjerenja temperature
	i2cStart(DS1621_ADDRESS, I2C_WRITE);
	i2cWrite(DS1621_START_CNV);
	i2cStop();
		
	while (1) {
		// pokretanje ocitanja temperature
		i2cStart(DS1621_ADDRESS, I2C_WRITE);
		i2cWrite(DS1621_RD_TEMP);
		i2cStart(DS1621_ADDRESS, I2C_READ);
		tempHighByte = i2cSReadACK();
		tempLowByte = i2cSReadNACK();
		i2cStop();
		// izracun temperature
		T = (float) tempHighByte;
		if (tempLowByte & 0x80)	{
			T += 0.5;
		}
		// ispis temperature na LCD
		lcdClrScr();
		lcdprintf("T = %.1f", T);
		_delay_ms(1000);
	}
}