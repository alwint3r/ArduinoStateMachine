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
    _stateMap->insert(StatePair(state->getName(), state));
}

void StateMachine::removeState(StateClass *state)
{
    _stateMap->erase(state->getName());
}

void StateMachine::processEvent(StateEvent *event)
{
    if (_currentState != NULL)
    {
        auto result = _currentState->process(event);
        if (result.size() < 0)
        {
            return;
        }

        if (auto foundState = _stateMap->find(result); foundState != _stateMap->end())
        {
            _currentState->exit();
            _currentState = foundState->second;
            _currentState->enter();
        }
    }
}
