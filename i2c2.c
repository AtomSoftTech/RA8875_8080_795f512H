#include "fubsd.h"
#include <xc.h>
#include <plib.h>
#include "i2c2.h"

void delay1(int time)
{
    unsigned int j;
    while(time--)
        for(j=0;j<48;j++);
}
void delay2()
{
    unsigned char j;
    for(j=0;j<4;j++);
}
char sda_setup(void)
{
    SDA_HIGH;
    delay1(5);
    return isSDA;
}
//IIC start
void I2C_Start(void)
{
	SDA_HIGH;
	delay2();
	SCL_HIGH;
	delay1(5);
	SDA_LOW;
	delay1(5);
	SCL_LOW;
	delay2();
}
//IIC stop
void I2C_Stop(void)
{
	SDA_LOW;
	delay2();
	SCL_HIGH;
	delay1(5);
	SDA_HIGH;
	delay1(5);
	SCL_LOW;
	delay2();
}
//Wait for an answer signal
unsigned char I2C_Wait_Ack(void)
{	unsigned char errtime=0;

	SDA_HIGH;
	delay1(1);
	SCL_HIGH;
	delay1(1);
  	while(isSDA == 1)
	{
	    errtime++;
	    if(errtime>250)
            {
              I2C_Stop();
              return 1;
            }
	}
	SCL_LOW;
	delay2();
}
//Acknowledge
void I2C_Ack(void)
{	SCL_LOW;
	SDA_LOW;
	delay1(2);
	SCL_HIGH;
	delay1(2);
	SCL_LOW;
	delay2();
}
//NO Acknowledge
void I2C_NAck(void)
{	SCL_LOW;
	SDA_HIGH;
	delay1(2);
	SCL_HIGH;
	delay1(2);
	SCL_LOW;
	delay2();
}
void I2C_Send_Byte(unsigned char data)
{	unsigned char t;

    for(t=0;t<8;t++)
    {
        SCL_LOW;

        if((data & 0x80) > 0)
            SDA_HIGH;
        else
            SDA_LOW;

        data <<=1;
        delay1(2);
        SCL_HIGH;
        delay1(2);
        SCL_LOW;
        delay1(2);
    }


}
unsigned char I2C_Read_Byte(unsigned char ack)
{
    unsigned char t,receive=0;

    SCL_LOW;
    SDA_HIGH;
    for(t = 0; t < 8; t++)
    {
        delay2();
        SCL_HIGH;
        delay2();

        receive <<= 1;

        if(isSDA == 1)
            receive |= 0x01;

        delay1(2);
        SCL_LOW;
        delay1(2);
    }


    if (ack)  I2C_NAck();//NO Acknowledge
    else       I2C_Ack(); //Send Acknowledge

     return receive;
}
void I2C_Wr_Reg(unsigned char WRADD, unsigned char RegIndex,unsigned char RegValue1)
{
    I2C_Start();
    I2C_Send_Byte(WRADD);
    I2C_Wait_Ack();
    I2C_Send_Byte(RegIndex);
    I2C_Wait_Ack();

    I2C_Send_Byte(RegValue1);
    I2C_Wait_Ack();

    I2C_Stop();
    delay1(100);
}
unsigned char I2C_Read_Reg(unsigned char WRADD, unsigned char RegIndex)
{
    unsigned char receive=0;

    I2C_Start();
    I2C_Send_Byte(WRADD);
    I2C_Wait_Ack();
    I2C_Send_Byte(RegIndex);
    I2C_Wait_Ack();

    I2C_Start();
    I2C_Send_Byte((WRADD|1));
    I2C_Wait_Ack();
    receive=I2C_Read_Byte(1);
    I2C_Stop();

    return receive;
}

