/*
 Tema: Povezivanje odabranih elektronickih modula na mikroupravljac - Servo motor - funkcija
 Autor: Danijel Radocaj
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 13.5.b
*/ 

#include "AVR/avrlib.h"
#include "Timer/timer.h"
#include "LCD/lcd.h"
#include "Interrupt/interrupt.h"
#include "ADC/adc.h"
#include <avr/io.h>
#include <util/delay.h>

// pokusno dobivene ref. vr. DC za servo motor
#define DUTY_MIN 4.3		// za kut 0
#define DUTY_MAX 20.22		// za kut 180
#define DUTY_MID 11.7		// za kut 90

void init()
{
	lcdInit();	// inicijalizacija LCD
	adcInit();	// inicijalizacija ADC

	// timer 2 nacin rada phase correct u mode 5 (OCR2A = top)
	timer2PhaseCorrectPWM_mode5();
	// djelitelj frekvencije 1024
	timer2SetPrescaler(TIMER2_PRESCALER_1024);
	// top vrijednost do koje timer broji
	OCR2A = 156;
	// OC2B kanal izlazni PWM signala, nalazi se na pinu PD3
	DDRD |= (1<<PD3);
}

void setServoPosition(float angle)
{
	uint8_t dutyCycle = 0;
	
	if(angle <= 90.0) {		// ako je kut < 90
		// skaliraj duty cycle da krece od 4.3 i ide do 11.7
		dutyCycle = DUTY_MIN+(DUTY_MID-DUTY_MIN)/90.0*angle;
	}
	else {		// ako je kut > 90
		// skaliraj duty cycle da ide krece od 11.7 i ide do 20.22
		dutyCycle = DUTY_MID+(DUTY_MAX-DUTY_MID)/90.0*(angle-90.0);
	}
	
	OCR2B = (uint8_t)dutyCycle;	// azuriranje DC za PWM signal pin OC2B
}

int main(void){
	
	init();	// inicijalizacija mikroupravljaca
	
	uint16_t varPot = 0;	// varijabla ADC
	float rotAngle, duty;	// varijable: kut, duty cycle
	
	while(1) {
		
		varPot = adcRead(ADC0);	// ADC ch ADC0 (POT)
		// skaliranje ADC (0 do 1023) -> kut (0 do 180)
		rotAngle = varPot / 1023.0 * 180.0;
		
		setServoPosition(rotAngle);	// fnc - servomotor position update
		
		lcdClrScr();	// ocisti prethodni ispis na LCD
		lcdHome();		// postavljanje pokazivaca LCD na koordinate 1,1
		lcdprintf("duty = %d\n",  (uint8_t)duty); // ispis DC 1.red LCD
		lcdprintf("angle = %0.3f\n", rotAngle);	// ispis kuta 2.red LCD
		
		_delay_ms(150);
	}
}