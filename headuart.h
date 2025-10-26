#include<lpc21xx.h>
#define lcd 0xff<<0
#define rs 1<<10
#define e 1<<11


void delay(int ms)
{
	int i;
	for(;ms>0;ms--)
	for(i=12000;i>0;i--);
}

void init(void);
void cmd(unsigned char);
void data(unsigned char);
void integer(unsigned int);
void string(unsigned char *);

void init(void)
{
	IODIR0|=lcd|rs|e;
	cmd(0x01);
	cmd(0x02);
	cmd(0x0c);
	cmd(0x38);
}

void cmd(unsigned char cmd)
{
	IOCLR0=lcd;
	IOSET0=cmd;
	IOCLR0=rs;
	IOSET0=e;
	delay(2);
	IOCLR0=e;
}

void data(unsigned char d)
{
	IOCLR0=lcd;
	IOSET0=d;
	IOSET0=rs;
	IOSET0=e;
	delay(2);
	IOCLR0=e;
}

void string(unsigned char *p)
{
	while(*p)
	{
		data(*p++);
	}
}

void integer(unsigned int n)
{
	unsigned char arr[100];
	signed char i=0;
	if(n==0)
		data('0');
	else
	{
		if(n<0)
		{
			data('-');
			n=-n;
		}
		while(n>0)
		{
			arr[i++]=n%10;
			n=n/10;
		}
		for(i=i-1;i>=0;i--)
		data(arr[i]+48);
	}
}


