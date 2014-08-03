#ifndef GUI_GRAPH_PRIMITIVES_H_
#define GUI_GRAPH_PRIMITIVES_H_
#include "guiLcdHAL.h"
#include "stdint.h"
#include "guiFonts.h"
#include "guiImages.h"
typedef struct {
    int16_t x1;
    int16_t y1;
    int16_t x2;
    int16_t y2;
} rect_t;



typedef struct {
    int16_t x;
    int16_t y;
} point_t;

typedef enum    {
    line_style_solid    = 0x10,
    line_stayle_dashed  = 0x20,
    line_stali_doted    = 0x30
} line_style_t;

// Dashed and dotted line style settings
// Counter increments from 0 to guiGraph_xxx_PERIOD-1
// if counter < LCD_xxx_COMPARE, pixel is put unchaged
// if counter >= LCD_xxx_COMPARE, pixel is put inversed
#define LCD_DOT_PERIOD      4
#define LCD_DOT_COMPARE     2
#define LCD_DASH_PERIOD     7
#define LCD_DASH_COMPARE    5


typedef enum    {
    image_paint_set_pixels  = 0x01,
    image_paint_void_pixels = 0x02
} image_paint_pixels_t;


// Align modes - required alignment mode is selected by
// combining these flags
#define ALIGN_CENTER    0x00
#define ALIGN_LEFT      0x01
#define ALIGN_RIGHT     0x02
#define ALIGN_TOP       0x04
#define ALIGN_BOTTOM    0x08
// Aliases
#define ALIGN_TOP_LEFT      (ALIGN_TOP | ALIGN_LEFT)
#define ALIGN_BOTTOM_LEFT   (ALIGN_BOTTOM | ALIGN_LEFT)
#define ALIGN_TOP_RIGHT     (ALIGN_TOP | ALIGN_RIGHT)
#define ALIGN_BOTTOM_RIGHT   (ALIGN_BOTTOM | ALIGN_RIGHT)




void guiGraph_SetPenColor(const color_t newColor);
void guiGraph_SetAltPenColor(const color_t newColor);
void guiGraph_SetFillColor(const color_t newColor);
void guiGraph_SetLineStyle(line_style_t newStyle);

void guiGraph_DrawRect(rect_t *rect);
void guiGraph_DrawFillRect(rect_t *rect);
void guiGraph_DrawCircle(int16_t x0, int16_t y0, int16_t radius);
void guiGraph_DrawFillCircle(int16_t x0, int16_t y0, int16_t radius);

void guiGraph_DrawHLine(uint16_t x, uint16_t y, uint16_t length);
void guiGraph_DrawVtLine(uint16_t x, uint16_t y, uint16_t length);
void guiGraph_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

void guiGraph_DrawPackedImage(const uint8_t *img, uint16_t x_pos, uint16_t y_pos, uint16_t img_width, uint16_t img_height);

void guiGraph_SetFont(const tFont *newFont);
void guiGraph_PrintString(char *str, uint8_t x, uint8_t y);
void guiGraph_PrintStringAligned(char *str, rect_t *rect, uint8_t alignment);

#endif
