/*
 * TimerTest.c
 *
 * Created: 3/31/2015 5:02:22 PM
 *  Author: admin
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Digital.h"



int main(void)
{
	sei();
	pinMode(13, OUTPUT);
	TCCR1B |= (1 << CS12);
	TIMSK1 |= (1 << OCIE1A);
	OCR1A = 3125;
	
	//timerCTC();
	//timerPWM();
    while(1)
    {
        
    }
}

ISR(TIMER1_COMPA_vect)
{
	if(digitalRead(13))
	{
		OCR1A += 3125;
		digitalWrite(13, LOW);
	}
	else
	{
		OCR1A += 9375;
		digitalWrite(13, HIGH);
	}
}

ISR(TIMER1_CAPT_vect)
{
	digitalWrite(13, HIGH);
}


void timerCTC()
{
	ICR1 = 12500;
	TIMSK1 |= (1<<ICIE1);
	TCCR1B |= (1<<WGM12);
	TCCR1B |= (1<<WGM13);
}

void timerPWM()
{
	TCCR1B |= (1<<WGM13);
	OCR1C = 1563;
	ICR1 = 6250;
	TCCR1A = (1<<COM1C1);
}

int8_t pinMode(uint8_t pin, uint8_t mode)
{
	if (pin > 53 || mode > INPUT_PULLUP ||
	pin < 0 || mode < INPUT)
	{
		return -1;
	}
	
	if (mode == INPUT)
	{
		//DDRD &= ~(1<<pin);
		//PORTD &= ~(1<<pin);
		*(pins[pin].port-1) &= ~(1<<pins[pin].bitpos);//DDR
		*(pins[pin].port-2) &= ~(1<<pins[pin].bitpos);//Pin
	}
	else if(mode == OUTPUT)
	{
		//DDRD |= (1<<pin);
		*(pins[pin].port-1) |= ~(1<<pins[pin].bitpos);//DDR
	}
	else//INPUT PULLUP
	{
		//DDRD &= ~(1<<pin);
		//PORTD |= (1<<pin);
		*(pins[pin].port-1) &= ~(1<<pins[pin].bitpos);//DDR
		*(pins[pin].port) |= ~(1<<pins[pin].bitpos);//PORT
	}
	return 0;
}

int8_t digitalRead(uint8_t pin)
{
	if (pin > 53 || pin < 0)
	{
		return -1;
	}
	
	return ((*(pins[pin].port-2) ^ (1<<pins[pin].bitpos)) ? 1 : 0);
}

int8_t digitalWrite(uint8_t pin, uint8_t value)
{
	if (pin > 53 || pin < 0 ||
	value < 0 || value > 1)
	{
		return -1;
	}
	
	if (value == HIGH)
	{
		//PORTD |= (1<<pin);
		*(pins[pin].port) |= ~(1<<pins[pin].bitpos);//PORT
	}
	else
	{
		//PORTD &= ~(1<<pin);
		*(pins[pin].port) &= ~(1<<pins[pin].bitpos);//PORT
	}
	return 0;
}
