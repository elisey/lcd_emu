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
    pBaseWgt->handlers.count = 0;
    pBaseWgt->isContainer = 0;
    pBaseWgt->isFocused = 0;
    pBaseWgt->isVisible = 1;
    pBaseWgt->parent = parent;
    pBaseWgt->processEvent = guiWidgetText_ProcessEvent;
    pBaseWgt->requireDraw = 1;
    pBaseWgt->requireDrawFocus = 0;
    pBaseWgt->requireUpdate = 0;
    pBaseWgt->type = 1; //FIXME

    wgt->font = &guiWGT_TEXT_DefaultFont;
    wgt->hasFrame = guiWGT_TEXT_DefaultHasFrame;
    wgt->redrawText = 0;
}

uint8_t guiWidgetText_ProcessEvent(guiWidgetBase_t *wgt, guiEvent_t *event)
{
    switch (event->type) {
    case GUI_EVENT_DRAW:
        guiWidgetText_Draw( (guiWidgetText_t*)wgt );
        break;
    default:
        break;
    }
    guiCore_CallEventHandler(wgt, event);
    return GUI_EVENT_ACCEPTED;
}

void guiWidgetText_Draw(guiWidgetText_t *wgt)
{
    guiGraph_SetFont(wgt->font);
    guiGraph_PrintString(wgt->text, wgt->widget.x, wgt->widget.y);
}
