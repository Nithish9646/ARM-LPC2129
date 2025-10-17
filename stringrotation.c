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

int i=0X80,j;
int main()
{

LCD_INIT();
while(1)
{
LCD_CMD(i++);
if(i==0x90)
i=0x80;

STRING("NITHISH");
LCD_CMD(0X01);
}
}

void STRING(unsigned char *p)
{
j=i;
while(*p)
{
 LCD_CMD(j++);
if(j==0x90)
j=0x80;
LCD_DATA(*p++);
}
delay(500);
}



