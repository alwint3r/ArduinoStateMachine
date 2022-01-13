#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <map>
#include <string>
#include "StateTypedefs.h"
#include "StateClass.h"
#include <type_traits>

typedef std::map<std::string, StateClass *> StateMap;

class StateMachine
{
public:
    StateMachine();
    virtual ~StateMachine();

    void setInitialState(StateClass *state)
    {
        _currentState = state;
    }

    void addState(StateClass *state);
    void removeState(StateClass *state);

    template<typename T>
    void event(const T& eventId)
    {
        if constexpr (std::is_integral<T>::value)
        {
            dispatchEvent({static_cast<uint32_t>(eventId), nullptr});
        }
        else
        {
            dispatchEvent(eventId);
        }
    }

    template<typename T>
    void eventFromISR(const T& eventId)
    {
        if constexpr (std::is_integral<T>::value)
        {
            dispatchEventFromISR({static_cast<uint32_t>(eventId), nullptr});
        }
        else
        {
            dispatchEventFromISR(eventId);
        }
    }

protected:
    virtual void dispatchEvent(const StateEvent &event) = 0;
    virtual void dispatchEventFromISR(const StateEvent &event) = 0;

    void processEvent(StateEvent *event);

protected:
    StateMap *_stateMap;
    StateClass *_currentState = nullptr;
};

#endif // STATE_MACHINE_H