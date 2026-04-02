/*
 Datoteka: SBR_7seg.h
 Namjena biblioteke: Numericki displej i posmacni registar
 Autor: Zoran Vrhovski
 Autor: Danijel Radocaj
 Licenca: Ovo djelo je dano na koristenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */

#include "SBR_7seg.h"

//-----------------------------------------------------------------------------------------
// FUNCTION: sbr_init
// PURPOSE: initialize SBRs chips (SI; RCK; SCK)

void sbr_init(void)
{
	// inicijalizacija serijskog ulaza (SI) u SBR
	SI_DDR |= (1 << SI_PIN);	
	// inicijalizacija register clock ulaza (RCK) u SBR
	RCK_DDR |= (1 << RCK_PIN);	
	// inicijalizacija serial clock ulaza (SCK) u SBR
	SCK_DDR |= (1 << SCK_PIN);	
}

//-----------------------------------------------------------------------------------------
// FUNCTION: sbr_serial_clock
// PURPOSE: send a serial clock to SBRs

void sbr_serial_clock(void)
{
	SCK_PORT |= (1 << SCK_PIN);
	_delay_us(1);
	SCK_PORT &= ~(1 << SCK_PIN);
	_delay_us(1);
}

//-----------------------------------------------------------------------------------------
// FUNCTION: sbr_register_clock
// PURPOSE: send a register clock to SBRs

void sbr_register_clock(void)
{
	RCK_PORT |= (1 << RCK_PIN);
	_delay_us(1);
	RCK_PORT &= ~(1 << RCK_PIN);
	_delay_us(1);
}

//-----------------------------------------------------------------------------------------
// FUNCTION: sbr_send_1B
// PURPOSE: send a 1 byte of data to SBRs

void sbr_send_1B(uint8_t data)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if (data & 0x01)
		{
			SI_PORT |= (1 << SI_PIN);
		}
		else
		{
			SI_PORT &= ~(1 << SI_PIN);
		}
		
		sbr_serial_clock();
		
		data = data >> 1;
	}
}

//-----------------------------------------------------------------------------------------
// FUNCTION: sbr_send_4B
// PURPOSE: send a 4 bytes of data to SBRs

void sbr_send_4B(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4)
{
	sbr_send_1B(d4);
	sbr_send_1B(d3);
	sbr_send_1B(d2);
	sbr_send_1B(d1);

	sbr_register_clock();
}