#include<lpc21xx.h>
#include "header.h"
void uart(void);
void tx(unsigned char);
unsigned char rx(void);
void string(unsigned char *);
void gsm_msg(unsigned char *);
char ch;
char a[100];
int i=0;
int main()
{
uart();
LCD_INIT();
string("AT\r\n");
delay(1000);
while(1)
	{
	ch=rx();
	if(ch=='\r')
	break;
	a[i++]=ch;
	tx(ch);	
	}
	LCD_CMD(0X80);
	STRING((unsigned char *)a);
	gsm_msg((unsigned char *)a);
}

void uart(void)
{
PINSEL0=5<<16;
U1LCR=0X83;
U1DLL=97;
U1DLM=0;
U1LCR=0X03;
}

void tx(unsigned char ch)
{
while(((U1LSR>>5)&1)==0);
U1THR=ch;
}

unsigned char rx(void)
{
while((U1LSR&0X01)==0);
return U1RBR;
}
void string(unsigned char *p)
{
while(*p)
tx(*p++);

}
void gsm_msg(unsigned char *sms)
{
string("AT");
delay(500);
string("AT+CMGF=1\r\n");
delay(500);
string("AT+CMGS=\"+918667276946\"\r\n");
delay(1000);
string(sms);
delay(500);
string("\r\n");
delay(500);
string((unsigned char *)0x1A);
delay(2000);
}
