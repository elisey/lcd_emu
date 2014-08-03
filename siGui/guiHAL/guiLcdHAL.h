#ifndef __GUI_LCD_HAL_
#define __GUI_LCD_HAL_

#include <stdint.h>

typedef uint32_t color_t;

#define colorFromRgb(red, green, blue) ((uint32_t)red | ((uint32_t)green << 8) | ((uint32_t)blue << 16))
#define CL_WHITE colorFromRgb(255,255,255)
#define CL_BLACK colorFromRgb(0,0,0)
#define CL_RED colorFromRgb(255,0,0)
#define CL_GREEN colorFromRgb(0,255,0)
#define CL_BLUE colorFromRgb(0,0,255)
#define CL_YELLOW colorFromRgb(255,255,0)
#define CL_LIGHT_GREY colorFromRgb(200,200,200)

extern color_t guiLcdBuffer[];

void LCD_PutPixel(uint16_t x, uint16_t y, color_t color);
color_t LCD_GetPixel(uint16_t x, uint16_t y);

#endif
