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
 
 int main()
 {
 int i;
 LCD_INIT();
 while(1)
 {
 for(i=0;i<16;i++)
 {
 delay(500);
 LCD_CMD(0x01);
 LCD_CMD(0x80+i);
 STRING("NITHISH");
 }
 }
 }
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
char ch=0;
while(*p)
{
int i=0;
LCD_DATA(*p++);
ch++;
if(ch>15)
{
LCD_CMD(0x80+(i++));
}
}
		}