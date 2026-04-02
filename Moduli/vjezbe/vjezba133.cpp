/*
 Tema: Povezivanje odabranih elektronickih modula na mikroupravljac - HC-SR04 UZV
 Autor: Danijel Radocaj
 Autor: Zoran Vrhovski
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 Vježba 13.3
*/ 

#include <avr/io.h>
#include "AVR/avrlib.h"
#include "Timer/timer.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"
#include "Interrupt/interrupt.h"
#include <util/delay.h>

// zastavica za signalizaciju da je trigger puls poslan
// pomocna varijabla za spremanje brojenja pulseva
// pomocna zastavica za signalizaciju zavrsenog mjerenja

ISR(INT1_vect) {
	if() {	// ECHO pin -> idle state
		// timer counter registar -> nula
	}
	else {
		// broj pulseva -> pulseCount
		// zastavicom mjerenje zavrseno
	}
}

void HCSR04_trigger() {		// fnc za trigger puls
	// high state na pinu PD0
	_delay_us(20);			// koje traje 20 us
	// low state na pinu PD0
	HCSR04_triggerSent = true;	// zastavica trigger poslan
}

void init(){		// inicijalizacija mikroupravljaca
	// inicijalizacija LCD displeja
	// inicijalizacija AD pretvornika
	
	lcdClrScr();	// ocisti prethodni zapis na LCD
	lcdHome();		// pokazivac LCD na koordinate 1,1
	
	// prekidna rutina 1 rastuci i padajuci brid signala ECHO
	// omoguci prekidnu rutinu 1
	// timer 1 -> normalni nacin rada
	// djelitelj frekvencije za timer 1 ce biti 8
	
	config_output(DDRD,PD0);	// PD0 pin -> izlaz (TRIG)
	config_input(DDRD,PD3);		// PD3 pin -> ulaz (ECHO)
	
	interruptEnable();		// globalno omogucenje rutina
}

int main(void){
	
	init();		// poziv fnc inicijalizacija mikroupravljaca
	
	// varijabla za vremenski istek zahtjeva za trigger puls
	// varijabla za pohranu proteklog vremena koje se mjeri timerom
	// varijabla za izracunatu vrijednost udaljenosti bez korekcije
	// varijabla za izracunatu vrijednost udaljenosti s korekcijom
	// brzina zvuka
	// varijabla za korektiranu brzinu zvuka s obzirom na temperaturu
	// varijabla za vrijednost temperature dobivene ADC sa senz. LM35
	// varijabla za pohranu vrijednosti AD pretvorbe na kanalu ADC0
	
	while (1)
	{
		// ako nije poslan trigger i vremenski istek nije aktivan
		if(!HCSR04_triggerSent && timeout == 0) {
			// funkcija za slanje trigger pulsa
		}
		
		if ()	// zastavica -> zavrseno mjerenje
		{
			// izracun proteklog vremena da se puls vrati
			pulseTime =
			// izracun udaljenosti pomocu brzine zvuka i vremena
			dist =
			
			valADC = adcRead(ADC0);		// ADC izlaza senzora LM35
			temp = valADC * 5.0 / 1024 * 100;	// izracun temperature
			// izracun korigirane brzine zvuka uz vrijednost temperature
			vSoundCorrected =
			
			// izracun korigirane udaljenosti s korigiranom vr. brzine zv.
			distCorrected =
			
			lcdClrScr();	// ocisti prethodni ispis na LCD
			lcdHome();		// postavi pokazivac LCD na koordinate 1,1
			// u prvi redak LCD displeja ispisi udaljenost bez korekcije
			lcdprintf("Dist: %.2fcm\n", dist);
			// u drugi redak LCD displeja ispisi udaljenost s korekcijom
			lcdprintf("DistCorr: %.2fcm", distCorrected);
			
			// postavi zastavicu za signaliziranje mjerenja false
			HCSR04_measured = false;
			// postavi zastavicu za signaliziranje trigger signala false
			HCSR04_triggerSent = false;
		}
		_delay_ms(150);
	}
	return 0;
	
}