/* 
 * File:   main.c
 * Author: Jason
 *
 * Created on July 5, 2014, 4:38 PM
 */

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <plib.h>

#include "fubsd.h"
#include "RA8875.h"
#include "ft5206.h"

#include "spi2.h"
#include "ff.h"
#include "diskio.h"

#include "keyboard.h"

//* Oscillator Settings
#pragma config FNOSC    = PRIPLL                                // Oscillator selection
#pragma config POSCMOD  = HS                                    // Primary oscillator mode
#pragma config FPLLIDIV = DIV_2                                 // PLL input divider
#pragma config FPLLMUL  = MUL_20                                // PLL multiplier
#pragma config FPLLODIV = DIV_1                                 // PLL output divider
#pragma config FPBDIV   = DIV_1                                 // Peripheral bus clock divider
#pragma config FSOSCEN  = OFF                                   // Secondary oscillator enable

//* Clock control settings
#pragma config IESO     = OFF                                   // Internal/external clock switchover
#pragma config FCKSM    = CSECME                                // Clock switching (CSx)/Clock monitor (CMx)
#pragma config OSCIOFNC = OFF                                   // Clock output on OSCO pin enable

//* USB Settings
#pragma config UPLLEN   = ON                                    // USB PLL enable
#pragma config UPLLIDIV = DIV_2                                 // USB PLL input divider
#pragma config FUSBIDIO = OFF									// USB USID pin controlled by port function
#pragma config FVBUSONIO = OFF									// USB VBUSON pin controlled by port function

//* Other Peripheral Device settings
#pragma config FWDTEN   = OFF                                   // Watchdog timer enable
#pragma config WDTPS    = PS1024                                // Watchdog timer postscaler

//* Code Protection settings
#pragma config CP       = OFF                                   // Code protection
#pragma config BWP      = OFF                                   // Boot flash write protect
#pragma config PWP      = OFF                                   // Program flash write protect

//* Debug settings
#pragma config ICESEL   = ICS_PGx2                              // ICE pin selection

#define _CPU_NAME_                  "32MX795F512H"
#define VEND                        vendFubarino
#define PROD                        prodFubarinoSD_512K
#define F_CPU                       80000000UL

#define FLASH_BYTES                 0x80000                     // 512K
#define FLASH_PAGE_SIZE             4096
#define LoadFlashWaitStates()       (CHECON = 2)            // 0 for 0-30Mhz, 1 for 31-60Mhz, 2 for 61-80Mhz

#define SYS_FREQ             (80000000L)
#define PB_DIV                 8
#define PRESCALE               256
#define TOGGLES_PER_SEC        1
#define T1_TICK               (SYS_FREQ/PB_DIV/PRESCALE/TOGGLES_PER_SEC)


unsigned int fColor = color_black;
unsigned int bColor = color_white;

char usr_msg[128];

void init_board(void);

Touch OldTouch;
FATFS fs;          // Work area (file system object) for the volume
BYTE FILE_IN_BUFF[512];
DSTATUS iStat;
char messageOut[128];
FIL fil;       /* File object */
char line[82]; /* Line buffer */
volatile Keyboard AtomKB;

void main() {
    int fSize = 30;
    unsigned int tryCount = 1;
    unsigned int FFST = 0;
    unsigned int i,t;
    char keytemp;

    init_board();
    TRISEbits.TRISE5 = 0;   //USR_LED = output

    TOUCH_Init();

    LCD_Initial();
    //Backlight(RA8875_PWM_CLK_DIV8,80);

    Write_Dir(0X01,0X80);//display on

    Active_Window(0,799,0,479);//Set the working window size
    SetColors(fColor,bColor);
    ClearScreen(0);

    FontWrite_Position(0,10);
    String("  AtomSoftTech - RA8875 7\" TFT with Capacitive Touch");

    FontWrite_Position(0,30);
    String("  MCU: PIC32MX795F512H");

    FontWrite_Position(0,50);
    String("  LCD Mode: 8080 - 8bit");

    FontWrite_Position(0,90);
    String("  Insert SD Card...Waiting");

    SpiChnClose(2);
    SpiInitDevice(2,SPI_SLOWEST,0);

    while(isCD() == 1);
    FontWrite_Position(0,110);
    String("  SD Card...Found!");

    do
    {
        while(isCD() == 1);
        iStat = FR_NOT_READY;
        Delay10ms(20);
        FontWrite_Position(0,130);

        sprintf(messageOut, "  Mounting SD Card with Elm Chan's FatFS. Try #%d  \0", tryCount);
        String(messageOut);
        tryCount++;
        iStat = f_mount(&fs, "", 1);//(&fs);  //MountSD(fs);
    }
    while(iStat != FR_OK);

    if(fs.fs_type == FS_FAT12)
        FFST = 12;
    if(fs.fs_type == FS_FAT16)
        FFST = 16;
    if(fs.fs_type == FS_FAT32)
        FFST = 32;

    SpiChnClose(2);
    SpiInitDevice(2,SPI_MED1,0);

    FontWrite_Position(0,150);
    sprintf(messageOut, "  SD Card Filesystem... FAT%d  \0", FFST);
    String(messageOut);

    FontWrite_Position(0,190);
    sprintf(messageOut, "  Initiating Keyboard...  \0");
    String(messageOut);

    for(i=0;i<5;i++)
    {
        FontWrite_Position(0,210);
        sprintf(messageOut, "  Loading in ... %d\0", (5-i));
        String(messageOut);
        delay_ms(999);
    }

/*
    SetColors(fColor,bColor);//delay_ms(2);
    ClearScreen(0);delay_ms(30);
    draw_kb(SHIFT,100,260,600,color_black,color_white,color_black);
    delay_ms(2000);

    SetColors(fColor,bColor);//delay_ms(2);
    ClearScreen(0);delay_ms(30);
    draw_kb(SHIFT,100,260,600,color_black,color_red,color_white);
    delay_ms(2000);

    SetColors(fColor,bColor);//delay_ms(2);
    ClearScreen(0);delay_ms(30);
    draw_kb(SHIFT,100,260,600,color_black,color_purple,color_white);
    delay_ms(2000);
*/
    SetColors(fColor,bColor);//delay_ms(2);
    ClearScreen(0);delay_ms(30);
    AtomKB = draw_kb(NOSHIFT,100,200,600,color_black,color_blue,color_white);

    SetColors(fColor,bColor);//delay_ms(2);
    
    for(i=0;i<128;i++)
        messageOut[i] = 0x20;

    messageOut[0] = '_';
    i = 0;

    while(1)
    {
        if(CheckPen() == 0)        //The touch screen is pressed
        {
            do
            {
                ft5x0x_read_data();

                keytemp = isKey(AtomKB, ts_event.x1,ts_event.y1);
                
                if(keytemp)
                {
                    if(i == 100)
                    {
                        i = 0; //RESET CUR POS IN BUFF
                        for(t=0;t<128;t++){
                            messageOut[t] = 0x20;
                            messageOut[0] = '_';
                        }
                    }

                    

                    if(AtomKB.shift == 1)
                    {
                        if(AtomKB.caps == 0)
                        {
                            AtomKB = draw_kb(NOSHIFT,100,200,600,color_black,color_blue,color_white);
                        }
                    }
                    switch(keytemp)
                    {
                        case 0x08:  //DEL
                            if((i > 0))
                                i--;

                            messageOut[i] = 0x20;
                            messageOut[i+1] = 0x20;
                            messageOut[i] = '_';
                            break;
                        case 0x0d:  //RETURN
                            messageOut[i++] = '[';
                            messageOut[i++] = 'E';
                            messageOut[i++] = 'N';
                            messageOut[i++] = 'T';
                            messageOut[i++] = ']';
                            messageOut[i] = '_';
                            break;
                        case 0x09:  //TAB
                            messageOut[i++] = '[';
                            messageOut[i++] = 'T';
                            messageOut[i++] = 'A';
                            messageOut[i++] = 'B';
                            messageOut[i++] = ']';
                            messageOut[i] = '_';
                            break;
                        case 0x1c:
                            if(AtomKB.caps == 0){
                                AtomKB = draw_kb(CAPS,100,200,600,color_black,color_blue,color_white);
                            }else{
                                AtomKB = draw_kb(NOSHIFT,100,200,600,color_black,color_blue,color_white);
                            }
                            break;
                        case 0x1d:
                            if(AtomKB.caps == 1) break;

                            if(AtomKB.shift == 0){
                                AtomKB = draw_kb(SHIFT,100,200,600,color_black,color_blue,color_white);
                            } else {
                                AtomKB = draw_kb(NOSHIFT,100,200,600,color_black,color_blue,color_white);
                            }
                            break;
                        default:
                            messageOut[i++] = keytemp;
                            messageOut[i] = '_';
                            break;
                    }
                    SetColors(fColor,bColor);
                    FontWrite_Position(10,100);
                    String(messageOut);
                    delay_ms(160);
                }
            }while(isPEN()==0);


            ts_event.Key_Sta=Key_Up;
        }
    }
    while(1);   //TEST STOP HERE

    SetColors(fColor,bColor);
    //OpenASI("main.asi",0,0);
    delay_ms(10000);
    ClearScreen(0);
    delay_ms(200);

    while(1)
    {

        if(CheckPen() == 0)        //The touch screen is pressed
        {
            do
            {
                ft5x0x_read_data();

                SetColors(fColor,bColor);

                FontWrite_Position(0,180);
                sprintf(usr_msg, "  X1: %i    ",ts_event.x1);
                String(usr_msg);

                FontWrite_Position(0,200);
                sprintf(usr_msg, "  Y1: %i    ",ts_event.y1);
                String(usr_msg);

                FontWrite_Position(0,230);
                sprintf(usr_msg, "  X2: %i    ",ts_event.x2);
                String(usr_msg);

                FontWrite_Position(0,250);
                sprintf(usr_msg, "  Y2: %i    ",ts_event.y2);
                String(usr_msg);

                FontWrite_Position(0,280);
                sprintf(usr_msg, "  X3: %i    ",ts_event.x3);
                String(usr_msg);

                FontWrite_Position(0,300);
                sprintf(usr_msg, "  Y3: %i    ",ts_event.y3);
                String(usr_msg);

                FontWrite_Position(0,330);
                sprintf(usr_msg, "  X4: %i    ",ts_event.x4);
                String(usr_msg);

                FontWrite_Position(0,350);
                sprintf(usr_msg, "  Y4: %i    ",ts_event.y4);
                String(usr_msg);

                FontWrite_Position(0,380);
                sprintf(usr_msg, "  X5: %i    ",ts_event.x5);
                String(usr_msg);

                FontWrite_Position(0,400);
                sprintf(usr_msg, "  Y5: %i    ",ts_event.y5);
                String(usr_msg);

                switch(ts_event.touch_point)
                {
                    case 5:
                        DrawCircle(OldTouch.x5,OldTouch.y5,fSize,color_white,1);delay_us((fSize*15));
                        DrawCircle(ts_event.x5,ts_event.y5,fSize,color_purple,1);delay_us((fSize*15));
                    case 4:
                        DrawCircle(OldTouch.x4,OldTouch.y4,fSize,color_white,1);delay_us((fSize*15));
                        DrawCircle(ts_event.x4,ts_event.y4,fSize,color_cyan,1);delay_us((fSize*15));
                    case 3:
                        DrawCircle(OldTouch.x3,OldTouch.y3,fSize,color_white,1);delay_us((fSize*15));
                        DrawCircle(ts_event.x3,ts_event.y3,fSize,color_blue,1);delay_us((fSize*15));
                    case 2:
                        DrawCircle(OldTouch.x2,OldTouch.y2,fSize,color_white,1);delay_us((fSize*15));
                        DrawCircle(ts_event.x2,ts_event.y2,fSize,color_green,1);delay_us((fSize*15));
                    case 1:
                        DrawCircle(OldTouch.x1,OldTouch.y1,fSize,color_white,1);delay_us((fSize*15));
                        DrawCircle(ts_event.x1,ts_event.y1,fSize,color_red,1);delay_us((fSize*15));
                        break;
                }

                OldTouch = ts_event;
            }while(isPEN()==0);


            ts_event.Key_Sta=Key_Up;
        }
    }

}

void init_board(void)
{
    AD1CON1bits.ADON = 0;       //ADC Module OFF
    AD1PCFG = 0x00FF;           //ALL DIGITAL
    IEC1 = 0;                   //ALL Interrupt Disabled

    CM1CON = 0;			//Comparator 1 OFF
    CM2CON = 0;			//Comparator 2 OFF
    CMSTAT = 0;
    CNCON = 0;
    ODCD = ODCE = ODCF = ODCC = 0;
    PMCON = 0;
	
    OpenTimer1(T1_ON | T1_IDLE_CON | T1_PS_1_8 | T1_SOURCE_INT,  25000);  //10MHz Timer

}

void delay_us(int time)
{
    while(time--)
    {
        WriteTimer1(0);
        while(ReadTimer1() < 10);
    }
}
void delay_ms(int time)
{
    while(time--)
    {
        WriteTimer1(0);
        while(ReadTimer1() < 10000);
    }
}