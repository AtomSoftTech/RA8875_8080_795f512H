#ifndef I2C2_H
#define I2C2_H


#define SDA TRISFbits.TRISF1
#define SDA_LOW        TRISFbits.TRISF1 = 0;LATFbits.LATF1 = 0
#define SDA_HIGH       TRISFbits.TRISF1 = 1
#define isSDA          PORTFbits.RF1

#define SCL TRISEbits.TRISE0
#define SCL_LOW        TRISEbits.TRISE0 = 0;LATEbits.LATE0 = 0
#define SCL_HIGH       TRISEbits.TRISE0 = 1

#define MMA8453Q 0x38

void delay1(int time);
void delay2();
char sda_setup(void);
void I2C_Start(void);
void I2C_Stop(void);
unsigned char I2C_Wait_Ack(void);
void I2C_Ack(void);
void I2C_NAck(void);
void I2C_Send_Byte(unsigned char data);
unsigned char I2C_Read_Byte(unsigned char ack);
void I2C_Wr_Reg(unsigned char WRADD, unsigned char RegIndex,unsigned char RegValue1);
unsigned char I2C_Read_Reg(unsigned char WRADD, unsigned char RegIndex);

#endif
