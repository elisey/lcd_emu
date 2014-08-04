#ifndef GUI_WIDGET_TEXT_H_
#define GUI_WIDGET_TEXT_H_

#include "guiWidgets.h"

#define guiWGT_TEXT_DefaultFont         font_h10
#define guiWGT_TEXT_DefaultHasFrame     0
#define guiWGT_TEXT_Default
#define guiWGT_TEXT_Default
#define guiWGT_TEXT_Default

typedef struct guiWidgetText_t   {
    guiWidgetBase_t widget;
    char *text;
    const tFont *font;
    uint8_t textAlignment;
    uint8_t hasFrame : 1;
    uint8_t redrawText : 1;
} guiWidgetText_t;

void guiWidgetText_Init(guiWidgetText_t *wgt, guiWidgetBase_t *parent);
void guiWidgetText_SetText(guiWidgetText_t *wgt, const char* text);
#endif
