#include "guiCore.h"
//#include "guiLcdHAL.h"
#include "guiWidgetText.h"
#include "guiWidgetPanel.h"

#include "guiMsg.h"
#include "guiConfig.h"
#include <string.h>


guiWidgetBase_t *rootWidget;
guiWidgetBase_t *focusedWidget;
guiContainer_t *activeWindow;           //Текущее активное окно. Тип Контейнер.

void prv_graphPrimitivesTest();
uint8_t lbl_OnDraw(void *sender, guiEvent_t *event);
//uint8_t lbl_processEvent(guiObject_t *pObject, guiEvent_t event);

void guiCore_Init(guiWidgetBase_t* root)
{
    rootWidget = root;
    focusedWidget = 0;

    guiMsg_InitQueue();
    guiGraph_SetPenColor(CL_WHITE);
    guiGraph_SetAltPenColor(CL_GREEN);
    guiGraph_SetFillColor(CL_BLUE);
    prv_graphPrimitivesTest();

}


void prv_graphPrimitivesTest()
{


    guiWidgetPanel_t panel;
    guiWidgetPanel_Init(&panel, 0);
    guiCore_AllocateWidgetCollection((guiContainer_t*)&panel, 3);

    guiWidgetText_t lbl;
    guiWidgetText_Init(&lbl, (guiWidgetBase_t*)&panel);
    lbl.font = &font_h12;
    lbl.hasFrame = 0;
    lbl.redrawText = 0;
    lbl.text = "This is lbl.";
    lbl.textAlignment = ALIGN_CENTER;
    lbl.widget.acceptFocusByTab = 1;
    guiWidgets_SetSize((guiWidgetBase_t*)&lbl, 15,15, 45,45);


    guiWidgetText_t lbl2;
    guiWidgetText_Init(&lbl2, (guiWidgetBase_t*)&panel);
    lbl2.font = &font_h10;
    lbl2.text = "THis is second lbl.";
    lbl2.widget.acceptFocusByTab = 1;
    guiWidgets_SetSize((guiWidgetBase_t*)&lbl2, 15,70, 45,45);

    guiCore_AllocateHandlers((guiWidgetBase_t*)&lbl2, 1);
    guiCore_AddHandler((guiWidgetBase_t*)&lbl2, GUI_EVENT_DRAW, lbl_OnDraw);

    guiMsg_AddMessageToQueue((guiWidgetBase_t*)(&panel), &guiEvent_DRAW);
    guiMsg_AddMessageToQueue((guiWidgetBase_t*)(&lbl), &guiEvent_DRAW);
    guiMsg_AddMessageToQueue((guiWidgetBase_t*)(&lbl2), &guiEvent_DRAW);

    //guiCore_FocusChange((guiWidgetBase_t*)&panel);

    //guiCore_FocusNext();
    //guiCore_FocusNext();
    guiMsg_ProcessMessageQueue();


}


uint8_t lbl_OnDraw(void *sender, guiEvent_t *event)
{
    guiWidgetText_t *pTxt = (guiWidgetText_t*)sender;

    pTxt->text = "fjkldsfjkl";
    //guiMsg_AddMessageToQueue((guiObject_t*)(&lbl2), &guiEvent_DRAW);
    return 1;
}


// REAL CODE===================================================================================

#define emGUI_BYTE_ALIGNMENT_MASK ( emGUI_BYTE_ALIGNMENT - 1 )
// A few bytes might be lost to byte aligning the heap start address
#define emGUI_ADJUSTED_HEAP_SIZE	( emGUI_HEAP_SIZE - emGUI_BYTE_ALIGNMENT )

static unsigned char gui_heap[emGUI_HEAP_SIZE];
static size_t allocated_bytes_count = (size_t) 0;


void *guiCore_malloc(size_t wantedSize)
{
    static unsigned char *p_heap = 0;
    void *result = 0;

    // Make sure blocks are aligned
    #if emGUI_BYTE_ALIGNMENT != 1
        if (wantedSize & emGUI_BYTE_ALIGNMENT_MASK)
        {
            // Adjust allocated block size
            wantedSize += (emGUI_BYTE_ALIGNMENT - (wantedSize & emGUI_BYTE_ALIGNMENT_MASK));
        }
    #endif

    if (p_heap == 0)
    {
        p_heap = (unsigned char *)(((emGUI_POINTER_SIZE_TYPE)&gui_heap[emGUI_BYTE_ALIGNMENT_MASK]) & ((emGUI_POINTER_SIZE_TYPE) ~emGUI_BYTE_ALIGNMENT_MASK));
    }

    // Check if there is enough space
    if( ( ( allocated_bytes_count + wantedSize ) < emGUI_ADJUSTED_HEAP_SIZE ) &&
        ( ( allocated_bytes_count + wantedSize ) > allocated_bytes_count )	)   // Check for overflow
    {
        // Return the next free byte then increment the index past this block
        result = p_heap + allocated_bytes_count;
        allocated_bytes_count += wantedSize;
    }

    if (result == 0)
    {
        // Trace error
        guiCore_Error(emGUI_ERROR_OUT_OF_HEAP);
    }
    return result;
}


void *guiCore_calloc(size_t wantedSize)
{
    void *result = guiCore_malloc(wantedSize);
    if (result)
    {
        memset(result, 0, wantedSize);
    }
    return result;
}


size_t guiCore_GetFreeHeapSize( void )
{
    return ( emGUI_ADJUSTED_HEAP_SIZE - allocated_bytes_count );
}


void guiCore_AllocateHandlers(guiWidgetBase_t *obj, uint16_t count)
{
    if (obj != 0)
    {
        obj->handlers.count = count;
        obj->handlers.elements = guiCore_calloc(count * sizeof(guiWidgetHandler_t));
    }
    else
    {
        guiCore_Error(emGUI_ERROR_NULL_REF);
    }
}

uint8_t guiCore_AddHandler(guiWidgetBase_t *obj, uint8_t eventType, eventHandler_t handler)
{
    uint8_t i;
    //guiGenericWidget_t *w = (guiGenericWidget_t *)widget;
    if ((obj == 0) || (handler == 0))
        return 0;
    for (i = 0; i < obj->handlers.count; i++)
    {
        if (obj->handlers.elements[i].handler == 0)
        {
            // Found free item slot
            obj->handlers.elements[i].eventType = eventType;
            obj->handlers.elements[i].handler = handler;
            return 1;
        }
    }
    // No free space
    //guiCore_Error(emGUI_ERROR_OUT_OF_PREALLOCATED_MEMORY);//FEXME add error handler
    return 0;
}

//-------------------------------------------------------//
//  Call widget's handler for an event
//
//  Function searches through the widget's handler table
//  and call handlers for matching event type
//-------------------------------------------------------//
uint8_t guiCore_CallEventHandler(guiWidgetBase_t *obj, guiEvent_t *event)
{
    uint8_t i;
    uint8_t handlerResult = GUI_EVENT_DECLINE;
    for(i=0; i<obj->handlers.count; i++)
    {
        if (obj->handlers.elements[i].eventType == event->type)
        {
            handlerResult = obj->handlers.elements[i].handler(obj, event);
        }
    }
    return handlerResult;
}

void guiCore_RedrawAll()
{

}

//-------------------------------------------------------//
// Adds a widget to collection
// The widget being added gets specified container widget as parent
// Not used items in a collection must be zero
// If success, function returns non-zero
//-------------------------------------------------------//
uint8_t guiCore_AddWidgetToCollection(guiWidgetBase_t *widget, guiContainer_t *container)
{
    uint8_t i;
    if ((widget != 0) && (container != 0))
    {
        for (i = 0; i < container->children.count; i++)
        {
            if (container->children.elements[i] == 0)
            {
                // Found free item slot
                container->children.elements[i] = widget;
                widget->parent = (guiWidgetBase_t *)container;
                return 1;
            }
        }
    }
    else
    {
        guiCore_Error(emGUI_ERROR_NULL_REF);
        return 0;
    }
    guiCore_Error(emGUI_ERROR_OUT_OF_PREALLOCATED_MEMORY);
    return 0;
}

void guiCore_AllocateWidgetCollection(guiContainer_t *container, uint16_t count)
{
    if (container != 0)
    {
        container->children.count = count;
        container->children.elements = guiCore_calloc(count * sizeof(void *));
        int i;
        for (i = 0; i < count; ++i) {
            container->children.elements[i] = 0;
        }
    }
    else
    {
        guiCore_Error(emGUI_ERROR_NULL_REF);
    }
}

/*int guiCore_FocusChange(guiWidgetBase_t *wgt)
{
    if (wgt != 0)   {
        if (wgt->parent != 0)   {
            if (wgt->parent->isContainer == 1)  {
                guiContainer_t *collection;
                int i;
                collection = (guiContainer_t*)wgt->parent;

                for (i = 0; i < collection->children.count; ++i) {
                    if (collection->children.elements[i] == wgt) {
                        collection->children.focusedIndex = i;
                        break;
                    }
                }
            }
        }

        if (focusedWidget != 0) {
            guiMsg_AddMessageToQueue(focusedWidget, &guiEvent_UNFOCUS);
        }

        guiMsg_AddMessageToQueue(wgt, &guiEvent_FOCUS);
        focusedWidget = wgt;
        return 1;
    }
    else    {
        guiCore_Error(emGUI_ERROR_NULL_REF);
        return 0;
    }
}

int guiCore_FocusNext()
{
    int i;
    guiContainer_t *collection;
    collection = (guiContainer_t*)focusedWidget->parent;
    if (collection == 0)    {
        guiCore_Error(emGUI_ERROR_NULL_REF);
    }
    for (i = (collection->children.focusedIndex + 1); i < collection->children.count; ++i) {
        guiWidgetBase_t *baseWgt;
        baseWgt = collection->children.elements[i];
        if (baseWgt == 0) continue;
        if (baseWgt->acceptFocusByTab == 1) {
            guiMsg_AddMessageToQueue(focusedWidget, &guiEvent_UNFOCUS);
            guiMsg_AddMessageToQueue(baseWgt, &guiEvent_FOCUS);
            focusedWidget = baseWgt;
            collection->children.focusedIndex = i;
            return 1;
        }
    }
    return 0;
}


int guiCore_FocusPrev()
{
    return 1;
}

int guiCore_FocusPushToChild(guiContainer_t *container)
{
    int i;
    if (container == 0) {
        guiCore_Error(emGUI_ERROR_NULL_REF);
    }

    for (i = 0; i < container->children.count; ++i) {
        guiWidgetBase_t *baseWgt;
        baseWgt = container->children.elements[i];
        if (baseWgt == 0) continue;
        if (baseWgt->acceptFocusByTab == 1) {
            guiMsg_AddMessageToQueue(focusedWidget, &guiEvent_UNFOCUS);
            guiMsg_AddMessageToQueue(baseWgt, &guiEvent_FOCUS);
            focusedWidget = baseWgt;
            container->children.focusedIndex = i;
            return 1;
        }
    }
    return 0;

}*/

void guiCore_Error(uint8_t errCode)
{
    // One may trace call stack and thus find source of the error
    while(1);
}






int guiCore_SetActiveWindow(guiContainer_t *activeWnd)
{

}


int guiCore_GetActiveWindow(guiContainer_t **ptrActiveWnd)
{

}

/*  return -1 - нет допустимого элемента для фокусировки
 *
 */
int guiCore_FocusFirst()
{
    int idx;

    activeWindow->children.focusedIndex = -1;
    idx = guiCore_GetNextFocusableWgtIdx(1);
    if (idx == (-1) )    {
        return (-1);
    }
    activeWindow->children.focusedIndex = idx;
    guiCore_AcceptFocus(activeWindow->children.elements[idx]);
    return 0;
}

/*  return -1 - нет допустимого следующего элемента для фокусировки
 *
 */
int guiCore_FocusNext(int direction)
{
    int idx = guiCore_GetNextFocusableWgtIdx(direction);
    if (idx == -1)  {
        return (-1);
    }
    activeWindow->children.focusedIndex = idx;
    guiCore_AcceptFocus(activeWindow->children.elements[idx]);
    return 0;
}

int guiCore_GetNextFocusableWgtIdx(int direction)
{
    guiWidgetBase_t* wgt;
    int idx = activeWindow->children.focusedIndex;
    do  {
        idx = (direction > 0 ? idx+1: idx - 1);
        if ( ( idx < 0 ) || (idx > activeWindow->children.count) )    {
             return (-1);
        }

        wgt = activeWindow->children.elements[idx];
        if (wgt->acceptFocusByTab == 1) {
            return idx;
        }
    }while(1);
}






/*int guiCore_FocusChange(guiWidgetBase_t *wgt)
{
    if (wgt == 0)   {
        guiCore_Error(emGUI_ERROR_NULL_REF);
        return 0;
    }

    int result = guiCore_GetWgtContainerIndex(wgt);
    if (result != -1)   {
        guiContainer_t *container = (guiContainer_t*)wgt->parent;
        container->children.focusedIndex = result;
        activeWindow = container;
    }

    guiCore_AcceptFocus(wgt);

}*/

void guiCore_AcceptFocus(guiWidgetBase_t *wgt)
{
    if (wgt == 0)   {
        guiCore_Error(emGUI_ERROR_NULL_REF);
        return;
    }
    if (focusedWidget != 0) {
        guiMsg_AddMessageToQueue(focusedWidget, &guiEvent_UNFOCUS);
    }
    guiMsg_AddMessageToQueue(wgt, &guiEvent_FOCUS);
    focusedWidget = wgt;
}


/*int guiCore_GetWgtContainerIndex(guiWidgetBase_t *wgt)
{
    if (wgt == 0)   {
        guiCore_Error(emGUI_ERROR_NULL_REF);
        return -1;
    }
    if (wgt->parent == 0)   {
        //guiCore_Error(emGUI_ERROR_NULL_REF);
        return -1;
    }

    int i;
    guiContainer_t* container = (guiContainer_t*)wgt->parent;

    for (i = 0; i < container->children.count; ++i) {
        if (container->children.elements[i] == wgt) {
            return i;
        }
    }
    return -1;
}*/
