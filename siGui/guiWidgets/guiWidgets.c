#include "guiWidgets.h"
#include "guiCore.h"
void guiWidgets_SetSize(guiWidgetBase_t *pBaseWgt,int16_t x, int16_t y, uint16_t width, uint16_t height)
{
    pBaseWgt->x = x;
    pBaseWgt->y = y;
    pBaseWgt->width = width;
    pBaseWgt->height = height;
}


void guiWidgets_InitWidget(guiWidgetBase_t *pBaseWgt, guiWidgetBase_t *parent)
{
    if (parent != 0)    {
        guiCore_AddWidgetToCollection(pBaseWgt, (guiContainer_t*)parent);
    }
    pBaseWgt->handlers.count = 0;
    pBaseWgt->isFocused = 0;
    pBaseWgt->isVisible = 1;
    pBaseWgt->parent = parent;
    pBaseWgt->requireDraw = 1;
    pBaseWgt->requireDrawFocus = 0;
    pBaseWgt->requireUpdate = 0;
}


void guiWidgets_SetVisible(guiWidgetBase_t *pBaseWgt, int isVisible)
{
    if (isVisible)  {
        pBaseWgt->isVisible = 1;
        pBaseWgt->requireDraw = 1;
    }
    else    {
        pBaseWgt->isVisible = 0;
    }
}


void guiWidgets_SetFocused(guiWidgetBase_t *pBaseWgt, int isFocused)
{
    if (isFocused)  {
        pBaseWgt->isFocused = 1;
        pBaseWgt->requireDrawFocus = 1;
    }
    else    {
        pBaseWgt->isFocused = 0;
        pBaseWgt->requireDrawFocus = 1;
    }
}
