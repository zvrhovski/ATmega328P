/*
 Datoteka: avrlib.cpp
 Autor: Zoran Vrhovski
 Datum: 15. 9. 2021. 
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */ 

#include "avrlib.h"
#include <util/delay.h>


void pinMode(uint8_t pin, uint8_t config) {
	
	uint8_t _pin = toPin(pin);
	uint8_t _port = toPort(pin);
	
	if (is_port(_port)) {
		volatile uint8_t *ddr_reg = DDR[_port];
		volatile uint8_t *port_reg = PORT[_port];
		
		if (config == OUTPUT) {
			config_output(*ddr_reg, _pin);
			} else if (config == INPUT_PULLUP) {
			config_input(*ddr_reg, _pin);
			pull_up_on(*port_reg, _pin);
			} else if (config == INPUT) {
			config_input(*ddr_reg, _pin);
			pull_up_off(*port_reg, _pin);
			} else {
			return;
		}
	}
}


void pullUpOn(uint8_t pin) {
	
	uint8_t _pin = toPin(pin);
	uint8_t _port = toPort(pin);
	
	if (is_port(_port)) {
		volatile uint8_t *port_reg = PORT[_port];;
		pull_up_on(*port_reg, _pin);
		}
	
}

void pullUpOff(uint8_t pin) {
	
	uint8_t _pin = toPin(pin);
	uint8_t _port = toPort(pin);
	
	if (is_port(_port)) {
		volatile uint8_t *port_reg = PORT[_port];
		pull_up_off(*port_reg, _pin);
	}
}

void digitalWrite(uint8_t pin, uint8_t state) {

	uint8_t _pin = toPin(pin);
	uint8_t _port = toPort(pin);
	volatile uint8_t *port_reg = PORT[_port];
	
	if (is_port(_port)) {
		if (state == HIGH) {
			set_pin_on(*port_reg, _pin);
		} else if (state == LOW) {
			set_pin_off(*port_reg, _pin);
		} else {
			return;
		}
	}		
}

void digitalToggle(uint8_t pin) {

	uint8_t _pin = toPin(pin);
	uint8_t _port = toPort(pin);
	volatile uint8_t *port_reg = PORT[_port];
	
	if (is_port(_port)) {
		toggle_pin(*port_reg, _pin);
	} else {
		return;
	}
}


bool digitalRead(uint8_t pin) {

	uint8_t _pin = toPin(pin);
	uint8_t _port = toPort(pin);
	volatile uint8_t *pin_reg = PIN[_port];
	
	if (is_port(_port)) {
		if (get_pin(*pin_reg, _pin)) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
	
}


bool filteredPinState(uint8_t pin, bool value, uint16_t T){
	
	uint8_t _port = toPort(pin);

	if (is_port(_port)) {
		// provjera da li je 80% vremena pin u vrijednosti value
		if (digitalRead(pin) == value) {
			uint16_t a = 0;
			uint16_t brojac = 0;
			while(a++ < T){
				_delay_ms(1);
				if (digitalRead(pin) == value) brojac++;
			}
			if (brojac >= T * FILTER_TIME) {
				return value;
			}
		}
	}
	return !value;
}

// deklaracija i inicijalizacija varijabli koje se koriste za spremanje starog stanja
// PIN registra, a za potrebe funkcija koje testiraju padajuci i rastuci brid
uint8_t pinOldState[4] = {0xFF, 0xFF, 0xFF, 0xFF};

bool isFallingEdge(uint8_t pin) {

	uint8_t _pin = toPin(pin);
	uint8_t _port = toPort(pin);
	
	if (is_port(_port)) {	
		// ako je novo stanje pina false, a staro true => desio se padajuci brid
		if ((digitalRead(pin) == false) && (((pinOldState[_port] & (1 << _pin)) >> _pin) == true)) {
			pinOldState[_port] &= ~(1 << _pin);
			return true;
		}
		// ako nema brida, pohrani novu vrijednost pina u buducu staru vrijednost
		if (digitalRead(pin) == true) {
			pinOldState[_port] |= (1 << _pin);
		}
	}
	
	return false;
}

bool isRisingEdge(uint8_t pin) {

	uint8_t _pin = toPin(pin);
	uint8_t _port = toPort(pin);
	
	if (is_port(_port)) {	
		// ako je novo stanje pina true, a staro false => desio se rastuci brid
		if ((digitalRead(pin) == true) && (((pinOldState[_port] & (1 << _pin)) >> _pin) == false)) {
			pinOldState[_port] |= (1 << _pin);
			return true;
		}
		// ako nema brida, pohrani novu vrijednost pina u buducu staru vrijednost
		if (digitalRead(pin) == false) {
			pinOldState[_port] &= ~(1 << _pin);
		}
	}
	return false;
}

void buzz(uint64_t duration, int freq){
	long int i, cycles;
	cycles = duration * freq /1000.0; // broj ciklusa izmjena pina za zujalicu
	long int period = 1.0 / freq * 100000; // izracun poluperioda
	long int half_period =  period / 2;
	BUZZER_DDR |= (1 << BUZZER_PIN);  // konfiguriranje izlaznog pina za zujalicu
	
	for (i=0; i < cycles; i++)   // mijenjaj stanje pina zujalice (cycles) puta
	{
		half_period = period/2;
		while(half_period--) {
			_delay_us(10);
		}
		
		BUZZER_PORT |= (1 << BUZZER_PIN);    // postavi pin zujalice
		
		half_period = period/2;
		while(half_period--) {
			_delay_us(10);
		}                       // cekaj poluperiodu
		BUZZER_PORT &= ~(1 << BUZZER_PIN);   // resetiraj pin zujalice
	}
	
}