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
void cgram_write(void);
unsigned char cgram_lut[]={0x0e,0x1b,0x11,0x11,0x11,0x11,0x11,0x1f,
0x0e,0x1b,0x11,0x11,0x11,0x11,0x1f,0x1f,
0x0e,0x1b,0x11,0x11,0x11,0x1f,0x1f,0x1f,
0x0e,0x1b,0x11,0x11,0x1f,0x1f,0x1f,0x1f,
0x0e,0x1b,0x11,0x1f,0x1f,0x1f,0x1f,0x1f,
0x0e,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f};
 
 int main()
 {
 LCD_INIT();
 cgram_write();
 LCD_CMD(0x80);
 LCD_DATA(0);
 LCD_DATA(1);
 LCD_DATA(2);
 LCD_DATA(3);
 LCD_DATA(4);
 LCD_DATA(5);
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
while(*p)
{
LCD_DATA(*p++);
}
}
void cgram_write(void)
{
char i;
LCD_CMD(0x40);
for(i=0;i<48;i++)
LCD_DATA(cgram_lut[i]);
}
