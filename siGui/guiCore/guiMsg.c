#include "guiMsg.h"

#include "guiConfig.h"

// Predefined constant events - saves stack a bit
const guiEvent_t guiEvent_INIT = {GUI_EVENT_INIT, 0, 0, 0};
const guiEvent_t guiEvent_DRAW = {GUI_EVENT_DRAW, 0, 0, 0};
#ifdef CFG_USE_UPDATE
const guiEvent_t guiEvent_UPDATE = {GUI_EVENT_UPDATE, 0, 0, 0};
#endif
const guiEvent_t guiEvent_HIDE = {GUI_EVENT_HIDE, 0, 0, 0};
const guiEvent_t guiEvent_SHOW = {GUI_EVENT_SHOW, 0, 0, 0};
const guiEvent_t guiEvent_UNFOCUS = {GUI_EVENT_UNFOCUS, 0, 0, 0};
const guiEvent_t guiEvent_FOCUS = {GUI_EVENT_FOCUS, 0, 0, 0};

typedef struct {
    guiObject_t *target;
    guiEvent_t event;
} guiMsg_t;

typedef struct {
    uint8_t head;
    uint8_t tail;
    uint8_t count;
    guiMsg_t queue[emGUI_CORE_QUEUE_SIZE];
} guiMsgQueue_t;

guiMsgQueue_t guiMsgQueue;

void guiMsg_InitQueue ()
{
    guiMsgQueue.count = 0;
    guiMsgQueue.head = 0;
    guiMsgQueue.tail = 0;
}


uint8_t guiMsg_AddMessageToQueue(guiObject_t *target, const guiEvent_t *event)
{
    if (guiMsgQueue.count < emGUI_CORE_QUEUE_SIZE)
    {
        guiMsgQueue.queue[guiMsgQueue.tail].event = *event;
        guiMsgQueue.queue[guiMsgQueue.tail].target = (guiObject_t *)target;
        guiMsgQueue.count++;
        guiMsgQueue.tail++;
        if (guiMsgQueue.tail == emGUI_CORE_QUEUE_SIZE)
            guiMsgQueue.tail = 0;
        return 1;
     }
    return 0;
}


uint8_t guiMsg_GetMessageFromQueue(guiObject_t **target, guiEvent_t *event)
{
    if (guiMsgQueue.count > 0)
    {
        *target = guiMsgQueue.queue[guiMsgQueue.head].target;
        *event = guiMsgQueue.queue[guiMsgQueue.head].event;
        guiMsgQueue.count--;
        guiMsgQueue.head++;
        if (guiMsgQueue.head == emGUI_CORE_QUEUE_SIZE)
            guiMsgQueue.head = 0;
        return 1;
    }
    return 0;
}


void guiMsg_ProcessMessageQueue()
{
    guiObject_t *target;
    guiEvent_t targetEvent;
    uint8_t processResult;

    while(guiMsg_GetMessageFromQueue(&target,&targetEvent))
    {
        while(1)
        {
            if (target == 0)
                break;
            processResult = target->processEvent(target, targetEvent);
            if (processResult == GUI_EVENT_ACCEPTED)
                break;
            // Focused widget cannot process event - pass event to parent
            if (target->parent != 0)
            {
                target = target->parent;
            }
            else
            {
                // No widget can process this event - skip it.
                break;
            }
        }
    }
}
