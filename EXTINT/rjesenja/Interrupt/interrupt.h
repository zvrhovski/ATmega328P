/*
 Biblioteka: interrupt.h
 Autor: Zoran Vrhovski
 Datum: 22. 02. 2022. 
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/interrupt.h>

void interruptEnable(){
	sei();
}

void interruptDisable(){
	cli();
}	


/*******************************************************/
/*************************INT0**************************/

void int0Enable(){
	EIMSK |= (1 << INT0);
}

void int0Disable(){
	EIMSK &= ~(1 << INT0);
}

void int0LowLevel(){
	EICRA &= ~((1 << ISC01) | (1 << ISC00));
	EICRA |= (0 << ISC01) | (0 << ISC00);
}

void int0RisingFallingEdge(){
	EICRA &= ~((1 << ISC01) | (1 << ISC00));
	EICRA |= (0 << ISC01) | (1 << ISC00);
}

void int0FallingEdge(){
	EICRA &= ~((1 << ISC01) | (1 << ISC00));
	EICRA |= (1 << ISC01) | (0 << ISC00);
}


void int0RisingEdge(){
	EICRA &= ~((1 << ISC01) | (1 << ISC00));
	EICRA |= (1 << ISC01) | (1 << ISC00);
}



/*******************************************************/
/*************************INT1**************************/

void int1Enable(){
	EIMSK |= (1 << INT1);
}

void int1Disable(){
	EIMSK &= ~(1 << INT1);
}

void int1LowLevel(){
	EICRA &= ~((1 << ISC11) | (1 << ISC10));
	EICRA |= (0 << ISC11) | (0 << ISC10);
}

void int1RisingFallingEdge(){
	EICRA &= ~((1 << ISC11) | (1 << ISC10));
	EICRA |= (0 << ISC11) | (1 << ISC10);
}

void int1FallingEdge(){
	EICRA &= ~((1 << ISC11) | (1 << ISC10));
	EICRA |= (1 << ISC11) | (0 << ISC10);
}


void int1RisingEdge(){
	EICRA &= ~((1 << ISC11) | (1 << ISC10));
	EICRA |= (1 << ISC11) | (1 << ISC10);
}



/*******************************************************/
/*************************PCINT*************************/

uint8_t pcintPINBOld;
uint8_t pcintPINCOld;
uint8_t pcintPINDOld;

void pcintInit() {
	pcintPINBOld = PINB;
	pcintPINCOld = PINC;
	pcintPINDOld = PIND;
}

void pcintEnable7to0(){
	PCICR |= (1 << PCIE0);
}

void pcintEnable14to8(){
	PCICR |= (1 << PCIE1);
}

void pcintEnable23to16(){
	PCICR |= (1 << PCIE2);
}

void pcintDisable(){
	PCICR &= ~((1 << PCIE0) | (1 << PCIE1) | (1 << PCIE2));
}

void pcintPinEnable7to0(uint8_t pin){
	PCMSK0 |= (1 << pin);		
}

void pcintPinEnable14to8(uint8_t pin){
	PCMSK1 |= (1 << pin);
}

void pcintPinEnable23to16(uint8_t pin){
	PCMSK2 |= (1 << pin);
}

void pcintPinDisable7to0(uint8_t pin){
	PCMSK0 &= ~(1 << pin);
}

void pcintPinDisable14to8(uint8_t pin){
	PCMSK1 &= ~(1 << pin);
}

void pcintPinDisable23to16(uint8_t pin){
	PCMSK2 &= ~(1 << pin);
}


void pcintPinDisableAll(){
	PCMSK0 = 0x00;
	PCMSK1 = 0x00;
	PCMSK2 = 0x00;
}


uint8_t pcintPINDChanged() {
	uint8_t PINDChanged = pcintPINDOld ^ PIND;
	uint8_t pinIsChanged = 0;
	while(!(PINDChanged & 0x01)){
		pinIsChanged++;
		PINDChanged >>= 1;
		if (pinIsChanged == 8) {
			return pinIsChanged;
			break;
		}
	}
	return pinIsChanged;
}

/*
// prekidna rutina za vanjski prekid INT0
ISR(INT0_vect){

}

// prekidna rutina za vanjski prekid INT1
ISR(INT1_vect){

}

// prekidna rutina za PCINT0
ISR(PCINT0_vect) {

}


// prekidna rutina za PCINT1
ISR(PCINT1_vect) {

}


// prekidna rutina za PCINT2
ISR(PCINT2_vect) {

}

//*/

#endif /* INTERRUPT_H_ */