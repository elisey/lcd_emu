#ifndef GUI_WIDGETS_H_
#define GUI_WIDGETS_H_

#include "guiEvent.h"
#include "guiGraphPrimitives.h"



typedef uint8_t (*eventHandler_t)(void *sender, guiEvent_t *msg);



typedef struct guiObject_t {
    struct guiObject_t *parent;
    uint8_t (*processEvent)(struct guiObject_t *pObject, guiEvent_t event);
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




#endif
