/* 
 * File:   spi2.h
 * Author: Jason
 *
 * Created on March 1, 2014, 12:13 PM
 */

#ifndef SPI2_H
#define	SPI2_H

#include "fubsd.h"
#include <xc.h>
#include <plib.h>

//-----------------------
// SPEEDS
//-----------------------
#define SPI_SLOWEST 200     //400KHz
#define SPI_SLOW    20      //4MHz
#define SPI_MED     10      //8MHz
#define SPI_MED1    4       //20MHz
#define SPI_MED2    3       //26MHz
#define SPI_FAST    2       //40MHz
#define SPI_FASTEST 1       //80MHz
//-----------------------
// CHIP SELECTS
//-----------------------
#define SD_CS LATGbits.LATG9
#define SD_CS_LOW()       SD_CS = 0
#define SD_CS_HIGH()      SD_CS = 1


#define RFM_CSN FUB_P12
#define RFM_CSN_LOW()       PORTClearBits(RFM_CSN)
#define RFM_CSN_HIGH()      PORTSetBits(RFM_CSN)

#define RFM_CE  FUB_P13
#define RFM_CE_LOW()       PORTClearBits(RFM_CE)
#define RFM_CE_HIGH()      PORTSetBits(RFM_CE)
//-----------------------
// DATA PINS
//-----------------------
#define MOSI LATGbits.LATG8
#define MOSI_LOW()       MOSI = 0
#define MOSI_HIGH()      MOSI = 1

#define MISO PORTGbits.RG7
#define isMISO()          PORTGbits.RG7

#define SCK  LATGbits.LATG6
#define SCK_LOW()       SCK = 0
#define SCK_HIGH()      SCK = 1

//-----------------------
// MISC
//-----------------------
#define SD_CD PORTBbits.RB4
#define isCD()          SD_CD

//-----------------------
// CS TYPES
//-----------------------
#define LCD 0
#define SD 1

//-----------------------
// EXTERNAL FUNCTIONS
//-----------------------
void CS_LOW(char type);
void CS_HIGH();
void SpiInitDevice(int chn, int srcClkDiv, int samp);
void SpiConfigPins();
unsigned char SpiTransfer(unsigned char byte);
void release_spi();
unsigned char SpiTransfer2(unsigned char byte);

#endif	/* SPI2_H */

