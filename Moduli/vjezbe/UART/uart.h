/*
 Biblioteka: uart.h
 Autor: Zoran Vrhovski
 Datum: 5. 4. 2022. 
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */ 

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "stdbool.h"
#include <stdio.h>

#define END_CHAR '\r' // zakljucni znak // znak '\r' je Carriage Return (CR) ASCII kod 0x0D
#define MESSAGE_LENGTH 100 // maksimalna duljina poruke
char uartBuffer[MESSAGE_LENGTH + 1] = {}; // buffer za dolazne poruke
volatile char *uartBufferPtr = uartBuffer; //pointer na uartBuffer

void uartInit(uint32_t baudRate) {
	uint16_t ubrrValue;
	ubrrValue = F_CPU / (16. * baudRate) - 1;
	// konfiguracija baudrate - a
	UBRR0 = ubrrValue; 
	UCSR0C |= (0 << UCSZ02) | (1 << UCSZ01) | (1 << UCSZ00); // 8-bitna komunikacija, 
	UCSR0C |= (0 << USBS0) | (0 << UPM01) | (0 << UPM00); //1 stop bit, parity off
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // Rx i Tx omogucen
	UCSR0B |= (1 << RXCIE0); // Prekid Rx omogucen
}


char uartgetchar() {
	//cekaj dok podatak ne bude dostupan
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

// vraca pokazivac na uartBuffer
char* uartgets() {
	return uartBuffer;
}

// vraca pokazivac na uartBuffer
void uartCopyBuffer(char *usartMessage) {
	char *pok = uartBuffer;
	while(*pok) {
		*usartMessage = *pok;
		pok++;
		usartMessage++;
	}
}


// prekidna rutina koja prima poruke i zapisuje ih u buffer
ISR(USART_RX_vect) {
	*uartBufferPtr = uartgetchar();
	if (*uartBufferPtr != END_CHAR) {
		uartBufferPtr++;
	}
}	


// vraca true kada je stigla cijela poruka
bool uartIsMessageRecived() {
	if(*uartBufferPtr == END_CHAR) {
		*uartBufferPtr = '\0';
		uartBufferPtr = uartBuffer;
		return true;
	}	
	else {
		return false;	
	}
}

void uartputchar(char uartChar) {
	//cekaj dok transmiter ne bude spreman za slanje
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = uartChar;
}

void uartputs(const char *uartMessage) {
	while(*uartMessage) {
		uartputchar(*uartMessage);
		uartMessage++;
	}
}

void uartprintf(char *szFormat, ...) {
	// kreiranje stringa
	char szBuffer[MESSAGE_LENGTH];
	va_list pArgs;
	va_start(pArgs, szFormat);
	vsprintf(szBuffer, szFormat, pArgs);
	va_end(pArgs);
	//posalji string
	uartputs(szBuffer);
}

#endif /* UART_H_ */