#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <map>
#include <string>
#include "StateTypedefs.h"
#include "StateClass.h"
#include "StateEvent.h"

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
    virtual void event(const StateEvent &event) = 0;
    virtual void eventFromISR(const StateEvent &event) = 0;
    virtual void event(const uint32_t eventId);
    virtual void eventFromISR(const uint32_t eventId);

protected:
    void processEvent(StateEvent *event);

protected:
    StateMap *_stateMap;
    StateClass *_currentState = nullptr;
};

#endif // STATE_MACHINE_H