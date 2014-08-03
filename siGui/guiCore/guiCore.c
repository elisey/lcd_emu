#include "guiCore.h"
#include "guiLcdHAL.h"
#include "guiGraphPrimitives.h"

void prv_graphPrimitivesTest();

void guiCore_Init()
{
    prv_graphPrimitivesTest();

}


void prv_graphPrimitivesTest()
{
    guiGraph_SetPenColor(CL_WHITE);
    guiGraph_SetAltPenColor(CL_GREEN);
    guiGraph_SetFillColor(CL_BLUE);

    guiWidgetText_t lbl;

    guiWidgetBase_t *pWgt = (guiWidgetBase_t*)&lbl;

    pWgt->x = 32;
    pWgt->y = 12;
    pWgt->width = 50;
    pWgt->height = 40;

    guiCore_DrawWidget(pWgt);

    lbl.font = &font_h12;
    lbl.hasFrame = 0;
    lbl.redrawText = 0;
    lbl.text = "This is lbl.";
    lbl.textAlignment = ALIGN_CENTER;

    guiCore_DrawWidgetText(&lbl);
}


void guiCore_DrawWidget(guiWidgetBase_t *widget)
{
    rect_t rect;
    rect.x1 = widget->x;
    rect.y1 = widget->y;
    rect.x2 = widget->x + widget->width;
    rect.y2 = widget->y + widget->height;
    guiGraph_DrawFillRect(&rect);
}

void guiCore_DrawWidgetText(guiWidgetText_t *widget)
{
    guiGraph_SetFont(widget->font);
    guiGraph_PrintString(widget->text,widget->widget.x, widget->widget.y);
}
