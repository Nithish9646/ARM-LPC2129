#include<LPC21xx.h>

#define LCD_D 0xff<<0

#define RS 1<<8

#define E 1<<9

void delay(int ms)

{

int i;

for(;ms>0;ms--)

for(i=12000;i>0;i--);

}

void LCD_INIT(void);

void LCD_CMD(unsigned char);

void LCD_DATA(unsigned char);

void STRING(unsigned char *);

void INTEGER(int);


 void LCD_INIT(void)

 {

 IODIR0=LCD_D|RS|E;

 LCD_CMD(0x01);

 LCD_CMD(0x02);

 LCD_CMD(0x0c);

 LCD_CMD(0x38);

	}

void LCD_CMD(unsigned char cmd)

{

IOCLR0=LCD_D;

IOSET0=cmd;

IOCLR0=RS;

IOSET0=E;

delay(2);

IOCLR0=E;

}

void LCD_DATA(unsigned char d)

{

IOCLR0=LCD_D;

IOSET0=d;

IOSET0=RS;

IOSET0=E;

delay(2);

IOCLR0=E;

}

void STRING(unsigned char *p)

{

while(*p)

{

LCD_DATA(*p++);

}

}

void INTEGER(int n)

{

unsigned char arr[100];

signed char i=0;

if(n==0)

LCD_DATA('0');

else

{

if(n<0)

{

LCD_CMD('-');

n=-n;

}

while(n>0)

{

arr[i++]=n%10;

n=n/10;

 }

 for(i=i-1;i>=0;i--)

 LCD_DATA(arr[i]+48);

}

}

