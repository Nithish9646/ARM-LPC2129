 #include<LPC21xx.h>
 void delay(int ms)
 {
 int i;
 for(;ms>0;ms--)
 for(i=12000;i>0;i--);
 }
 int main()
 {
 int count=0;
 IODIR0=1<<0|1<<1|1<<2;
 IOSET0=1<<0|1<<1|1<<2;
 while(1)
 {
    if((IOPIN0 & 1<<14)==0)
	{
	    count++;
	  if(count==1)
	  {
	  IOCLR0=1<<0;
	   delay(500);
	  IOSET0=1<<0;
	  delay(500);
	  }
	  else if(count==2)
	  {
	  IOCLR0=1<<1;
	  delay(500);
	  IOSET0=1<<1;
	  delay(500);
	  }
	  else if(count==3)
	  {
	  IOCLR0=1<<2;
	  delay(500);
	  IOSET0=1<<2;
	  delay(500);
	  }
	 else if(count==4)
	 count=0;
   else
	 IOSET0=1<<0|1<<1|1<<2;
  }
  }
}