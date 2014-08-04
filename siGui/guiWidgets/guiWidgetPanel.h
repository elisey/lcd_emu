#ifndef GUI_WIDGET_PANEL_H_
#define GUI_WIDGET_PANEL_H_

#include "guiWidgets.h"

typedef struct guiWidgetPanel_t   {
    guiContainer_t container;
    uint8_t hasFrame : 1;
    color_t color;
} guiWidgetPanel_t;

void guiWidgetPanel_Init(guiWidgetPanel_t *wgt, guiWidgetBase_t *parent);

#endif
