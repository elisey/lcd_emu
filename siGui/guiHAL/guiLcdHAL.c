
#include "guiLcdHAL.h"
#include "guiConfig.h"

// Graphics configuration is set in file guiConfig.h
// Display buffer
uint32_t guiLcdBuffer[LCD_XSIZE * LCD_YSIZE];



void LCD_PutPixel(uint16_t x, uint16_t y, color_t color)
{
	uint32_t bufferOffset = y;
	bufferOffset *= LCD_XSIZE;
	bufferOffset += x;
    // Wrap buffer
    if (bufferOffset >= (LCD_XSIZE * LCD_YSIZE))
        bufferOffset %= (LCD_XSIZE * LCD_YSIZE);
	guiLcdBuffer[bufferOffset] = color;
}

color_t LCD_GetPixel(uint16_t x, uint16_t y)
{
	uint32_t bufferOffset = y;
	bufferOffset *= LCD_XSIZE;
	bufferOffset += x;
    // Wrap buffer
    if (bufferOffset >= (LCD_XSIZE * LCD_YSIZE))
        bufferOffset %= (LCD_XSIZE * LCD_YSIZE);
	return guiLcdBuffer[bufferOffset];
}
