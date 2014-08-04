#ifndef GUI_EVENTS_H_
#define GUI_EVENTS_H_

#include <stdint.h>
#include "guiWidgets.h"

#define GUI_EVENT_DECLINE       0x00
#define GUI_EVENT_ACCEPTED      0x01


void guiMsg_InitQueue ();
uint8_t guiMsg_AddMessageToQueue(guiWidgetBase_t *target, const guiEvent_t *event);
uint8_t guiMsg_GetMessageFromQueue(guiWidgetBase_t **target, guiEvent_t *event);
void guiMsg_ProcessMessageQueue(void);

#endif
