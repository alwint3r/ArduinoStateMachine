#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <map>
#include <string>
#include "StateTypedefs.h"
#include "StateClass.h"
#include <type_traits>

template <typename T, class C>
class StateMachine
{
public:
    StateMachine()
    {
        
    }

    virtual ~StateMachine()
    {

    }

    void setInitialState(StateClass<T, C> *state)
    {
        _currentState = state;
    }

    void addState(StateClass<T, C> *state)
    {
        _stateMap->insert(StatePair(state->getName(), state));
    }

    void removeState(StateClass<T, C> *state)
    {
        _stateMap->erase(state->getName());
    }

    void event(const StateEvent<T, C> &stateEvent)
    {
        dispatchEvent(stateEvent);
    }

    void event(const T &eventId)
    {

        auto stateEvent = StateEvent<T, C>(static_cast<T>(eventId), nullptr);
        dispatchEvent(stateEvent);
    }

    void eventFromISR(const StateEvent<T, C> &stateEvent)
    {
        dispatchEventFromISR(stateEvent);
    }

    void eventFromISR(const T &eventId)
    {
        auto stateEvent = StateEvent<T, C>(static_cast<T>(eventId), nullptr);
        dispatchEventFromISR(stateEvent);
    }

protected:
    virtual void dispatchEvent(const StateEvent<T, C> &event) = 0;
    virtual void dispatchEventFromISR(const StateEvent<T, C> &event) = 0;

    void processEvent(StateEvent<T, C> *event)
    {
        if (_currentState != NULL)
        {
            auto result = _currentState->process(event);
            if (result.size() < 0)
            {
                return;
            }

#if __cpp_structured_bindings >= 201606
            // C++17

            if (auto foundState = _stateMap->find(result); foundState != _stateMap->end())
#else
            // C++14 and below
            auto foundState = _stateMap->find(result);
            if (foundState != _stateMap->end())
#endif
            {
                _currentState->exit();
                _currentState = foundState->second;
                _currentState->enter();
            }
        }
    }

protected:
    using StateMap = std::map<std::string, StateClass<T, C> *>;
    using StatePair = std::pair<std::string, StateClass<T, C> *>;

    StateMap *_stateMap;
    StateClass<T, C> *_currentState = nullptr;
};

#endif // STATE_MACHINE_H