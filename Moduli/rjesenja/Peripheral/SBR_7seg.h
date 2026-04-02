/*
 Datoteka: SBR_7seg.cpp
 Namjena biblioteke: Numericki displej i posmacni registar
 Autor: Zoran Vrhovski
 Autor: Danijel Radocaj
 Licenca: Ovo djelo je dano na koristenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */

#ifndef SBR_7SEG_H_
#define SBR_7SEG_H_

#include "../AVR/avrlib.h"
#include <stdio.h>
#include <util/delay.h>

//-----------------------------------------------------------------------------------------
// CONFIGs: Configuration of physical pins for SBRs
// PURPOSE: simplify and cross-out need for changing whole lib when reconfigured
#define	SI_DDR DDRC
#define RCK_DDR DDRC
#define SCK_DDR DDRC

#define SI_PORT PORTC
#define RCK_PORT PORTC
#define SCK_PORT PORTC

#define SI_PIN PC1
#define RCK_PIN PC2
#define SCK_PIN PC3

//-----------------------------------------------------------------------------------------
// DEFINEs: Numerical chars
// PURPOSE: cross-out need for remembering HEX values of decade nums
#define NUM_DOT 0x01
#define NUM_0 0xFC
#define NUM_1 0x60
#define NUM_2 0xDA
#define NUM_3 0xF2
#define NUM_4 0x66
#define NUM_5 0xB6
#define NUM_6 0xBE
#define NUM_7 0xE0
#define NUM_8 0xFE
#define NUM_9 0xF6

const uint8_t charset[10] = {
	0xFC,	// 0
	0x60,	// 1
	0xDA,	// 2
	0xF2,	// 3
	0x66,	// 4
	0xB6,	// 5
	0xBE,	// 6
	0xE0,	// 7
	0xFE,	// 8
	0xF6	// 9
};

//-----------------------------------------------------------------------------------------
// FUNCTION: sbr_init
// PURPOSE: initialize SBRs chips (SER; RCK; SCK)

void sbr_init(void);

//-----------------------------------------------------------------------------------------
// FUNCTION: sbr_serial_clock
// PURPOSE: send a serial clock to SBRs

void sbr_serial_clock(void);

//-----------------------------------------------------------------------------------------
// FUNCTION: sbr_register_clock
// PURPOSE: send a register clock to SBRs

void sbr_register_clock(void);

//-----------------------------------------------------------------------------------------
// FUNCTION: sbr_send_1B
// PURPOSE: send a 1 byte of data to SBRs

void sbr_send_1B(uint8_t data);

//-----------------------------------------------------------------------------------------
// FUNCTION: sbr_send_4B
// PURPOSE: send a 4 bytes of data to SBRs

void sbr_send_4B(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4);


#endif /* SBR_7SEG_H_ */