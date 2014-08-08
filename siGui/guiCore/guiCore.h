#ifndef GUICORE_H
#define GUICORE_H

#include "guiWidgets.h"

#define emGUI_ERROR_OUT_OF_HEAP                 0x01
#define emGUI_ERROR_OUT_OF_PREALLOCATED_MEMORY  0x02
#define emGUI_ERROR_NULL_REF                    0x03

void guiCore_Init();
//void guiCore_DrawWidget(guiWidgetBase_t *widget);
//void guiCore_DrawWidgetText(guiWidgetText_t *widget);


void *guiCore_malloc(size_t wantedSize);
void *guiCore_calloc(size_t wantedSize);
size_t guiCore_GetFreeHeapSize( void );

void guiCore_AllocateHandlers(guiWidgetBase_t *obj, uint16_t count);
uint8_t guiCore_AddHandler(guiWidgetBase_t *obj, uint8_t eventType, eventHandler_t handler);
uint8_t guiCore_CallEventHandler(guiWidgetBase_t *obj, guiEvent_t *event);

void guiCore_RedrawAll();

uint8_t guiCore_AddWidgetToCollection(guiWidgetBase_t *widget, guiContainer_t *container);
void guiCore_AllocateWidgetCollection(guiContainer_t *container, uint16_t count);

/*int guiCore_FocusChange(guiWidgetBase_t* wgt);
int guiCore_FocusNext();
int guiCore_FocusPrev();
int guiCore_FocusPushToChild(guiContainer_t *container);*/

int guiCore_SetActiveWindow(guiContainer_t* activeWnd);
int guiCore_GetActiveWindow(guiContainer_t** ptrActiveWnd);
int guiCore_FocusFirst();
int guiCore_FocusNext(int direction);

//int guiCore_FocusChange(guiWidgetBase_t* wgt);
void guiCore_AcceptFocus(guiWidgetBase_t *wgt);
//int guiCore_GetWgtContainerIndex(guiWidgetBase_t *wgt);

void guiCore_Error(uint8_t errCode);

#endif // GUICORE_H
