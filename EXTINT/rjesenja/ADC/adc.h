/*
 Biblioteka: adc.h
 Autor: Zoran Vrhovski
 Datum: 3. 12. 2021. 
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */ 

#ifndef ADC_H_
#define ADC_H_

#include "../AVR/avrlib.h"
#include <util/delay.h>

// global variables
static float adcReference = 5.0;
static uint8_t ADC_REFERENCE = 0;
static bool adcInitialized = false;

/**************************SETUP************************************/

#define ADC_PRESCALE_MASK		((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))

#ifndef F_CPU
	#error "F_CPU not defined!"
#endif

// ADC prescaler in regarding to F_CPU
#if F_CPU >= 16000000
	// 16MHz F_CPU / 128 prescaler = 125Khz ADC clock source
	#define ADC_SET_PRESCALER() 		(ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))
	
#elif F_CPU >= 9600000
	// 9.6MHz F_CPU / 64 prescaler = 150Khz ADC clock source
	#define ADC_SET_PRESCALER() 		(ADCSRA |= (1 << ADPS2) | (1 << ADPS1))
	
#elif F_CPU >= 8000000
	// 8MHz F_CPU / 64 prescaler = 125Khz ADC clock source
	#define ADC_SET_PRESCALER() 		(ADCSRA |= (1 << ADPS2) | (1 << ADPS1))
	
#elif F_CPU >= 4800000
	// 4.8MHz F_CPU / 32 prescaler = 150Khz ADC clock source
	#define ADC_SET_PRESCALER() 		(ADCSRA |= (1 << ADPS2) | (1 << ADPS0))
	
#elif F_CPU >= 1000000
	// 1MHz or 1.2MHz F_CPU / 8 prescaler = 125Khz or 150KHz ADC clock source
	#define ADC_SET_PRESCALER() 		(ADCSRA |= (1 << ADPS1) | (1 << ADPS0))
	
#elif F_CPU >= 128000
	// 128KHz F_CPU / 2 default lowest prescaler = 64Khz ADC clock source
	#define ADC_SET_PRESCALER() 		(ADCSRA &= ~((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)))
	
#else
	#error "F_CPU not supported. Please request support."
#endif


// defining constants for reference voltage on ADC
#define ADC_REFERENCE_AREF		((0 << REFS1) | (0 << REFS0))	// AREF pin
#define ADC_REFERENCE_AVCC		((0 << REFS1) | (1 << REFS0))	// AVCC pin
#define ADC_REFERENCE_RSVD		((1 << REFS1) | (0 << REFS0))	// Reserved
#define ADC_REFERENCE_256V		((1 << REFS1) | (1 << REFS0))	// internal 2.56 V

// do not change the mask value
// bit mask for adc reference
#define ADC_REFERENCE_MASK		((1 << REFS1) | (1 << REFS0))
// bit mask for adc channel multiplexer
#define ADC_MUX_MASK			((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0))

// ADC channel on ATmega328P
#define ADC0			0x00
#define ADC1			0x01
#define ADC2			0x02
#define ADC3			0x03
#define ADC4			0x04
#define ADC5			0x05
#define ADC6			0x06 // not in use
#define ADC7			0x07 // not in use
#define ADCTEMP			0x08


/**************************FUNCTION*********************************/

// initializes the ADC
void adcInit(void);

// read ADC value (10 bit) of channel ch
uint16_t adcRead(uint8_t ch);

// average of n reade of ADC value (10 bit) of channel ch
// max value for n is 64
uint16_t adcReadAverage(uint8_t ch, uint8_t n);

// read ADC value (10 bit) of channel ch and scale to range [0.0, 100.0]
float adcReadScale0To100(uint8_t ch);

// scale 10 bit AD value to range [0.0, 100.0]
float adcScale0To100(uint16_t adc);


// read ADC value (10 bit) of channel ch and scale to range [a, b]
float adcReadScaleAToB(uint8_t ch, float a, float b);

// scale 10 bit AD value to range [a, b]
float adcScaleAToB(uint16_t adc, float a, float b);

// read voltage of channel ch (float)
float adcReadVoltage(uint8_t ch);

// convert ADC value to pin voltage 
float adcConvertToVoltage(uint16_t adc);

// disable ADC conversion
void adcDisable(void);

// enable ADC conversion
void adcEnable(void);

// set prescaler for ADC conversion
void adcSetPrescaler(void);

// set reference for ADC conversion
void adcSetReference(uint8_t ref);

#endif /* ADC_H_ */