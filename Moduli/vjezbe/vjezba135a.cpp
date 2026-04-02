/*
 Tema: Povezivanje odabranih elektronickih modula na mikroupravljac - Servo motor
 Autor: Danijel Radocaj
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 13.5.a
*/ 

#include "AVR/avrlib.h"
#include "Timer/timer.h"
#include "LCD/lcd.h"
#include "Interrupt/interrupt.h"
#include "ADC/adc.h"
#include <avr/io.h>
#include <util/delay.h>

// pokusno dobivene ref. vr. DC za servo motor

void init()
{
	// inicijalizacija LCD
	// inicijalizacija ADC

	// timer 2 nacin rada phase correct u mode 5 (OCR2A = top)
	// djelitelj frekvencije 1024
	// top vrijednost do koje timer broji
	// OC2B kanal izlazni PWM signala, nalazi se na pinu PD3

}

int main(void){
	
	// inicijalizacija mikroupravljaca
	
	// varijabla ADC
	// varijable: kut, duty cycle
	
	while(1) {
		
		// ADC ch ADC0 (POT)
		// skaliranje ADC (0 do 1023) -> kut (0 do 180)
		
		if(rotAngle <= 90.0) {		// ako je kut < 90
			
			// skaliraj duty cycle da krece od 4.3 i ide do 11.7
			
		}
		else {		// ako je kut > 90
			
			// skaliraj duty cycle da ide krece od 11.7 i ide do 20.22
			
		}
		
		// azuriranje DC za PWM signal pin OC2B
		
		// ocisti prethodni ispis na LCD
		// postavljanje pokazivaca LCD na koordinate 1,1
		// ispis DC 1.red LCD
		// ispis kuta 2.red LCD
		
		_delay_ms(150);
	}
}