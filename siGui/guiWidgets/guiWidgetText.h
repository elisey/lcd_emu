#ifndef GUI_WIDGET_TEXT_H_
#define GUI_WIDGET_TEXT_H_

#include "guiWidgets.h"

typedef struct guiWidgetText_t   {
    guiWidgetBase_t widget;
    char *text;
    const tFont *font;
    uint8_t textAlignment;
    uint8_t hasFrame : 1;
    uint8_t redrawText : 1;
} guiWidgetText_t;

void guiWidgetText_Init(guiWidgetText_t *wgt, guiObject_t *parent);


#endif
