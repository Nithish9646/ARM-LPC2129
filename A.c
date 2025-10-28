#include<lpc21xx.h>
#include "i2c-drives.h"
#define gled 1<<16
#define rled 1<<17
int main()
{ 
 u8 ch;
 IODIR0|=gled|rled;
 IOSET0|=gled|rled;
 I2C_INIT();
	i2c_eeprom_write(0x50,0x00,'A');
	ch=i2c_eeprom_read(0x50,0x00);
	delay_ms(100);
	if(ch=='A')
	{
	IOCLR0|=gled;
	}
	else
	{
	 IOCLR0|=rled;
	}
}
