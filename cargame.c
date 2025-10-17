#include<lpc21xx.h>
#include "headercar.h"
void cgram(void);
void cgram2(void);
unsigned char a[]={0x00,0x00,0x0f,0x1f,0x1f,0x0f,0x00,0x00};
unsigned char b[]={0x00,0x00,0x00,0x0e,0x0e,0x1f,0x1f,0x0a}; 
char c=0x8f,g=0xc8,k=0xc0;
void car(void) __irq
{
EXTINT=0X01;
if(k==0xc0)
k=0x80;
else 
k=0xc0;
VICVectAddr=0;
}
 int main()
 {
 unsigned char count=0;
 PINSEL1=0X01;
 init();
 VICIntSelect=0;
 VICVectCntl0=(0x20)|14;
 VICVectAddr0=(unsigned long)car;
 EXTMODE=0X01;
 EXTPOLAR=0X00;
 VICIntEnable=1<<14;
 cmd(0x80);
 string("START THE GAME");
 delay(1500);
 cmd(0x01);
 while(1)
 {
 cgram2();
 cmd(k);
 data(1);
 
 if((k==c)||(k==g))
 {
     cmd(0x01);
     break;
	 }

 cgram();
    cmd(c--); 
    data(0);
	cmd(g--);
	data(0);
	delay(500);
	cmd(0x01);

	if(c==0x7f)
	{
	count++;
	c=0x8f;
	}
	if(g==0xBF)
	{
	count++;
	g=0xc8;
	}
 }
 cmd(0x80);
 string("GAME-OVER");
 cmd(0xc0);
 string("SCORE->");
 cmd(0xca);
 integer(count);
 }

 void cgram()
 {
 int i;
 cmd(0x40);
 for(i=0;i<8;i++)
 data(a[i]);
 }

  void cgram2()
 {
 int j;
 cmd(0x48);
 for(j=0;j<8;j++)
 data(b[j]);
 }
