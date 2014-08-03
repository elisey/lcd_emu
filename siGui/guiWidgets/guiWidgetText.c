#include "guiWidgetText.h"
#include "guiGraphPrimitives.h"
#include "guiWidgets.h"

#include "guiMsg.h"
uint8_t guiWidgetText_ProcessEvent(guiObject_t *pObject, guiEvent_t event);
void guiWidgetText_Draw(guiWidgetText_t *wgt);


void guiWidgetText_Init(guiWidgetText_t *wgt, guiObject_t *parent)
{
    wgt->widget.object.processEvent = guiWidgetText_ProcessEvent;
    wgt->widget.object.parent = parent;
}

uint8_t guiWidgetText_ProcessEvent(guiObject_t *pObject, guiEvent_t event)
{
    switch (event.type) {
    case GUI_EVENT_DRAW:
        guiWidgetText_Draw( (guiWidgetText_t*)pObject );
        break;
    default:
        break;
    }
    return GUI_EVENT_ACCEPTED;
}

void guiWidgetText_Draw(guiWidgetText_t *wgt)
{
    guiGraph_SetFont(wgt->font);
    guiGraph_PrintString(wgt->text, wgt->widget.x, wgt->widget.y);
}
