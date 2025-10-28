#include<lpc21xx.h>
// BIT NUM OF SET&CLR
#define AA 2
#define SI 3
#define STO 4
#define STA 5
#define I2CEN 6

// BITS NUM OF SCL&SDA
#define SCL 0X0000010
#define SDA 0X0000040

// CLOCK VALUE
#define CCLK 60000000

// PCLK VALUE
#define PCLK (CCLK/4)

// I2C_SPEED
#define I2C_SPEED 100000

// I2C_LOAD-VALUE
#define LOAD_VAL  ((PCLK/I2C_SPEED)/2)

#define SA slave_address
#define DA data_address
#define A data

typedef unsigned char u8;

void I2C_INIT(void);
void delay_ms(int ms);
void i2c_eeprom_write(u8,u8,u8);
u8 i2c_eeprom_read(u8,u8);
u8 I2C_NACK(void);
void I2C_STOP(void);
void I2C_START(void);
void I2C_RESET(void);
void I2C_WRITE(u8);

void i2c_eeprom_write(u8 SA,u8 DA,u8 A)
{
	I2C_START();
	I2C_WRITE(SA<<1);
	I2C_WRITE(DA);
	I2C_WRITE(A);
	I2C_STOP();
	delay_ms(10);
}

u8 i2c_eeprom_read(u8 SA,u8 DA)
{
     u8 data;
	I2C_START();
	I2C_WRITE(SA<<1);
	I2C_WRITE(DA);
	I2C_RESET();
    I2C_WRITE(SA<<1|1);
	data=I2C_NACK();
	I2C_STOP();
	return data;
	
}

void I2C_INIT(void)
{
	PINSEL0=SCL|SDA;
	I2SCLL=LOAD_VAL;
	I2SCLH=LOAD_VAL;
	I2CONSET=I2CEN;		
}

void I2C_START(void)
{
	I2CONSET=1<<STA;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR=1<<STA;
}

void I2C_RESET(void)
{
	I2CONSET=1<<STA;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR=1<<STA;
}

void I2C_STOP(void)
{
	I2CONSET=1<<STO;
	I2CONCLR=1<<SI;	 	
}

void I2C_WRITE(u8 data)
{
	I2DAT=data;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);
}

u8 I2C_NACK(void)
{
	I2CONSET=0X00;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);
	return I2DAT;
}

void delay_ms(int ms)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<<ms);
	T0TCR=0X03;
	T0TCR=0X0;
}
