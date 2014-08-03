#ifndef GUI_WIDGETS_H_
#define GUI_WIDGETS_H_

#include "guiEvents.h"

typedef uint8_t (*eventHandler_t)(void *sender, guiEvent_t *event);

// Event handler record
typedef struct {
    uint8_t eventType;                                         // Event type
    uint8_t (*handler)(void *sender, guiEvent_t *event);       // Related callback function pointer
} guiWidgetHandler_t;

// Event handlers table
typedef struct {
    uint8_t count;                      // Count of handler records
    guiWidgetHandler_t *elements;       // Pointer to array of handler records
} guiHandlerTable_t;

// Widget collection type - used by containers
typedef struct {
    uint8_t count;
    uint8_t focusedIndex;
    uint8_t traverseIndex;              // Required by core for tree traverse
    void **elements;
} guiWidgetCollection_t;

typedef struct  {
    guiObject_t *parent;
    uint8_t (*processEvent)(struct guiObject_t *pObject, guiEvent_t event);
    guiHandlerTable_t handlers;
} guiObject_t;

typedef struct   {
    guiObject_t object;
    uint8_t type;                           //FIXME special type implement
    uint8_t isContainer         :   1;
    uint8_t isVisible           :   1;
    uint8_t isFocused           :   1;

    uint8_t requireUpdate       :   1;
    uint8_t requireDraw         :   1;
    uint8_t requireDrawFocus    :   1;

    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;

} guiWidget_t;


typedef struct  {
    guiWidget_t widget;

    guiWidgetCollection_t widgets;
} guiContainer_t


#endif