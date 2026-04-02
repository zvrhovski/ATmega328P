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
bool HCSR04_triggerSent = false;
// pomocna varijabla za spremanje brojenja pulseva
volatile uint32_t pulseCount = 0;	
// pomocna zastavica za signalizaciju zavrsenog mjerenja
volatile bool HCSR04_measured = false;	

ISR(INT1_vect) {
	if(get_pin(PIND,PD3) == 1) {	// ECHO pin -> idle state
		TCNT1 = 0;		// timer counter registar -> nula
	}
	else {
		pulseCount = TCNT1;		// broj pulseva -> pulseCount
		HCSR04_measured = true;	// zastavicom mjerenje zavrseno
	}
}

void HCSR04_trigger() {		// fnc za trigger puls
	PORTD |= (1 << PD0);	// high state na pinu PD0
	_delay_us(20);			// koje traje 20 us
	PORTD &= ~(1 << PD0);	// low state na pinu PD0
	HCSR04_triggerSent = true;	// zastavica trigger poslan
}

void init(){		// inicijalizacija mikroupravljaca
	lcdInit();		// inicijalizacija LCD displeja
	adcInit();		// inicijalizacija AD pretvornika
	
	lcdClrScr();	// ocisti prethodni zapis na LCD
	lcdHome();		// pokazivac LCD na koordinate 1,1
	
	// prekidna rutina 1 rastuci i padajuci brid signala ECHO
	int1RisingFallingEdge();
	int1Enable();		// omoguci prekidnu rutinu 1
	
	timer1NormalMode();		// timer 1 -> normalni nacin rada
	// djelitelj frekvencije za timer 1 ce biti 8
	timer1SetPrescaler(TIMER1_PRESCALER_8);
	
	config_output(DDRD,PD0);	// PD0 pin -> izlaz (TRIG)
	config_input(DDRD,PD3);		// PD3 pin -> ulaz (ECHO)
	
	interruptEnable();		// globalno omogucenje rutina
}

int main(void){
	
	init();		// poziv fnc inicijalizacija mikroupravljaca
	
	// varijabla za vremenski istek zahtjeva za trigger puls
	uint16_t timeout = 0;
	// varijabla za pohranu proteklog vremena koje se mjeri timerom
	float pulseTime = 0.0;
	// varijabla za izracunatu vrijednost udaljenosti bez korekcije
	float dist = 0.0;
	// varijabla za izracunatu vrijednost udaljenosti s korekcijom
	float distCorrected = 0.0;
	// brzina zvuka
	float vSound = 343.0;
	// varijabla za korektiranu brzinu zvuka s obzirom na temperaturu
	float vSoundCorrected;
	// varijabla za vrijednost temperature dobivene ADC sa senz. LM35
	float temp = 0.0;
	// varijabla za pohranu vrijednosti AD pretvorbe na kanalu ADC0
	float valADC = 0;			
	
	while (1)
	{
		// ako nije poslan trigger i vremenski istek nije aktivan
		if(!HCSR04_triggerSent && timeout == 0) {
			HCSR04_trigger();	// funkcija za slanje trigger pulsa
		}
		
		if (HCSR04_measured)	// zastavica -> zavrseno mjerenje
		{
			// izracun proteklog vremena da se puls vrati
			pulseTime = pulseCount * 8.0 / F_CPU;
			// izracun udaljenosti pomocu brzine zvuka i vremena
			dist = pulseTime / 2.0 * vSound * 100.0;
			
			valADC = adcRead(ADC0);		// ADC izlaza senzora LM35
			temp = valADC * 5.0 / 1024 * 100;	// izracun temperature
			// izracun korigirane brzine zvuka uz vrijednost temperature
			vSoundCorrected = 331.0 + 0.6 * temp;
			
			// izracun korigirane udaljenosti s korigiranom vr. brzine zv.
			distCorrected = pulseTime / 2.0 * vSoundCorrected * 100.0;
			
			lcdClrScr();	// ocisti prethodni ispis na LCD
			lcdHome();		// postavi pokazivac LCD na koordinate 1,1
			// u prvi redak LCD displeja ispisi udaljenost bez korekcije
			lcdprintf("Dist: %.2fcm\n", dist);
			// u drugi redak LCD displeja ispisi udaljenost s korekcijom
			lcdprintf("DistCorr: %.2fcm", distCorrected);
			
			// postavi zastavicu za signaliziranje mjerenja na false
			HCSR04_measured = false;
			// postavi zastavicu za signaliziranje poslanog trigger signala na false
			HCSR04_triggerSent = false;
		}
		_delay_ms(150);
	}
	
	return 0;
}