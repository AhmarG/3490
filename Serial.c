/*
 * Serial.c
 *
 * Created: 2/7/2015 2:20:53 PM
 *  Author: Ahmar Gordon
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000

#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x01
#define SERIAL_7N1 0x02
#define SERIAL_8N1 0x03
#define SERIAL_5N2 0x08
#define SERIAL_6N2 0x09
#define SERIAL_7N2 0x0A
#define SERIAL_8N2 0x0B
#define SERIAL_5E1 0x20
#define SERIAL_6E1 0x21
#define SERIAL_7E1 0x22
#define SERIAL_8E1 0x23
#define SERIAL_5E2 0x28
#define SERIAL_6E2 0x29
#define SERIAL_7E2 0x2A
#define SERIAL_8E2 0x2B
#define SERIAL_5O1 0x30
#define SERIAL_6O1 0x31
#define SERIAL_7O1 0x32
#define SERIAL_8O1 0x33
#define SERIAL_5O2 0x38
#define SERIAL_6O2 0x39
#define SERIAL_7O2 0x3A
#define SERIAL_8O2 0x3B
#define RECEIVE_LENGTH 32

void serial_open(long speed, int config);
unsigned char serial_read();
void serial_write(unsigned char data);
void serial_print(char* str);
char * serial_gets(char * buffer, uint8_t length);

//for USART
volatile static char *pData;
volatile char transmit_ISR_is_ready = 1;
char rbuff[RECEIVE_LENGTH];
volatile static char* buffPtr;
volatile static int available = 0;


int main(void)
{
	sei(); //enable global interrupts
	serial_open(19200, SERIAL_8N1);
	//char message[] = "Hello, world!\n";
	
	while(1)
	{
		serial_print(serial_gets(rbuff, RECEIVE_LENGTH));
		_delay_ms(1000);
	}
}

 //USART Init
void serial_open(long speed, int config)
{
	switch (speed)
	{
		case 2400:
		case 4800:
		case 9600:
		case 14400:
		case 19200:
		case 28800:
		case 38400:
		case 57600:
		case 76800:
		case 115200:
		case 230400:
		case 250000:
		UBRR0 = F_CPU/(16*speed);
		UCSR0A &= ~(1<<U2X0);
		break;
		default:
			return;
	}

	//set baud rate
	UBRR0H = (UBRR0 >> 8);
	UBRR0L =  UBRR0;
	
	UCSR0B = (1 << TXEN0) | (1 << RXEN0); //enable receiver and transmitter
}

unsigned char serial_read()
{
	//Wait for data to be received
	while (!(UCSR0A & (1<<RXC0)))
	{
		;
	}
	
	//Get and return received data from buffer
	return UDR0;
}

void serial_write(unsigned char data)
{
	//Wait for empty transmit buffer
	while((!UCSR0A) & (1<<UDRE0))
	{
		;
	}
		
	//puts data into buffer then sends the data
	UDR0 = data;
}

//transmits chars via USART until end of string
void serial_print(char* str)
{
	pData = str;
	UCSR0B |= (1<<UDRIE0);
	_delay_ms(1);
	while(!transmit_ISR_is_ready)
	{
		;
	}
	transmit_ISR_is_ready=0;
}

char * serial_gets(char * buffer, uint8_t length)
{
	buffPtr = buffer;
	available = 0;
	UCSR0B |= (1<<RXCIE0);
	while((UCSR0B & (1<<RXCIE0)))
	{
		;
	}
	
	return buffer;
}

ISR(USART0_RX_vect)
{
	if (available < (RECEIVE_LENGTH-1) && (UDR0 != '\n'))
	{
		*buffPtr = UDR0;
		available++;
		buffPtr++;
	}
	else
	{
		*buffPtr = '\0';
		UCSR0B &= ~(1<<RXCIE0);
	}
}

//Interrupt handler for UDR signal
ISR(USART0_UDRE_vect)
{
	if (*(pData) == '\0')
	{
		transmit_ISR_is_ready = 1;
		UCSR0B &= ~(1<<UDRIE0);
	}
	else
	{
		transmit_ISR_is_ready = 0;
		UDR0 = *pData;
		pData++;
	}
}
