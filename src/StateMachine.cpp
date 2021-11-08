#include "StateMachine.h"
#include <Arduino.h>

StateMachine::StateMachine()
{
    _stateMap = new StateMap();
    _currentState = NULL;
}

StateMachine::~StateMachine()
{
    delete _stateMap;
    _stateMap = NULL;
}

void StateMachine::addState(StateClass *state)
{
    _stateMap->insert(std::pair<std::string, StateClass *>(state->getName(), state));
}

void StateMachine::removeState(StateClass *state)
{
    _stateMap->erase(state->getName());
}

void StateMachine::eventById(uint32_t eventId)
{
    event({eventId, 0});
}

void StateMachine::eventById(int eventId)
{
    event({(uint32_t)eventId, 0});
}

void StateMachine::eventByIdFromISR(uint32_t eventId)
{
    eventFromISR({eventId, 0});
}

void StateMachine::eventByIdFromISR(int eventId)
{
    eventFromISR({(uint32_t)eventId, 0});
}

void StateMachine::processEvent(StateEvent *event)
{
    if (_currentState != NULL)
    {
        auto result = _currentState->process(event);
        if (result.change == StateChange::STATE_CHANGE_NONE)
        {
            return;
        }

        if (result.change == StateChange::STATE_CHANGE_CHANGED)
        {

            auto findState = _stateMap->find(result.nextStateName);
            if (findState != _stateMap->end())
            {
                auto nextState = findState->second;
                _currentState->exit();
                _currentState = nextState;
                _currentState->enter();
            }
        }
    }
}
