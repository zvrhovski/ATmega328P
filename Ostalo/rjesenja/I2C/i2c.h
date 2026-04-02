/*
 Biblioteka: i2c.h
 Autor: Zoran Vrhovski
 Datum: 22. 4. 2022. 
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */ 
#ifndef I2C_H
#define I2C_H

#ifndef  F_CPU
#define F_CPU 16000000UL
#endif

#include <util/twi.h>

// read & write values
// (address << 1) | RW
#define I2C_READ 1
#define I2C_WRITE 0

#define F_SCL 100000UL // SCL frekvencija 100 kHz
#define TWI_PRESCALER 1
#define TWBR_val ((((F_CPU / F_SCL) / TWI_PRESCALER) - 16 ) / 2) //  TWPS = 00

void i2cInit(){
	
	TWBR = TWBR_val; //SCL frekvencija
}

uint8_t i2cStart(uint8_t address, uint8_t RW){
	//Send START condition
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	// Wait for TWINT Flag set. This indicates 	that the START condition has been transmitted
	while(!(TWCR & (1 << TWINT)));
	// Check value of TWI Status Register. Mask prescaler bits. If status different from START go to ERROR
	if(TW_STATUS != TW_START) {
		return 1;
	}
	// Load SLA_W into TWDR Register. Clear TWINT bit in TWCR to start transmission of address
	TWDR = (address << 1) | RW;
	TWCR = (1 << TWINT) | (1 << TWEN);
	// Wait for TWINT Flag set. This indicates that the SLA+W has been transmitted,	and ACK/NACK has been received.
	while(!(TWCR & (1 << TWINT)));
	// Check if the device has acknowledged the READ / WRITE mode.
	if (((TW_STATUS & 0xF8) != TW_MT_SLA_ACK) && ((TW_STATUS & 0xF8) != TW_MR_SLA_ACK)) {
		return 1;
	}
	return 0;
}

uint8_t i2cWrite(uint8_t data){
	// load data into data register
	TWDR = data;
	// start transmission of data
	TWCR = (1 << TWINT) | (1 << TWEN);
	// wait for end of transmission
	while(!(TWCR & (1 << TWINT)));
	if(TW_STATUS != TW_MT_DATA_ACK) {
		return 1;
	}
	return 0;
}

uint8_t i2cSReadACK(){
	// start TWI module and acknowledge data after reception
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	// wait for end of transmission
	while(!(TWCR & (1 << TWINT)));
	// return received data from TWDR
	return TWDR;
}

uint8_t i2cSReadNACK(){
	// start receiving without acknowledging reception
	TWCR = (1 << TWINT) | (1 << TWEN);
	// wait for end of transmission
	while(!(TWCR & (1 << TWINT)));
	// return received data from TWDR
	return TWDR;
}

void i2cStop(){
	// transmit STOP condition
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	// wait until stop condition is executed and bus released
	while(TWCR & (1 << TWSTO));
}



uint16_t read_position(uint8_t address, uint8_t offset){
	
	uint8_t b0, b1;
	uint16_t position;
	
	i2cStart(address, I2C_WRITE);
	i2cWrite(offset);
	i2cStop();
	
	//_delay_ms(1);
	
	i2cStart(address, I2C_READ);
	b0 = i2cSReadACK();
	b1 = i2cSReadNACK();
	i2cStop();
	
	position = b1 << 8;
	position |= b0;
	
	return position;
}


void write_position(uint8_t address, uint16_t position){
	
	uint8_t b0, b1;
	
	b0 = position;
	b1 = position >> 8;
	
	i2cStart(address, I2C_WRITE);
	i2cWrite(0);
	i2cWrite(b0);
	i2cWrite(b1);
	i2cStop();
}

#endif // I2C_H
