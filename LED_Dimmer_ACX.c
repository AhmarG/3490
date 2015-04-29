/*
 * LED_Dimmer_ACX.c
 *
 * Created: 4/28/2015 12:11:32 PM
 *  Author: gordona
 */ 

#include "ADC.h"

void dimmer();
void setDelay();

int delay;

int main(void)
{
	serial_open(19200, SERIAL_8N1);
	ADMUX |= (1<<REFS0);
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	pinMode(53, OUTPUT);
	pinMode(13, OUTPUT);
	
	x_init();
	x_new(1, dimmer, 1);
	x_new(2, setDelay, 1);
	x_new(3, blinker, 1);
	
	while (1)
	{
		x_delay(500);
	}
}

void dimmer()
{
	while (1)
	{
		digitalWrite(13, HIGH);
		x_delay(delay);
		digitalWrite(13, LOW);
		x_delay(33 - delay);
		//x_delay(500);
	}
	
}

void setDelay()
{
	unsigned int num;
	while (1)
	{
		num = ADC_read(0, 10, true);
		delay = num >> 5;
		x_yield();
	}
	
}

void blinker()
{
	digitalWrite(10, HIGH);
	x_delay(250);
	digitalWrite(10, LOW);
	x_delay(750);
}

void doADC()
{
	
}
