#include "guiWidgetText.h"
#include "guiGraphPrimitives.h"
#include "guiWidgets.h"
#include "guiCore.h"
#include "guiMsg.h"

uint8_t guiWidgetText_ProcessEvent(guiWidgetBase_t *wgt, guiEvent_t *event);
void guiWidgetText_Draw(guiWidgetText_t *wgt);


void guiWidgetText_Init(guiWidgetText_t *wgt, guiWidgetBase_t *parent)
{
    guiWidgetBase_t *pBaseWgt = (guiWidgetBase_t*)wgt;
    guiWidgets_InitWidget(pBaseWgt, parent);

    pBaseWgt->isContainer = 0;
    pBaseWgt->processEvent = guiWidgetText_ProcessEvent;
    pBaseWgt->type = 1; //FIXME

    wgt->font = &guiWGT_TEXT_DefaultFont;
    wgt->hasFrame = guiWGT_TEXT_DefaultHasFrame;
    wgt->redrawText = 0;
}

void guiWidgetText_SetText(guiWidgetText_t *wgt, const char *text)
{
    wgt->text = text;
    wgt->widget.requireDraw = 1;
}

#define GUI_EVENT_DRAW          0x01
#define GUI_EVENT_INIT          0x02
#define GUI_EVENT_UPDATE        0x04
#define GUI_EVENT_HIDE          0x06
#define GUI_EVENT_SHOW          0x07
#define GUI_EVENT_UNFOCUS       0x08
#define GUI_EVENT_FOCUS         0x09

uint8_t guiWidgetText_ProcessEvent(guiWidgetBase_t *wgt, guiEvent_t *event)
{
    rect_t rect;

    switch (event->type) {
    case GUI_EVENT_DRAW:
        guiWidgetText_Draw( (guiWidgetText_t*)wgt );
        break;
    case GUI_EVENT_INIT:

        break;
    case GUI_EVENT_UPDATE:

        break;
    case GUI_EVENT_HIDE:

        break;
    case GUI_EVENT_SHOW:

        break;
    case GUI_EVENT_UNFOCUS:
        rect.x1 = wgt->x;
        rect.x2 = wgt->x + wgt->width;
        rect.y1 = wgt->y;
        rect.y2 = wgt->y + wgt->height;
        guiGraph_SetPenColor(CL_LIGHT_GREY);
        guiGraph_DrawRect(&rect);
        break;
    case GUI_EVENT_FOCUS:
        rect.x1 = wgt->x;
        rect.x2 = wgt->x + wgt->width;
        rect.y1 = wgt->y;
        rect.y2 = wgt->y + wgt->height;
        guiGraph_SetPenColor(CL_BLUE);
        guiGraph_DrawRect(&rect);
        break;
    default:
        return guiCore_CallEventHandler(wgt, event);
        break;
    }

    return GUI_EVENT_ACCEPTED;
}

void guiWidgetText_Draw(guiWidgetText_t *wgt)
{
    guiGraph_SetFont(wgt->font);
    guiGraph_PrintString(wgt->text, wgt->widget.x, wgt->widget.y);
}



