/*
 Biblioteka: timer.h
 Autor: Zoran Vrhovski
 Datum: 22. 02. 2022. 
 Licenca: Ovo djelo je dano na korištenje pod licencom Creative Commons 
 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 */ 


#ifndef TIMER_H_
#define TIMER_H_

float limitDuty (float D) {
	if(D > 100.0) {
		D = 100.0;
	}
	if(D < 0.0) {
		D = 0.0;
	}
	return D;
}


/*********************************************************/
/*************************TIMER0**************************/

//djelitelji frekvencije za sklop Timer/Counter1
#define TIMER0_PRESCALER_OFF		((0 << CS02) | (0 << CS01) | (0 << CS00))
#define TIMER0_PRESCALER_1			((0 << CS02) | (0 << CS01) | (1 << CS00))
#define TIMER0_PRESCALER_8			((0 << CS02) | (1 << CS01) | (0 << CS00))
#define TIMER0_PRESCALER_64			((0 << CS02) | (1 << CS01) | (1 << CS00))
#define TIMER0_PRESCALER_256		((1 << CS02) | (0 << CS01) | (0 << CS00))
#define TIMER0_PRESCALER_1024		((1 << CS02) | (0 << CS01) | (1 << CS00))
#define TIMER0_EXTERNAL_FALL_EDGE	((1 << CS02) | (1 << CS01) | (0 << CS00))
#define TIMER0_EXTERNAL_RISI_EDGE	((1 << CS02) | (1 << CS01) | (1 << CS00))

void timer0SetPrescaler(uint8_t prescaler){
	TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
	TCCR0B |= prescaler;
}

void timer0InterruptOVFEnable(){
	TIMSK0 |= (1 << TOIE0);
}

void timer0InterruptOVFDisable(){
	TIMSK0 &= ~(1 << TOIE0);
}

void timer0SetValue(uint8_t value){
	TCNT0 = value;
}

uint8_t timer0GetValue(){
	return TCNT0;
}

void timer0NormalMode(){
	// ocistiti WGM0 bitove u registrima TCCR0 A i B
	TCCR0A &= ~((1 << WGM01) | (1 << WGM00));
	TCCR0B &= ~(1 << WGM02);
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0));
	// postaviti Normalna nacin rada
	TCCR0A |= (0 << WGM01) | (0 << WGM00);
	TCCR0B |= (0 << WGM02);
}


void timer0FastPWM(){
	// ocistiti WGM0 bitove u registrima TCCR0 A i B
	TCCR0A &= ~((1 << WGM01) | (1 << WGM00));
	TCCR0B &= ~(1 << WGM02);
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0));
	// postaviti Fast PWM nacin rada
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (0 << WGM02);
}

void timer0PhaseCorrectPWM(){
	// ocistiti WGM0 bitove u registrima TCCR0 A i B
	TCCR0A &= ~((1 << WGM01) | (1 << WGM00));
	TCCR0B &= ~(1 << WGM02);
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0));
	// postaviti Phase correct PWM nacin rada
	TCCR0A |= (0 << WGM01) | (1 << WGM00);
	TCCR0B |= (0 << WGM02);
}


void timer0OC0AEnableNonInvertedPWM(){
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0));
	TCCR0A |= (1 << COM0A1) | (0 << COM0A0);
}

void timer0OC0AEnableInvertedPWM(){
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0));
	TCCR0A |= (1 << COM0A1) | (1 << COM0A0);
}

void timer0OC0ADisable(){
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0));
}

void timer0OC0BEnableNonInvertedPWM(){
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
	TCCR0A |= (1 << COM0B1) | (0 << COM0B0);
}

void timer0OC0BEnableInvertedPWM(){
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
	TCCR0A |= (1 << COM0B1) | (1 << COM0B0);
}

void timer0OC0BDisable(){
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
}


void timer0OC0ADutyCycle(float D){
	OCR0A = limitDuty(D)*2.55;
}

void timer0OC0BDutyCycle(float D){
	OCR0B = limitDuty(D)*2.55;
}


/*********************************************************/
/*************************TIMER1**************************/

//djelitelji frekvencije za sklop Timer/Counter1
#define TIMER1_PRESCALER_OFF		((0 << CS12) | (0 << CS11) | (0 << CS10))
#define TIMER1_PRESCALER_1			((0 << CS12) | (0 << CS11) | (1 << CS10))
#define TIMER1_PRESCALER_8			((0 << CS12) | (1 << CS11) | (0 << CS10))
#define TIMER1_PRESCALER_64			((0 << CS12) | (1 << CS11) | (1 << CS10))
#define TIMER1_PRESCALER_256		((1 << CS12) | (0 << CS11) | (0 << CS10))
#define TIMER1_PRESCALER_1024		((1 << CS12) | (0 << CS11) | (1 << CS10))
#define TIMER1_EXTERNAL_FALL_EDGE	((1 << CS12) | (1 << CS11) | (0 << CS10))
#define TIMER1_EXTERNAL_RISI_EDGE	((1 << CS12) | (1 << CS11) | (1 << CS10))

void timer1SetPrescaler(uint8_t prescaler){
	TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
	TCCR1B |= prescaler;
}


void timer1InterruptOVFEnable(){
	TIMSK1 |= (1 << TOIE1);
}

void timer1InterruptOVFDisable(){
	TIMSK1 &= ~(1 << TOIE1);
}

void timer1SetValue(uint16_t value){
	TCNT1 = value;
}

uint16_t timer1GetValue(){
	return TCNT1;
}

void timer1NormalMode(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));
	// postaviti Normalna nacin rada
	TCCR1A |= (0 << WGM11) | (0 << WGM10);
	TCCR1B |= (0 << WGM13) | (0 << WGM12);
}


//VRH vrijednost za PWM sklopa Timer/Counter1
#define PWM_8BIT_TOP 255
#define PWM_9BIT_TOP 511
#define PWM_10BIT_TOP 1023
#define PWM_ICR1_TOP ICR1

uint16_t pwm_timer0_top;


void timer1FastPWM8bit(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));
	// postaviti Fast PWM nacin rada - 8 bita [0, 255]
	TCCR1A |= (0 << WGM11) | (1 << WGM10);
	TCCR1B |= (0 << WGM13) | (1 << WGM12);
	pwm_timer0_top = PWM_8BIT_TOP;
}

void timer1FastPWM9bit(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));
	// postaviti Fast PWM nacin rada - 9 bita [0, 511]
	TCCR1A |= (1 << WGM11) | (0 << WGM10);
	TCCR1B |= (0 << WGM13) | (1 << WGM12);
	pwm_timer0_top = PWM_9BIT_TOP;
}

void timer1FastPWM10bit(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));
	// postaviti Fast PWM nacin rada - 10 bita [0, 1023]
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	TCCR1B |= (0 << WGM13) | (1 << WGM12);
	pwm_timer0_top = PWM_10BIT_TOP;
}

void timer1FastPWMICR1(uint16_t top){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));
	// postaviti Fast PWM nacin rada -  raspon brojanja [0, ICR1]
	TCCR1A |= (1 << WGM11) | (0 << WGM10);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);
	ICR1 = top;
	pwm_timer0_top = top;
}


void timer1PhaseCorrectPWM8bit(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));
	// postaviti Phase correct PWM nacin rada - 8 bita [0, 255]
	TCCR1A |= (0 << WGM11) | (1 << WGM10);
	TCCR1B |= (0 << WGM13) | (0 << WGM12);
	pwm_timer0_top = PWM_8BIT_TOP;
}

void timer1PhaseCorrectPWM9bit(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));
	// postaviti Phase correct PWM nacin rada - 9 bita [0, 511]
	TCCR1A |= (1 << WGM11) | (0 << WGM10);
	TCCR1B |= (0 << WGM13) | (0 << WGM12);
	pwm_timer0_top = PWM_9BIT_TOP;
}

void timer1PhaseCorrectPWM10bit(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));
	// postaviti Phase correct PWM nacin rada - 10 bita [0, 1023]
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	TCCR1B |= (0 << WGM13) | (0 << WGM12);
	pwm_timer0_top = PWM_10BIT_TOP;
}


void timer1PhaseCorrectPWMICR1(uint16_t top){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));
	// postaviti Phase correct PWM nacin rada - raspon brojanja [0, ICR1]
	TCCR1A |= (1 << WGM11) | (0 << WGM10);
	TCCR1B |= (1 << WGM13) | (0 << WGM12);
	ICR1 = top;
	pwm_timer0_top = top;
}

void timer1OC1AEnableNonInvertedPWM(){
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
	TCCR1A |= (1 << COM1A1) | (0 << COM1A0);
}

void timer1OC1AEnableInvertedPWM(){
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
}

void timer1OC1ADisable(){
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
}

void timer1OC1BEnableNonInvertedPWM(){
	TCCR1A &= ~((1 << COM1B1) | (1 << COM1B0));
	TCCR1A |= (1 << COM1B1) | (0 << COM1B0);
}

void timer1OC1BEnableInvertedPWM(){
	TCCR1A &= ~((1 << COM1B1) | (1 << COM1B0));
	TCCR1A |= (1 << COM1B1) | (1 << COM1B0);
}

void timer1OC1BDisable(){
	TCCR1A &= ~((1 << COM1B1) | (1 << COM1B0));
}

void timer1OC1ADutyCycle(float D){
	OCR1A = limitDuty(D) * pwm_timer0_top / 100.0;
}

void timer1OC1BDutyCycle(float D){
	OCR1B = limitDuty(D) * pwm_timer0_top / 100.0;
}

/*********************************************************/
/*************************TIMER2**************************/

//djelitelji frekvencije za sklop Timer/Counter2
#define TIMER2_PRESCALER_OFF		((0 << CS22) | (0 << CS21) | (0 << CS20))
#define TIMER2_PRESCALER_1			((0 << CS22) | (0 << CS21) | (1 << CS20))
#define TIMER2_PRESCALER_8			((0 << CS22) | (1 << CS21) | (0 << CS20))
#define TIMER2_PRESCALER_32			((0 << CS22) | (1 << CS21) | (1 << CS20))
#define TIMER2_PRESCALER_64			((1 << CS22) | (0 << CS21) | (0 << CS20))
#define TIMER2_PRESCALER_128		((1 << CS22) | (0 << CS21) | (1 << CS20))
#define TIMER2_PRESCALER_256		((1 << CS22) | (1 << CS21) | (0 << CS20))
#define TIMER2_PRESCALER_1024		((1 << CS22) | (1 << CS21) | (1 << CS20))

void timer2InterruptOVFEnable(){
	TIMSK2 |= (1 << TOIE2);
}

void timer2InterruptOVFDisable(){
	TIMSK2 &= ~(1 << TOIE2);
}


void timer2SetPrescaler(uint8_t prescaler){
	TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
	TCCR2B |= prescaler;
}

void timer2SetValue(uint8_t value){
	TCNT2 = value;
}

uint8_t timer2GetValue(){
	return TCNT2;
}

void timer2NormalMode(){
	// ocistiti WGM2 bitove u registrima TCCR2 A i B
	TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
	TCCR2B &= ~(1 << WGM22);
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) | (1 << COM2B0));
	// postaviti Normalna nacin rada
	TCCR2A |= (0 << WGM21) | (0 << WGM20);
	TCCR2B |= (0 << WGM22);
}


void timer2FastPWM(){
	// ocistiti WGM2 bitove u registrima TCCR2 A i B
	TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
	TCCR2B &= ~(1 << WGM22);
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) | (1 << COM2B0));
	// postaviti Fast PWM nacin rada
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	TCCR2B |= (0 << WGM22);
}

void timer2PhaseCorrectPWM(){
	// ocistiti WGM2 bitove u registrima TCCR2 A i B
	TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
	TCCR2B &= ~(1 << WGM22);
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) | (1 << COM2B0));
	// postaviti Phase correct PWM nacin rada
	TCCR2A |= (0 << WGM21) | (1 << WGM20);
	TCCR2B |= (0 << WGM22);
}


void timer2OC2AEnableNonInvertedPWM(){
	TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0));
	TCCR2A |= (1 << COM2A1) | (0 << COM2A0);
}

void timer2OC2AEnableInvertedPWM(){
	TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0));
	TCCR2A |= (1 << COM2A1) | (1 << COM2A0);
}

void timer2OC2ADisable(){
	TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0));
}

void timer2OC2BEnableNonInvertedPWM(){
	TCCR2A &= ~((1 << COM2B1) | (1 << COM2B0));
	TCCR2A |= (1 << COM2B1) | (0 << COM2B0);
}

void timer2OC2BEnableInvertedPWM(){
	TCCR2A &= ~((1 << COM2B1) | (1 << COM2B0));
	TCCR2A |= (1 << COM2B1) | (1 << COM2B0);
}

void timer2OC2BDisable(){
	TCCR2A &= ~((1 << COM2B1) | (1 << COM2B0));
}


void timer2OC2ADutyCycle(float D){
	OCR2A = limitDuty(D) * 2.55;
}

void timer2OC2BDutyCycle(float D){
	OCR2B = limitDuty(D) * 2.55;
}



/*
// prekidna rutina za Timer0
ISR(TIMER0_OVF_vect){
	TCNT0 = 0;
}

// prekidna rutina za Timer1
ISR(TIMER1_OVF_vect){
	TCNT1 = 0;
}

// prekidna rutina za Timer2
ISR(TIMER2_OVF_vect){
	TCNT2 = 0;
}
*/

#endif /* TIMER_H_ */