#include "guiWidgetPanel.h"
#include "guiGraphPrimitives.h"
#include "guiWidgets.h"
#include "guiCore.h"
#include "guiMsg.h"

uint8_t guiWidgetPanel_ProcessEvent(guiWidgetBase_t *wgt, guiEvent_t *event);
void guiWidgetPanel_Draw(guiWidgetPanel_t *wgt);

void guiWidgetPanel_Init(guiWidgetPanel_t *wgt, guiWidgetBase_t *parent)
{
    guiWidgetBase_t *pBaseWgt = (guiWidgetBase_t*)wgt;
    guiWidgets_InitWidget(pBaseWgt, parent);

    pBaseWgt->isContainer = 1;
    pBaseWgt->processEvent = guiWidgetPanel_ProcessEvent;
    pBaseWgt->type = 2; //FIXME

    guiContainer_t *pContainer = (guiContainer_t*)wgt;
    pContainer->children.count = 0;
    pContainer->children.focusedIndex = 0;
    pContainer->children.traverseIndex = 0;

    wgt->hasFrame = 0;
    wgt->color = CL_LIGHT_GREY;
}

uint8_t guiWidgetPanel_ProcessEvent(guiWidgetBase_t *wgt, guiEvent_t *event)
{
    switch (event->type) {
    case GUI_EVENT_INIT:

        break;
    case GUI_EVENT_DRAW:
        guiWidgetPanel_Draw( (guiWidgetPanel_t*)wgt );
        break;
    case GUI_EVENT_UNFOCUS:

        break;
    case GUI_EVENT_FOCUS:
        //guiCore_FocusPushToChild((guiContainer_t*)wgt);
        break;
    default:
        break;
    }
    return guiCore_CallEventHandler(wgt, event);
    //return GUI_EVENT_ACCEPTED;
}

void guiWidgetPanel_Draw(guiWidgetPanel_t *wgt)
{
    guiGraph_SetFillColor(wgt->color);
    rect_t rect = {0,0,320, 240};

    guiGraph_DrawFillRect(&rect);
}
