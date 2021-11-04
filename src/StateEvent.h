#ifndef STATEEVENT_H
#define STATEEVENT_H

#include <stdint.h>

typedef struct StateEvent
{
    uint32_t id;
    void *context;
} StateEvent;

#endif // STATEEVENT_H