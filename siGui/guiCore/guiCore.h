#ifndef GUICORE_H
#define GUICORE_H

#include "guiWidgets.h"
#include "guiWidgetPanel.h"
#define emGUI_ERROR_OUT_OF_HEAP                 0x01
#define emGUI_ERROR_OUT_OF_PREALLOCATED_MEMORY  0x02
#define emGUI_ERROR_NULL_REF                    0x03

extern guiWidgetPanel_t panel, panel2;


void guiCore_Init();

void *guiCore_malloc(size_t wantedSize);
void *guiCore_calloc(size_t wantedSize);
size_t guiCore_GetFreeHeapSize( void );

void guiCore_AllocateHandlers(guiWidgetBase_t *obj, uint16_t count);
uint8_t guiCore_AddHandler(guiWidgetBase_t *obj, uint8_t eventType, eventHandler_t handler);
uint8_t guiCore_CallEventHandler(guiWidgetBase_t *obj, guiEvent_t *event);

void guiCore_RedrawAll();

uint8_t guiCore_AddWidgetToCollection(guiWidgetBase_t *widget, guiContainer_t *container);
void guiCore_AllocateWidgetCollection(guiContainer_t *container, uint16_t count);

int guiCore_SetActiveWindow(guiContainer_t* _activeWindow);
void guiCore_GetActiveWindow(guiContainer_t** ptrActiveWnd);
int guiCore_FocusFirst();
int guiCore_FocusNext(int direction);
int guiCore_GetNextFocusableWgtIdx();
void guiCore_AcceptFocus(guiWidgetBase_t *wgt);

void guiCore_DrawWindow();

void guiCore_Error(uint8_t errCode);

#endif // GUICORE_H
