#include<lpc21xx.h>
#include "headerfile.h"
 int a;
void ext_eint0 (void)  __irq
{
EXTINT =0X01;
T0PR=6-1;
T0TCR=0X01;
a=T0PC;
if(a==0)
a=6;
VICVectAddr=0;
}

int main()
{
unsigned int count=0;
PINSEL1=0X01;
LCD_INIT();
VICIntSelect=0;
VICVectCntl0=(0x20)|14;
VICVectAddr0=(unsigned long)ext_eint0;

EXTMODE=0X01;
EXTPOLAR=0X00;

VICIntEnable=1<<14;
while(1)
{ 
 LCD_CMD(0X80);
STRING("DICE-ROLL");
LCD_DATA(':');

LCD_CMD(0XC0);
INTEGER(a);



LCD_CMD(0X8B);
STRING("COUNT:");
LCD_CMD(0XCC);
INTEGER(count);
 if((IOPIN0&1<<16)==0)
 {
 delay(250);
 count++;
 }
 }

 }


