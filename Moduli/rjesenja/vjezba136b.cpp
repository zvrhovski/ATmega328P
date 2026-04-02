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
	encValue = rotEncUPDATEnREAD(encValue);		// azuriranje & citanje RE
}

void init() {		// inicijalizacija mikroracunala
	
	rotEncINIT();	// inicijalizacija rotacijskog enkodera
	rgbINIT();		// inicijalizacija RGB LE diode
	lcdInit();		// inicijalizacija LCD displeja
	interruptEnable();	// omogucavanje globalnih prekidnih rutina
	
	lcdClrScr();	// inicijalno postavljanje ispisa na LCD
	lcdHome();
	lcdprintf("PWM: %d/100%c", encValue, 37);	// prikaz vrijednosti RE
	lcdGotoXY(2,1);
	lcdprintf("RGB CH: %c", rgbCH);		// prikaz kanala RGB diode

}

int main(void) {
	
	init();		// poziv funkcije za inicijalizaciju mikroupravljaca
	
	uint8_t RGB[3] = {0, 0, 0};		// polje trenutne vrijednosti RGB kanala
	
	while (1) {

		if(rotEncBTN())	// tipkalo padajuci detekcija - promjeni RGB
		{
			switch(rgbCH){
				case 'R':
				RGB[0] = encValue;	// spremi vrijednost RE - R kanal RGB
				rgbCH = 'G';		// sljedeci kanal RGB diode
				break;
				
				case 'G':
				RGB[1] = encValue;	// spremi vrijednost RE - G kanal RGB
				rgbCH = 'B';		// sljedeci kanal RGB diode
				break;
				
				case 'B':
				RGB[2] = encValue;	// spremi vrijednost RE - B kanal RGB
				rgbCH = 'R';		// sljedeci kanal RGB diode
				break;
				
				default:
				asm("nop");		// no operation
			}
			
			while(!get_pin(PIND, PD5));		// cekaj otpustastanje tipkala
		}
		
		rgbCHwrite(RGB[0], RGB[1], RGB[2]);	// azuriranje vrijednosti RGB
		
		lcdClrScr();	// ocisti LCD displej
		lcdHome();		// postavljanje pokazivaca LCD na koordinate 1, 1
		lcdprintf("PWM: %d/100%c", encValue, 37);	// prikaz vrijednosti RE
		lcdGotoXY(2,1);		// postavljanje pokazivaca LCD na koordinate 2, 1
		lcdprintf("RGB CH: %c", rgbCH);		// prikaz trenutnog kanala RGB
		
		_delay_ms(100);
	}
}