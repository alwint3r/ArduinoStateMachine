#include "DefaultMachine.h"

DefaultMachine::DefaultMachine() : StateMachine()
{
    _events = new std::vector<StateEvent>();
}

DefaultMachine::~DefaultMachine()
{
    delete _events;
    _events = NULL;
}

void DefaultMachine::event(const StateEvent& event)
{
    _events->push_back(event);
}

void DefaultMachine::eventFromISR(const StateEvent& event)
{
    _events->push_back(event);
}

void DefaultMachine::run()
{
    if (_events->size() > 0)
    {
        StateEvent event = _events->at(0);

        processEvent(&event);

        _events->erase(_events->begin());
    }
}