/*
 Biblioteka: lm35.h
 Autor: Zoran Vrhovski
 Datum: 10. 12. 2021. 
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */ 


#ifndef LM35_H_
#define LM35_H_
#include "../ADC/adc.h"

inline float readTempLM35(uint8_t ch) {
	return adcReadVoltage(ch) * 100.0;
}

inline float adcConvertToTempLM35(uint16_t adc) {
	return adcConvertToVoltage(adc) * 100.0;
}



#endif /* LM35_H_ */