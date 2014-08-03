#ifndef GUI_WIDGETS_H_
#define GUI_WIDGETS_H_

#include "guiMsg.h"
#include "guiGraphPrimitives.h"
//extern typedef struct guiObject_t;

typedef uint8_t (*eventHandler_t)(void *sender, guiMsg_t *msg);

// Event handler record
typedef struct {
    uint8_t eventType;                                         // Event type
    uint8_t (*handler)(void *sender, guiMsg_t *msg);       // Related callback function pointer
} guiWidgetHandler_t;

// Event handlers table
#ifdef GG
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
#endif

typedef struct guiObject_t {
    struct guiObject_t *parent;
    uint8_t (*processEvent)(struct guiObject_t *pObject, guiMsg_t *msg);
    //guiHandlerTable_t handlers;
} guiObject_t ;

typedef struct guiWidgetBase_t  {
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

} guiWidgetBase_t;


typedef struct guiContainer_t {
    guiWidgetBase_t widget;

    //guiWidgetCollection_t widgets;
} guiContainer_t;

typedef struct guiWidgetText_t   {
    guiWidgetBase_t widget;
    char *text;
    const tFont *font;
    uint8_t textAlignment;
    uint8_t hasFrame : 1;
    uint8_t redrawText : 1;
} guiWidgetText_t;


#endif
