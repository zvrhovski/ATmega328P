/*
 Tema: UART komunikacija
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 11.4
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "UART/uart.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	uartInit(19200); // inicijalizacija UART komunikacij
	interruptEnable(); // globalno omoguceni prekidi
	pinMode(B1, OUTPUT); // PB1 konfiguriran kao izlazni pin (crvena LED dioda)
	pinMode(B2, OUTPUT); // PB2 konfiguriran kao izlazni pin (zuta LED dioda)
	// postavljanje Phase Correct PWM nacina rada za timer1 - 8 bit
	timer1PhaseCorrectPWM8bit();
	// djelitelj frekvencije F_CPU / 8
	timer1SetPrescaler(TIMER1_PRESCALER_8);
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	int dutyCrvena = 0;
	int dutyZuta = 0;
	bool DUpdate = false;
	char pin, stanje;
	while (1) {
		if (uartIsMessageRecived())	{
			lcdClrScr();
			// prikaz primljene poruke
			lcdprintf("%s", uartBuffer);
			// omogu?enje PWM signala
			if (uartBuffer[0] == 'B') {
				pin = uartBuffer[1];
				stanje = uartBuffer[2];
				// automat stanja za enable i disable PWM kanala
				switch(pin) {
					case '1':
					if (stanje == '1') {
						timer1OC1AEnableNonInvertedPWM();
						uartprintf("OC1A omogucen (crvena LED dioda)!\r");
					}
					if (stanje == '0') {
						timer1OC1ADisable();
						uartprintf("OC1A onemogucen (crvena LED dioda)!\r");
					}
					break;
					case '2':
					if (stanje == '1') {
						timer1OC1BEnableNonInvertedPWM();
						uartprintf("OC1B omogucen (zuta LED dioda)!\r");
					}
					if (stanje == '0') {
						timer1OC1BDisable();
						uartprintf("OC1B onemogucen (zuta LED dioda)!\r");
					}
					break;
					default:
					break;
				}
			}
			// odabir faktora vodenja
			if (uartBuffer[0] == 'P') {
				sscanf(uartBuffer, "P%d;%d", &dutyCrvena, &dutyZuta);
				DUpdate = true;
			}
		}
		// osvjezavanje faktora vodenja kroz registar OCR1A i OCR1B
		if (DUpdate) {
			timer1OC1ADutyCycle(dutyCrvena);
			timer1OC1BDutyCycle(dutyZuta);
			uartprintf("Faktor vodenja za crvenu LED: %d %%\r", dutyCrvena);
			uartprintf("Faktor vodenja za zutu LEDF: %d %%\r", dutyZuta);
			DUpdate = false;
		}
	}
}