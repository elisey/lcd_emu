#ifndef GUI_WIDGETS_H_
#define GUI_WIDGETS_H_

#include "guiEvent.h"
#include "guiGraphPrimitives.h"
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
	int8_t focusedIndex;
    uint8_t traverseIndex;              // Required by core for tree traverse
    void **elements;
} guiWidgetCollection_t;

typedef struct guiWidgetBase_t  {
    struct guiWidgetBase_t *parent;
    uint8_t (*processEvent)(struct guiWidgetBase_t *pObject, guiEvent_t *event);
    guiHandlerTable_t handlers;
    uint8_t type;                           //FIXME special type implement
    uint8_t isContainer         :   1;
    uint8_t isVisible           :   1;
    uint8_t isFocused           :   1;

    uint8_t requireUpdate       :   1;
    uint8_t requireDraw         :   1;
    uint8_t requireDrawFocus    :   1;

    uint8_t acceptFocusByTab    :   1;
    uint8_t tabIndex;


    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;

} guiWidgetBase_t;


typedef struct guiContainer_t {
    guiWidgetBase_t widget;
    guiWidgetCollection_t children;
} guiContainer_t;


void guiWidgets_SetSize(guiWidgetBase_t *pBaseWgt,int16_t x, int16_t y, uint16_t width, uint16_t height);
void guiWidgets_InitWidget(guiWidgetBase_t *pBaseWgt, guiWidgetBase_t* parent);
void guiWidgets_SetVisible(guiWidgetBase_t *pBaseWgt, int isVisible);
void guiWidgets_SetFocused(guiWidgetBase_t *pBaseWgt, int isFocused);
#endif
