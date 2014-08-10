#include "guiCore.h"
//#include "guiLcdHAL.h"
#include "guiWidgetText.h"
#include "guiWidgetPanel.h"

#include "guiMsg.h"
#include "guiConfig.h"

#include "guiKey.h"
#include <string.h>


guiWidgetBase_t *rootWidget;
guiWidgetBase_t *focusedWidget;
guiContainer_t *activeWindow;           //Текущее активное окно. Тип Контейнер.

void prv_graphPrimitivesTest();

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


void prv_wnd1Init();
guiWidgetPanel_t panel;
guiWidgetText_t lbl;
guiWidgetText_t lbl2;
guiWidgetText_t lbl3;

void prv_wnd2Init();
guiWidgetPanel_t panel2;
guiWidgetText_t lbl4;
guiWidgetText_t lbl5;
guiWidgetText_t lbl6;

uint8_t panel_keyHandler(void *sender, guiEvent_t *event);

void prv_graphPrimitivesTest()
{



    guiWidgetPanel_Init(&panel, 0);
    guiCore_AllocateWidgetCollection((guiContainer_t*)&panel, 3);


    guiWidgetText_Init(&lbl, (guiWidgetBase_t*)&panel);
    lbl.font = &font_h12;
    lbl.hasFrame = 0;
    lbl.redrawText = 0;
    lbl.text = "This is lbl.";
    lbl.textAlignment = ALIGN_CENTER;
    lbl.widget.acceptFocusByTab = 1;
    guiWidgets_SetSize((guiWidgetBase_t*)&lbl, 15,15, 45,45);

	guiWidgetText_Init(&lbl3, (guiWidgetBase_t*)&panel);
	lbl3.font = &font_h12;
	lbl3.text = "This is another text lable. So";
	lbl3.widget.acceptFocusByTab = 1;
	guiWidgets_SetSize((guiWidgetBase_t*)&lbl3, 15,90, 45,45);

    guiWidgetText_Init(&lbl2, (guiWidgetBase_t*)&panel);
    lbl2.font = &font_h10;
    lbl2.text = "THis is second lbl.";
    lbl2.widget.acceptFocusByTab = 1;
    guiWidgets_SetSize((guiWidgetBase_t*)&lbl2, 15,70, 45,45);




    guiMsg_AddMessageToQueue((guiWidgetBase_t*)(&panel), &guiEvent_DRAW);
    guiMsg_AddMessageToQueue((guiWidgetBase_t*)(&lbl), &guiEvent_DRAW);
    guiMsg_AddMessageToQueue((guiWidgetBase_t*)(&lbl2), &guiEvent_DRAW);
	guiMsg_AddMessageToQueue((guiWidgetBase_t*)(&lbl3), &guiEvent_DRAW);

	prv_wnd1Init();
	prv_wnd2Init();

	guiCore_SetActiveWindow((guiContainer_t*)&panel);
	guiMsg_ProcessMessageQueue();
}

void prv_wnd1Init()
{
	guiWidgetPanel_Init(&panel, 0);
	guiCore_AllocateWidgetCollection((guiContainer_t*)&panel, 3);


	guiWidgetText_Init(&lbl, (guiWidgetBase_t*)&panel);
	lbl.font = &font_h12;
	lbl.hasFrame = 0;
	lbl.redrawText = 0;
	lbl.text = "This is lbl.";
	lbl.textAlignment = ALIGN_CENTER;
	lbl.widget.acceptFocusByTab = 1;
	guiWidgets_SetSize((guiWidgetBase_t*)&lbl, 15,15, 45,45);

	guiWidgetText_Init(&lbl3, (guiWidgetBase_t*)&panel);
	lbl3.font = &font_h12;
	lbl3.text = "This is another text lable. So";
	lbl3.widget.acceptFocusByTab = 1;
	guiWidgets_SetSize((guiWidgetBase_t*)&lbl3, 15,70, 45,45);

	guiWidgetText_Init(&lbl2, (guiWidgetBase_t*)&panel);
	lbl2.font = &font_h10;
	lbl2.text = "THis is second lbl.";
	lbl2.widget.acceptFocusByTab = 1;
	guiWidgets_SetSize((guiWidgetBase_t*)&lbl2, 15,90, 45,45);

	guiCore_AllocateHandlers((guiWidgetBase_t*)(&panel), 1);
	guiCore_AddHandler((guiWidgetBase_t*)(&panel),GUI_EVENT_KEY, panel_keyHandler);
}

void prv_wnd2Init()
{
	guiWidgetPanel_Init(&panel2, 0);
	guiCore_AllocateWidgetCollection((guiContainer_t*)&panel2, 3);


	guiWidgetText_Init(&lbl4, (guiWidgetBase_t*)&panel2);
	lbl4.font = &font_h12;
	lbl4.hasFrame = 0;
	lbl4.redrawText = 0;
	lbl4.text = "This is lbl.";
	lbl4.textAlignment = ALIGN_CENTER;
	lbl4.widget.acceptFocusByTab = 1;
	guiWidgets_SetSize((guiWidgetBase_t*)&lbl4, 55,55, 45,15);

	guiWidgetText_Init(&lbl5, (guiWidgetBase_t*)&panel2);
	lbl5.font = &font_h12;
	lbl5.text = "This is another text lable. So";
	lbl5.widget.acceptFocusByTab = 1;
	guiWidgets_SetSize((guiWidgetBase_t*)&lbl5, 15,70, 45,15);

	guiWidgetText_Init(&lbl6, (guiWidgetBase_t*)&panel2);
	lbl6.font = &font_h10;
	lbl6.text = "THis is second lbl.";
	lbl6.widget.acceptFocusByTab = 1;
	guiWidgets_SetSize((guiWidgetBase_t*)&lbl6, 15,120, 45,15);
	guiCore_AllocateHandlers((guiWidgetBase_t*)(&panel2), 1);
	guiCore_AddHandler((guiWidgetBase_t*)(&panel2),GUI_EVENT_KEY, panel_keyHandler);
}


uint8_t panel_keyHandler(void *sender, guiEvent_t *event)
{
	int dir;
	int result;
	switch (event->hparam) {
	case guiKey_Enter:

		break;
	case guiKey_Esc:
		guiCore_FocusFirst();
		break;
	case guiKey_Left:
	case guiKey_Right:
		if (event->hparam == guiKey_Left)	{
			dir = -1;
		}
		else if (event->hparam == guiKey_Right)	{
			dir = 1;
		}

		result = guiCore_FocusNext(dir);
		if (result == -1)	{
			if (sender == (void*)&panel)	{
				guiCore_SetActiveWindow((guiContainer_t*)&panel2);
			}
			else if (sender == (void*)&panel2)	{
				guiCore_SetActiveWindow((guiContainer_t*)&panel);
			}
		}
		break;
	default:
		break;
	}
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

void guiCore_Error(uint8_t errCode)
{
	volatile uint8_t dummy;
	dummy = errCode;
    // One may trace call stack and thus find source of the error
    while(1);
}

/*
 * Установка активного окна. В качестве окна может выступать
 * любой контейнер.
 * @param:
 * guiContainer_t *_activeWindow указатель на новое активное окно
 *
 * @return
 * int - (-1) не удалось выставить фокус на дочерние элементы
 * int - 0 фокус выставлен на первый доступный дочерний элемент.
 */
int guiCore_SetActiveWindow(guiContainer_t *_activeWindow)
{
	if (activeWindow == _activeWindow)	return (-1);
	activeWindow = _activeWindow;
	guiCore_DrawWindow();
	return guiCore_FocusFirst();
}

/*
 * Получить указатель на текущее активное окно.
 * @param
 * guiContainer_t **ptrActiveWnd указатель на указатель на текущее
 * активнео окн
 * @return void
 */
void guiCore_GetActiveWindow(guiContainer_t **ptrActiveWnd)
{
	*ptrActiveWnd = activeWindow;
}

/*
 * Сфокусироваться на первом доступном элементе в текущем окне (контейнере)
 * @param
 * none
 * @return
 * (-1) - нет допустимого элемента для фокусировки
 * idx - индекс элемента, на котором произведено фокусирование
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
	return idx;
}

/*
 * Сфокусироваться на следующем доступном элементе в текущем окне (контейнере)
 * @param
 * int direction - направление сдвига фокуса: >0 - вперед, <0 - назад
 * @return
 * (-1) - нет допустимого элемента для фокусировки
 * idx - индекс элемента, на котором произведено фокусирование
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

/*
 * Взять индекс следующего доступного элемента для фокусировки
 * @param
 * int direction - направление сдвига фокуса: >0 - вперед, <0 - назад
 * @return
 * (-1) - нет допустимого элемента для фокусировки
 * idx - индекс элемента, на котором произведено фокусирование
 */
int guiCore_GetNextFocusableWgtIdx(int direction)
{
	guiWidgetBase_t* wgt;
	int idx = activeWindow->children.focusedIndex;
	do  {
		idx = (direction > 0 ? idx+1: idx - 1);
		if ( ( idx < 0 ) || (idx >= activeWindow->children.count) )    {
			 return (-1);
		}

		wgt = activeWindow->children.elements[idx];
		if (wgt == 0) continue;
		if (wgt->acceptFocusByTab == 1) {
			return idx;
		}
	}while(1);
}

/*
 * Принять изменение фокуса. Происходит отправка сообщения снятия
 * и установки фокуса. Изменять сфокусированность ТОЛЬКО через эту функцию
 * @param
 * guiWidgetBase_t *wgt - указатель виджет для фокусировки.
 * @return
 * void
 */
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

void guiCore_DrawWindow()
{
	guiMsg_AddMessageToQueue( (guiWidgetBase_t*)activeWindow, &guiEvent_DRAW );
	int i;
	for (i = 0; i < activeWindow->children.count; ++i) {
		if (activeWindow->children.elements[i] == 0)	continue;
		guiMsg_AddMessageToQueue( (guiWidgetBase_t*)activeWindow->children.elements[i], &guiEvent_DRAW );
	}
}
