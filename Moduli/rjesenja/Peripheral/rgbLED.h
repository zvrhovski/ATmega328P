/*
 Datoteka: rgbLED.h
 Namjena biblioteke: RGB LE dioda
 Autor: Danijel Radocaj
 Licenca: Ovo djelo je dano na koristenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */

#ifndef RGBLED_H_
#define RGBLED_H_

// START USER CODE
#include "../AVR/avrlib.h"

void rgbINIT();		// funkcija za inicijalizaciju RGB LE diode
void rgbCHwrite(uint8_t chR, uint8_t chG, uint8_t chB);		// funkcija za postavljanje duty cycle vrijednosti za PWM kanale  - OC1A, OC1B, OC2A

// END USER CODE

#endif /* RGBLED_H_ */