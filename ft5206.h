#ifndef FT5206_H
#define	FT5206_H
#include "main.h"

void _nop_();
/* touch panel interface define */

#define PEN PORTFbits.RF0
#define isPEN()     PORTFbits.RF0


#define CONFIG_FT5X0X_MULTITOUCH    //Define the multi-touch
//Touch Status
#define Key_Down 0x01
#define Key_Up   0x00


typedef struct _Touch_ {
    unsigned int    x1;
    unsigned int    y1;
    unsigned int    x2;
    unsigned int    y2;
    unsigned int    x3;
    unsigned int    y3;
    unsigned int    x4;
    unsigned int    y4;
    unsigned int    x5;
    unsigned int    y5;
    unsigned char   touch_point;
    unsigned char   Key_Sta;
} Touch;


extern Touch ts_event;
#define FT5206_DEVICE_MODE 0x00

#define WRITE_ADD	0x70
#define READ_ADD	0x71

void  TOUCH_Init(void);
void  TOUCH_Start(void);
void  TOUCH_Stop(void);
unsigned char TOUCH_Wait_Ack(void);
void  TOUCH_Ack(void);
void  TOUCH_NAck(void);

void  TOUCH_Send_Byte(unsigned char txd);
unsigned char TOUCH_Read_Byte(unsigned char ack);
void  TOUCH_Wr_Reg(unsigned char RegIndex,unsigned char RegValue1);
void  TOUCH_RdParFrPCTPFun(unsigned char *PCTP_Par,unsigned char ValFlag);
unsigned char TOUCH_Read_Reg(unsigned char RegIndex);
void  Draw_Big_Point(unsigned int x,unsigned int y,unsigned int colour);
unsigned char ft5x0x_read_data(void);  //unsigned char ft5x0x_read_data(void);

char CheckPen(void);

#endif