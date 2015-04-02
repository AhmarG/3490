/*
 * Digital.h
 *
 * Created: 3/31/2015 5:51:42 PM
 *  Author: admin
 */ 


#ifndef DIGITAL_H_
#define DIGITAL_H_

#define HIGH 0x1
#define LOW 0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

int8_t pinMode(uint8_t pin, uint8_t mode);
int8_t digitalRead(uint8_t pin);
int8_t digitalWrite(uint8_t pin, uint8_t value);
void delay(int time);

typedef struct
{
	volatile uint8_t * port;
	uint8_t bitpos;
} pinMap;

pinMap pins[] = {
	{&PORTE, 0}, // pin 0
	{&PORTE, 1}, // pin 1
	{&PORTE, 4}, // pin 2
	{&PORTE, 5}, // pin 3
	{&PORTE, 3}, // pin 4
	{&PORTE, 3}, // pin 5
	{&PORTH, 3}, // pin 6
	{&PORTH, 4}, // pin 7
	{&PORTH, 5}, // pin 8
	{&PORTH, 6}, // pin 9
	{&PORTB, 4}, // pin 10
	{&PORTB, 5}, // pin 11
	{&PORTB, 8}, // pin 12
	{&PORTB, 7}, // pin 13
	{&PORTJ, 1}, // pin 14
	{&PORTJ, 0}, // pin 15
	{&PORTH, 1}, // pin 16
	{&PORTH, 0}, // pin 17
	{&PORTD, 3}, // pin 18
	{&PORTD, 2}, // pin 19
	{&PORTD, 1}, // pin 20
	{&PORTD, 0}, // pin 21
	{&PORTA, 0}, // pin 22
	{&PORTA, 1}, // pin 23
	{&PORTA, 2}, // pin 24
	{&PORTA, 3}, // pin 25
	{&PORTA, 4}, // pin 26
	{&PORTA, 5}, // pin 27
	{&PORTA, 6}, // pin 28
	{&PORTA, 7}, // pin 29
	{&PORTC, 7}, // pin 30
	{&PORTC, 6}, // pin 31
	{&PORTC, 5}, // pin 32
	{&PORTC, 4}, // pin 33
	{&PORTC, 3}, // pin 34
	{&PORTC, 2}, // pin 35
	{&PORTC, 1}, // pin 36
	{&PORTC, 0}, // pin 37
	{&PORTD, 7}, // pin 38
	{&PORTG, 2}, // pin 39
	{&PORTG, 1}, // pin 40
	{&PORTG, 0}, // pin 41
	{&PORTL, 7}, // pin 42
	{&PORTL, 6}, // pin 43
	{&PORTL, 5}, // pin 44
	{&PORTL, 5}, // pin 45
	{&PORTL, 4}, // pin 44
	{&PORTL, 3}, // pin 46
	{&PORTL, 2}, // pin 47
	{&PORTL, 1}, // pin 48
	{&PORTL, 0}, // pin 49
	{&PORTB, 3}, // pin 50
	{&PORTB, 2}, // pin 51
	{&PORTB, 1}, // pin 52
	{&PORTB, 0} // pin 53
};

#endif /* DIGITAL_H_ */
