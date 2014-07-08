#ifndef _ra8875_h
#define _ra8875_h

#define LCD_PORT PORTD
#define LCD_LAT  LATD
#define LCD_TRIS TRISD

#define RESET LATCbits.LATC13
#define RESET_TRIS TRISCbits.TRISC13
#define RESET_LOW()        RESET = 0
#define RESET_HIGH()       RESET = 1

#define C86 LATCbits.LATC14
#define C86_TRIS TRISCbits.TRISC14
#define C86_LOW()        C86 = 0
#define C86_HIGH()       C86 = 1

#define RD LATDbits.LATD8
#define RD_TRIS TRISDbits.TRISD8
#define RD_LOW()        RD = 0
#define RD_HIGH()       RD = 1

#define RS LATDbits.LATD11
#define RS_TRIS TRISDbits.TRISD11
#define RS_LOW()        RS = 0
#define RS_HIGH()       RS = 1

#define WR LATDbits.LATD9
#define WR_TRIS TRISDbits.TRISD9
#define WR_LOW()        WR = 0
#define WR_HIGH()       WR = 1

#define LCD_CS LATDbits.LATD10
#define LCD_CS_TRIS TRISDbits.TRISD10
#define LCD_CS_LOW()        LCD_CS = 0
#define LCD_CS_HIGH()       LCD_CS = 1

//typedef unsigned int uint;

typedef unsigned char uchar;
typedef unsigned long ulong;


#define RA8875_DCR                    0x90
#define RA8875_DCR_LINESQUTRI_START   0x80
#define RA8875_DCR_LINESQUTRI_STOP    0x00
#define RA8875_DCR_LINESQUTRI_STATUS  0x80
#define RA8875_DCR_CIRCLE_START       0x40
#define RA8875_DCR_CIRCLE_STATUS      0x40
#define RA8875_DCR_CIRCLE_STOP        0x00
#define RA8875_DCR_FILL               0x20
#define RA8875_DCR_NOFILL             0x00
#define RA8875_DCR_DRAWLINE           0x00
#define RA8875_DCR_DRAWTRIANGLE       0x01
#define RA8875_DCR_DRAWSQUARE         0x10

#define RA8875_P1CR             0x8A
#define RA8875_P1CR_ENABLE      0x80
#define RA8875_P1CR_DISABLE     0x00
#define RA8875_P1CR_CLKOUT      0x10
#define RA8875_P1CR_PWMOUT      0x00

#define RA8875_P1DCR            0x8B

#define RA8875_P2CR             0x8C
#define RA8875_P2CR_ENABLE      0x80
#define RA8875_P2CR_DISABLE     0x00
#define RA8875_P2CR_CLKOUT      0x10
#define RA8875_P2CR_PWMOUT      0x00

#define RA8875_P2DCR            0x8D

#define RA8875_PWM_CLK_DIV1     0x00
#define RA8875_PWM_CLK_DIV2     0x01
#define RA8875_PWM_CLK_DIV4     0x02
#define RA8875_PWM_CLK_DIV8     0x03
#define RA8875_PWM_CLK_DIV16    0x04
#define RA8875_PWM_CLK_DIV32    0x05
#define RA8875_PWM_CLK_DIV64    0x06
#define RA8875_PWM_CLK_DIV128   0x07
#define RA8875_PWM_CLK_DIV256   0x08
#define RA8875_PWM_CLK_DIV512   0x09
#define RA8875_PWM_CLK_DIV1024  0x0A
#define RA8875_PWM_CLK_DIV2048  0x0B
#define RA8875_PWM_CLK_DIV4096  0x0C
#define RA8875_PWM_CLK_DIV8192  0x0D
#define RA8875_PWM_CLK_DIV16384 0x0E
#define RA8875_PWM_CLK_DIV32768 0x0F

#define color_brown   0x40c0
#define color_black   0x0000
#define color_white   0xffff
#define color_red     0xf800
#define color_green   0x07e0
#define color_blue    0x001f
#define color_yellow  color_red|color_green
#define color_cyan    color_green|color_blue
#define color_purple  color_red|color_blue


void Delay1ms(unsigned int i);
void Delay10ms(unsigned int i);
void Delay100ms(unsigned int i);
void NextStep(void);

void LCD_CmdWrite(unsigned char cmd);
void LCD_DataWrite(unsigned char Data);
unsigned char LCD_DataRead(void);

void Write_Dir(unsigned char Cmd,unsigned char Data);
unsigned char LCD_StatusRead(void);

void LCD_Reset(void);
void Chk_Busy(void);
void Chk_BTE_Busy(void);
void Chk_DMA_Busy(void);
void PLL_ini(void);
void Active_Window(unsigned int XL,unsigned int XR ,unsigned int YT ,unsigned int YB);
void LCD_Initial(void);
void Text_Background_Color1(unsigned int b_color);
void Text_Background_Color(unsigned char setR, uchar setG, uchar setB);
void Text_Foreground_Color1(unsigned int b_color);
void Text_Foreground_Color(unsigned char setR,uchar setG,uchar setB);
void BTE_Size(unsigned int width, unsigned int height);
void BTE_Source(unsigned int SX,unsigned int DX ,unsigned int SY ,unsigned int DY);
void MemoryWrite_Position(unsigned int X,unsigned int Y);
void FontWrite_Position(unsigned int X,unsigned int Y);
void String(unsigned char *str);
void Scroll_Window(unsigned int XL,unsigned int XR ,unsigned int YT ,unsigned int YB);
void Scroll(unsigned int X,unsigned int Y);
void DMA_block_mode_size_setting(unsigned int BWR,unsigned int BHR,unsigned int SPWR);
void DMA_Start_address_setting(ulong set_address);
void  Draw_Circle(unsigned int X,unsigned int Y,unsigned int R);
void  Draw_Ellipse(unsigned int X,unsigned int Y,unsigned int R1,unsigned int R2);
void Draw_Line(unsigned int XS,unsigned int XE ,unsigned int YS,unsigned int YE);
void Draw_Triangle(unsigned int X3,unsigned int Y3);
char Touch_Status(void);
char Chk_INT(void);
char Chk_INT2(void);
unsigned char ADC_X(void);
unsigned char ADC_Y(void);
unsigned char ADC_XY(void);
void TP(void);
void Displaypicture(unsigned char picnum);
void CutPictrue(unsigned char picnum,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned long x,unsigned long y);
void Test(void);

void MakeCircle(unsigned int x0, unsigned int y0, unsigned int r, unsigned int color, char filled);
char waitPoll(uchar regname, uchar waitflag);
void fillRect(void);
void drawRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color, char filled);
void drawLine(unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1, unsigned int color);

#define FILL 1
#define NOFILL 0

typedef struct _Button_ {
    unsigned int top;
    unsigned int left;
    unsigned int width;
    unsigned int height;
} Button;


typedef struct _Fader_ {
    unsigned int    bar_value;
    unsigned int    bar_max;

    unsigned int    sel_width;
    unsigned int    sel_height;
    unsigned int    sel_color;

    unsigned int    bar_x;
    unsigned int    bar_y;
    unsigned int    bar_width;
    unsigned int    bar_height;
    unsigned int    bar_color;
    
} Fader;

typedef struct _TouchButton_ {
    unsigned int top;
    unsigned int left;
    unsigned int width;
    unsigned int height;
    unsigned int fore_color;
    unsigned int back_color;
    char text[13];
} TouchButton;

typedef struct _ImageButton_ {
    unsigned int top;
    unsigned int left;
    unsigned int width;
    unsigned int height;
    char up[13];
    char down[13];
} ImageButton;

//BELOW ARE ATOMSOFT TECH MODS
void PWM2config(char on, uchar clock);
void PWM1config(char on, uchar clock);
void PWM2out(uchar p);
void PWM1out(uchar p);

void ClearScreen(char area);
void Display(char val);
void Layers(char val);
void FontSize (char size);
void SetColors(unsigned int f_color, unsigned int b_color);
void GraphicCursor(unsigned int x, unsigned int y, uchar color1, uchar color2);
void Backlight(uchar div, uchar pwm);
void DrawLine (unsigned int xs,unsigned int ys,unsigned int xe,unsigned int ye, unsigned int color);
void DrawSquare ( unsigned int x,unsigned int y,unsigned int w,unsigned int h, unsigned int color, char fill);
void DrawCircle(unsigned int x0, unsigned int y0, unsigned int r, unsigned int color, char filled);
void LCD_ReadBuff(char *buff, unsigned int len);
void SetGraphicsCursorRead(unsigned int x, unsigned int y);
void SetGraphicsCursorWrite(unsigned int x, unsigned int y);
void WriteCommandW(uchar command, unsigned int data);
void WriteCommand(unsigned char command, unsigned int data);
void putPixelStream(uchar * p, unsigned int count, unsigned int x, unsigned int y);
void OpenASI (char *filename, unsigned int x, unsigned int y);
void ReplaceASI (char *filename, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
char isImageButton (ImageButton btn);
void BtnClick(Button btn);
void DrawFinger(unsigned int x,unsigned int y,unsigned int colour);
#endif