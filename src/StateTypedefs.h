#ifndef STATE_TYPEDEFS_H
#define STATE_TYPEDEFS_H

#include <functional>
#include <string>
#include <cstdint>
#include <map>
template<typename T, class C>
class StateEvent
{
public:
    StateEvent(T id, C *context)
    {
        this->id = id;
        this->context = context;
    }

    T id;
    C *context;
};

#endif