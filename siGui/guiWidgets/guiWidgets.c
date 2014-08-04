#include "guiWidgets.h"

void guiWidgets_SetSize(guiWidgetBase_t *pBaseWgt,int16_t x, int16_t y, uint16_t width, uint16_t height)
{
    pBaseWgt->x = x;
    pBaseWgt->y = y;
    pBaseWgt->width = width;
    pBaseWgt->height = height;
}
