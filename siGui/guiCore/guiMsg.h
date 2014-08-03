#ifndef GUI_EVENTS_H_
#define GUI_EVENTS_H_

#include <stdint.h>

typedef struct {
    uint8_t type;
    uint8_t spec;
    uint16_t lparam;
    uint16_t hparam;
} guiMsg_t;

#endif
