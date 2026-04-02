/*
 Datoteka: adc.cpp
 Autor: Zoran Vrhovski
 Datum: 3. 12. 2021. 
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */ 
#include "adc.h"

// inicijalizacija adc pretvorbe
void adcInit() {
	// postavi referencu
	adcSetReference(ADC_REFERENCE_AVCC);
	// postavi djelitelj frekvencije
	adcSetPrescaler();
	// omoguci adc pretvorbu
	adcEnable();
	adcInitialized = true;
}

void adcSetPrescaler(void) {
	ADCSRA &= ~ADC_PRESCALE_MASK;
	ADC_SET_PRESCALER();
}

void adcSetReference(uint8_t ref) {
	ADMUX &= ~ADC_REFERENCE_MASK;
	ADMUX |= ref;
	ADC_REFERENCE = ref;
	switch(ref) {
		case ADC_REFERENCE_AVCC:
		adcReference = 5.0;
		break;
		case ADC_REFERENCE_AREF:
		adcReference = 5.0;
		break;
		case ADC_REFERENCE_11V:
		adcReference = 1.1;
		break;
		default:
		break;
	}	
}

uint16_t adcRead(uint8_t ch){
	// ako nije inicijaliziran ADC, inicijaliziraj
	if(adcInitialized == false){
		adcInit();
	}
	// ako se pozove kanal koji ne postoji
	if (ch == ADC6 || ch == ADC7 || ch > ADCTEMP) { 
		return 0;
	}
	
	// ako se koristi on-chip temperaturni senzor, tada se mijenja referenca na 2.56V
	if (ch == ADCTEMP){
		adcSetReference(ADC_REFERENCE_256V);
	}
	
	// odabir kanala
	ADMUX &= ~ADC_MUX_MASK;
	ADMUX |= (ch & ADC_MUX_MASK);
	
	// Start conversion
	ADCSRA |= (1 << ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1 << ADIF)));

	//Clear ADIF by writing one to it
	ADCSRA |= (1<<ADIF);
	
	// ako se koristi on-chip temperaturni senzor, tada se mijenja referenca na 2.56V
	// nakon izracuna ADC vrijednosti, referenca se vraca na ADC_REFERENCE u adc.h
	if (ch == ADCTEMP){
		adcSetReference(ADC_REFERENCE);
	}
	
	return (ADC);  // read ADC (full 10 bits);
}

uint16_t adcReadAverage(uint8_t ch, uint8_t n) {
	uint16_t adc = 0;
	
	if (n > 64) n = 64;
	if (n == 0) n = 1;
	for (uint8_t i = 0; i < n; i ++) {
		adc += adcRead(ch);
		_delay_ms(10);
	}
	
	adc /= n;	
	return adc;
}


float adcReadScale0To100(uint8_t ch){
	uint16_t adc = adcRead(ch);
	return adc / 1023.0f * 100.0;
}

float adcScale0To100(uint16_t adc){
	return adc / 1023.0f * 100.0;
}



float adcReadScaleAToB(uint8_t ch, float a, float b) {
	uint16_t adc = adcRead(ch);
	return (adc / 1023.0f * (b - a) + a);	
}


float adcScaleAToB(uint16_t adc, float a, float b) {
	return (adc / 1023.0f * (b - a) + a);
}


float adcReadVoltage(uint8_t ch) {
	uint16_t adc = adcRead(ch);
	return adc / 1024.0f * adcReference;
}

float adcConvertToVoltage(uint16_t adc) {
	return adc / 1024.0f * adcReference;
}


void adcDisable(void){
	ADCSRA &= ~(1 << ADEN);
}


void adcEnable(void){
	// Power up the ADC
	ADCSRA |= (1 << ADEN);
}
