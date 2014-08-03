#include "guiCore.h"
//#include "guiLcdHAL.h"
#include "guiWidgetText.h"
#include "guiMsg.h"

void prv_graphPrimitivesTest();
uint8_t lbl_processEvent(guiObject_t *pObject, guiEvent_t event);

void guiCore_Init()
{
    prv_graphPrimitivesTest();

}


void prv_graphPrimitivesTest()
{
    guiMsg_InitQueue();

    guiGraph_SetPenColor(CL_WHITE);
    guiGraph_SetAltPenColor(CL_GREEN);
    guiGraph_SetFillColor(CL_BLUE);

    guiWidgetText_t lbl;
    guiWidgetText_Init(&lbl, 0);
    guiWidgetBase_t *pWgt = (guiWidgetBase_t*)&lbl;

    pWgt->x = 32;
    pWgt->y = 12;
    pWgt->width = 50;
    pWgt->height = 40;

    lbl.font = &font_h12;
    lbl.hasFrame = 0;
    lbl.redrawText = 0;
    lbl.text = "This is lbl.";
    lbl.textAlignment = ALIGN_CENTER;

   // guiEvent_t event;
   // event.type = guiEvent_DRAW;

    guiMsg_AddMessageToQueue((guiObject_t*)(&lbl), &guiEvent_DRAW);
    guiMsg_ProcessMessageQueue();


}
