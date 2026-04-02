/*
 Tema: Povezivanje odabranih elektronickih modula na mikroupravljac - RGB LE dioda
 Autor: Danijel Radocaj
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 13.6.b
*/

#include "AVR/avrlib.h"
#include "Timer/timer.h"
#include "LCD/lcd.h"
#include "Interrupt/interrupt.h"
#include "Peripheral/rotEnc.h"
#include "Peripheral/rgbLED.h"
#include <avr/io.h>
#include <util/delay.h>

char rgbCH = 'R';		// globalna varijabla trenutne vrijednosti RGB
uint8_t encValue = 0;	// globalna varijabla trenutne vrijednosti RE

ISR(INT0_vect){		// prekidna rutina za azuriranje vrijednosti RE
	encValue = rotEncUPDATEnREAD(encValue);		// azuriranje \& citanje RE
}

void init() {		// inicijalizacija mikroracunala
	
	// inicijalizacija rotacijskog enkodera
	// inicijalizacija RGB LE diode
	// inicijalizacija LCD displeja
	// omogucavanje globalnih prekidnih rutina
	
	// inicijalno postavljanje ispisa na LCD
	
	// prikaz vrijednosti RE
	
	// prikaz kanala RGB diode

}

int main(void) {
	
	init();		// poziv funkcije za inicijalizaciju mikroupravljaca
	
	uint8_t RGB[3] = {0, 0, 0};		// polje trenutne vrijednosti RGB kanala
	
	while (1) {

		if(rotEncBTN())	// tipkalo padajuci detekcija - promjeni RGB
		{
			switch(rgbCH){
				case 'R':
				// spremi vrijednost RE kao R kanal RGB
				// sljedeci kanal RGB diode
				break;
				
				case 'G':
				// spremi vrijednost RE - G kanal RGB
				// sljedeci kanal RGB diode
				break;
				
				case 'B':
				// spremi vrijednost RE - B kanal RGB
				// sljedeci kanal RGB diode
				break;
				
				default:
				asm("nop");		// no operation
			}
			
			while(!get_pin(PIND, PD5));		// cekaj otpustastanje tipkala
		}
		
		// azuriranje vrijednosti kanala RGB
		
		// ocisti LCD displej
		// postavljanje pokazivaca displeja na koordinate 1, 1
		// prikaz vrijednosti dobivene RE
		// postavljanje pokazivaca displeja na koordinate 2, 1
		// prikaz trenutnog kanala RGB diode
		
		_delay_ms(100);
	}
}