/*
 Datoteka: rotEnc.h
 Namjena biblioteke: Rotacijski enkoder
 Autor: Danijel Radocaj
 Licenca: Ovo djelo je dano na koristenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */


#ifndef ROTENC_H_
#define ROTENC_H_

// START USER CODE
#include "../AVR/avrlib.h"
#include <stdio.h>

#define ENCODER_LOW_THRESHOLD 0			// najmanja moguca vrijednost enkodera
#define ENCODER_HIGH_THRESHOLD 100		// najveca moguca vrijednost enkodera

void rotEncINIT();		// funkcija za inicijalizaciju rotacijskog enkodera
bool rotEncBTN();		// funkcija za detekciju stanja tipkala rotacijskog enkodera
bool rotEncDIR();		// funkcija za detekciju smjera okretanja rotacijskog enkodera
uint8_t rotEncUPDATEnREAD(uint8_t encValue);		// funkcija za azuriranje i citanje vrijednosti enkodera u neku varijablu

// END USER CODE

#endif /* ROTENC_H_ */