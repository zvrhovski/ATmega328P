/*
 Biblioteka: avrlib.h
 Autor: Zoran Vrhovski
 Datum: 15. 9. 2021. 
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */ 

#ifndef AVRLIB_H_
#define AVRLIB_H_
#include <avr/io.h>
#ifndef F_CPU // ako nije definiran F_CPU, definiraj ga na 16MHz
#define F_CPU 16000000UL
#endif

#ifndef MESSAGE_LENGTH
#define MESSAGE_LENGTH 50 // maksimalna duljina poruke
#endif

// definicija pinova za mikroupravljac ATmega328P
//PORTB
#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7
//PORTC
#define PC0 0
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5
#define PC6 6
//PORTD
#define PD0 0
#define PD1 1
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

// definicija pinova za mikroupravljac ATmega328P za funkcijski pristup konfiguriranju pinova

#define B0 8
#define B1 9
#define B2 10
#define B3 11
#define B4 12
#define B5 13
#define B6 14
#define B7 15

#define C0 16
#define C1 17
#define C2 18
#define C3 19
#define C4 20
#define C5 21
#define C6 22

#define D0 24
#define D1 25
#define D2 26
#define D3 27
#define D4 28
#define D5 29
#define D6 30
#define D7 31


#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

#define LOW 0
#define HIGH 1


volatile uint8_t *const PORT[4] = {((volatile uint8_t *)0), &PORTB, &PORTC, &PORTD};
volatile uint8_t *const DDR[4] = {((volatile uint8_t *)0), &DDRB, &DDRC, &DDRD};
volatile uint8_t *const PIN[4] = {((volatile uint8_t *)0), &PINB, &PINC, &PIND};

#define is_port(x) (x == 1 || x == 2 || x == 3) 



//ukljucivanje i iskljucivanje pull up otpornika
#define pull_up_on(port, pin_position) port |= (1 << pin_position)
#define pull_up_off(port, pin_position) port &= ~(1 << pin_position)

//ukljucivanje i iskljucivanje pina
#define set_pin_on(port, pin_position) port |= (1 << pin_position)
#define set_pin_off(port, pin_position) port &= ~(1 << pin_position)

//promjena stanja pina
#define toggle_pin(port, pin_position) port ^= (1 << pin_position)

//citanje stanja na pinu
#define get_pin(port, pin_position) ((port & (1 << pin_position)) >> pin_position)

//postavljanje ulaznih i izlaznih pinova
#define config_output(x,y) x |= (1 << y)
#define config_input(x,y) x &= ~(1 << y)

//postavljanje bita u 8-bitnoj maski
#define set_bit(bit) (1 << bit)
#define reset_bit(bit) ~(1 << bit)

//postavljanje bita u registru x na poziciji y 
#define set_bit_reg(x,y) x |= set_bit(y) // postavljanje u 1
#define reset_bit_reg(x,y) x &= reset_bit(y) // postavljanje u 0



inline uint8_t toPort(uint8_t pp) {return pp / 8;}
inline uint8_t toPin(uint8_t pp) {return pp % 8;}


void pinMode(uint8_t pin, uint8_t config);
void digitalWrite(uint8_t pin, uint8_t state);
bool digitalRead(uint8_t pin);
void pullUpOn(uint8_t pin);
void pullUpOff(uint8_t pin);


//definiranje ina za zujalicu i funkcija BUZZ za zujanje
#define BUZZER_PORT PORTD
#define BUZZER_DDR  DDRD
#define BUZZER_PIN  PD1


	
#define FILTER_TIME70PERCENT 7 / 10
#define FILTER_TIME80PERCENT 8 / 10
#define FILTER_TIME90PERCENT 9 / 10
#define FILTER_TIME100PERCENT 10 / 10
#define FILTER_TIME FILTER_TIME90PERCENT

bool filteredPinState(uint8_t pin, bool value, uint16_t T);

void digitalToggle(uint8_t pin);
bool isFallingEdge(uint8_t pin);
bool isRisingEdge(uint8_t pin);

#endif /* AVRLIB_H_ */