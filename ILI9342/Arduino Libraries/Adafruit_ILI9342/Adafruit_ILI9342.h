/*!
* @file Adafruit_ILI9342.h
*
* This is the documentation for Adafruit's ILI9342 driver for the
* Arduino platform.
*
* This library works with the Adafruit 2.8" Touch Shield V2 (SPI)
*    http://www.adafruit.com/products/1651
* Adafruit 2.4" TFT LCD with Touchscreen Breakout w/MicroSD Socket - ILI9342
*    https://www.adafruit.com/product/2478
* 2.8" TFT LCD with Touchscreen Breakout Board w/MicroSD Socket - ILI9342
*    https://www.adafruit.com/product/1770
* 2.2" 18-bit color TFT LCD display with microSD card breakout - ILI9340
*    https://www.adafruit.com/product/1770
* TFT FeatherWing - 2.4" 320x240 Touchscreen For All Feathers
*    https://www.adafruit.com/product/3315
*
* These displays use SPI to communicate, 4 or 5 pins are required
* to interface (RST is optional).
*
* Adafruit invests time and resources providing this open source code,
* please support Adafruit and open-source hardware by purchasing
* products from Adafruit!
*
*
* This library depends on <a href="https://github.com/adafruit/Adafruit_GFX">
* Adafruit_GFX</a> being present on your system. Please make sure you have
* installed the latest version before using this library.
*
* Written by Limor "ladyada" Fried for Adafruit Industries.
*
* BSD license, all text here must be included in any redistribution.
*
*/

#ifndef _ADAFRUIT_ILI9342H_
#define _ADAFRUIT_ILI9342H_

#include "Arduino.h"
#include "Print.h"
#include <SPI.h>
#include "Adafruit_GFX.h"
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>

#define ILI9342_TFTWIDTH   320      ///< ILI9342 max TFT width
#define ILI9342_TFTHEIGHT  240      ///< ILI9342 max TFT height

#define ILI9342_NOP        0x00     ///< No-op register
#define ILI9342_SWRESET    0x01     ///< Software reset register
#define ILI9342_RDDID      0x04     ///< Read display identification information
#define ILI9342_RDDST      0x09     ///< Read Display Status

#define ILI9342_SLPIN      0x10     ///< Enter Sleep Mode
#define ILI9342_SLPOUT     0x11     ///< Sleep Out
#define ILI9342_PTLON      0x12     ///< Partial Mode ON
#define ILI9342_NORON      0x13     ///< Normal Display Mode ON

#define ILI9342_RDMODE     0x0A     ///< Read Display Power Mode
#define ILI9342_RDMADCTL   0x0B     ///< Read Display MADCTL
#define ILI9342_RDPIXFMT   0x0C     ///< Read Display Pixel Format
#define ILI9342_RDIMGFMT   0x0D     ///< Read Display Image Format
#define ILI9342_RDSELFDIAG 0x0F     ///< Read Display Self-Diagnostic Result

#define ILI9342_INVOFF     0x20     ///< Display Inversion OFF
#define ILI9342_INVON      0x21     ///< Display Inversion ON
#define ILI9342_GAMMASET   0x26     ///< Gamma Set
#define ILI9342_DISPOFF    0x28     ///< Display OFF
#define ILI9342_DISPON     0x29     ///< Display ON

#define ILI9342_CASET      0x2A     ///< Column Address Set
#define ILI9342_PASET      0x2B     ///< Page Address Set
#define ILI9342_RAMWR      0x2C     ///< Memory Write
#define ILI9342_RAMRD      0x2E     ///< Memory Read

#define ILI9342_PTLAR      0x30     ///< Partial Area
#define ILI9342_MADCTL     0x36     ///< Memory Access Control
#define ILI9342_VSCRSADD   0x37     ///< Vertical Scrolling Start Address
#define ILI9342_PIXFMT     0x3A     ///< COLMOD: Pixel Format Set

#define ILI9342_FRMCTR1    0xB1     ///< Frame Rate Control (In Normal Mode/Full Colors)
#define ILI9342_FRMCTR2    0xB2     ///< Frame Rate Control (In Idle Mode/8 colors)
#define ILI9342_FRMCTR3    0xB3     ///< Frame Rate control (In Partial Mode/Full Colors)
#define ILI9342_INVCTR     0xB4     ///< Display Inversion Control
#define ILI9342_DFUNCTR    0xB6     ///< Display Function Control

#define ILI9342_PWCTR1     0xC0     ///< Power Control 1
#define ILI9342_PWCTR2     0xC1     ///< Power Control 2
#define ILI9342_PWCTR3     0xC2     ///< Power Control 3
#define ILI9342_PWCTR4     0xC3     ///< Power Control 4
#define ILI9342_PWCTR5     0xC4     ///< Power Control 5
#define ILI9342_VMCTR1     0xC5     ///< VCOM Control 1
#define ILI9342_VMCTR2     0xB7     ///< VCOM Control 2

#define ILI9342_RDID1      0xDA     ///< Read ID 1
#define ILI9342_RDID2      0xDB     ///< Read ID 2
#define ILI9342_RDID3      0xDC     ///< Read ID 3
#define ILI9342_RDID4      0xDD     ///< Read ID 4

#define ILI9342_GMCTRP1    0xE0     ///< Positive Gamma Correction
#define ILI9342_GMCTRN1    0xE1     ///< Negative Gamma Correction
#define ILI9342_PWCTR6     0xFC

// Color definitions
#define ILI9342_BLACK       0x0000  ///<   0,   0,   0
#define ILI9342_NAVY        0x000F  ///<   0,   0, 123
#define ILI9342_DARKGREEN   0x03E0  ///<   0, 125,   0
#define ILI9342_DARKCYAN    0x03EF  ///<   0, 125, 123
#define ILI9342_MAROON      0x7800  ///< 123,   0,   0
#define ILI9342_PURPLE      0x780F  ///< 123,   0, 123
#define ILI9342_OLIVE       0x7BE0  ///< 123, 125,   0
#define ILI9342_LIGHTGREY   0xC618  ///< 198, 195, 198
#define ILI9342_DARKGREY    0x7BEF  ///< 123, 125, 123
#define ILI9342_BLUE        0x001F  ///<   0,   0, 255
#define ILI9342_GREEN       0x07E0  ///<   0, 255,   0
#define ILI9342_CYAN        0x07FF  ///<   0, 255, 255
#define ILI9342_RED         0xF800  ///< 255,   0,   0
#define ILI9342_MAGENTA     0xF81F  ///< 255,   0, 255
#define ILI9342_YELLOW      0xFFE0  ///< 255, 255,   0
#define ILI9342_WHITE       0xFFFF  ///< 255, 255, 255
#define ILI9342_ORANGE      0xFD20  ///< 255, 165,   0
#define ILI9342_GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define ILI9342_PINK        0xFC18  ///< 255, 130, 198

/**************************************************************************/
/*!
@brief Class to manage hardware interface with ILI9342 chipset (also seems to work with ILI9340)
*/
/**************************************************************************/

class Adafruit_ILI9342 : public Adafruit_SPITFT {
    public:
        Adafruit_ILI9342(int8_t _CS, int8_t _DC, int8_t _MOSI, int8_t _SCLK,
          int8_t _RST = -1, int8_t _MISO = -1);
        Adafruit_ILI9342(int8_t _CS, int8_t _DC, int8_t _RST = -1);
#if !defined(ESP8266)
        Adafruit_ILI9342(SPIClass *spiClass, int8_t dc,
          int8_t cs = -1, int8_t rst = -1);
#endif // end !ESP8266
        Adafruit_ILI9342(tftBusWidth busWidth, int8_t d0, int8_t wr, int8_t dc,
          int8_t cs = -1, int8_t rst = -1, int8_t rd = -1);

        void    begin(uint32_t freq=0);
        void    setRotation(uint8_t r);
        void    invertDisplay(bool i);
        void    invert();
        void    scrollTo(uint16_t y);

        // Transaction API not used by GFX
        void    setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

        uint8_t readcommand8(uint8_t reg, uint8_t index=0);
};

#endif // _ADAFRUIT_ILI9342H_
