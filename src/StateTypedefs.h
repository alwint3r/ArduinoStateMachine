#ifndef STATE_TYPEDEFS_H
#define STATE_TYPEDEFS_H

#include <functional>
#include <string>
#include <cstdint>
#include <map>

class StateClass;

using StateEvent = struct __state_event
{
    uint32_t id;
    void *context;
};

using StateFunction = std::function<void()>;
using StateEventFunction = std::function<std::string(StateEvent *)>;
using StateMap = std::map<std::string, StateClass *>;
using StatePair = std::pair<std::string, StateClass *>;

#endif