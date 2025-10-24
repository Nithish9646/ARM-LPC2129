#include<lpc21xx.h>
#include "headuart.h"
void uart1(void);
void tx(unsigned char);
unsigned char rx(void);
void string1(unsigned char *);
char n;
int main()
{
	IODIR0|=1<<20;
	IOSET0=1<<20;
	uart1();
	init();	
	
	while(1)
	{
	n=rx();
		tx(n);
		if(n==49)
		{
			IOCLR0=1<<20;
			cmd(0x80);
			string("LED 1 ON");
			
		}
		else if(n==50)
		{
			IOSET0=1<<20;
			cmd(0x80);
			string("LED 1 OFF");
		}
		else if((n!=49)&&(n!=50))
		{
			cmd(0x80);
			string("VALID DATA");
			cmd(0xc0);
			string("1 OR 2");
		}
	}
}

void uart1(void)
{
	PINSEL0=5<<16;
	U1LCR=0X83;
	U1DLL=97;
	U1DLM=0;
	U1LCR=0X03;
}

void tx(unsigned char n)
{
	while(((U1LSR>>5)&1)==0);
	U1THR=n;
}

unsigned char rx(void)
{
	while((U1LSR&0X01)==0);
	return U1RBR;
}

void string1(unsigned char *p)
{
	while(*p)
		tx(*p++);
}
