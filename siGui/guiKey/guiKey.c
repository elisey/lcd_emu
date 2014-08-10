#include "guiKey.h"
#include "guiMsg.h"
#include "guiEvent.h"
#include "guiCore.h"

void guiKey_ProcessKey(guiKey_t key, guiPressType_t pressType)
{
	guiEvent_t event;
	event.type = GUI_EVENT_KEY;
	event.hparam = key;
	event.lparam = pressType;


	guiContainer_t *currentWindow;
	guiCore_GetActiveWindow(&currentWindow);

	guiMsg_AddMessageToQueue( (guiWidgetBase_t*)currentWindow, &event);
}
