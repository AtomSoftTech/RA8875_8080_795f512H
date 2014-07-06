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


uint fColor = color_black;
uint bColor = color_white;

char usr_msg[128];

void init_board(void);

Touch OldTouch;

void main() {
    int fSize = 20;

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

    while(1)
    {

        if(CheckPen() == 0)        //The touch screen is pressed
        {
            do
            {
                ft5x0x_read_data();

                SetColors(fColor,bColor);

                FontWrite_Position(0,10);
                String("  AtomSoftTech - RA8875 7\" TFT with Capacitive Touch");

                FontWrite_Position(0,30);
                String("  MCU: PIC32MX795F512H");

                FontWrite_Position(0,50);
                String("  LCD Mode: 8080 - 8bit");

                FontWrite_Position(0,100);
                sprintf(usr_msg, "  X1: %i    ",ts_event.x1);
                String(usr_msg);

                FontWrite_Position(0,120);
                sprintf(usr_msg, "  Y1: %i    ",ts_event.y1);
                String(usr_msg);

                FontWrite_Position(0,150);
                sprintf(usr_msg, "  X2: %i    ",ts_event.x2);
                String(usr_msg);

                FontWrite_Position(0,170);
                sprintf(usr_msg, "  Y2: %i    ",ts_event.y2);
                String(usr_msg);

                FontWrite_Position(0,200);
                sprintf(usr_msg, "  X3: %i    ",ts_event.x3);
                String(usr_msg);

                FontWrite_Position(0,220);
                sprintf(usr_msg, "  Y3: %i    ",ts_event.y3);
                String(usr_msg);

                FontWrite_Position(0,250);
                sprintf(usr_msg, "  X4: %i    ",ts_event.x4);
                String(usr_msg);

                FontWrite_Position(0,270);
                sprintf(usr_msg, "  Y4: %i    ",ts_event.y4);
                String(usr_msg);

                FontWrite_Position(0,300);
                sprintf(usr_msg, "  X5: %i    ",ts_event.x5);
                String(usr_msg);

                FontWrite_Position(0,320);
                sprintf(usr_msg, "  Y5: %i    ",ts_event.y5);
                String(usr_msg);

                switch(ts_event.touch_point)
                {
                    case 5:
                        DrawCircle(OldTouch.x5,OldTouch.y5,fSize,color_white,1);delay_us((fSize*10));
                        DrawCircle(ts_event.x5,ts_event.y5,fSize,color_purple,1);delay_us((fSize*10));
                    case 4:
                        DrawCircle(OldTouch.x4,OldTouch.y4,fSize,color_white,1);delay_us((fSize*10));
                        DrawCircle(ts_event.x4,ts_event.y4,fSize,color_cyan,1);delay_us((fSize*10));
                    case 3:
                        DrawCircle(OldTouch.x3,OldTouch.y3,fSize,color_white,1);delay_us((fSize*10));
                        DrawCircle(ts_event.x3,ts_event.y3,fSize,color_blue,1);delay_us((fSize*10));
                    case 2:
                        DrawCircle(OldTouch.x2,OldTouch.y2,fSize,color_white,1);delay_us((fSize*10));
                        DrawCircle(ts_event.x2,ts_event.y2,fSize,color_green,1);delay_us((fSize*10));
                    case 1:
                        DrawCircle(OldTouch.x1,OldTouch.y1,fSize,color_white,1);delay_us((fSize*10));
                        DrawCircle(ts_event.x1,ts_event.y1,fSize,color_red,1);delay_us((fSize*10));
                        break;
                }

                OldTouch = ts_event;
            }while(isPEN()==0);


            ts_event.Key_Sta=Key_Up;
        }
    }
    while(1)
    {
        USR_LED = 0;
        delay_ms(160);
        USR_LED = 1;
        delay_ms(160);
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