#include<lpc21xx.h>
#include "header.h"
void cgram(void);
unsigned char a[]={0x00,0x0E,0x1F,0x1F,0x1F,0x1F,0x0E,0x00};

int main()
{
int i,j;
LCD_INIT();
cgram();
while(1)
{
for(i=0;i<16;i++)
{
   LCD_CMD(0XC0+i);
   LCD_DATA(0);
   delay(1000);
   ++i;
   LCD_CMD(0X01);
   LCD_CMD(0X80+i);
   LCD_DATA(0);
   delay(1000);
   LCD_CMD(0X01);

}
}
}

void cgram(void)
{
char i,j;
{
LCD_CMD(0X40);
for(i=0;i<8;i++)
LCD_DATA(a[i]);
}
}
