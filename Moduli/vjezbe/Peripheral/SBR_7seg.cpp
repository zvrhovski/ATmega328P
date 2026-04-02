/*
 Datoteka: SBR_7seg.cpp
 Namjena biblioteke: Numericki displej i posmacni registar
 Autor: Danijel Radocaj
 Licenca: Ovo djelo je dano na koristenje pod licencom Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */

#include "SBR_7seg.h"

//-----------------------------------------------------------------------------------------
// FUNCTION: sbr_init
// PURPOSE: initialize SBRs chips (SER; RCK; SCK)

void sbr_init(void)
{
	SER_DDR |= (1 << SER_PIN);	// inicijalizacija serijskog ulaza (SER) u SBR
	RCK_DDR |= (1 << RCK_PIN);	// inicijalizacija register clock ulaza (RCK) u SBR
	SCK_DDR |= (1 << SCK_PIN);	// inicijalizacija serial clock ulaza (SCK) u SBR
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
			SER_PORT |= (1 << SER_PIN);
		}
		else
		{
			SER_PORT &= ~(1 << SER_PIN);
		}
		
		sbr_serial_clock();
		
		data = data >> 1;
	}

	//sbr_register_clock();
}

//-----------------------------------------------------------------------------------------
// FUNCTION: sbr_send_4B
// PURPOSE: send a 4 bytes of data to SBRs

void sbr_send_4B(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
	sbr_send_1B(data1);
	sbr_send_1B(data2);
	sbr_send_1B(data3);
	sbr_send_1B(data4);

	sbr_register_clock();
}