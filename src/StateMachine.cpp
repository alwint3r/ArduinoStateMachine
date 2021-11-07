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

void StateMachine::event(const uint32_t eventId)
{
    event({eventId, 0});
}

void StateMachine::eventFromISR(const uint32_t eventId)
{
    eventFromISR({eventId, 0});
}

void StateMachine::processEvent(StateEvent *event)
{
    if (_currentState != NULL)
    {
        auto result = _currentState->process(event);
        if (result.change == StateChange::STATE_CHANGE_NONE)
        {
            Serial.println("No state change");
            return;
        }
        
        if (result.change == StateChange::STATE_CHANGE_CHANGED)
        {
            Serial.printf("Received state change: %s\n", result.nextStateName.c_str());

            auto findState = _stateMap->find(result.nextStateName);
            if (findState != _stateMap->end())
            {
                auto nextState = findState->second;
                _currentState->exit();
                _currentState = nextState;
                _currentState->enter();
            }
            else
            {
                Serial.printf("State %s not found\n", result.nextStateName.c_str());
            }
        }
    }
}
