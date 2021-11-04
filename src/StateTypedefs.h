#ifndef STATE_TYPEDEFS_H
#define STATE_TYPEDEFS_H

#include <functional>
#include <string>
#include "StateEvent.h"

typedef enum {
    STATE_CHANGE_NONE,
    STATE_CHANGE_CHANGED,
} StateChange;

typedef struct StateProcessResult {
    StateChange change;
    std::string nextStateName;
} StateProcessResult;

typedef std::function<void()> StateFunction;
typedef std::function<StateProcessResult(StateEvent *)> StateEventFunction;

#endif