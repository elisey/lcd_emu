#include "guiGraphPrimitives.h"
//#include "guiFonts.h"


uint8_t prv_GetFontItem(const tFont *font, uint8_t code, uint8_t *width, uint16_t *offset);
uint8_t prv_GetStringWidth(const tFont *font, char *string);

const tFont* currentFont;     // Font that currently used
color_t penColor;             // Pen is used for drawing lines, frames, circles, etc
color_t altPenColor;          //
color_t fillColor;            // Used for filling objects
line_style_t lineStyle;

uint8_t imageOutputMode;       // FIXME Specifies text background - OUTPUT_MODE_TRANSPARENT or OUTPUT_MODE_SOLID

void guiGraph_SetFont(const tFont *newFont)
{
    currentFont = newFont;
}

void guiGraph_SetPenColor(const color_t newColor)
{
    penColor = newColor;
}

void guiGraph_SetAltPenColor(const color_t newColor)
{
    altPenColor = newColor;
}

void guiGraph_SetFillColor(const color_t newColor)
{
    fillColor = newColor;
}

void guiGraph_SetLineStyle(line_style_t newStyle)
{
    lineStyle = newStyle;
}

void guiGraph_SetImageOutput(uint8_t newMode)
{
    imageOutputMode = newMode & (image_paint_set_pixels | image_paint_void_pixels);
}

void guiGraph_DrawRect(rect_t *rect)
{
    uint16_t width, height;
    if ((rect->x1 > rect->x2) || (rect->y1 > rect->y2))
        return;
    width = rect->x2 - rect->x1 + 1;
    height = rect->y2 - rect->y1 + 1;
    guiGraph_DrawVtLine(rect->x1,rect->y1,height);
    guiGraph_DrawVtLine(rect->x2,rect->y1,height);
    guiGraph_DrawHLine(rect->x1,rect->y1,width);
    guiGraph_DrawHLine(rect->x1,rect->y2,width);
}

void guiGraph_DrawFillRect(rect_t *rect)
{
    uint16_t x,y;
    rect_t drawRect = *rect;
    for (x=drawRect.x1; x<=drawRect.x2; x++)
        for (y=drawRect.y1; y<=drawRect.y2; y++)
            LCD_PutPixel(x,y,fillColor);
}

void guiGraph_DrawCircle(int16_t x0, int16_t y0, int16_t radius)
{
    int16_t x = radius;
    int16_t y = 0;
    int16_t xChange = 1 - (radius << 1);
    int16_t yChange = 0;
    int16_t radiusError = 0;

    while (x >= y)
    {
        LCD_PutPixel(x0 - x, y0 + y, penColor);
        LCD_PutPixel(x0 + x, y0 + y, penColor);
        LCD_PutPixel(x0 - x, y0 - y, penColor);
        LCD_PutPixel(x0 + x, y0 - y, penColor);

        LCD_PutPixel(x0 - y, y0 + x, penColor);
        LCD_PutPixel(x0 + y, y0 + x, penColor);
        LCD_PutPixel(x0 - y, y0 - x, penColor);
        LCD_PutPixel(x0 + y, y0 - x, penColor);

        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
}

void guiGraph_DrawFillCircle(int16_t x0, int16_t y0, int16_t radius)
{
    int16_t x = radius;
    int16_t y = 0;
    int16_t xChange = 1 - (radius << 1);
    int16_t yChange = 0;
    int16_t radiusError = 0;
    int16_t i;

    while (x >= y)
    {
        for (i = x0 - x; i <= x0 + x; i++)
        {
            LCD_PutPixel(i, y0 + y, fillColor);
            LCD_PutPixel(i, y0 - y, fillColor);
        }
        for (i = x0 - y; i <= x0 + y; i++)
        {
            LCD_PutPixel(i, y0 + x, fillColor);
            LCD_PutPixel(i, y0 - x, fillColor);
        }

        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
}

void guiGraph_DrawHLine(uint16_t x, uint16_t y, uint16_t length)
{
    uint8_t dashCompare;
    uint8_t dashPeriod;
    uint8_t dashCounter = 0;

    switch(lineStyle)
    {
        case line_stayle_dashed:
            dashPeriod = LCD_DASH_PERIOD;
            dashCompare = LCD_DASH_COMPARE;
            break;
        case line_stali_doted:
            dashPeriod = LCD_DOT_PERIOD;
            dashCompare = LCD_DOT_COMPARE;
            break;
        default: //LINE_STYLE_SOLID:
            dashPeriod = 10;
            dashCompare = 10;   // arbitrary, but >= dashPeriod
            break;
    }

    while(length--)
    {
        if (dashCounter < dashCompare)
            LCD_PutPixel(x,y,penColor);

        x++;
        dashCounter++;
        if (dashCounter == dashPeriod)
            dashCounter = 0;
    }
}

void guiGraph_DrawVtLine(uint16_t x, uint16_t y, uint16_t length)
{
    uint8_t dashCompare;
    uint8_t dashPeriod;
    uint8_t dashCounter = 0;

    switch(lineStyle)
    {
        case line_stayle_dashed:
            dashPeriod = LCD_DASH_PERIOD;
            dashCompare = LCD_DASH_COMPARE;
            break;
        case line_stali_doted:
            dashPeriod = LCD_DOT_PERIOD;
            dashCompare = LCD_DOT_COMPARE;
            break;
        default: //LINE_STYLE_SOLID:
            dashPeriod = 10;
            dashCompare = 10;   // arbitrary, but >= dashPeriod
            break;
    }

    while(length--)
    {
        if (dashCounter < dashCompare)
            LCD_PutPixel(x,y,penColor);

        y++;
        dashCounter++;
        if (dashCounter == dashPeriod)
            dashCounter = 0;
    }
}

void guiGraph_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    int16_t dy = 0;
    int16_t dx = 0;
    int16_t stepx = 0;
    int16_t stepy = 0;
    int16_t fraction = 0;

    dy = y2 - y1;
    dx = x2 - x1;
    if (dy < 0)
    {
        dy = -dy;
        stepy = -1;
    }
    else stepy = 1;
    if (dx < 0)
    {
        dx = -dx;
        stepx = -1;
    }
    else stepx = 1;
    dy <<= 1;
    dx <<= 1;
    LCD_PutPixel(x1,y1,penColor);
    if (dx > dy)
    {
        fraction = dy - (dx >> 1);
        while (x1 != x2)
        {
            if (fraction >= 0)
            {
                y1 += stepy;
                fraction -= dx;
            }
            x1 += stepx;
            fraction += dy;
            LCD_PutPixel(x1,y1,penColor);
        }
    }
    else
    {
        fraction = dx - (dy >> 1);
        while (y1 != y2)
        {
            if (fraction >= 0)
            {
                x1 += stepx;
                fraction -= dy;
            }
            y1 += stepy;
            fraction += dx;
            LCD_PutPixel(x1,y1,penColor);
        }
    }
}



//=======================================================//
//=======================================================//
//  FONTS
//-------------------------------------------------------//
// Prints a string with LCD_currentFont at current position
//
//-------------------------------------------------------//
void guiGraph_PrintString(char *str, uint8_t x, uint8_t y)
{
    uint8_t index = 0;
    uint8_t charWidth;
    uint16_t charOffset;
    char c;

    imageOutputMode = image_paint_set_pixels;   // Paint only set pixels in font bitmaps
    while((c = str[index++]))
    {
        if (prv_GetFontItem(currentFont, c, &charWidth, &charOffset))
        {
            guiGraph_DrawPackedImage(&currentFont->data[charOffset], x, y, charWidth, currentFont->height);
            x += charWidth + currentFont->spacing;
        }
    }
}



//-------------------------------------------------------//
// Prints a string with LCD_currentFont inside rectangle using
//  alignment
//-------------------------------------------------------//
void guiGraph_PrintStringAligned(char *str, rect_t *rect, uint8_t alignment)
{
    uint8_t index = 0;
    uint8_t charWidth;
    uint16_t charOffset;
    char c;
    int16_t x_aligned, y_aligned;
    int16_t strWidthPx;

    // Find horizontal position
    if (alignment & ALIGN_LEFT)
    {
        x_aligned = rect->x1;       // pretty simple - take left rect border as starting point
    }
    else
    {
        // We need to compute length of whole string in pixels
        strWidthPx = prv_GetStringWidth(currentFont,str);
        if (alignment & ALIGN_RIGHT)
            x_aligned = (int16_t)rect->x2 + 1 - strWidthPx;
        else
            x_aligned = rect->x1 + ((int16_t)(rect->x2 - rect->x1 + 1) - strWidthPx) / 2;
    }

    // Find vertical position
    if (alignment & ALIGN_TOP)
    {
        y_aligned = rect->y1;
    }
    else if (alignment & ALIGN_BOTTOM)
    {
        y_aligned = (int16_t)rect->y2 + 1 - currentFont->height;
    }
    else
    {
        y_aligned = rect->y1 + ((int16_t)(rect->y2 - rect->y1 + 1) - currentFont->height) / 2;
    }

    // Now print string
    imageOutputMode = image_paint_set_pixels;   // Paint only set pixels in font bitmaps
    while((c = str[index++]))
    {
        if (prv_GetFontItem(currentFont, c, &charWidth, &charOffset))
        {
            guiGraph_DrawPackedImage(&currentFont->data[charOffset], x_aligned, y_aligned, charWidth, currentFont->height);
            x_aligned += charWidth + currentFont->spacing;
        }
    }
}

//-------------------------------------------------------//
// Draws B/W packed image, coordinates are absolute.
// Image is printed using:
//  - penColor
//  - altPenColor
//  - outputMode
//-------------------------------------------------------//
void guiGraph_DrawPackedImage(const uint8_t *img, uint16_t x_pos, uint16_t y_pos, uint16_t img_width, uint16_t img_height)
{
    uint8_t bit_mask = 0x01;
    uint8_t temp;
    uint16_t img_index;
    uint16_t img_start_index = 0;
    uint16_t x;
    uint16_t y_fin = y_pos + img_height;

    while(y_pos < y_fin)
    {
        img_index = img_start_index;
        for (x = x_pos; x < x_pos + img_width; x++)
        {
            temp = img[img_index++];
            if (temp & bit_mask)
            {
                if (imageOutputMode & image_paint_set_pixels)
                {
                    LCD_PutPixel(x,y_pos,penColor);
                }
            }
            else if (imageOutputMode & image_paint_void_pixels)
            {
                LCD_PutPixel(x,y_pos,altPenColor);
            }
        }
        y_pos++;
        if (bit_mask == 0x80)
        {
            bit_mask = 0x01;
            img_start_index += img_width;
        }
        else
        {
            bit_mask = bit_mask << 1;
        }
    }
}


//-------------------------------------------------------//
// Rerurns width and offset of a font item
// Font array MUST be sorted by code.
// If no item with such code is found, 0 is returned.
// Using binary search, http://kvodo.ru/dvoichnyiy-poisk.html
//-------------------------------------------------------//
uint8_t prv_GetFontItem(const tFont *font, uint8_t code, uint8_t *width, uint16_t *offset)
{
    uint8_t itemCode;
    uint8_t start_index = 0;
    uint8_t end_index;
    uint8_t i;

    if (font->codeTable == 0)
    {
        // Font char set is a contiguous array
        start_index = font->firstCharCode;
        end_index = start_index + (font->charCount - 1);
        if ((code < start_index) || (code > end_index))
            return 0;
        else
        {
            i = code-start_index;
            if (offset != 0)
            {
                if (font->offsetTable == 0)
                    *offset = (uint16_t)i * font->bytesPerChar;
                else
                    *offset = font->offsetTable[i];
            }
            if (font->widthTable == 0)
                *width = font->width;
            else
                *width = font->widthTable[i];
            return 1;
        }
    }
    else
    {
        end_index = font->charCount;
        // Font char set is defined by charTable
        while (start_index < end_index)
        {
            i = start_index + (end_index - start_index) / 2;
            itemCode = font->codeTable[i];
            if (code < itemCode)
                end_index = i;
            else if (code > itemCode)
                start_index = i+1;
            else
            {
                // Found
                if (offset != 0)
                    // Font must have valid offsetTable when codeTable is used
                    *offset = font->offsetTable[i];
                if (font->widthTable == 0)
                    *width = font->width;
                else
                    *width = font->widthTable[i];
                return 1;
            }
        }
    }
    return 0;
}

//-------------------------------------------------------//
// Rerurns length of a string in pixels
//
//-------------------------------------------------------//
uint8_t prv_GetStringWidth(const tFont *font, char *string)
{
    uint8_t length = 0;
    uint8_t index = 0;
    uint8_t charWidth;
    char c;

    while((c = string[index++]))
    {
        if (prv_GetFontItem(currentFont, c, &charWidth, 0))
            length += charWidth + font->spacing;
    }

    length -= font->spacing;
    return length;
}


