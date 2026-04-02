/*
 Tema: UART komunikacija
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 11.5
 */ 

#include "AVR/avrlib.h"
#include "LCD/lcd.h"
#include "UART/uart.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"
#include "ADC/adc.h" 

volatile uint32_t vrijemeRada = 0;

ISR(TIMER1_OVF_vect) {
	timer1SetValue(3036); // pocetna vrijednost TCNT1 za 1 s
	vrijemeRada++;
	digitalToggle(B3); // promjena stanja na zelene LED diode
}

void ispisiHelp() {
	uartprintf("\r");	
	uartprintf("*****************************************************\r");
	uartprintf("* Povratne informacije za ispis podataka u terminal *\r");
	uartprintf("Unesite dolje navedeni znak i pritisnete Enter:\r");
	uartprintf(" I - informacije o mikroupravljacu\r");
	uartprintf(" Z - stanje zelene LED diode (PB3)\r");
	uartprintf(" T - stanje tipkala T1 (PD4)\r");
	uartprintf(" A - rezultat AD pretvorbe na pinu ADC0\r");
	uartprintf(" U - napon na pinu ADC0\r");
	uartprintf(" P - pozicija potenciometra u %%\r");
	uartprintf(" V - vrijeme rada mikroupravljaca u [s]\r");
	uartprintf(" ? - pomoc\r");
	uartprintf("*****************************************************\r");
	uartprintf("\r");	
}

void init() {
	lcdInit(); // inicijalizacija LCD displeja
	adcInit(); // inicijalizacija AD pretvorbe
	uartInit(19200); // inicijalizacija UART komunikacij
	interruptEnable(); // globalno omoguceni prekidi
	pinMode(B3, OUTPUT); // PB3 konfiguriran kao izlazni pin (zelena LED dioda)
	pinMode(D4, INPUT); // PD4 konfiguriran kao ulazni pin (tipkalo T1)
	pullUpOn(D4); // ukljucen pull up na pinu PD4
	// postavljanje normalnog nacina rada
	timer1NormalMode();
	// djelitelj frekvencije F_CPU / 64
	timer1SetPrescaler(TIMER1_PRESCALER_256);
	timer1InterruptOVFEnable(); // omogucenje prekida preljevom za timer1
	timer1SetValue(3036); // pocetna vrijednost TCNT1 za 250 ms
	ispisiHelp();
}	

int main(void) {
	
	init(); // inicijalizacija mikroupravljaca
	float U, P;
	while (1) {
		if (uartIsMessageRecived())	{
			lcdClrScr();
			// prikaz primljene poruke
			lcdprintf("%s", uartBuffer);
			if (uartBuffer[1] == '\0') {
				// automat stanja za obradu poruka
				switch(uartBuffer[0]) {
					case 'I':
						//informacije o ATmega328P
						uartprintf("Mikroupravljac: ATmega328P\r");
						uartprintf("Programska memorija: 32 kB\r");
						uartprintf("Podatkovna memorija: 2 kB\r");
						uartprintf("Broj tajmera: 3, Broj PWM kanala: 6\r\r");
					break;
					case 'Z':
						//stanje zelene LED diode
						if (digitalRead(B3)) {
							uartprintf("LED zeleno: ON\r\r");
						} else {
							uartprintf("LED zeleno: OFF\r\r");
						}
					break;
					case 'T':
						//stanje tipkala T1
						if (digitalRead(D4)) {
							uartprintf("Tipkalo T1: nije pritisnuto\r\r");
						} else {
							uartprintf("Tipkalo T1: pritisnuto je\r\r");
						}
					break;
					case 'A':
						//rezultat AD pretvorbe na pinu ADC0
						uartprintf("ADC0 = %d\r\r", adcRead(ADC0));
					break;
					case 'U':
						//napon na pinu ADC0
						U = adcReadVoltage(ADC0);
						uartprintf("Napon na pinu ADC: %.3f V\r\r", U);
					break;
					case 'P':
						//zakret potenciometra u %
						P = adcReadScale0To100(ADC0);
						uartprintf("Zakret potenciometra: %.2f%%\r\r", P);
					break;
					case 'V':
						//vrijeme rada mikroupravljaca
						uartprintf("Vrijeme rada: %d s\r\r", vrijemeRada);
					break;
					case '?':
					// ispisivanje pomoci oko unosa znakova
					ispisiHelp();
					break;
					default:
						uartprintf("Neispravan unos! Unesite ? za pomoc!\r");
					break;
				}
			} else {
				uartprintf("Neispravan unos! Unesite ? za pomoc!\r");
			}
		}
	}
}