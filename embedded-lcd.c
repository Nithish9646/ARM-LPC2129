#include<lpc21xx.h>
#include "headuart.h"
void uart1(void);
void tx(unsigned char);
unsigned char rx(void);
unsigned char n;
int i=0;
unsigned char a[20];
int main()
{
	uart1();
	init();
	while(1)
	{
		n=rx();
		if(n=='\r')
			break;
		a[i++]=n;
		tx(n^32);
	}
	//a[i]='\0';
	cmd(0x80);
	string(a);
//	tx();
	
}
void uart1(void)
{
	PINSEL0=5<<16;
	U1LCR=0X83;
	U1DLL=97;
	U1DLM=0;
	U1LCR=0X03;
}
unsigned char rx(void)
{
	while((U1LSR&0X1)==0);
	return U1RBR;
} 
void tx(unsigned char n)
{
	while(((U1LSR>>5)&1)==0);
		U1THR=n;
}
