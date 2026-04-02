/*
 Biblioteka: lcd.h
 Autor: Zoran Vrhovski
 Datum: 25. 11. 2021. 
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */ 

#ifndef LCD_H_
#define LCD_H_

#include "../AVR/avrlib.h"
#include <stdio.h>
#include <util/delay.h>

//--------------------------------------------------------------------------------
// korisnik mijenja samo konfiguraciju displeja pri korištenju ove biblioteke
// konfiguracija LCD displeja
#define LCD_D4_PIN		C3 // D4 na LCD displeju - 4 bita komunikacija - pin
#define LCD_D5_PIN		C2 // D5 na LCD displeju - 4 bita komunikacija - pin
#define LCD_D6_PIN		C1 // D6 na LCD displeju - 4 bita komunikacija - pin
#define LCD_D7_PIN		B0 // D7 na LCD displeju - 4 bita komunikacija - pin

#define LCD_RS_PIN		B5 // RS na LCD displeju - pin za odabir registra
#define LCD_EN_PIN      B4 // E na LCD displeju - pin za odabir registra

#define LCD_LINES		2  // broj redova na LCD displeju
#define LCD_DISP_LENGTH 16 // broj znakova (vidljivih) u redu na LCD displeju
// kraj konfiguracije LCD displeja
//--------------------------------------------------------------------------------

// definiranje vlastitih znakova
const uint8_t customChar1[] = {0x00, 0x08, 0x0E, 0x1F, 0x1F, 0x1E, 0x00, 0x00}; //like
const uint8_t customChar2[] = {0x0A, 0x04, 0x0E, 0x11, 0x10, 0x11, 0x0E, 0x00}; //ch
const uint8_t customChar3[] = {0x02, 0x04, 0x0E, 0x11, 0x10, 0x11, 0x0E, 0x00}; //tj
const uint8_t customChar4[] = {0x02, 0x07, 0x02, 0x0E, 0x12, 0x12, 0x0E, 0x00}; //dj
const uint8_t customChar5[] = {0x0A, 0x04, 0x0E, 0x10, 0x0E, 0x01, 0x1E, 0x00}; //sh
const uint8_t customChar6[] = {0x0A, 0x04, 0x1F, 0x02, 0x04, 0x08, 0x1F, 0x00}; //z?
const uint8_t customChar7[] = {0x00, 0x00, 0x0A, 0x00, 0x0E, 0x11, 0x00, 0x00}; // :(
const uint8_t customChar8[] = {0x00, 0x00, 0x0A, 0x00, 0x11, 0x0E, 0x00, 0x00}; // :)
// moguce je definirati vise od 8 znakova, a u LCD upisati samo one znakove koji su Vam potrebni   


// korisnik ne mijenja dolje navedene konstante, makronaredbe i deklaracije funkcija 
// pozicije pinova oblika Pxi, npr. PB0, PC3 itd. za potrebe makronaredbi set_bit i reset_bit
#define LCD_D4		LCD_D4_PIN % 8   // D4 na LCD displeju - 4 bita komunikacija - pin oblika Pxi
#define LCD_D5		LCD_D5_PIN % 8   // D5 na LCD displeju - 4 bita komunikacija - pin oblika Pxi
#define LCD_D6		LCD_D6_PIN % 8	 // D6 na LCD displeju - 4 bita komunikacija - pin oblika Pxi
#define LCD_D7		LCD_D7_PIN % 8   // D7 na LCD displeju - 4 bita komunikacija - pin oblika Pxi
#define LCD_RS		LCD_RS_PIN % 8	 // RS na LCD displeju - pin za odabir registra
#define LCD_EN		LCD_EN_PIN % 8   // E na LCD displeju - pin za odabir registra	


// pokazivaci na PORT registre pinova LCD-a
static volatile uint8_t *lcdD4Port = PORT[toPort(LCD_D4_PIN)];
static volatile uint8_t *lcdD5Port = PORT[toPort(LCD_D5_PIN)];
static volatile uint8_t *lcdD6Port = PORT[toPort(LCD_D6_PIN)];
static volatile uint8_t *lcdD7Port = PORT[toPort(LCD_D7_PIN)];
static volatile uint8_t *lcdRSPort = PORT[toPort(LCD_RS_PIN)];
static volatile uint8_t *lcdENPort = PORT[toPort(LCD_EN_PIN)];

// instrukcije LCD displeja
// osnovne instrukcije LCD displeja s opisom na engleskom jeziku
#define LCD_CLEARDISPLAY   0x01  // clear LCD display 
#define LCD_RETURNHOME     0x02  // return to home
#define LCD_ENTRYMODESET   0x04  // set entry mode
#define LCD_DISPLAYCONTROL 0x08	 // display control
#define LCD_CURSORSHIFT    0x10  // shift cursor
#define LCD_FUNCTIONSET    0x20	 // set function
#define LCD_SETCGRAMADDR   0x40  // set CGRAM memory address
#define LCD_SETDDRAMADDR   0x80  // set DGRAM memory address

// set entry mode: display shift on/off, dec/inc cursor move direction
#define LCD_ENTRY_DEC            0x04	// display shift off, dec cursor move dir
#define LCD_ENTRY_DEC_SHIFT      0x05   // display shift on,  dec cursor move dir
#define LCD_ENTRY_INC_           0x06   // display shift off, inc cursor move dir
#define LCD_ENTRY_INC_SHIFT      0x07   // display shift on,  inc cursor move dir

// display on/off, cursor on/off, blinking char at cursor position
#define LCD_DISP_OFF             0x08   // display off
#define LCD_DISP_ON              0x0C   // display on, cursor off
#define LCD_DISP_ON_BLINK        0x0D   // display on, cursor off, blink char
#define LCD_DISP_ON_CURSOR       0x0E   // display on, cursor on
#define LCD_DISP_ON_CURSOR_BLINK 0x0F   // display on, cursor on, blink char

// move cursor/shift display
#define LCD_MOVE_CURSOR_LEFT     0x10   // move cursor left  (decrement)
#define LCD_MOVE_CURSOR_RIGHT    0x14   // move cursor right (increment)
#define LCD_MOVE_DISP_LEFT       0x18   // shift display left
#define LCD_MOVE_DISP_RIGHT      0x1C   // shift display right

// function set: set interface data length and number of display lines
#define LCD_FUNCTION_4BIT_1LINE  0x20   // 4-bit interface, single line, 5x7 dots
#define LCD_FUNCTION_4BIT_2LINES 0x28   // 4-bit interface, dual line,   5x7 dots
#define LCD_FUNCTION_8BIT_1LINE  0x30   // 8-bit interface, single line, 5x7 dots
#define LCD_FUNCTION_8BIT_2LINES 0x38   // 8-bit interface, dual line,   5x7 dots

#define LCD_START_LINE1  		 0x00   // DDRAM address of first char of line 1
#define LCD_START_LINE2  		 0x40   // DDRAM address of first char of line 2
#define LCD_START_LINE3  		 0x14   // DDRAM address of first char of line 3
#define LCD_START_LINE4  		 0x54   // DDRAM address of first char of line 4

// deklaracije funkcija s opisom na engleskom jeziku
//-----------------------------------------------------------------------------------------
// FUNCTION: lcdENToggle
// PURPOSE: toggle enable pin
void lcdENToggle(void);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdWrite
// PURPOSE: send a character or an instruction to the LCD
void lcdWrite(uint8_t data,uint8_t rs) ;

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdInstruction
// PURPOSE:  send an instruction to the LCD
void lcdInstruction(uint8_t instr);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdChar
// PURPOSE:  send a character to the LCD
void lcdChar(uint8_t data);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdInit
// PURPOSE:  Initialize LCD to 4 bit I/O mode
void lcdInit();

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdSetline
// PURPOSE:  Move cursor on specified line
void lcdSetline(uint8_t line);

extern int g_nCurrentLine;

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdPrint
// PURPOSE:  send a null terminated string to the LCD eg. char x[10]="hello!";
void lcdPrint(char *text);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdprintf
// PURPOSE:  printf sintax 
void lcdprintf(char *szFormat, ...);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdGotoXY
// PURPOSE:  Set cursor to specified position
//           Input:    x  row (1 -> first row)
//                     y  column (1 -> first column)
void lcdGotoXY(uint8_t x, uint8_t y);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdClrScr
// PURPOSE:  Clear display and set cursor to home position
void lcdClrScr(void);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdHome
// PURPOSE:  Set cursor to home position
void lcdHome(void);
//-----------------------------------------------------------------------------------------
// FUNCTION: lcdCreateChar
// PURPOSE:  set additional characters in CGRAM
void lcdCreateChar(uint8_t addr,  const uint8_t *customChar);

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdShiftLeft
// PURPOSE:  shift the contents of the LCD display (text and cursor) one space to the left. 
void lcdShiftLeft();

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdShiftRight
// PURPOSE:  shift the contents of the LCD display (text and cursor) one space to the right.
void lcdShiftRight();

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdShiftOff
// PURPOSE:  disable shift of contents on the LCD display
void lcdShiftOff();

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdENDelay
// PURPOSE:   _delay_us(1);

inline void lcdENDelay() { _delay_us(1);};
	
//-----------------------------------------------------------------------------------------
// FUNCTION: lcdENHigh
// PURPOSE:   set pin E;
inline void lcdENHigh() { *lcdENPort  |=  set_bit(LCD_EN);}
	
//-----------------------------------------------------------------------------------------
// FUNCTION: lcdENLow
// PURPOSE:  reset pin E;
inline void lcdENLow() { *lcdENPort  &= reset_bit(LCD_EN);}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdENHigh
// PURPOSE:   set pin RS;
inline void lcdRSHigh() { *lcdRSPort |=  set_bit(LCD_RS);}

//-----------------------------------------------------------------------------------------
// FUNCTION: lcdENLow
// PURPOSE:  reset pin RS;
inline void lcdRSLow() { *lcdRSPort &= reset_bit(LCD_RS);}
	
	
#endif /* LCD_H_ */