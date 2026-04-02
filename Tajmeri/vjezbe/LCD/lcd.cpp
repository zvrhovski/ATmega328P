/*
 Datoteka: lcd.cpp
 Autor: Zoran Vrhovski
 Datum: 25. 11. 2021. 
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */ 

#include "lcd.h"

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdENToggle
// PURPOSE: toggle enable pin
void lcdENToggle(void){
	lcdENHigh();
	lcdENLow();
	
	_delay_us(300);	
}


//-----------------------------------------------------------------------------------------
// FUNCTION: lcdWrite
// PURPOSE: send a character or an instruction to the LCD
void lcdWrite(uint8_t data, uint8_t rs){
	//check write type
	if (rs)
	lcdRSHigh(); //write data
	else
	lcdRSLow();  //write instruciton
	
	// output high nibble first
		
	*lcdD7Port &= reset_bit(LCD_D7);
	*lcdD6Port &= reset_bit(LCD_D6);
	*lcdD5Port &= reset_bit(LCD_D5);
	*lcdD4Port &= reset_bit(LCD_D4);
		
	if(data & 0x80) *lcdD7Port |= set_bit(LCD_D7);
	if(data & 0x40) *lcdD6Port |= set_bit(LCD_D6);
	if(data & 0x20) *lcdD5Port |= set_bit(LCD_D5);
	if(data & 0x10) *lcdD4Port |= set_bit(LCD_D4);
	lcdENToggle();
	
	// output low nibble
	
	*lcdD7Port &= reset_bit(LCD_D7);
	*lcdD6Port &= reset_bit(LCD_D6);
	*lcdD5Port &= reset_bit(LCD_D5);
	*lcdD4Port &= reset_bit(LCD_D4);
	
	if(data & 0x08) *lcdD7Port |= set_bit(LCD_D7);
	if(data & 0x04) *lcdD6Port |= set_bit(LCD_D6);
	if(data & 0x02) *lcdD5Port |= set_bit(LCD_D5);
	if(data & 0x01) *lcdD4Port |= set_bit(LCD_D4);
	lcdENToggle();
	
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdChar
// PURPOSE:  send a character to the LCD
void lcdChar(uint8_t data){
	if (data =='\n'){
		if (g_nCurrentLine >= LCD_LINES - 1)
		lcdSetline(0);
		else
		lcdSetline(g_nCurrentLine+1);
	} else{
	lcdWrite(data,1);
	}
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdInstruction
// PURPOSE:  send an instruction to the LCD
void lcdInstruction(uint8_t instr)
{
	lcdWrite(instr,0);
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdInit
// PURPOSE:  Initialize LCD to 4 bit I/O mode
void lcdInit(){
	
	// configure all port bits as output (LCD data and control lines on different ports
	*(lcdRSPort - 1) |= set_bit(LCD_RS);
	*(lcdENPort - 1)  |= set_bit(LCD_EN);
	*(lcdD4Port - 1) |= set_bit(LCD_D4);
	*(lcdD5Port - 1) |= set_bit(LCD_D5);
	*(lcdD6Port - 1) |= set_bit(LCD_D6);
	*(lcdD7Port - 1) |= set_bit(LCD_D7);
	
	// wait for more than 40 ms after VCC rises to 2.7 V
	_delay_ms(50);
	
	// initial write to lcd is 8bit
	
	*lcdD5Port |= set_bit(LCD_D5); 
	*lcdD5Port |= set_bit(LCD_D4);
	lcdENToggle();
	_delay_us(4100); // delay, busy flag can't be checked here

	*lcdD5Port |= set_bit(LCD_D5);
	*lcdD5Port |= set_bit(LCD_D4);
	lcdENToggle();
	_delay_us(4100); // delay, busy flag can't be checked here

	*lcdD5Port |= set_bit(LCD_D5);
	*lcdD5Port |= set_bit(LCD_D4);
	lcdENToggle();
	_delay_us(4100); // delay, busy flag can't be checked here

	*lcdD5Port &= reset_bit(LCD_D4); //busy flag can be checked after the following instructions
	*lcdD5Port |= set_bit(LCD_D5);
	lcdENToggle();
	
	lcdInstruction(LCD_FUNCTION_4BIT_2LINES); // 4-bit interface, dual line,   5x7 dots
	
	lcdInstruction(LCD_DISP_OFF); // display off
	
	lcdInstruction(LCD_CLEARDISPLAY);	//clear display
	_delay_ms(2);

	lcdInstruction(LCD_RETURNHOME); // return to home position (0,0)
	_delay_ms(2);
	
	lcdInstruction(LCD_DISP_ON); // display on
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdSetline
// PURPOSE:  Move cursor on specified line
void lcdSetline(uint8_t line){
	uint8_t addressCounter = 0;
	switch(line){
		case 0: addressCounter = LCD_START_LINE1; break;
		case 1: addressCounter = LCD_START_LINE2; break;
		case 2: addressCounter = LCD_START_LINE3; break;
		case 3: addressCounter = LCD_START_LINE4; break;
		default:addressCounter = LCD_START_LINE1; break;
	}
	
	g_nCurrentLine = line;

	lcdInstruction(LCD_SETDDRAMADDR + addressCounter);
}

int g_nCurrentLine = 0;

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdPrint
// PURPOSE:  send a null terminated string to the LCD eg. char x[10]="hello!";
void lcdPrint(char *text){
	char c;
	while ( (c = *text++) )
	lcdChar(c);
}
//-----------------------------------------------------------------------------------------
// FUNCTION: lcdprintf
// PURPOSE:  printf sintax
void lcdprintf(char *szFormat, ...){
	char szBuffer[80]; //in this buffer we form the message
	va_list pArgs;
	va_start(pArgs, szFormat);
	vsprintf(szBuffer, szFormat, pArgs);
	va_end(pArgs);
	
	lcdPrint(szBuffer);
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdGotoXY
// PURPOSE:  Set cursor to specified position
//           Input:    x  row
//                     y  column

void lcdGotoXY(uint8_t y, uint8_t x) {
	y--;
	x--;
	#if LCD_LINES==1
	lcdInstruction(LCD_SETDDRAMADDR + LCD_START_LINE1 + x);
	#elif LCD_LINES==2
	switch (y){
		case 0: lcdInstruction(LCD_SETDDRAMADDR + LCD_START_LINE1 + x);break;
		case 1: lcdInstruction(LCD_SETDDRAMADDR + LCD_START_LINE2 + x);break;
		default: break;
	}
	#elif LCD_LINES==4
	switch (y){
		case 0: lcdInstruction(LCD_SETDDRAMADDR + LCD_START_LINE1 + x);break;
		case 1: lcdInstruction(LCD_SETDDRAMADDR + LCD_START_LINE2 + x);break;
		case 2: lcdInstruction(LCD_SETDDRAMADDR + LCD_START_LINE3 + x);break;
		case 3: lcdInstruction(LCD_SETDDRAMADDR + LCD_START_LINE4 + x);break;
		default: break;
	}
	#endif
}


//-----------------------------------------------------------------------------------------
// FUNCTION: lcdClrScr
// PURPOSE:  Clear display and set cursor to home position
void lcdClrScr(void){
	g_nCurrentLine = 0;
	lcdInstruction(LCD_CLEARDISPLAY);
	_delay_us(2000);
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdHome
// PURPOSE:  Set cursor to home position
void lcdHome(void){
	g_nCurrentLine = 0;
	lcdInstruction(LCD_RETURNHOME);
	_delay_us(2000);
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdCreateChar
// PURPOSE:  set additional characters in CGRAM
void lcdCreateChar(uint8_t addr,  const uint8_t *customChar) {
	
	lcdInstruction(LCD_SETCGRAMADDR + (addr << 3));
	for (uint8_t j = 0; j < 8; j++)	{
	lcdWrite(customChar[j], 1);
	}
}


//-----------------------------------------------------------------------------------------
// FUNCTION: lcdShiftLeft
// PURPOSE:  shift the contents of the LCD display (text and cursor) one space to the left.
void lcdShiftLeft() {
	//lcdInstruction(LCD_ENTRY_INC_SHIFT);
	lcdInstruction(LCD_MOVE_DISP_LEFT);
}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdShiftRight
// PURPOSE:  shift the contents of the LCD display (text and cursor) one space to the right.
void lcdShiftRight() {
	//lcdInstruction(LCD_ENTRY_INC_SHIFT);
	lcdInstruction(LCD_MOVE_DISP_RIGHT);	
}


//-----------------------------------------------------------------------------------------
// FUNCTION: lcdShiftOff
// PURPOSE:  disable shift of contents on the LCD display
void lcdShiftOff() {
	lcdInstruction(LCD_DISP_ON); 
}
