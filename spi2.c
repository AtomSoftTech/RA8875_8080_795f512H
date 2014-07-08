#include <xc.h>
#include <plib.h>
#include "spi2.h"
#include "RA8875.h"

void spi_delay()
{
    UINT tt;
    tt = 10;
    while(tt--)
        Nop();
}

unsigned char SpiTransfer2(unsigned char byte)
{
    unsigned char counter;

    for(counter=0; counter < 8; counter++)
    {
        if (byte & 0x80)
            MOSI_HIGH();
        else
            MOSI_LOW();

        byte <<= 1;

        SCK_HIGH(); /* a slave latches input data bit */
        //spi_delay();
        if (isMISO())
            byte |= 0x01;

        SCK_LOW(); /* a slave shifts out next output data bit */
        //spi_delay();
    }

    return(byte);
}


void SpiInitDevice(int chn, int srcClkDiv, int samp)
{
    unsigned int config = SPI_OPEN_MSTEN|SPI_OPEN_MODE8|SPI_OPEN_CKE_REV|SPI_OPEN_SMP_END;
    //unsigned int config = SPI_CON_MSTEN | SPI_CON_MODE8 | SPI_SMP_OFF | SPI_CKE_ON | CLK_POL_ACTIVE_HIGH |SPI_CON_ON;    // SPI configuration word
    //if(samp == 0)
        //config2 |= ;

    SpiChnOpen(chn, config, srcClkDiv);  
    SpiConfigPins();
    release_spi();
}

void SpiConfigPins()
{

    SYSKEY = 0x0; // Make sure SYSKEY is locked
    SYSKEY = 0xAA996655; // SYSKEY unlock sequence
    SYSKEY = 0x556699AA;

    //PPSInput(3,SDI2,RPA4); //MISO2 - P18
    //PPSOutput(2,RPA1,SDO2); //MOSI2 - P06

    SYSKEY = 0x0; // Relock SYSKEY

    TRISGbits.TRISG6 = 0; //SCK OUT
    TRISGbits.TRISG7 = 1; //MISO IN
    TRISGbits.TRISG8 = 0; //MOSI OUT
    TRISBbits.TRISB4 = 1; //CD IN
    TRISGbits.TRISG9 = 0; //CS OUT
}

unsigned char SpiTransfer(unsigned char byte)
{
    	SpiChnPutC(2,byte);
        while(SpiChnIsBusy(2) > 0);
        return SpiChnGetC(2);
}

void release_spi()
{
    CS_HIGH();
    SpiTransfer(0xff);
}

void CS_HIGH()
{
    LCD_CS = 1;
    SD_CS = 1;
}

void CS_LOW(char type)
{
    CS_HIGH();
    switch(type)
    {
        case LCD:
            LCD_CS = 0;
            break;
        case SD:
            SD_CS = 0;
            break;
    }
}