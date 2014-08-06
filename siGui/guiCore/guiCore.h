#ifndef GUICORE_H
#define GUICORE_H

#include "guiWidgets.h"

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

int guiCore_FocusWidget(guiWidgetBase_t* wgt);
int guiCore_FocusNext();
int guiCore_FocusPrev();

#endif // GUICORE_H
